/*
 * O( |v|^3 )
 */
struct Edge {
  int from, to, cap, flow, index;
  Edge( int from, int to, int cap, int flow, int index ) :
  from(from), to(to), cap(cap), flow(flow), index(index) { }
};

struct Network {
  int n;
  vector< vector<Edge> > graph;
  vll excess;
  vi dist, active, count;
  queue< int > q;
  
  Network( int n ) : n( n ), graph( n ), excess( n ), dist( n ), active( n ), count( 2*n ) { }
  
  void add_edge( int from, int to, int cap ) {
    graph[ from ].PB( Edge( from, to, cap, 0, SIZE( graph[to] ) ) );
    if( from == to ) graph[ from ].back( ).index++;
    graph[ to ].PB( Edge( to, from, 0, 0, SIZE( graph[from] )-1 ) );
  }
  void enqueue( int v ) {
    if( !active[ v ] && excess[ v ] > 0 ) {
      active[ v ] = true;
      q.push( v );
    }
  }
  void push( Edge &e ) {
    int amt = int( min( excess[ e.from ], ll( e.cap-e.flow ) ) );
    if( dist[ e.from ] <= dist[ e.to ] || amt == 0 ) return ;
    e.flow += amt;
    graph[ e.to ][ e.index ].flow -= amt;
    excess[ e.to ] += amt;
    excess[ e.from ] -= amt;
    enqueue( e.to );
  }
  void gap( int k ) {
    for( int v = 0; v < n; v++ ) {
      if( dist[ v ] < k ) continue;
      count[ dist[ v ] ]--;
      dist[ v ] = max( dist[ v ], n+1 );
      count[ dist[ v ] ]++;
      enqueue( v );
    }
  }
  void relabel( int v ) {
    count[ dist[ v ] ]--;
    dist[ v ] = 2*n;
    for( int i = 0; i < SIZE( graph[v] ); i++ )
      if( graph[ v ][ i ].cap-graph[ v ][ i ].flow > 0 )
        dist[ v ] = min( dist[ v ], dist[ graph[ v ][ i ].to ]+1 );
    count[ dist[ v ] ]++;
    enqueue( v );
  }
  void discharge( int v ) {
    for( int i = 0; excess[ v ] > 0 && i < SIZE( graph[v] ); i++ )
      push( graph[ v ][ i ]);
    if( excess[ v ] > 0 ) {
      if( count[ dist[ v ] ] == 1 )
        gap( dist[ v ] );
      else
        relabel( v );
    }
  }
  ll max_flow( int s, int t ) {
    count[ 0 ] = n-1;
    count[ n ] = 1;
    dist[ s ] = n;
    active[ s ] = active[ t ] = true;
    for( int i = 0; i < SIZE( graph[s] ); i++ ) {
      excess[ s ] += graph[ s ][ i ].cap;
      push( graph[ s ][ i ] );
    }
    while( !q.empty( ) ) {
      int v = q.front( ); q.pop( );
      active[ v ] = false;
      discharge( v );
    }
    ll totflow = 0;
    for (int i = 0; i < SIZE( graph[s] ); i++ )
      totflow += graph[ s ][ i ].flow;
    return totflow;
  }
};