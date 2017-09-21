namespace BlockCutTree {

  int t, rootCh, typeCnt;
  int low[ MAX ], dfn[ MAX ], type[ MAX ];
  vi graph[ MAX ];
  bool cut[ MAX ];
  map< pii, int > bridges;
  stack< int > s;

  void init( ) {
    t = rootCh = typeCnt = 0;
    bridges.clear( );
    for( int i = 0; i < MAX; i++ ) {
      dfn[ i ] = 0;
      cut[ i ] = false;
      graph[ i ].clear( );
    }
  }

  void add_edge( int u, int v ) {
    graph[ u ].push_back( v );
  }
  
  void tarjan( int u, int fu ) {
    low[ u ] = dfn[ u ] = ++t;
    for( auto& v : graph[ u ] ) {
      if( v == fu ) continue;
      if( !dfn[ v ] ){
        if( u == 1 ) rootCh++;
        s.push( v );
        tarjan( v, u );
        low[ u ] = min( low[ u ], low[ v ] );
        if( low[ v ] >= dfn[ u ] ) {
          int w;
          typeCnt++;
          do {
            w = s.top( ); s.pop( );
            if( cut[ w ] )
              LowestCommonAncestor::add_edge( typeCnt, type[ w ] );
            else type[ w ] = typeCnt;
          } while( w != v );
          if( low[ v ] > dfn[ u ] ) 
            bridges[ make_pair( min( u, v ), max( u, v ) ) ] = typeCnt;
          if( !cut[ u ] ) {
            cut[ u ] = true;
            type[ u ] = ++typeCnt;
            LowestCommonAncestor::add_edge( typeCnt, typeCnt-1 );
          }
          else
            LowestCommonAncestor::add_edge( type[ u ], typeCnt );
        }
      }
      else low[ u ] = min( low[ u ], dfn[ v ] );
    }
  }
  
  void create_block_cut_tree( ) {
    LowestCommonAncestor::init( );
    tarjan( 1, 1 );
    if( rootCh == 1 ){
      cut[ 1 ] = false;
      type[ 1 ] = --typeCnt;
    }
    LowestCommonAncestor::dfs( type[ 1 ], type[ 1 ] );
    LowestCommonAncestor::build_sparse_table( );
  }

}