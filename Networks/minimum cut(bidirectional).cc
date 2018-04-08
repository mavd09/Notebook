/*
 * O( |v|^3 )
 */
int n;
pair< int, vi > min_cut( vector< vi >& graph ) {
  vi used( n );
  vi cut, best_cut;
  int best_weight = -1;
  for( int phase = n-1; phase >= 0; --phase ) {
    vi w = graph[ 0 ];
    vi added = used;
    int prev, last = 0;
    for( int i = 0; i < phase; ++i ) {
      prev = last; last = -1;
      for( int j = 1; j < n; ++j )
        if( !added[j] && ( last == -1 || w[j] > w[last] ) )
          last = j;
      if( i == phase-1 ) {
        for( int j = 0; j < n; j++ )
          graph[ prev ][ j ] += graph[ last ][ j ];
        for( int j = 0; j < n; j++ )
          graph[ j ][ prev ] = graph[ prev ][ j ];
        used[ last ] = true;
        cut.PB( last );
        if( best_weight == -1 || w[last] < best_weight ) {
          best_cut = cut;
          best_weight = w[last];
        }
      } else {
        for( int j = 0; j < n; j++ )
          w[ j ] += graph[ last ][ j ];
        added[ last ] = true;
      }
    }
  }
  return MP( best_weight, best_cut );
}