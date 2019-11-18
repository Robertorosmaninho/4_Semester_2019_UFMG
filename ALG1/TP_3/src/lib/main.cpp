#include <iostream>
#include <fstream>

#include "../include/MatrixToGraph.h"

int main(int argv, char *argc[]){
  if(argv < 2){
    std::cout << "Entre com um arquivo de imput!\n";
    return 1;
  }
  std::fstream file;
  file.open(argc[1]);

  int N, I, J; // size(NxN), I/J -> Columns/Lines of each block
  file >> N >> I >> J;

  auto matrix = new std::vector<int>[N];

  int aux = 0;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      file >> aux;
      matrix[i].push_back(aux);
    }
  }

  MatrixToGraph(N, I, J, matrix);

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}