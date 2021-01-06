/*
  header for the bellman ford algorithm
  
  author  : jannis schürmann
  date    :
  to-do   :
  caution :

  program :
*/

#ifndef _BELLMAN_FORD_H_
#define _BELLMAN_FORD_H_

#include "csr_matrix.h"

// bellman ford that biatch
std::vector <float> bellman_ford(csr_matrix &mat, std::size_t start) {

  // alloc priority vector
  std::vector <float> v_pri(mat.n, std::numeric_limits<float>::max());
  v_pri[start] = 0;

  csr_matrix mat_tr = transpose(mat);
  
  // repeat the loop over all the edges
  for (std::size_t i = 0; i < mat.m; ++i) {
    
    // loop over all the edges in normal matrix
    // #pragma omp parallel
    for (std::size_t u = 0; u < mat.n; ++u) {
      for (std::size_t idx = mat.ind[u]; idx < mat.ind[u+1]; ++idx) {
	std::size_t v = mat.cols[idx];
	if (v_pri[u] + mat.weights[idx] < v_pri[v]) {
	  v_pri[v] = v_pri[u] + mat.weights[idx];
	}
      }
    }

    // loop over all the edges in transposed matrix
    // #pragma omp parallel
    for (std::size_t u = 0; u < mat_tr.n; ++u) {
      for (std::size_t idx = mat_tr.ind[u]; idx < mat_tr.ind[u+1]; ++idx) {
	std::size_t v = mat_tr.cols[idx];
	if (v_pri[u] + mat_tr.weights[idx] < v_pri[v]) {
	  v_pri[v] = v_pri[u] + mat_tr.weights[idx];
	}
      }
    }
  }

  return v_pri;
}

#endif // _BELLMAN_FORD_H_
