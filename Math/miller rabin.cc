bool check( ll a, ll n ) {
  ll u = n-1;
  int t = 0;
  while( u%2LL == 0 ) t++, u /= 2LL;
  ll nxt = mod_pow( a, u, n );
  if( nxt == 1 ) return false;
  ll lst;
  for( int i = 0; i < t; i++ ) {
    lst = nxt;
    nxt = mod_mul( lst, lst, n );
    if( nxt == 1 ) return ( lst != n-1 );
  }
  return ( nxt != 1 );
}
bool miller_rabin( ll n, int it = 20 ) {
  if( n <= 1 ) return false;
  if( n == 2 ) return true;
  if( n%2LL == 0 ) return false;
  for( int i = 0; i < it; i++ ) {
    ll a = rand( )%( n-1 ) + 1;
    if( check( a, n ) ) return false;
  }
  return true;
}