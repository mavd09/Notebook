vi count_divisors_sieve( ) {
  const int mx = int( 1e7 )+1;
  bitset< mx > is_prime; is_prime.set( );
  vi cnt( mx, 1 );
  is_prime[ 0 ] = is_prime[ 1 ] = 0;
  for( int i = 2; i < mx; i++ ) {
    if( is_prime[ i ] ) {
      cnt[ i ]++;
      for( int j = i+i; j < mx; j += i ) {
        int n = j, c = 1;
        while( n%i == 0 ) {
          n /= i;
          c++;
        }
        cnt[ j ] = cnt[ j ]*c;
        is_prime[ j ] = 0;
      }
    }
  }
  return cnt;
}
vi euler_phi_sieve( ) {
  const int mx = int( 1e7 )+1;
  bitset< mx > is_prime; is_prime.set( );
  vi phi( mx );
  for( int i = 1; i < mx; i++ )
    phi[ i ] = i;
  is_prime[ 0 ] = is_prime[ 1 ] = 0;
  for( int i = 2; i < mx; i++ ) {
    if( is_prime[ i ] ) {
      for( int j = i; j < mx; j += i ) {
        phi[ j ] = phi[ j ]-( phi[ j ]/i ); 
        is_prime[ j ] = 0;
      }
    }
  }
  return phi;
}
ll count_divisors( vll& prime, ll n ) {
  int total_primes = int( prime.size( ) );
  ll r = 1;
  for( int i = 0; prime[ i ]*prime[ i ] <= n && i < total_primes; i++ ) {
    ll p = 1;
    while( n%prime[ i ] == 0 ) {
      n /= prime[ i ];
      p++;
    }
    r = r*p;
  }
  if( n != 1 )
    r = r*2LL;
  return r;
}
ll highest_exponent( ll n, ll p ) {
  ll r = 0, t = p;
  while( t <= n ) {
    r = r+( n/t );
    t = t*p;
  }
  return r;
} 
ll count_divisors_factorial( vll& prime, ll n ) {
  int total_primes = int( prime.size( ) );
  ll r = 0;
  for( int i = 0; prime[ i ] <= n && i < total_primes; i++ )
    r = r*( highest_exponent( n, prime[ i ] )+1 );
  return r;
}
ll sum_divisors( vll& prime, ll n ) {
  int total_primes = int( prime.size( ) );
  ll r = 1;
  for( int i = 0; prime[ i ]*prime[ i ] <= n && i < total_primes; i++ ) {
    ll p = 1;
    while( n%prime[ i ] == 0 ) {
      n /= prime[ i ];
      p++;
    }
    r = r*( ( bin_pow( prime[ i ], p )-1 )/( prime[ i ]-1 ) );
  }
  if( n != 1 ) r = r*( ( bin_pow( n, 2 )-1 )/( n-1 ) );
  return r;
}
ll euler_phi( vll& prime, ll n ) {
  int total_primes = int( prime.size( ) );
  ll r = n;
  for( int i = 0; prime[ i ]*prime[ i ] <= n && i < total_primes; i++ ) {
    if( n%prime[ i ] == 0 ) r = r-( r/prime[ i ] );
    while( n%prime[ i ] == 0 ) n /= prime[ i ];
  }
  if( n != 1 ) r = r-( r/n );
  return r;
}