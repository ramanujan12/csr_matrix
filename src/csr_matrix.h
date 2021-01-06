/*
  header for the csr_matrix

  author  : jannis schürmann
  date    :
  to-do   :
  caution :

  program :
*/

#ifndef _CSR_MATRIX_H_
#define _CSR_MATRIX_H_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

template<typename F>
void read_graph_unweighted(std::istream &ins, F fn) {
  std::string line;
  bool seen_header = false;
  while (std::getline(ins, line)) {
    if(line.empty())
      continue;
    if(line.front() == '%')
      continue;
    
    std::istringstream ls(line);
    unsigned int u, v;
    if (!(ls >> u >> v))
      throw std::runtime_error("Parse error while reading input graph");
    
    if(!seen_header) {
      seen_header = true;
      continue;
    }
    
    fn(u, v);
  }
}

//___________________________________________________________________________
struct csr_matrix {
  unsigned int n;
  unsigned int m;
  std::vector <unsigned int> ind;
  std::vector <unsigned int> cols;
  std::vector <float> weights;
};

//___________________________________________________________________________
// transpose a given csr matrix
csr_matrix transpose(const csr_matrix& inp) {
  csr_matrix out = {
    inp.n,
    inp.m,
    std::vector <unsigned int>(inp.ind.size() + 1, 0.),
    std::vector <unsigned int>(inp.m, 0),
    std::vector <float>       (inp.weights.size(), 0.)
  };

  // count the entries per column for indice vector
  for (auto &col : inp.cols) {
    ++out.ind[col+2];
  }

  // run sum the new indice vector
  for (std::size_t i = 2; i < out.ind.size(); ++i) {
    out.ind[i] += out.ind[i-1];
  }

  // transform the matrix row by row
  for (std::size_t row = 0; row < inp.n; ++row) {
    for (std::size_t idx = inp.ind[row]; idx < inp.ind[row+1]; ++idx) {
      std::size_t idx_new = out.ind[inp.cols[idx] + 1]++;
      out.weights[idx_new] = inp.weights[idx];
      out.cols[idx_new]    = row;
    }
  }

  out.ind.pop_back();
  return out;
}

//___________________________________________________________________________
// get a spcific element
float get(const csr_matrix& m, std::size_t row, std::size_t col) {
  // check for validity
  if (m.n < row or m.n < col) {
    throw std::runtime_error(std::string(__FUNCTION__) + ": m.n <= row ro m.n <= col");
  }

  // get the row indice
  if (m.ind[row] != m.ind[row+1]) {
    for (std::size_t i = m.ind[row]; i < m.ind[row+1]; ++i) {
      if (col == m.cols[i]) {
	return m.weights[i];
      }
    }
    return 0.0;
  }

  // row does not contain elements
  else {
    return 0.0;
  }
}

csr_matrix coordinates_to_csr(unsigned int n,
			      std::vector<std::tuple<unsigned int, unsigned int, float>> cv) {
  unsigned int m = cv.size();
  
  csr_matrix mat;
  mat.n = n;
  mat.m = m;
  mat.ind.resize(n + 1);
  mat.cols.resize(m);
  mat.weights.resize(m);
  
  // Count the number of neighbors of each node.
  for(auto ct : cv) {
    auto u = std::get<0>(ct);
    ++mat.ind[u];
  }
  
  // Form the prefix sum.
  for(unsigned int i = 1; i <= n; ++i)
    mat.ind[i] += mat.ind[i - 1];
  assert(mat.ind[n] == m);
  
  // Insert the entries of the matrix in reverse order.
  for(auto it = cv.rbegin(); it != cv.rend(); ++it) {
    auto u = std::get<0>(*it);
    auto v = std::get<1>(*it);
    auto weight = std::get<2>(*it);
    mat.cols[mat.ind[u] - 1] = v;
    mat.weights[mat.ind[u] - 1] = weight;
    --mat.ind[u];
  }
  
  return mat;
}

//__________________________________________________________________________________________
// check the transpose for the matrix
bool check_transpose(const csr_matrix& mat, const csr_matrix& mat_tr) {
  for (std::size_t row = 0; row < mat.n; ++row)
    for (std::size_t col = 0; col < mat.n; ++col)
      if (get(mat, row, col) != get(mat_tr, col, row))
	return false;
  return true;
}

//__________________________________________________________________________________________
// output the matrix data
void output_data(const csr_matrix& m) {
  std::cout << "n : " << m.n << std::endl;
  std::cout << "m : " << m.m << std::endl;
  std::cout << "ind : ";
  for (auto &i : m.ind) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << "cols : ";
  for (auto &c : m.cols) {
    std::cout << c << " ";
  }
  std::cout << std::endl;

  std::cout << "weights : ";
  for (auto &w : m.weights) {
    std::cout << w << " ";
  }
  std::cout << std::endl;
}

#endif // _CSR_MATRIX_H_
