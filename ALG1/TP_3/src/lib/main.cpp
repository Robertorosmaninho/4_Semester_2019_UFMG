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

 /* std::cout << std::endl;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }*/

  auto graph = MatrixToGraph(N, I, J, matrix);
  bool solution = graph.solveSudoku();

 // std::cout << "\n\n";
  auto _graph = graph.get_graph();

  if(solution)
    std::cout << "solução\n";
  else
    std::cout << "sem solução\n";

  for(int i = 0, j = 0, col = 0, row = 1; i < N*N; j++) {
    if (j % N == 0 && col == N && row % J != 0) {
      std::cout << std::endl;
      col = 0;
      i -= (I+J+1);
      row++;
    }else if(col == N && row % J == 0){
      std::cout << std::endl;
      row++;
      col = 0;
    }
    if(col == I)
      i+=I;
    if(i < N*N) {
      int num = _graph[i][0]->get_number();
      std::cout << num << " ";
    }else {
      std::cout << 0 << "\n";
    }
    col++;
    i++;
  }

  return 0;
}