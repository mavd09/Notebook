/*
 * O( v*e ) where v = # nodes, e = # edges
 */
int n, m;
vi graph[ MAXN ];
int match[ MAXM ];
bool seen[ MAXM ];
bool dfs( int u ) {
  for( int i = 0; i < SIZE( graph[u] ); ++i ){
    int v = graph[ u ][ i ];
    if( seen[ v ] ) continue;
    seen[ v ] = true;
    if( match[ v ] == -1 || dfs( match[v] ) ) {
      match[ v ] = u;
      return true;
    }
  }
  return false;
}
int mbm( ) {
  int r = 0;
  memset( match, -1, sizeof(match) );
  for( int u = 0; u < n; ++u ) {
    memset( seen, false, sizeof(seen) );
    r += dfs( u );
  }
  return r;
}