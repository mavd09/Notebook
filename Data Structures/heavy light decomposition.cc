struct Edge { int v, c, idx; };

int n;
vector< Edge > graph[ MAXN ];
int base_array[ MAXN ], ptr;
int n_chain, chain_ind[ MAXN ], chain_head[ MAXN ], pos_base[ MAXN ];
int depth[ MAXN ], dp[ LOG2 ][ MAXN ], other_end[ MAXN ], subsize[ MAXN ];
int st[ MAXN*4 ];

void init( ) {
  n_chain = ptr = 0;
  for( int i = 0; i < n; ++i ) {
    graph[i].clear();
    chain_head[i] = -1;
    for( int j = 0; j < LOG2; ++j ) {
      dp[j][i] = -1;
    }
  }
}

void make_tree( int node, int s, int e );
void update_tree( int node, int s, int e, int x, int val );
int query_tree( int node, int s, int e, int l, int r );
void create_LCA( );
int LCA( int u, int v );

int query_up(int u, int v) {
  if( u == v ) return 0;
  int uchain, vchain = chain_ind[v], ans = -1;
  while( true ) {
    uchain = chain_ind[u];
    if( uchain == vchain ) {
      if( u != v ) {
        ans = max( ans, query_tree( 1, 0, n-1, pos_base[v]+1, pos_base[u] ) );
      }
      return ans;
    }
    ans = max( ans, query_tree( 1, 0, n-1, pos_base[ chain_head[uchain] ], pos_base[u] ) );
    u = chain_head[uchain];
    u = dp[0][u];
  }
  return -1;
}

int query( int u, int v ) {
  int lca = LCA( u, v );
  return max( query_up( u, lca ), query_up( v, lca ) );
}

void change( int i, int val ) {
  int u = other_end[i];
  update_tree( 1, 0, n-1, pos_base[u], val );
}

void HLD( int u, int p = -1, int c = -1 ) {
  if( chain_head[n_chain] == -1 ) {
    chain_head[n_chain] = u;
  }
  chain_ind[u] = n_chain;
  pos_base[u] = ptr;
  base_array[ptr++] = c;
  int child = -1, ncost;
  for( int i = 0; i < SIZE(graph[u]); ++i ) {
    Edge& e = graph[u][i];
    if( e.v == p ) continue;
    if( child == -1 || subsize[child] < subsize[e.v] ) {
      child = e.v;
      ncost = e.c;
    }
  }
  if( child != -1 ) {
    HLD( child, u, ncost );
  }
  for( int i = 0; i < SIZE(graph[u]); ++i ) {
    Edge& e = graph[u][i];
    if( e.v == p || e.v == child ) continue;
    n_chain++;
    HLD( e.v, u, e.c );
  }
}

void dfs( int u, int p = -1 ) {
  dp[0][u] = p;
  depth[u] = ( p == -1 ? 0 : depth[p]+1 );
  subsize[u] = 1;
  for( int i = 0; i < SIZE(graph[u]); ++i ) {
    Edge& e = graph[u][i];
    if( e.v == p ) continue;
    other_end[ e.idx ] = e.v;
    dfs( e.v, u );
    subsize[u] += subsize[e.v];
  }
}

void create_HLD( ) {
  dfs( 0 );
  HLD( 0 );
  make_tree( 1, 0, n-1 );
  create_LCA( );
}