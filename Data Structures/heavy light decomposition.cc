/*
 * idx must be equal to 0
 * hld_child and hld_root must be initialized with -1
 * define a new data type called 'data' and overload + operator
 */

int idx;
int sz[ MAXN ], hld_child[ MAXN ], hld_index[ MAXN ], hld_root[ MAXN ];

void dfs( int u, int p = 0 ) {
  sz[u] = 1;
  jump[0][u] = p;
  for( auto& v : graph[u] ) {
    if( v == p ) continue;
    depth[v] = depth[u]+1;
    dfs(v, u);
    sz[u] += sz[v];
    if( hld_child[u] == -1 || sz[hld_child[u]] < sz[v] ) {
      hld_child[u] = v;
    }
  }
}

void build_hld( int u, int p = 0 ) {
  hld_index[u] = idx++;
  narr[hld_index[u]] = arr[u];
  if( hld_root[u] == -1 ) {
    hld_root[u] = u;
  }
  if( hld_child[u] != -1 ) {
    hld_root[hld_child[u]] = hld_root[u];
    build_hld(hld_child[u], u);
  }
  for( auto& v : graph[u] ) {
    if( v == p || v == hld_child[u] ) continue;
    build_hld(v, u);
  }
}

void update_hld( int u, int val ) {
  update_tree(hld_index[u], val);
}

data query_hld( int u, int v ) {
  data val = NULL_DATA;
  while( hld_root[u] != hld_root[v] ) {
    if( depth[hld_root[u]] < depth[hld_root[v]] ) swap(u, v);
    val = val+query_tree(hld_index[hld_root[u]], hld_index[u]);
    u = jump[0][hld_root[u]];
  }
  if( depth[u] > depth[v] ) swap(u, v);
  val = val+query_tree(hld_index[u], hld_index[v]);
  return val;
}

void build() {
  dfs(0);
  build_hld(0);
  build_tree();
}