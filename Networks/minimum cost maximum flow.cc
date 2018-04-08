struct Edge { 
  int from, to, cap, cost, flow;
  Edge( ) { }
  Edge( int from, int to, int cap, int cost, int flow ) : 
    from(from), to(to), cap(cap), cost(cost), flow(flow) { }
};
struct Network {
  int n;
  vector< Edge > edge;
  vector< vi > graph;
  vi pred, dist, phi;
  Network( int n ) : n(n), graph(n), pred(n), dist(n), phi(n) { }
  void add_edge( int from, int to, int cap, int cost ) {
    graph[ from ].PB( SIZE( edge ) );
    edge.PB( Edge( from, to, cap, cost, 0 ) );
    graph[ to ].PB( SIZE( edge ) );
    edge.PB( Edge( to, from, 0, -cost, 0 ) );
  }
  bool dijkstra( int s, int t ) {
    fill( ALL(dist), oo );
    fill( ALL(pred), -1 );
    set< pii > pq;
    dist[ s ] = 0;
    for( pq.insert( MP( dist[s], s ) ); !pq.empty( ); ) {
      int u = ( *pq.begin() ).SE; pq.erase( pq.begin() );
      for( int i = 0; i < SIZE( graph[u] ); i++ ) {
        Edge& e = edge[ graph[u][i] ];
        int ndist = dist[e.from]+e.cost+phi[e.from]-phi[e.to];
        if( e.cap-e.flow > 0 && ndist < dist[e.to] ) {
          pq.erase( MP( dist[e.to], e.to ) );
          dist[ e.to ] = ndist;
          pred[ e.to ] = graph[ u ][ i ];
          pq.insert( MP( dist[e.to], e.to ) );
        }
      }
    }
    for( int i = 0; i < n; i++ )
      phi[ i ] = min( oo, phi[i]+dist[i] );
    return ( dist[t] != oo );
  }
  pair< ll, ll > max_flow( int s, int t ) {
    ll mincost = 0, maxflow = 0;
    fill( ALL(phi), 0 );
    while( dijkstra( s, t ) ) {
      int flow = oo;
      for( int v = pred[t]; v != -1; v = pred[ edge[v].from ] )
        flow = min( flow, edge[v].cap-edge[v].flow );
      for( int v = pred[t]; v != -1; v = pred[ edge[v].from ] ) {
        Edge& e1 = edge[ v ];
        Edge& e2 = edge[ v^1 ];
        mincost += e1.cost*flow;
        e1.flow += flow;
        e2.flow -= flow;
      }
      maxflow += flow;
    }
    return MP( maxflow, mincost );
  }
};