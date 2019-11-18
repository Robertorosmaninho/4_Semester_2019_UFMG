//
// Created by Roberto Rosmaninho on 17/11/19.
//

#include "../include/MatrixToGraph.h"
#include <iostream>

MatrixToGraph::MatrixToGraph(int V, int I, int J,
                              std::vector<int> *matrix) :
                              block_line(J), block_column(I) {
  this->graph = new std::vector<Node>[V*V];


  int h = 0, i = 0 , j = 0, k = 0;

  //Set the first nodes
  for(i = 0; i < V; i++) {
    for (j = 0; j < V; j++) {
      graph[k].emplace_back(k, matrix[i][j], i, j);
      k++;
    }
  }


  k=0;
  int line_test = 0, column_test = 0;
  int column = 0, line = block_line;
  //Set the blocks
  h = 0, i = 0, j = 0;
  //Column
  for(i = block_column - 1, j = block_line - 1; i < V; i+=block_column){
    blocks.emplace_back(i, j);
    for(j+=block_line; j < V; j+=block_line)
      blocks.emplace_back(i, j);
  }


  /*k = 0;
  for(int i = 0; i < V; i++){
    std::cout << "i(" << i << ") -> ";
    for(int j = 0; j < V; j++){
      if(k == j)
        continue;
      std::cout << matrix[j][i] << " ";
      graph[k].push_back(matrix[j][i]);
      k++;
    }
    std::cout << "\n";
    k = 0;
  }*/

  std::cout << "===================================\n";
  for(int i = 0; i < V*V; i++){
    std::cout << "i(" << i << ", " << graph[i][0].get_number() << ") -> ";
    for(long j = 0; j < graph[i].size(); j++) {
      std::cout << graph[i][j].get_number() << " ";
    }
    std::cout << "\n";
  }

  std::cout << "===================================\n";
}

MatrixToGraph::~MatrixToGraph() {
 // for(int i = 0; i < this->graph->size(); i++)
  //  for(int j = 0; j < this->graph[i].size(); j++)
   //   graph[i][j].~Node();

}

bool MatrixToGraph::verify(int V, int number) {
  return false;
}

