/*
 * O( n ) where n = |text|
 * Returns a vector with size equal to 2*|text|. For each i in such vector, p[ i ] is equal to the maximum palindrome centered at this position. 
 */
vi manacher( string t ) {
  int len = SIZE( t );
  vi p( 2*len );
  int C = -1, R = -1;
  int n = (len-1)<<1;
  for( int i = 0; i <= n; i++ ) {
    int j = 2*C-i;
    p[ i ] = ( R >= i ) ? min( R-i+1, p[ j ] ) : !( i%2 );
    int l = (i-p[ i ])>>1;
    int r = (i+p[ i ]+1)>>1;
    while( l >= 0 && r < len && t[ l ] == t[ r ] ) {
      p[ i ] += 2;
      l--; r++;
    }
    int ri = p[ i ] ? ((i+p[ i ])>>1)<<1 : i;
    if( ri > R ) C = i, R = ri;
  }
  return p;
}