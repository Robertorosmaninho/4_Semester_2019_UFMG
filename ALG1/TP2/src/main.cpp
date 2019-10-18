#include "include/lib.h"
#include <fstream>
#include <iostream>

int main(int argv, char *argc[]){
  if(argv < 2){
    std::cout << "Entre com um arquivo de imput!\n";
    return 1;
  }
  std::fstream file;
  file.open(argc[1]);

  int N, M; //Money, Islands
  int P, D; //Points, Cost p/ day

  file >> N >> M;
  //std::cout << N << " "<< M << "\n";

  Lib *q1 = new Lib(N,M);
  std::map<int, int, classcomp> islands; //points, cost

  for(int i = 0; i < M; i++){
    file >> D >> P;
    islands.insert(std::pair<int, int>(P,D));
//    std::cout << D << " "<< P << "\n";
  }

  q1->set_islands(islands);
  q1->set_cost_benefit();
  std::cout << "M: " << q1->set_matrix() << "\n";

  std::cout <<  q1->get_total_points() << " " << q1->get_days() << "\n";

  file.close();
return 0;
}
