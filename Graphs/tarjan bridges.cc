void dfs( int u, int p = -1 ) {
  dfn[ u ] = low[ u ] = ++t;
  int children = 0;
  for( int i = 0; i < SIZE( graph[u] ); ++i ) {
    int v = graph[ u ][ i ];
    if( !dfn[ v ] == -1 ) {
      children++;
      dfs( v, u );
      low[ u ] = min( low[u], low[v] );
      ///Bridges
      if( low[v] > dfn[u] ) {
        cout << u << " " << v << endl;
      }
      ///Articulation points
      if( p == -1 && children > 1 ) {
        ap[ u ] = true;
      }
      if( p != -1 && low[v] >= dfn[u] ) {
        ap[ u ] = true;
      }
    }
    else if( v != p ) {
      low[ u ] = min( low[u], dfn[v] );
    }
  }
}