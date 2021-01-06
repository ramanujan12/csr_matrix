/*
  running dijkstra

  author  : jannis schürmann
  date    :
  to-do   :
  caution :

  program :
*/

#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <limits>

#include "csr_matrix.h"
#include "d_ary_heap.h"

template <typename key_type, unsigned arity = 2>
std::vector <float> dijkstra(csr_matrix& mat, key_type start) {
  
  // allocate the priority vector
  std::vector <float> v_pri(mat.n, std::numeric_limits<float>::max());
  
  // comparison function for the d_ary_heap
  auto cmp_pri = [&] (key_type lhs, key_type rhs) {
    return v_pri[lhs] < v_pri[rhs];
  };
  
  // init the d-ary heap 
  DAryAddressableIntHeap <key_type, arity, std::function<bool(key_type, key_type)>> q(cmp_pri);

  // transpose matrix for easier neighbours
  csr_matrix mat_tr = transpose(mat);
  
  // start the queue
  v_pri[start] = 0.0; // set the starting point to zero
  q.push(start);
  while(!q.empty()) {
    key_type u = q.extract_top();

    // update the neighbours for the non zero row elements for a matrix
    auto update_neighbours = [&] (csr_matrix &mat) {
      for (key_type idx = mat.ind[u]; idx < mat.ind[u+1]; ++idx) {
	key_type v = mat.cols[idx];
	if (v_pri[u] + mat.weights[idx] < v_pri[v]) {
	  v_pri[v] = v_pri[u] + mat.weights[idx];
	  q.update(v);
	}
      }
    };
    
    // 1. -> non zero elements in csr_matrix row
    update_neighbours(mat);

    // 2. -> non zero elements in csr_matrix col
    // -> non zero elements in csr_matrix_tr row
    update_neighbours(mat_tr);
  }
  
  // return the priority values
  return v_pri;
}

// check the dijkstra for different things
template <typename key_type, unsigned arity = 2>
bool check_dijkstra(csr_matrix& mat) {
  std::vector <float> pri_start, pri_goal;
  for (key_type start = 0; start < mat.n; ++start) {
    pri_start = dijkstra<key_type, arity>(mat, start);
    for (key_type goal = 0; goal < mat.n; ++goal) {
      pri_goal  = dijkstra<key_type, arity>(mat, goal);
      if ((float)(pri_goal[start] - pri_start[goal])
	  > std::numeric_limits<float>::epsilon())
	return false;
    }
  }
  return true;
}

#endif // _DIJKSTRA_H_
