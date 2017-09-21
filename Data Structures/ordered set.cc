#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
 
typedef
tree<
  T,
  null_type,
  less< T >,
  rb_tree_tag,
  tree_order_statistics_node_update >
ordered_set;

// Get Kth element of type T [ 0, size )
*X.find_by_order( y )
// Count elements smaller than y
X.order_of_key( y )