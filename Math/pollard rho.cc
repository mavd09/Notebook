ll pollard_rho( ll n ) {
  ll x, y, i = 1, k = 2, d;
  x = y = rand( )%n;
  while( true ) {
    i++;
    x = mod_mul( x, x, n );
    x += 2;
    if( x >= n ) x -= n;
    if( x == y ) return 1;
    d = __gcd( abs( x-y ), n );
    if( d != 1 ) return d;
    if( i == k ) y = x, k *= 2LL;
  }
  return 1;
}
vll factorize( ll n ) {
  vll ans;
  if( n == 1 ) return ans;
  if( miller_rabin( n ) ) ans.PB( n );
  else {
    ll d = 1;
    while( d == 1 ) d = pollard_rho( n );
    vll dd = factorize( d );
    ans = factorize( n/d );
    for( int i = 0; i < dd.size( ); i++ )
      ans.PB( dd[ i ] );
  }
  return ans;
}