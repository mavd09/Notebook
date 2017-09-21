/*
 * Modular Arithmetic 
 */
int mod_of( int n, int mod ) {
  return ( ( n%mod )+mod )%mod;
}

/// returns d = gcd( a, b ); finds x, y such that d = a*x + b*y
int extended_euclid( int a, int b, int &x, int &y ) {
  int xx = 0; y = 0;
  int yy = 1; x = 1;
  while( b ) {
    int q = a/b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}

int mod_inverse( int a, int n ) {
  int x, y;
  int d = extended_euclid( a, n, x, y );
  if( d > 1 ) {
    return -1;
  }
  return x%n;
}

/// computes x and y such that ax + by = c
bool linear_diophantine( int a, int b, int c, int &x, int &y ) {
  int d = __gcd( a, b );
  if( c%d ) {
    return false;
  }
  x = c/d*mod_inverse( a/d, b/d );
  y = ( c-a*x )/b;
  return true;
}

/// finds all solutions to a*x = b ( mod n )
vi modular_linear_equation_solver( int a, int b, int n ) {
  a = mod_of( a, n );
  b = mod_of( b, n );
  vi ret;
  int x, y;
  int d = extended_euclid( a, n, x, y );
  if( b%d == 0 ) {
    x = mod_of( x*( b/d ), n );
    for( int i = 0; i < d; i++ ) {
      ret.PB( mod_of( x+i*( n/d ), n ) );
    }
  }
  return ret;
}

/// Chinese remainder theorem (special case): find z such that
/// z % x = a, z % y = b. Here, z is unique modulo M = lcm(x,y).
/// Return (z,M). On failure, M = -1.
pii chinese_remainder_theorem( int x, int a, int y, int b ) {
  int s, t;
  int d = extended_euclid( x, y, s, t );
  if( a%d != b%d ) {
    return MP( 0, -1 );
  }
  return MP( mod_of( s*b*x+t*a*y, x*y )/d, x*y/d );
}

/// Chinese remainder theorem: find z such that
/// z % x[i] = a[i] for all i. Note that the solution is
/// unique modulo M = lcm_i (x[i]). Return (z,M). On
/// failure, M = -1. Note that we do not require the a[i]'s
/// to be relatively prime.
pii chinese_remainder_theorem( const vi& x, const vi& a ) {
  pii ret = MP( a[ 0 ], x[ 0 ] );
  for (int i = 1; i < int( x.size( ) ); i++ ) {
    ret = chinese_remainder_theorem( ret.SE, ret.FI, x[ i ], a[ i ] );
    if( ret.SE == -1 ) {
      break;
    }
  }
  return ret;
}