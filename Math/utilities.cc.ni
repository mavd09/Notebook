ll mod_mul( ll a, ll b, ll mod ) {
  ll x = 0, y = a%mod;
  while( b ) {
    if( b&1 ) {
      x = ( x+y )%mod;
    }
    y = ( y+y )%mod;
    b >>= 1;
  }
  return x;
}

ll mod_pow( ll b, ll e, ll mod ) {
  ll r = 1;
  while( e > 0 ) {
    if( e&1 ) {
      r = mod_mul( r, b, mod );
    }
    b = mod_mul( b, b, mod );
    e >>= 1;
  }
  return r;
}

ll bin_pow( ll b, ll e ) {
  ll r = 1;
  while( e > 0 ) {
    if( e&1 ) {
      r = r*b;
    }
    b = b*b;
    e >>= 1;
  }
  return r;
}