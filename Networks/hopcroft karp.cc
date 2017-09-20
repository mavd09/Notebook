/*
 * O( |e|*sqrt(|v|) )
 */
struct MBM {
  int n1, n2, edges;
  vi last, prev, head, matching, dist, q;
  vb used, seen;

  MBM( ) :
  last(MAXN1), prev(MAXM), head(MAXM), matching(MAXN2), 
  dist(MAXN1), q(MAXN1), used(MAXN1), seen(MAXN1) { }

  void init( int n1, int n2 ) {
    this->n1 = n1; this->n2 = n2;
    edges = 0;
    fill( last.begin(), last.begin()+n1, -1 );
  }
  void add_edge( int u, int v ) {
    head[ edges ] = v;
    prev[ edges ] = last[ u ];
    last[ u ] = edges++;
  }
  void bfs( ) {
    fill( dist.begin(), dist.begin()+n1, -1 );
    int size_q = 0;
    for( int u = 0; u < n1; u++ ) {
      if( !used[ u ] ) {
        q[ size_q++ ] = u;
        dist[ u ] = 0;
      }
    }
    for( int i = 0; i < size_q; i++ ) {
      int u1 = q[ i ];
      for( int e = last[u1]; e >= 0; e = prev[e] ) {
        int u2 = matching[ head[e] ];
        if( u2 >= 0 && dist[u2] < 0 ) {
          dist[ u2 ] = dist[u1]+1;
          q[ size_q++ ] = u2;
        }
      }
    }
  }
  bool dfs( int u1 ) {
    seen[ u1 ] = true;
    for( int e = last[u1]; e >= 0; e = prev[e] ) {
      int v = head[ e ];
      int u2 = matching[ v ];
      if( u2 < 0 || ( !seen[u2] && dist[u2] == dist[u1]+1 && dfs(u2) ) ) {
        matching[ v ] = u1;
        used[ u1 ] = true;
        return true;
      }
    }
    return false;
  }
  int max_matching( ) {
    fill( used.begin(), used.begin()+n1, false );
    fill( matching.begin(), matching.begin()+n2, -1 );
    int ans = 0;
    while( true ) {
      bfs( );
      fill( seen.begin(), seen.begin()+n1, false );
      int f = 0;
      for( int u = 0; u < n1; u++ ) {
        if( !used[ u ] && dfs( u ) ) {
          f++;
        }
      }
      if( f == 0 ) {
        return ans;
      }
      ans += f;
    }
    return 0;
  }
};