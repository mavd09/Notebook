bool cmp_pt_d( const pt &a, const pt &b, int d ) {
  for( int i = 0; i < DIM; ++i )
    if( a.v[i] != b.v[ (d+i)%DIM ] )
      return a.v[i] < b.v[ (d+i)%DIM ];
  return true;
}
bool cmp_pt( const pt &a, const pt &b ) { return cmp_pt_d( a,b,0 ); }
struct Node {
  int dim;
  pt p;
  Node *l, *r;
  Node( int dim, pt &p, Node *l, Node *r ) : dim( dim ), p( p ), l( l ), r( r ) {}
};
typedef Node *      pnode;
void k_sort( int f, int mi, int t ) {
  for( int i = f; i <= t; ++i ) extra[ i ] = P[ 0 ][ i ];
  for( int i = 1; i < DIM; ++i ) {
    for( int j = f, ii = f, jj = mi+1; j <= t; ++j ) {
      if( extra[ mi ].idx == P[i][j].idx ) continue;
      if( !cmp_pt_d( extra[ mi ], P[i][j], DIM-i ) )
        P[ i-1 ][ ii++ ] = P[ i ][ j ];
      else P[ i-1 ][ jj++ ] = P[ i ][ j ];
    }
  }
  for( int i = f; i <= t; ++i ) P[ DIM-1 ][ i ] = extra[ i ];
}
void create_kd_tree( pnode &root, int f, int t, int d ) {
  if( t == f ) {
    root = new Node( d, points[P[0][f].idx], NULL, NULL );
    return;
  }
  int nd = (d+1)%DIM;
  if( t-f == 1 ) {
    if( cmp_pt( P[0][f], P[0][t] ) ) {
      create_kd_tree( root, t, t, d );
      create_kd_tree( root->l, f, f, nd );
    } else {
      create_kd_tree( root, f, f, d );
      create_kd_tree( root->l, t, t, nd );
    }
    return;
  }
  int mi = (t+f+1)/2;
  k_sort( f, mi, t );
  root = new Node( d, points[ P[0][mi].idx ], NULL, NULL );
  create_kd_tree( root->l, f, mi-1, nd );
  create_kd_tree( root->r, mi+1, t, nd );
}
void kd_insert( pnode &root, pt &point, int d ) {
  if( root == NULL )
    root = new Node( d, point, NULL, NULL );
  else if( root->p.v[d] <= point.v[d] )
    kd_insert( root->r, point, (d+1)%DIM );
  else kd_insert( root->l, point, (d+1)%DIM );
}
pt min_pt( pt p, pt q, int d ) {
  if( p.v[d] < q.v[d] ) return p;
  if( p.v[d] > q.v[d] ) return q;
  if( samePt(p,q) ) return p;
  return min_pt( p, q, (d+1)%DIM );
}
pt find_min( pnode root, int d ) {
  if( root == NULL ) return pt(oo,oo);
  if( root->dim == d ) {
    if( root->l == NULL ) return root->p;
    return find_min( root->l, d );
  }
  pt p = find_min( root->l, d );
  pt q = find_min( root->r, d );
  return min_pt( min_pt(p,q,d), root->p, d );
}
void kd_delete( pnode &root, pt point ) {
  if( root == NULL ) return;
  if( samePt(root->p, point) ) {
    if( root->r == NULL && root->l == NULL ) {
      root = NULL;
    } else {
      if( root->r == NULL ) swap( root->l, root->r );
      root->p = find_min( root->r, root->dim );
      kd_delete( root->r, root->p );
    }
    return;
  }
  if( root->p.v[ root->dim ] <= point.v[ root->dim ] )
    kd_delete( root->r, point );
  else
    kd_delete( root->l, point );
}
void nearest_neighbor( pt &point, pnode &root, pt &r, lf &d ) {
  if( !root ) return;
  lf curd = dist( point, root->p );
  if( curd && d > curd ) {
    d = curd;
    r = root->p;
  }
  lf delta = abs( point.v[ root->dim ] - root->p.v[ root->dim ] );
  delta *= delta;
  if( point.v[ root->dim ] <= root->p.v[ root->dim ] ) {
    nearest_neighbor( point, root->l, r, d );
    if( d >= delta ) nearest_neighbor( point, root->r, r, d );
  } else {
    nearest_neighbor( point, root->r, r, d );
    if( d >= delta ) nearest_neighbor( point, root->l, r, d );
  }
}