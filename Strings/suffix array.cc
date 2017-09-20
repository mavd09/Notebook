/*
 * O( n*log(n) ) where n = |text|
 * sa[i] contains the starting position of the i-th smallest suffix in t, ensuring that for all 1 < i <= n, t[sa[i-1], n] < t[sa[i], n] holds.
 * O( n ) where n = |text|
 * lcp[i] stores the lengths of the longest common prefixes between all pairs of consecutive suffixes in a sorted suffix array (needs sa).
 */

int n, mx;
string t;
int pos[ MAXN ], cnt[ MAXN ];
int aux_sa[ MAXN ], aux_pos[ MAXN ];
int sa[ MAXN ], lcp[ MAXN ];

bool check( int i, int gap ) {
  if( pos[ sa[i-1] ] != pos[ sa[i] ] ) {
    return true;
  }
  if( sa[ i-1 ]+gap < n && sa[ i ]+gap < n ) {
    return ( pos[ sa[i-1]+gap ] != pos[ sa[i]+gap ] );
  }
  return true;
}
void radix_sort( int k ) {
  for( int i = 0; i < mx; ++i ) {
    cnt[ i ] = 0;
  }
  for( int i = 0; i < n; i++ ) {
    cnt[ (i+k < n) ? pos[ i+k ]+1 : 1 ]++;
  }
  for( int i = 1; i < mx; i++ ) {
    cnt[ i ] += cnt[ i-1 ];
  }
  for( int i = 0; i < n; i++ ) {
    aux_sa[ cnt[ (sa[ i ]+k < n) ? pos[ sa[i]+k ] : 0 ]++ ] = sa[ i ];
  }
  for( int i = 0; i < n; i++ ) {
    sa[ i ] = aux_sa[ i ];
  }
}
void build_sa( ) {
  for( int i = 0; i < n; i++ ) {
    sa[ i ] = i;
    pos[ i ] = t[ i ];
  }
  for( int gap = 1; gap < n; gap <<= 1 ) {
    radix_sort( gap );
    radix_sort( 0 );
    aux_pos[ sa[0] ] = 0;
    for( int i = 1; i < n; i++ ) {
      aux_pos[ sa[i] ] = aux_pos[ sa[i-1] ] + check( i, gap );
    }
    for( int i = 0; i < n; i++ ) {
      pos[ i ] = aux_pos[ i ];
    }
    if( pos[ sa[n-1] ] == n-1 ) {
      break;
    }
  }
}
void build_lcp( ) {
  int k = 0;
  lcp[ 0 ] = 0;
  for( int i = 0; i < n; i++ ) {
    if( pos[ i ] == 0 ) {
      continue;
    }
    while( t[ i+k ] == t[ sa[ pos[i]-1 ]+k ] ) {
      k++;
    }
    lcp[ pos[ i ] ] = k;
    k = max( 0, k-1 );
  }
}
void build( string s ) {
  n = SIZE( s );
  t = s+"#";
  mx = max( 256, n );
  build_sa( );
  build_lcp( );
}