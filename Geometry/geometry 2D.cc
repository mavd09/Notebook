const int DIM = 2;
struct pt {
  lf v[DIM];
  pt( ) { }
  pt( lf x, lf y ) {
    v[0] = x;
    v[1] = y;
  }
};

inline lf x( pt P ) { return P.v[0]; }
inline lf y( pt P ) { return P.v[1]; }

istream& operator >> ( istream& in, pt& p ) {
  for( int i = 0; i < DIM; ++i ) {
    in >> p.v[i];
  }
  return in;
}

ostream& operator << ( ostream& out, const pt& p ) {
  for( int i = 0; i < DIM; ++i ) {
    out << double(p.v[i]) << " ";
  }
  return out;
}

pt operator + ( const pt& A, const pt& B ) { return pt( x(A)+x(B), y(A)+y(B) ); }
pt operator - ( const pt& A, const pt& B ) { return pt( x(A)-x(B), y(A)-y(B) ); }
pt operator * ( const lf& B, const pt& A ) { return pt( x(A)*B, y(A)*B ); }
pt operator * ( const pt& A, const lf& B ) { return pt( x(A)*B, y(A)*B  ); }
pt operator * ( const pt& A, const pt& B ) { return pt( x(A)*x(B)-y(A)*y(B), x(A)*y(B)+y(A)*x(B) ); }
pt operator / ( const pt& A, const lf& B ) { return pt( x(A)/B, y(A)/B ); }

inline lf dot( pt A, pt B ) { return x(A)*x(B) + y(A)*y(B); }
inline lf cross( pt A, pt B ) { return x(A)*y(B) - y(A)*x(B); }
inline lf norm( pt A ) { return x(A)*x(A) + y(A)*y(A); }
inline lf abs( pt A ) { return sqrt( norm(A) ); }
inline lf arg( pt A ) { return atan2( y(A), x(A) ); }
inline pt exp( pt A ) { return pt( exp( x(A) )*cos( y(A) ), exp( x(A) )*sin( y(A) ) ) ; }
inline pt rot( pt P, lf ang ) { return P*exp( pt(0,1)*ang ); }
inline pt rotccw( pt P ) { return P*pt(0,1); }
inline pt rotcw( pt P ) { return P*pt(0,-1); }
inline bool same( lf a, lf b ) { return a+EPS > b && b+EPS > a; }
inline bool samePt( pt A, pt B ) { return same ( x(A), x(B) ) && same ( y(A), y(B) ); }
inline lf angle( pt A, pt O, pt B ) { return (lf)acos( dot(A-O, B-O) / sqrt(norm(O-A) * norm(O-B)) ); }
inline bool parallel( pt A, pt B, pt C, pt D ) { return same ( 0, cross( B-A, D-C ) ); }
inline bool ortho( pt A, pt B, pt C, pt D ) { return same ( 0, dot( B-A, D-C ) ); }
inline lf dist( pt A, pt B ) { return abs( B - A ); }

pt inversion( lf r, pt A ) { 
  return r*A / norm(A);
}
int get_points( pt p, pt q ) {
  return __gcd( abs(x(p)-x(q)), abs(y(p)-y(q)) );
}

// 0  for collineal points ( angle = 0 )
// 1  for angle BAX counter clockwise
// -1 for angle BAX clockwise
int ccw( pt X, pt A, pt B ) {
  lf c = cross( B-A, X-A );
  if( same( c, 0.0 ) ) { return 0; }
  if( c > EPS ) { return 1; }
  return -1;
}

lf distToLine( pt p, pt A, pt B, pt &c ) {
  lf u = dot( p-A , B-A ) / norm( B-A );
  c = A + u*( B-A );
  return dist( p , c );
}

pt refPoint( pt X, pt A, pt B ) {
  pt aux; distToLine( X, A, B, aux );
  return X + lf(2.0)*(aux-X);
}

pt linesIntersection( pt A, pt B, pt C, pt D ) {
  lf x = cross( C, D-C ) - cross( A, D-C );
  x /= cross( B-A, D-C );
  return A + x*(B-A);
}

inline bool lineContains( pt X, pt A, pt B ) { return fabs(cross( B-A , X-A )) < EPS; }

