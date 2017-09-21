struct Lat_Lon {
  double r, lat, lon;
};

struct Rect {
  double x, y, z;
};

Lat_Lon convert( Rect& p ) {
  Lat_Lon q;
  q.r = sqrt( p.x*p.x + p.y*p.y + p.z*p.z );
  q.lat = 180.0/PI*asin( p.z/q.r );
  q.lon = 180.0/PI*acos( p.x/sqrt( p.x*p.x + p.y*p.y ) );
  return q;
}

Rect convert( Lat_Lon& q ) {
  Rect p;
  p.x = q.r*cos( q.lon*PI/180.0 )*cos( q.lat*PI/180.0 );
  p.y = q.r*sin( q.lon*PI/180.0 )*cos( q.lat*PI/180.0 );
  p.z = q.r*sin( q.lat*PI/180.0 );
  return p;
}