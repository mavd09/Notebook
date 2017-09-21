/*
 * Equivalences
 * (s1^a2)v(a1^s2) = (s1vs2)^(a1va2)^(s1va1)^(s2va2)
 */
struct SAT {
  int n;
  vector< vector< vi > > graph;
  vi tag;
  vb seen, value;
  stack< int > st;
  SAT( int n ) : n( n ), graph( 2, vector< vi >( 2*n ) ), tag( 2*n ), seen( 2*n ), value( 2*n ) { }
  int neg( int x ) {
    return 2*n-x-1;
  }
  ///We give u v v and it makes ¬u -> v and ¬v -> u
  void make_implication( int u, int v ) {
    implication( neg(u), v );
    implication( neg(v), u );
  }
  void make_true( int u ) {
    add_edge( neg(u), u );
  }
  void make_false( int u ) {
    make_true( neg(u) );
  }
  void eq( int u, int v ) {
    implication( u, v );
    implication( v, u );
  }
  void diff( int u, int v ) {
    eq( u, neg(v) );
  }
  void implication( int u, int v ) {
    add_edge( u, v );
    add_edge( neg(v), neg(u) );
  }
  void add_edge( int u, int v ) {
    graph[ 0 ][ u ].push_back( v );
    graph[ 1 ][ v ].push_back( u );
  }
  void dfs( int id, int u, int t = 0 ) {
    seen[ u ] = true;
    for( auto& v : graph[ id ][ u ] )
      if( !seen[ v ] )
        dfs( id, v, t );
    if( id == 0 )
      st.push( u );
    else
      tag[ u ] = t;
  }
  void kosaraju( ) {
    for( int u = 0; u < n; u++ ) {
      if( !seen[ u ] )
        dfs( 0, u );
      if( !seen[ neg(u) ] )
        dfs( 0, neg(u) );
    }
    fill( seen.begin( ), seen.end( ), false );
    int t = 0;
    while( !st.empty( ) ) {
      int u = st.top( ); st.pop( );
      if( !seen[ u ] )
        dfs( 1, u, t++ );
    }
  }
  bool satisfiable( ) {
    kosaraju();
    for( int i = 0; i < n; i++ ) {
      if( tag[ i ] == tag[ neg(i) ] ) return false;
      value[ i ] = tag[ i ] > tag[ neg(i) ];
    }
    return true;
  }
};