inline bool segContains( pt X, pt A, pt B ) {
  if ( !same( 0, cross ( A-X, B-X ) ) ) return 0;
  return ( dot( A-X, B-X ) < EPS );
}

inline bool collinearSegsIntersects ( pt A, pt B, pt C, pt D ) {
  return segContains(A,C,D) || segContains(B,C,D)
      || segContains(C,A,B) || segContains(D,A,B);
}

bool segmentsIntersect( pt A, pt B, pt C, pt D ) {
  if( samePt(A,B) )
    return segContains( A, C, D );
  if( samePt(C,D) )
    return segContains( C, A, B );
  if( parallel(A,B,C,D) )
    return collinearSegsIntersects( A,B,C,D );
  pt aux = linesIntersection(A,B,C,D);
  return segContains(aux,A,B) && segContains(aux,C,D);
}

lf distToSegment( pt p, pt A, pt B, pt &c ) {
  lf u = dot( p-A , B-A ) / norm( B-A );
  if( u < -EPS ) { c = A; return dist( p , A ); }
  if( (u-1.0) > EPS ) { c = B; return dist( p, B ); }
  return distToLine(p,A,B,c);
}

inline bool insideCircle( pt p, pt c, lf r ) { return norm(c-p) < (r*r)+EPS;  }

//From two Points and Radius, get center of the circle
//There are two possible centers, to get the other, reverse p1 p2
bool circle2Pt (pt p1, pt p2, lf r, pt& c) {
  lf d2 = x(p1-p2) * x(p1-p2) + y(p1-p2) * y(p1-p2);
  lf det = r*r / d2 - 0.25;
  if( det < -EPS ) return false;
  lf h = sqrt(det);
  c.v[0] = x(p1+p2)*0.5 + y(p1-p2)*h ;
  c.v[1] = y(p1+p2)*0.5 + x(p2-p1)*h ;
  return true;
}

pt circle3Pt(pt a, pt b, pt c) {
  b = (a+b)/lf(2.0); c = (a+c)/lf(2.0);
  return linesIntersection(b, b+rotcw(a-b), c, c+rotcw(a-c));
}


bool circleLineIntersection( pt c, lf r, pt A, pt B, pt &p1, pt &p2 ) {
  pt t;
  lf u = distToLine( c, A, B, t );
  if( u > r+EPS ) {
    return false;
  }
  pt v = (B-A)/abs(B-A);
  lf d = sqrt(r*r - u*u);
  p1 = t + d*v;
  p2 = t - d*v;
  return true;
}

// -1 for same circles
// 0 for no intersection
// 1 for tangent
// 2 for 2 points of intersection
int intersectionCircles( pt c1, lf r1, pt c2, lf r2, pt &p1, pt &p2 ) {
  if( samePt( c1, c2 ) && same(r1,r2) ) return -1;
  lf sr = (r1 + r2) * (r1 + r2);
  lf dr = (r1 - r2) * (r1 - r2);
  lf d = norm( c2-c1 );
  if( d+EPS < dr || d > sr+EPS ) return 0;
  if ( same(d,sr) || same(d,dr) ) {
    p1 = p2 = c1 + (c2-c1)/sqrt(d) * r1;
    return 1;
  }
  pt tmp;
  tmp.v[0] = (r1*r1 - r2*r2 + d ) / (2.0*sqrt(d)) ;
  tmp.v[1] = sqrt( r1*r1 - x(tmp)*x(tmp) ) ;
  lf ang = arg( c2 - c1 );
  p1 = rot( tmp, ang ) + c1;
  p2 = refPoint( p1, c1, c2 );
  return 2;
}

// P[0] must be equal to P[n]
double perimeter(const vector<pt> &P) {
  double result = 0.0;
  for(int i = 0; i < (int)P.size()-1; i++) result += dist( P[i],P[i+1] );
  return result;
}

// P[0] must be equal to P[n]
// Area is positive if the polygon is ccw
double signedArea(const vector<pt> &P) {
  double result = 0.0;
  for(int i = 0; i < (int)P.size()-1; i++) result += cross( P[i],P[i+1] );
  return result / 2.0;
}

