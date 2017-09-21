struct Data_Node {
  int prnt, dpth, value, id, sz, chain;
  Data_Node( ) : 
    prnt( 0 ), dpth( 0 ), value( 0 ), 
    id( 0 ), sz( 1 ), chain( 0 ) { }
};
struct Heavy_Light_Decomposition {
  int n, node_counted, cur_chain;
  vvi G, A;
  vector< Data_Node > data_node;
  vi chain_head;
  Segment_Tree st;
  Heavy_Light_Decomposition( int n, vi& value ) : 
    n( n ), G( n ), A( n, vi( LOG2 ) ), 
    data_node( n, Data_Node( ) ), chain_head( n, -1 ), st( 0, n-1 ) {
    node_counted = cur_chain = 0;
    for( int i = 0; i < n; i++ )
      data_node[ i ].value = value[ i ];
  }
  void add_edge( int u, int v ) {
    G[ u ].PB( v );
    G[ v ].PB( u );
  }
  void set_value( int u, int v ) {
    data_node[ u ].value = v;
    st.update( data_node[ u ].id, data_node[ u ].value );
  }
  void dfs( int u, int d ) {
    data_node[ u ].dpth = d;
    for( int i = 0; i < int( G[ u ].size( ) ); i++ ) {
      int v = G[ u ][ i ];
      if( v == data_node[ u ].prnt )
        continue;
      data_node[ v ].prnt = A[ v ][ 0 ] = u;
      dfs( v, d+1 );
      data_node[ u ].sz += data_node[ v ].sz;
    }
  }
  void build_hld( int u ) {
    if( chain_head[ cur_chain ] == -1 )
      chain_head[ cur_chain ] = u;
    data_node[ u ].chain = cur_chain;
    data_node[ u ].id = node_counted++;
    st.update( data_node[ u ].id, data_node[ u ].value );
    int best_child = -1;
    for( auto& v : G[ u ] ) {
      if( v == data_node[ u ].prnt )
        continue;
      if( best_child == -1 || ( data_node[ best_child ].sz < data_node[ v ].sz ) )
        best_child = v;
    }
    if( best_child != -1 )
      build_hld( best_child );
    for( auto& v : G[ u ] ) {
      if( v == data_node[ u ].prnt || v == best_child )
        continue;
      cur_chain++;
      build_hld( v );
    }
  }
  void build( ) {
    dfs( 0, 0 );
    build_lca( );
    build_hld( 0 );
  }
  int query_hld_util( int u, int a ) {
    int r = data_node[ u ].value;
    int chain_u, chain_a = data_node[ a ].chain;
    while( true ) {
      chain_u = data_node[ u ].chain;
      if( chain_u == chain_a ) {
        if( u != a )
          r = __gcd( r, st.query( data_node[ u ].id, data_node[ a ].id ) );
        else
          r = __gcd( r, data_node[ u ].value );
        break;
      }
      else {
        r = __gcd( r, st.query( data_node[ chain_head[ chain_u ] ].id, data_node[ u ].id ) );
        u = data_node[ chain_head[ chain_u ] ].prnt;
      }
    }
    return r;
  }
  int query_hld( int u, int v ) {
    int lca = query_lca( u, v );
    return __gcd( query_hld_util( u, lca ), query_hld_util( v, lca ) );
  }
};