/*
 * O( n*alphabet ) where n = |text|
 * Returns a matrix such that a[ i ][ j ] is equal to the transition if I'm at i-th position and see the character j.
 */

const int alphabet = 256;
vector< vi > kmp_automaton( string t ) {
  int len = SIZE( t );
  vi phi = kmp( t );
  vector< vi > aut( len, vi( alphabet ) );
  for( int i = 0; i < len; ++i ) {
    for( int c = 0; c < alphabet; ++c ) {
      if( i > 0 && char(c) != t[ i ] ) {
        aut[ i ][ c ] = aut[ phi[i-1] ][ c ];
      } else {
        aut[ i ][ c ] = i + ( char(c) == t[ i ] );
      }
    }
  }
  return aut;
}