double area(const vector<pt> &P) { return fabs(signedArea(P)); }

// P[0] must be equal to P[n]
bool isConvex( const vector<pt> &P) {
  int sz = (int) P.size(); if(sz <= 3) return false;
  bool isL = ccw(P[0], P[1], P[2]) >= 0;
  for (int i = 1; i < sz-1; i++) {
    if( ( ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) >= 0 ) != isL) return false;
  }
  return true;
}

// P[0] must be equal to P[n]
pt computeCentroid(const vector<pt> &p) {
  pt c(0,0);
  lf scale = 6.0 * signedArea(p);
  for (int i = 0, j = 1; i < p.size()-1; i++, j++)
    c = c + (p[i]+p[j])*(x(p[i]) * y(p[j]) - x(p[j]) * y(p[i]));
  return c / scale;
}

// P[0] must be equal to P[n]
bool isSimple(const vector<pt> &p) {
  for (int i = 0, j, l; i < p.size()-1; i++) {
    for (int k = i+1; k < p.size()-1; k++) {
      j = (i+1); l = (k+1);
      if (i == l || j == k) continue;
      if (segmentsIntersect(p[i], p[j], p[k], p[l]))
        return false;
    }
  }
  return true;
}

// P[0] must be equal to P[n]
// Return 1 for interior, 0 for boundary and -1 for exterior
// O( N )
int inPolygon(pt X, const vector<pt> &P) {
  const int n = P.size(); int cnt = 0;
  for (int i = 0; i < n-1; i++) {
    if( segContains(X, P[i], P[i+1]) ) return 0;
    if( y(P[i]) <= y(X) ) {
      if( y(P[i+1]) > y(X) )
        if( !(ccw( X, P[i], P[i+1]) >= 0) ) cnt++;
    }
    else if ( y(P[i+1]) <= y(X) ) {
      if( ccw( X, P[i], P[i+1]) >= 0 ) cnt--;
    }
  }
  if(cnt == 0) return -1;
  else return 1;
}

// P[ 0 ] must be the left most (down) point
// 0 for collinear, 1 for inside, -1 for outside
// O( Log N )
int inConvexPolygon( pt X, lf mnx, lf mxx, vector<pt> &P ) {
  if( x(X) < mnx || x(X) > mxx )
    return -1;
  int lo = 1, hi = int( P.size() )-1, mi;
  while( lo <= hi ) {
    mi = (lo+hi)/2;
    if( cross( P[mi]-P[0], X-P[0] ) < -EPS ) {
      lo = mi+1;
    }
    else {
      hi = mi-1;
    }
  }
  lo = hi;
  if( hi == -1 ) return -1;
  lf c = cross( X-P[lo], X-P[lo+1] );
  if( same( c, 0.0 ) )
    return ( segContains( X, P[lo], P[lo+1] ) ? 0 : -1 );
  if( c > EPS )
    return -1;
  return 1;
}

// O( N )
lf diameterOfConvexPolygon( const vector<pt> &P, pt &A, pt &B ) {
  lf ans = -oo, d;
  int lo = 0, hi = 0;
  int sz = int(P.size());
  for( int i = 0, j = 0; i < sz; ++i ) {
    while( dist( P[i], P[j] )+EPS < dist( P[i], P[ (j+1)%sz ] )  ) {
      j = (j+1)%sz;
    }
    d = dist( P[i], P[j] );
    if( ans+EPS < d ) {
      ans = d;
      lo = i; hi = j;
    }
  }
  A = P[lo]; B = P[hi];
  return ans;
}

//Returns the Polygon to the left of AB (counter clockwise)
// O( N )
vector<pt> cutPolygon (pt A, pt B, const vector<pt> &P) {
  vector<pt> Q;
  for (int i = 0; i < (int)P.size(); i++) {
    double left1 = cross( B-A , P[i]-A ), left2 = 0;
    if(i != (int)P.size()-1) left2 = cross( B-A , P[i+1]-A );
    if(left1 > -EPS) Q.push_back(P[i]);
    if( left1 * left2 < -EPS ) Q.push_back( linesIntersection(P[i], P[i+1], A, B) );
  }
  if (!Q.empty() && !samePt(Q.back(), Q.front()) ) Q.push_back(Q.front());
  return Q;
}

