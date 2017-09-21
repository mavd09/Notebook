struct node {
  ll k, p, mn;
  node *l, *r;
  node( ll k ) : k(k), p(rand()), mn(oo), l(nullptr), r(nullptr) { }
};

typedef node* pnode;

ll min_node( pnode t ) {
  if( t == nullptr ) {
    return oo;
  }
  return t->mn;
}

void upd_min( pnode t ) {
  if( t != nullptr ) {
    t->mn = min( t->k, min( min_node( t->l ), min_node( t->r ) ) );
  }
}

void merge( pnode &t, pnode left, pnode right ) {
  if( left == nullptr || right == nullptr ) {
    t = ( right == nullptr ) ? left : right;
  }
  else if( left->p > right->p ) {
    merge( left->r, left->r, right );
    t = left;
  }
  else {
    merge( right->l, left, right->l );
    t = right;
  }
  upd_min( t );
}

void split( pnode t, ll k, pnode &left, pnode &right ) {
  if( t == nullptr ) {
    left = right = nullptr;
  }
  else if( t->k < k ) {
    split( t->r, k, t->r, right );
    left = t;
  }
  else {
    split( t->l, k, left, t->l );
    right = t;
  }
  upd_min( t );
}

void insert( pnode &t, pnode new_node ) {
  if( t == nullptr ) {
    t = new_node;
  }
  else if( t->p < new_node->p ) {
    split( t, new_node->k, new_node->l, new_node->r );
    t = new_node;
  }
  else if( t->k < new_node->k ) {
    insert( t->r, new_node );
  }
  else {
    insert( t->l, new_node );
  }
  upd_min( t );
}

void erase( pnode &t, ll k ) {
  if( t == nullptr ) {
    return;
  }
  if( t->k == k ) {
    merge( t, t->l, t->r );
  }
  else if( t->k < k ) {
    erase( t->r, k );
  }
  else {
    erase( t->l, k );
  }
  upd_min( t );
}