/*
 * O( |e|*flow_complexity )
 */
bool cmp_edge( const Edge &e1, const Edge &e2 ) {
  if( e1.cap != e2.cap ) return e1.cap > e2.cap;
  return e1.index < e2.index;
}
bool ok[ MAXN ];
ll get_flow( int s, int t ) {
  Network netw( n );
  for( int i = 0; i < m; ++i ) {
    if( !ok[ edges[i].index ] ) {
      netw.add_edge( edges[i].from, edges[i].to, edges[i].cap );
    }
  }
  return netw.max_flow( s, t );
}
vi min_cut( int s, int t ) {
  sort( ALL(edges), cmp_edge );
  ll flow = get_flow( s, t );
  vi ans;
  for( int i = 0; flow; ++i ) {
    ok[ edges[i].index ] = true;
    ll cur_flow = get_flow( s, t );
    ok[ edges[i].index ] = (flow-cur_flow == edges[i].cap);
    if( ok[ edges[i].index ] ) {
      ans.PB( edges[i].index );
      flow = cur_flow;
    }
  }
}
