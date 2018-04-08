struct pt {
  lf x, y, z;
  pt( ) { }
  pt( lf x, lf y, lf z ) : x( x ), y ( y ), z ( z ) { }
};
const lf EPS = 1e-9;
const lf PI = acos( -1.0 );
const pt o = pt( 0.0, 0.0, 0.0 );
pt operator / ( const pt& A, const lf& B ) { return { x(A)/B, y(A)/B, z(A)/B }; }
inline pt cross( pt A, pt B ) { return pt( y(A)*z(B)-z(A)*y(B), z(A)*x(B)-x(A)*z(B), x(A)*y(B)-y(A)*x(B) ); }
inline lf dot( pt A, pt B ) { return x(A)*x(B) + y(A)*y(B) + z(A)*z(B); }
inline lf norm( pt A ) { return x(A)*x(A) + y(A)*y(A) + z(A)*z(A); }
inline lf abs( pt A ) { return sqrt( norm(A) ); }
inline bool same ( lf a, lf b ) { return a+EPS > b && b+EPS > a; }
inline bool samePt ( pt A, pt B ) { return same ( x(A), x(B) ) && same ( y(A), y(B) ) && same ( z(A), z(B) ); }
inline bool zero( lf d ) { return d >= -EPS && d <= EPS; }
bool is_plane( pt A, pt B, pt C ) { return !samePt( cross( B-A, C-A ), o ); }
// 1 for intersect, 0 for inside, -1 for parallel
int linePlane( pt S, pt T, pt A, pt B, pt C, pt& r ) {
  pt n = cross( B-A, C-A );
  pt u = T-S;
  lf d = dot( n, u );
  if( !zero( d ) ) {
    d = dot( n, A-S ) / d;
    r = S + u*d;
    return 1;
  }
  d = dot( n, A-S );
  if( zero( d ) ) return 0;
  return -1;
}
bool lineLineIntersection( pt A, pt B, pt C, pt D, pt& S ) {
  pt e = B-A, f = D-C, g = C-A;
  pt fg = cross( f, g ), fe = cross( f, e );
  lf h = abs( fg ), k = abs( fe );
  if( zero( h ) || zero( k ) ) return false;
  if( samePt( cross( fg, fe ), o ) ) S = A + e*h/k;
  else S = A - e*h/k;
  return true;
}
bool planesIntersection( pt A, pt B, pt C, pt D, pt E, pt F, pt& S, pt& T ) {
  pt n1 = cross( B-A, C-A );
  pt n2 = cross( D-E, F-E );
  pt u = cross( n1, n2 );
  if( samePt( u, o ) ) return false;
  lineLineIntersection( A, B, D, E, S );
  T = S + u;
}