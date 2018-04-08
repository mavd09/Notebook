struct Line {
  ll m, b;
  Line( ) { }
  Line( ll m, ll b ) : m(m), b(b) { }
  ll solve( ll x ) { return m*x + b; }
};
int sz;
Line hull[ MAXN ];
lf inters[ MAXN ];
lf find_intersection( const Line& l1, const Line& l2 ) {
  return lf( l1.b-l2.b )/lf( l2.m-l1.m );
}
void add_line( ll m, ll b ) {
  hull[ sz ] = Line( m, b );
  if( sz == 0 ) {
    inters[ sz ] = oo;
  } else {
    inters[ sz ] = find_intersection( hull[ sz ], hull[ sz-1 ] );
  }
  while( sz >= 2 && inters[ sz ] > inters[ sz-1 ] ) {
    hull[ sz-1 ] = hull[ sz ];
    inters[ sz-1 ] = find_intersection( hull[ sz-2 ], hull[ sz-1 ] );
    sz--;
  }
  sz++;
}
ll get_min( ll x ) {
  int lo = 0, hi = sz-1, mi;
  while( lo <= hi ) {
    mi = ( lo+hi )>>1;
    if( inters[ mi ] > x ) lo = mi+1;
    else hi = mi-1;
  }
  return hull[ hi ].solve( x );
}
