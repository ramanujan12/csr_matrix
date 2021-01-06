/*
  script to test the csr matrix
*/

#include "timing.h"
#include "dijkstra.h"
#include "bellman_ford.h"

// int main(int argc, char **argv) {
int main(int argc, char **argv) {
  //std::ifstream ins("foodweb-baydry.konect");
  //std::ifstream ins("test.txt");
  std::ifstream ins("cit-patent.edges");
  std::vector<std::tuple<unsigned int, unsigned int, float>> cv;
  std::mt19937 prng{42};
  std::uniform_real_distribution<float> distrib {0.0f, 1.0f};
  read_graph_unweighted(ins, [&] (unsigned int u, unsigned int v) {
      // Generate a random edge weight in [a, b).
      cv.push_back(std::tuple <unsigned int, unsigned int, float> {u, v, distrib(prng)});
    });
  
  // Determine n as the maximal node ID.
  unsigned int n = 0;
  for(auto ct : cv) {
    auto u = std::get<0>(ct);
    auto v = std::get<1>(ct);
    if (u > n)
      n = u;
    if (v > n)
      n = v;
  }
  
  auto mat = coordinates_to_csr(n+1, std::move(cv));
  /*
  stopwatch sw_tr;
  sw_tr.start();
  csr_matrix mat_tr = transpose(mat);
  sw_tr.stop();
  std::cout << "transpose : " << sw_tr.ms() << std::endl;
  */
  // assert(check_transpose(mat, mat_tr));
  
  stopwatch sw;
  sw.start();
  std::vector <float> v_pri_dij = dijkstra<unsigned, 2>(mat, 2);
  sw.stop();
  std::cout << "dijkstra : " << sw.ms() << std::endl;
  
  /*
  sw.start();
  std::vector <float> v_pri_bell = bellman_ford(mat, 2);
  sw.stop();
  std::cout << "bellman-ford : " << sw.ms() << std::endl;
  */
  /*
  std::cout << sw.ms() << std::endl;
  */
  /*
  for (std::size_t i = 0; i < v_pri_dij.size(); ++i) {
    std::cout << v_pri_dij[i] << " " << v_pri_bell[i] << std::endl;
  }
  */
  // use dijsktra

  /*
  stopwatch sw;
  sw.start();
  check_dijkstra<std::size_t, 2>(mat);
  sw.stop();
  std::cout << "4  : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 3>(mat);
  sw.stop();
  std::cout << "3  : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 4>(mat);
  sw.stop();
  std::cout << "4  : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 5>(mat);
  sw.stop();
  std::cout << "5  : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 6>(mat);
  sw.stop();
  std::cout << "6  : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 7>(mat);
  sw.stop();
  std::cout << "7  : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 8>(mat);
  sw.stop();
  std::cout << "8  : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 9>(mat);
  sw.stop();
  std::cout << "9  : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 10>(mat);
  sw.stop();
  std::cout << "10 : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 11>(mat);
  sw.stop();
  std::cout << "11 : " << sw.ms() << std::endl;
  sw.start();
  check_dijkstra<std::size_t, 12>(mat);
  sw.stop();
  std::cout << "12 : " << sw.ms() << std::endl;
  */
}
