/*
 * O( n ) where n = |text|
 * For each i, phi[ i ] is equal to the longest prefix that also is a suffix ending at i.
 */

vi kmp( string t ) {
  int len = SIZE( t );
  vi phi( len );
  phi[ 0 ] = 0;
  for( int i = 1, j = 0; i < len; ++i ) {
    while( j > 0 && t[ i ] != t[ j ] ) {
      j = phi[ j-1 ];
    }
    if( t[ i ] == t[ j ] ) {
      ++j;
    }
    phi[ i ] = j;
  }
  return phi;
}