const double EPS = 1e-10;

double Gauss_Jordan( vvd& a, vvd& b ) {
  const int n = int( a.size( ) );
  const int m = int( a[ 0 ].size( ) );
  vi irow( n ), icol( n ), ipiv( n );
  double det = 1;
  for( int i = 0; i < n; i++ ) {
    int pj = -1, pk = -1;
    for( int j = 0; j < n; j++ ) {
      if( !ipiv[ j ] ) {
        for( int k = 0; k < n; k++ ) {
          if( !ipiv[ k ] ) {
            if( pj == -1 || abs( a[ j ][ k ] ) > abs( a[ pj ][ pk ] ) ) {
              pj = j; 
              pk = k;
            }
          }
        }
      }
    }
    if( abs( a[ pj ][ pk ]) < EPS ) {
      cerr << "Matrix is singular." << endl;
      exit( 0 );
    }
    ipiv[ pk ]++;
    swap( a[ pj ], a[ pk ] );
    swap( b[ pj ], b[ pk ] );
    if( pj != pk ) {
      det *= -1;
    }
    irow[ i ] = pj;
    icol[ i ] = pk;
    double c = 1.0/a[ pk ][ pk ];
    det *= a[ pk ][ pk ];
    a[ pk ][ pk ] = 1.0;
    for( int p = 0; p < n; p++ ) {
      a[ pk ][ p ] *= c;
    }
    for( int p = 0; p < m; p++ ) {
      b[ pk ][ p ] *= c;
    }
    for( int p = 0; p < n; p++ ) {
      if( p != pk ) {
        c = a[ p ][ pk ];
        a[ p ][ pk ] = 0;
        for( int q = 0; q < n; q++ ) {
          a[ p ][ q ] -= a[ pk ][ q ]*c;
        }
        for( int q = 0; q < m; q++ ) {
          b[ p ][ q ] -= b[ pk ][ q ]*c;
        }      
      }
    }
    for( int p = n-1; p >= 0; p-- ) {
      if( irow[ p ] != icol[ p ] ) {
        for( int k = 0; k < n; k++ ) {
          swap( a[ k ][ irow[ p ] ], a[ k ][ icol[ p ] ] );
        }
      }
    }
  }
  return det;
}