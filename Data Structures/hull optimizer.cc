/*
 * O( n ) where n = number of lines added
 * Given a set of lines of the form y = mx + b, find the minimum y-value when any of the given lines are evaluated at the specified x.
 * To optimize for maximum y-value, call the constructor with query_max = true.
 * Reference: https://github.com/alxli
 */

class hull_optimizer {
  struct line {
    ll m, b, val;
    lf xlo;
    bool is_query, query_max;
    line( ll m, ll b, ll val, bool is_query, bool query_max )
        : m(m), b(b), val(val), xlo(-oo),
          is_query(is_query), query_max(query_max) { }
    bool parallel( const line& l )const {
      return m == l.m;
    }
    lf intersect( const line &l )const {
      if( parallel( l ) ) {
        return oo;
      }
      return (lf)( l.b-b )/( m-l.m );
    }
    bool operator < ( const line &l )const {
      if( l.is_query ) {
        return query_max ? ( xlo < l.val ) : ( l.val < xlo );
      }
      return m < l.m;
    }
  };

  set< line > hull;
  bool query_max;
  typedef set<line>::iterator hulliter;

  bool has_prev( hulliter it )const {
    return it != hull.begin( );
  }
  bool has_next( hulliter it )const {
    return ( it != hull.end( ) ) && ( ++it != hull.end( ) );
  }
  bool irrelevant( hulliter it )const {
    if( !has_prev( it ) || !has_next( it ) ) {
      return false;
    }
    hulliter prev = it, next = it;
    --prev;
    ++next;
    return query_max ? (prev->intersect(*next) <= prev->intersect(*it))
                     : (next->intersect(*prev) <= next->intersect(*it));
  }
  hulliter update_left_border( hulliter it ) {
    if( (query_max && !has_prev(it)) || (!query_max && !has_next(it)) ) {
      return it;
    }
    hulliter it2 = it;
    lf val = it->intersect(query_max ? *--it2 : *++it2);
    line l(*it);
    l.xlo = val;
    hull.erase(it++);
    return hull.insert( it, l );
  }

 public:
  hull_optimizer( bool query_max = false ) {
    this->query_max = query_max;
  }
  void add_line( ll m, ll b ) {
    line l( m, b, 0, false, query_max );
    hulliter it = hull.lower_bound( l );
    if( it != hull.end( ) && it->parallel( l ) ) {
      if( ( query_max && it->b < b ) || ( !query_max && b < it->b ) ) {
        hull.erase( it++ );
      } else {
        return ;
      }
    }
    it = hull.insert( it, l );
    if( irrelevant( it ) ) {
      hull.erase(it);
      return;
    }
    while( has_prev( it ) && irrelevant( --it ) ) {
      hull.erase( it++ );
    }
    while( has_next( it ) && irrelevant( ++it ) ) {
      hull.erase( it-- );
    }
    it = update_left_border( it );
    if( has_prev( it ) ) {
      update_left_border( --it );
    }
    if( has_next( ++it ) ) {
      update_left_border( ++it );
    }
  }
  ll get_best( ll x )const {
    line q( 0, 0, x, true, query_max );
    hulliter it = hull.lower_bound( q );
    if( query_max ) {
      --it;
    }
    return it->m*x + it->b;
  }
};