void dfs( int u ) {
  dfn[ u ] = low[ u ] = ++t;
  st.push( u );
  in_stack[ u ] = true;
  for( int i = 0; i < SIZE( graph[u] ); ++i ) {
    int v = graph[ u ][ i ];
    if( dfn[ v ] == -1 ) {
      dfs( v );
      low[ u ] = min( low[ u ], low[ v ] );
    } else if( in_stack[v] == true )
      low[ u ] = min( low[u], dfn[v] );
  }
  if( low[ u ] == dfn[ u ] ) {
    int w;
    while( st.top( ) != u ) {
      w = st.top( );
      in_stack[ w ] = false;
      st.pop( );
    }
    w = st.top( );
    in_stack[ w ] = false;
    st.pop( );
  }
}