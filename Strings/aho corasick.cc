/*
 * O( |t|+SUM( |p_i| )+matches ) where t is a text and p_i are the patterns
 */
const int alphabet = 26;
int fail[ MAX_N ];
int mv( int node, int c ){
  while( !trie[ node ][ c ] ) node = fail[ node ];
  return trie[ node ][ c ];
}
void build_aho_corasick( ) {
  memset( fail, 0, sizeof( fail ) );
  queue< int > q;
  for( int i = 0; i < alphabet; i++ ) {
    if( trie[1][i] ) {
      q.push( trie[1][i] );
      fail[ trie[1][i] ] = 1;
    }
    else trie[1][i] = 1;
  }
  while( !q.empty( ) ) {
    int node = q.front( ); q.pop( );
    for( int i = 0; i < alphabet; i++ ){
      if( trie[node][i] ) {
        fail[ trie[node][i] ] = mv( fail[ node ], i );
        q.push( trie[node][i] );
      }
    }
  }
}