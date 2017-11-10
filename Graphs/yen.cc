/*
 * YEN's algorithm, O( KN( N+M logN ) ) ~ O( KN^3 )
 * Algorithm to find the kth shortest path from S to T
 */ 
int n;
vi graph[ MAX ];
int cost[ MAX ][ MAX ], dist[ MAX ], connect[ MAXP ], path[ MAX ];
ll vis = 0, mark = 0, edge[ MAX ];
vi emp;

struct Path {
  int w;
  vi p;
  Path( ) : w(0) { }
  Path( int w ) : w(w) { }
  Path( int w, vi p ) : w(w), p(p) { }
  bool operator < ( const Path& other )const {
    if( w == other.w ) {
      return lexicographical_compare( ALLR(p), ALLR(other.p) );
    }
    return w < other.w;
  }
  bool operator > ( const Path& other )const {
    if( w == other.w ){
      return lexicographical_compare( ALLR(other.p), ALLR(p) );
    }
    return w > other.w;
  }
};

void add_edge( int u, int v, int w ) {
  cost[u][v] = w;
  edge[u] |= ( 1LL<<v );
  graph[u].PB( v );
}

Path dijkstra( int s, int t ) {
  priority_queue< pii, vpii, greater<pii> > pq;
  fill( dist, dist+n+1, oo );
  pq.push( MP(0,s) );
  dist[s] = 0;
  while( !pq.empty() ) {
    int u = pq.top().SE, c = pq.top().FI;
    pq.pop();
    if( u == t ) break;
    if( ((vis>>u)&1) && s != u )
      continue;
    vis |= ( 1LL<<u );
    for( int i = 0; i < SIZE(graph[u]); ++i ) {
      int v = graph[u][i];
      if( ((vis>>v)&1) || ( s == u && !((mark>>v)&1)) ) {
        continue;
      }
      if( cost[u][v] != oo && dist[v] >= c+cost[u][v] ) {
        if( dist[v] > c+cost[u][v] || ( dist[v] == c+cost[u][v] && u < path[v] ) ) {
          dist[v] = c+cost[u][v];
          path[v] = u;
          pq.push( MP( dist[v], v ) );
        }
      }
    }
  }
  if( dist[t] == oo ) {
    return Path();
  }
  Path ret( dist[t] );
  for( int u = t; u != s; u = path[u] ) {
    ret.p.PB( u );
  }
  ret.p.PB( s );
  reverse( ALL(ret.p) );
  return ret;
}

vi yen( int s, int t, int k ) {
  priority_queue< Path, vector<Path>, greater<Path> > B;
  vector< vi > A( MAXP );
  vis = 0;
  mark = edge[s];
  A[0] = dijkstra( s, t ).p;
  if( SIZE(A[0]) == 0 ) {
    return A[0];
  }
  for( int it = 1; it < k; ++it ){
    Path root_path;
    memset( connect, -1, sizeof(connect) );
    vis = 0;
    bool F = true;
    for( int i = 0; i < SIZE(A[it-1])-1; ++i ) {
      bool flag = false;
      if( F && it > 2 && SIZE(A[it-1]) > i+1 && SIZE(A[it-2]) > i+1 && A[it-1][i+1] == A[it-2][i+1] ) {
        flag = true;
      } else {
        F = false;
      }
      if( i >= SIZE(A[it-1])-1 ) continue;
      int spur_node = A[it-1][i];
      mark = edge[ spur_node ];
      root_path.w += ( i ? cost[ A[it-1][i-1] ][ spur_node ] : 0 );
      root_path.p.PB( spur_node );
      vis |= ( 1LL<<spur_node );
      for( int j = 0; j < it; ++j ) {
        if( connect[j] == i-1 && SIZE(A[j]) > i && A[j][i] == spur_node ) {
          connect[j] = i;
          if( SIZE(A[j]) > i+1 ) {
            mark &= ~( 1LL<<A[j][i+1] );
          }
        }
      }
      if( flag ) continue;
      ll prev_vis = vis;
      Path spur_path = dijkstra( spur_node, t );
      vis = prev_vis;
      if( spur_path.p.empty() ) continue;
      Path cur_path = root_path;
      cur_path.w += spur_path.w;
      for( int j = 1; j < SIZE(spur_path.p); ++j ) {
        cur_path.p.PB( spur_path.p[j] );       
      }
      B.push( cur_path );
    }
    if( B.empty() ) return emp;
    A[ it ] = B.top().p;
    while( !B.empty() && B.top().p == A[it] ) {
      B.pop();
    }
  }
  return A[ k-1 ];
}