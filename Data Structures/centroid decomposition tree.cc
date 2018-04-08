int pr[ MAXN ], sz[ MAXN ];
bool cent[ MAXN ];
void dfs_sz( int u, int p = -1 ) {
  sz[u] = 1;
  for( auto& v : graph[u] ) {
    if( v == p || cent[v] ) continue;
    dfs_sz( v, u );
    sz[u] += sz[v];
  }
}
int find_cent( int u ) {
  for( int t = sz[u]/2, p; ; ) {
    bool ok = true;
    for( auto& v : graph[u] ) {
      if( v == p || cent[v] ) continue;
      if( sz[v] > t ) {
        p = u; u = v;
        ok = false;
        break;
      }
    }
    if( ok ) return u;
  }
  return -1;
}
void decompose( int u, int p = -1 ) {
  dfs_sz( u );
  int c = find_cent( u );
  pr[c] = p;
  cent[c] = true;
  for( auto& v : graph[c] ) {
    if( cent[v] ) continue;
    decompose( v, c );
  }
}