// Returns Polygon in clockwise and with leftmost (down) point at P[0]
// O( N )
vector<pt> reorganize( vector<pt> &P ) {
  int n = int(P.size());
  vector<pt> R( n );
  if( P.size() == 1 ) {
    R[ 0 ] = P[ 0 ];
    return R;
  }
  //Check if is counterclockwise
  if ( signedArea( P ) > EPS ) { reverse( P.begin(), P.end() ); }
  int s = 0;
  for( int i = 1; i < n; ++i ) {
    if( x(P[s]) > x(P[i]) || ( x(P[s]) == x(P[i]) && y(P[s]) > y(P[i]) ) ) {
        s = i;
    }
  }
  R[ 0 ] = P[ s ];
  for( int i = (s+1)%n, j = 1; i != s; i = (i+1)%n, ++j ) {
    if( samePt( P[i], P[(i-1+n)%n] ) ) {
      j--;
      continue;
    }
    R[ j ] = P[ i ];
  }
  R[ n-1 ] = R[ 0 ];
  return R;
}

// P and Q must P[0] = P[n]
// Be careful with polygons of just one point
// O( N + M )
vector<pt> convexPolygonSum( vector<pt> &P, vector<pt> &Q ) {
  P = reorganize( P );
  Q = reorganize( Q );
  int n = int( P.size() ), m = int( Q.size() );
  vector<pt> R( n+m-1 );
  R[ 0 ] = (P[ 0 ] + Q[ 0 ]);
  int i = 1, j = 1, k = 1;
  for( ; i < n && j < m; ++k ) {
    if( cross( P[i]-P[i-1], Q[j]-Q[j-1] ) < -EPS ) {
      R[ k ] = R[ k-1 ] + ( P[ i ]-P[ i-1 ] );
      ++i;
    }
    else {
      R[ k ] = R[ k-1 ] + ( Q[ j ]-Q[ j-1 ] );
      ++j;
    }
  }
  while( i < n ) {
    R[ k ] = R[ k-1 ] + ( P[ i ]-P[ i-1 ] );
    ++i;
    ++k;
  }
  while( j < m ) {
    R[ k ] = R[ k-1 ] + ( Q[ j ]-Q[ j-1 ] );
    ++j;
    ++k;
  }
  vector<pt> T;
  T.PB( R[ 0 ] );
  for( int i = 1; i+1 < int(R.size()); ++i ) {
    if( same( cross( R[i]-R[i-1], R[i+1]-R[i-1] ), 0.0 ) )
      continue;
    T.PB( R[i] );
  }
  T.PB( T[ 0 ] );

  return T;
}

// Monotone Chain O( N Log N )
bool cmpPt( pt A, pt B ) {
  if( !same( x(A), x(B) ) ) return x(A) < x(B);
  return y(A) < y(B);
}

int turn(pt A, pt B, pt C) {
  lf r = cross(B-A, C-A);
  if( same( r, 0.0 ) ) return 0;
  if( r > EPS ) return 1;
  return -1;
}

// Return CH in ccw order starting at leftmost - downmost x
// Doesn't return P[ n ] = P[ 0 ]
vector<pt> CH( vector<pt> &P ) {
  if ( P.size() == 1 ) return P;
  const int n = P.size();
  sort ( P.begin(), P.end(), cmpPt );
  vector<pt> up;
  up.push_back(P[0]); up.push_back(P[1]);
  vector<pt> dn;
  dn.push_back(P[0]); dn.push_back(P[1]);
  for ( int i = 2; i < n; ++i ) {
    // If collineal points are needed is > and <, otherwise >= and <=
    while ( up.size() > 1 && turn(up[up.size()-2],up.back(),P[i]) >= 0 )
      up.pop_back();
    while ( dn.size() > 1 && turn(dn[dn.size()-2],dn.back(),P[i]) <= 0 )
      dn.pop_back();
    up.push_back(P[i]);
    dn.push_back(P[i]);
  }
  for (int i = (int) up.size() - 2; i >= 1; i--) dn.push_back(up[i]);
  return dn;
}
