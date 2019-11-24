#include "include/lib.h"
#include <fstream>
#include <iostream>
#include <vector>

int main(int argv, char *argc[]){
  if(argv < 2){
    std::cout << "Entre com um arquivo de imput!\n";
    return 1;
  }
  std::fstream file;
  file.open(argc[1]);

  int N = 0, M = 0; //Money, Islands
  int P = 0, D = 0; //Points, Cost p/ day

  file >> N >> M;

  Lib *q1 = new Lib(N,M);
  std::vector<std::tuple<float, int, int>> islands; //points, cost


  for(int i = 0; i < M; i++){
    file >> D >> P;
    islands.push_back(std::make_tuple(D/P, D, P));
  }

  q1->set_islands(islands);
  q1->set_greedy();
  q1->set_dynamic_programming(N,M);

  std::cout << q1->get_total_points() << " " << q1->get_days() << "\n";
  std::cout << q1->get_total_points_pd() << " " << q1->get_days_pd() << "\n";

  file.close();
return 0;
}
