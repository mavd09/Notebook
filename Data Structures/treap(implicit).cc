struct node {
  int k, p, cnt, mn;
  bool rvs;
  node *l, *r;
  node( int k ) : k( k ), p( rand() ), cnt( 1 ), rvs( false ), l( NULL ), r( NULL ) {}
};
typedef node* pnode;
int cnt( pnode &t ) {
  if( !t ) return 0;
  return t->cnt;
}
void upd_cnt( pnode &t ) {
  if( t )
    t->cnt = 1 + cnt( t->l ) + cnt( t->r );
}
void push( pnode &t ) {
  if( t && t->rvs ) {
    t->rvs = false;
    swap( t->l, t->r );
    if( t->l != NULL ) t->l->rvs ^= true;
    if( t->r != NULL ) t->r->rvs ^= true;
  }
}
void merge( pnode &t, pnode left, pnode right ) {
  push( left ); push( right );
  if( !left || !right ) {
    t = left ? left : right ;
    return;
  }
  if( left->p > right->p ) {
    merge( left->r, left->r, right );
    t = left;
  } else {
    merge( right->l, left, right->l );
    t = right;
  }
  upd_cnt( t );
}
void split( pnode t, int k, pnode &left, pnode &right, int add = 0 ) {
  if( !t ) {
    left = right = NULL;
    return;
  }
  push( t );
  int cur_key = add + cnt( t->l );
  if( cur_key < k ) {
    split( t->r, k, t->r, right, add + 1 + cnt( t->l ) );
    left = t;
  } else {
    split( t->l, k, left, t->l, add );
    right = t;
  }
  upd_cnt( t );
}
void insert( pnode &t, int idx, int k ) {
  pnode new_node = new node( k );
  if( !t ) {
    t = new_node;
    return;
  }
  pnode left, right;
  split( t, idx, left, right );
  merge( left, left, new_node );
  merge( t, left, right );
  upd_cnt( t );
}
void erase( pnode &t, int k ) {
  if( !t ) return;
  push( t );
  if( t->k == k ) merge( t, t->l, t->r );
  else if( t->k < k ) erase( t->r, k );
  else erase( t->l, k );
  upd_cnt( t );
}
