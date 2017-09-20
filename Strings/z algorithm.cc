/*
 * O( n ) where n = |text|
 * For each i, z[ i ] is equal to the longest substring starting at i that is prefix of the text.
 */

vi z_algorithm( string str ) {
  int len = SIZE( str );
  vi z( len );
  z[ 0 ] = 0;
  for( int i = 1, l = 0, r = 0; i < len; ++i ) {
    if( i <= r ) z[ i ] = min( r-i+1, z[ i-l ] );
    while( i+z[ i ] < len && str[ z[i] ] == str[ i+z[i] ] ) z[ i ]++;
    if( i+z[ i ]-1 > r ) {
      l = i;
      r = i+z[ i ]-1;
    }
  }
  return z;
}