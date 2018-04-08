/*
 * O( n ) where n = |text|
 * Find the lexicographically minimal string rotation.
 */
int minimum_expression( string t ) {
  t = t+t;
  int len = SIZE( t );
  int i = 0, j = 1, k = 0;
  while( i+k < len && j+k < len ) {
    if( t[ i+k ] == t[ j+k ] ) k++;
    else if( t[ i+k ] > t[ j+k ] ) {
      i = i+k+1;
      if( i <= j ) i = j+1;
      k = 0;
    } else {
      j = j+k+1;
      if( j <= i ) j = i+1;
      k = 0;
    }
  }
  return min( i, j );
}