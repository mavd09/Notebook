const lf PI = acos( -1.0 );

struct cp { lf r, i; };

cp operator + ( const cp& a, const cp& b ) { return { a.r+b.r, a.i+b.i }; }
cp operator - ( const cp& a, const cp& b ) { return { a.r-b.r, a.i-b.i }; }
cp operator * ( const cp& a, const cp& b ) { return { a.r*b.r-a.i*b.i, a.r*b.i+a.i*b.r }; }
cp operator * ( const cp& a, lf x ) { return { a.r*x, a.i*x }; }
cp operator * ( lf x, const cp& a ) { return { a.r*x, a.i*x }; }
cp operator / ( const cp& a, lf x ) { return { a.r/x, a.i/x }; }

ostream& operator << ( ostream& out, const cp& c ) {
  out << c.r;
  return out;
}

void rev( cp* a, int n ) {
  int i, j, k;
  for( i = 1, j = n>>1; i < n-1; ++i ) {
    if( i < j ) swap( a[ i ], a[ j ] );
    for( k = n>>1; j >= k; j -= k, k >>= 1 );
    j += k;
  }
}

void dft( cp* a, int n, int flag = 1 ) {
  rev( a, n );
  for( int m = 2; m <= n; m <<= 1 ) {
    cp wm = { cos( flag*2.0*PI/m ), sin( flag*2.0*PI/m ) };
    for( int k = 0; k < n; k += m ) {
      cp w = { 1.0, 0.0 };
      for( int j = k; j < k+(m>>1); ++j, w = w*wm ) {
        cp u = a[ j ], v = a[ j+(m>>1) ]*w;
        a[ j ] = u+v;
        a[ j+(m>>1) ] = u-v;
      }
    }
  }
}

void mul( int na, cp* a, int nb, cp* b ) {
  int n = 1;
  while( n <= na+nb+1 ) n <<= 1;
  dft( a, n ); dft( b, n );
  for( int i = 0; i < n; ++i ) {
    a[ i ] = a[ i ]*b[ i ];
  }
  dft( a, n, -1 );
  for( int i = 0; i < n; ++i ) {
    a[ i ].r = round( a[ i ].r/lf(n) );
  }
}