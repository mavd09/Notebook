/*
 * O( |v|^2*|e| )
 */
struct Edge {
  int from, to, cap, flow;
  Edge( int from, int to, int cap, int flow ) :
  from(from), to(to), cap(cap), flow(flow) { }
};
 
struct Network {
  int n;
  vector< Edge > edges;
  vector< vi > graph;
  vi dist, ptr;

  Network( int n ) : n(n), graph(n), dist(n), ptr(n) { }
   
  void add_edge( int from, int to, int cap ) {
    graph[ from ].PB( SIZE(edges) );
    edges.PB( Edge( from, to, cap, 0 ) );
    graph[ to ].PB( SIZE(edges) );
    edges.PB( Edge( to, from, 0, 0 ) );
  }
  bool bfs( int s, int t ) {
    fill( ALL(dist), -1 );
    queue< int > q;
    q.push( s );
    dist[ s ] = 0;
    while( !q.empty( ) && dist[ t ] == -1 ) {
      int u = q.front( ); q.pop( );
      for( int i = 0; i < SIZE( graph[u] ); ++i ) {
        int id = graph[ u ][ i ], v = edges[ id ].to;
        if( dist[ v ] == -1 && edges[ id ].flow < edges[ id ].cap ) {
          q.push( v );
          dist[ v ] = dist[ u ]+1;
        }
      }
    }
    return ( dist[ t ] != -1 );
  }
  int dfs( int u, int t, int flow ) {
    if( !flow ) return 0;
    if( u == t ) return flow;
    for( ; ptr[ u ] < SIZE( graph[u] ); ++ptr[ u ] ) {
      int id = graph[ u ][ ptr[u] ], v = edges[ id ].to;
      if( dist[ v ] != dist[ u ]+1 ) continue;
      int pushed = dfs( v, t, min( flow, edges[id].cap-edges[id].flow ) );
      if( pushed ) {
        edges[ id ].flow += pushed;
        edges[ id^1 ].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }
  ll max_flow( int s, int t ) {
    ll flow = 0;
    while( bfs( s, t ) ) {
      fill( ALL(ptr), 0 );
      while( int pushed = dfs( s, t, oo ) ) {
        flow += pushed;
      }
    }
    return flow;
  }
};
