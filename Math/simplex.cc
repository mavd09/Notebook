// Maximize: c^T * x
// Subject to: A*x = b, x_i >= 0
// Where:
// A = m*n matrix
// b = ( b_1, ... , b_m ), constants with b_i >= 0
// x = ( x_1, ... , x_n ), variables of the problem
// c = ( c_1, ... , c_n ), coefficients of the objective function
const lf eps = 1e-9, oo = 1/.0;
lf simplex( vector< vd >& A, vd& b, vd& c ) {
  int n = SIZE(c), m = SIZE(b);
  vector< vd > T( m+1, vd( n+m+1 ) );
  vi base( n+m ), row( m );
  for( int j = 0; j < m; ++j ) {
    for( int i = 0; i < n; ++i )
      T[j][i] = A[j][i];
    T[j][n+j] = 1;
    row[j] = n+j;
    base[row[j]] = 1;
    T[j][n+m] = b[j];
  }
  for( int i = 0; i < n; ++i ) T[m][i] = c[i];
  while( true ) {
    int p = 0, q = 0;
    for( int i = 0; i < n+m; ++i )
      if( T[m][i] <= T[m][p] )
        p = i;
    for( int j = 0; j < m; ++j )
      if( T[j][n+m] <= T[q][n+m] )
        q = j;
    lf t = min( T[m][p], T[q][n+m] );
    if( t >= -eps ) {
      vd x(n);
      for( int i = 0; i < m; ++i )
        if( row[i] < n )
          x[row[i]] = T[i][n+m];
      // x is the solution
      return -T[m][n+m]; // optimal
    }
    if( t < T[q][n+m] ) {
      // tight on c -> primal update
      for( int j = 0; j < m; ++j )
        if( T[j][p] >= eps && T[j][p]*( T[q][n+m]-t ) >= T[q][p]*( T[j][n+m]-t ) )
          q = j;
      if( T[q][p] <= eps )
        return oo; // primal infeasible
    } else {
      // tight on b -> dual update
      for( int i = 0; i < n+m+1; ++i )
        T[q][i] = -T[q][i];
      for( int i = 0; i < n+m; ++i )
        if( T[q][i] >= eps && T[q][i]*( T[m][p]-t ) >= T[q][p]*( T[m][i]-t ) )
          p = i;
      if( T[q][p] <= eps )
        return -oo; // dual infeasible
    }
    for( int i = 0; i < m+n+1; ++i )
      if( i != p )
        T[q][i] /= T[q][p];
    T[q][p] = 1; // pivot(q, p)
    base[p] = 1;
    base[row[q]] = 0;
    row[q] = p;
    for( int j = 0; j < m+1; ++j ) {
      if (j != q) {
        lf alpha = T[j][p];
        for( int i = 0; i < n+m+1; ++i )
          T[j][i] -= T[q][i] * alpha;
      }
    }
  }
  return oo;
}
