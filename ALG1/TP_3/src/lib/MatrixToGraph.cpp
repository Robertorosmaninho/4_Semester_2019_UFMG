//
// Created by Roberto Rosmaninho on 17/11/19.
//

#include "../include/MatrixToGraph.h"
#include <iostream>

MatrixToGraph::MatrixToGraph(int V, int I, int J,
                              std::vector<int> *matrix) :
                              block_line(J), block_column(I) {
  this->_graph = new std::vector<Node>[V * V];

  int h = 0, i = 0, j = 0, k = 0;
  int e = 0, f = 0, x = 0;
  int size = block_line * block_column;

  //Itera sobre as linhas em blocos
  for (; h < V; h += block_line, e += (block_line), f = 0) {
    //Itera sobre as colunas em blocos
    for (i = 0; i < V; i += block_column, f += (block_column)) {
      //Itera sobre as linhas dos blocos
      for (j = 0; j < block_line; j++) {
        //Itera sobre as colunas dos blocos
        for (k = 0; k < block_column; k++, x++) {
          //Adiciona todos os itens dobloco em uma lista
          nodes.emplace_back(matrix[j + e][k + f], j + e, k +f);
          //Cria um nó no grafo com o número atual
          _graph[x].emplace_back(matrix[j + e][k + f], j + e, k +f);
        }
      }
      x -= size; //Retorna o iterador para a posicão anterior à adição dos
      // numeros do bloco atual para passar por cada item novamente

      //Itera sobre cada item para que loop inferior adcione cada item da
      // lista ao nó atual no grafo
      for(int p = 0; p < nodes.size(); p++, x++) {
        for (auto node : nodes) {
          if(!(node.get_line() == _graph[x][0].get_line() &&
              node.get_column() == _graph[x][0].get_column())){
            _graph[x].push_back(node);
          }
        }
      }
      nodes.clear(); //Reinicia a lista
    }
  }

  //Fill the nodes with the lines
  for(int a = 0; a < V*V; a++)
    for(int b = _graph[a][0].get_line(), c = 0; c < V; c++)
      if(!(_graph[a][0].get_line() == b && _graph[a][0].get_column() == c))
        _graph[a].emplace_back(matrix[b][c], b, c);


  //Fill the nodes with columns
  for(int a = 0; a < V*V; a++)
    for (int b = 0, c = _graph[a][0].get_column(); b < V; b++)
      if (!(_graph[a][0].get_line() == b && _graph[a][0].get_column() == c))
        _graph[a].emplace_back(matrix[b][c], b, c);


  std::cout << "===================================\n";
  for(int i = 0; i < V*V; i++){
    std::cout << "i(" << i << ", " << _graph[i][0].get_number() << ") -> ";
    for(long j = 1; j < _graph[i].size(); j++) {
      std::cout << _graph[i][j].get_number() << " ";
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

