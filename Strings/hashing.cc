/*
 * gen_mod( ) generates two random primes ~10^9
 * fill_hash( acc, t ) acc[ i ] ( 1 <= i <= |t| ) stores the hash of t[0, i-1].
 * get_hash( acc, l, r ) return the hash [ l, r ] using the acc array.
 */

void gen_mod( ) {
  srand( time( nullptr ) );
  for( int i = 0; i < 2; ++i ) {
    int mod = int(1e9) + rand()%int(5e6);
    while( !is_prime( mod ) ) {
      mod++;
    }
    cout << mod << '\n';
  }
}

typedef pair< int, int > mint;
const int MOD[ ] = { 1001864327, 1001265673 };
const mint BASE( 256, 256 ), ZERO( 0, 0 ), ONE( 1, 1 );
inline int add( int a, int b, const int& mod ) { return ( a+b >= mod ) ? a+b-mod : a+b; }
inline int sbt( int a, int b, const int& mod ) { return ( a-b < 0 ? a-b+mod : a-b ); }
inline int mul( int a, int b, const int& mod ) { return ll(a)*ll(b) % ll(mod); }

inline ll operator ! ( const mint a ) { return (ll(a.FI)<<32)|ll(a.SE); }
inline mint operator + ( const mint a, const mint b ) {
  return mint( add( a.FI, b.FI, MOD[0] ), add( a.SE, b.SE, MOD[1] ) );
}
inline mint operator - ( const mint a, const mint b ) {
  return mint( sbt( a.FI, b.FI, MOD[0] ), sbt( a.SE, b.SE, MOD[1] ) );
}
inline mint operator * ( const mint a, const mint b ) {
  return mint( mul( a.FI, b.FI, MOD[0] ), mul( a.SE, b.SE, MOD[1] ) );
}

void fill_hash( mint* acc, const string& t ) {
  acc[ 0 ] = ZERO;
  for( int i = 1; i <= n; ++i ) {
    acc[ i ] = acc[ i-1 ]*BASE + val[ t[i-1] ];
  }
}
mint get_hash( mint* acc, int l, int r ) {
  return acc[ r+1 ] - acc[ l ]*base[ r-l+1 ];
}