//
// Created by Roberto Rosmaninho on 17/11/19.
//

#include "../include/MatrixToGraph.h"
#include <iostream>

MatrixToGraph::MatrixToGraph(int V, int I, int J,
                              std::vector<std::vector<int>> matrix) : V(V),
                              block_row(J), block_column(I) {
  this->_graph = std::vector<std::vector<Node*>>(V * V);
  this->_matrix = matrix;

  //Fill the nodes with items on blocks
  set_block();

  //Fill the nodes with items on rows
  set_row();

  //Fill the nodes with items on columns
  set_column();
}

void MatrixToGraph::set_block() {
  int h = 0, i = 0, j = 0, k = 0;
  int e = 0, f = 0, x = 0;
  int size = block_row * block_column;

  //Itera sobre as linhas em blocos
  for (; h < V; h += block_row, e += (block_row), f = 0) {
    //Itera sobre as colunas em blocos
    for (i = 0; i < V; i += block_column, f += (block_column)) {
      //Itera sobre as linhas dos blocos
      for (j = 0; j < block_row; j++) {
        //Itera sobre as colunas dos blocos
        for (k = 0; k < block_column; k++, x++) {
          //Adiciona todos os itens dobloco em uma lista
          Node *node = new Node(_id, _matrix[j + e][k + f], j + e, k +
          f);
          _nodes.push_back(node);
          //Cria um nó no grafo com o número atual
          _graph[x].push_back(node);
          _matrix[j + e][k + f] = _id;
          _id++;
        }
      }
      x -= size; //Retorna o iterador para a posicão anterior à adição dos
      // numeros do bloco atual para passar por cada item novamente

      //Itera sobre cada item para que loop inferior adcione cada item da
      // lista ao nó atual no grafo
      for(int p = 0; p < _nodes.size(); p++, x++) {
        for (auto node : _nodes) {
          if(!(node->get_row() == _graph[x][0]->get_row() &&
               node->get_column() == _graph[x][0]->get_column())){
            _graph[x].push_back(node);
          }
        }
      }
      _nodes.clear(); //Reinicia a lista
    }
  }
  for(int i = 0; i < _nodes.size(); i++){
    delete _nodes[i];
  }
}

void MatrixToGraph::set_row() {
  for (int a = 0; a < V*V; a++){
    for (int b = _graph[a][0]->get_row(), c = 0; c < V; c++) {
      if (!(_graph[a][0]->get_row() == b && _graph[a][0]->get_column() == c)) {
        _graph[a].emplace_back(_graph[_matrix[b][c]][0]);
      }
    }
  }
}

void MatrixToGraph::set_column() {
  for(int a = 0; a < V*V; a++) {
    for (int b = 0, c = _graph[a][0]->get_column(); b < V; b++) {
      if (!(_graph[a][0]->get_row() == b && _graph[a][0]->get_column() == c)) {
        _graph[a].emplace_back(_graph[_matrix[b][c]][0]);
      }
    }
  }
}

MatrixToGraph::~MatrixToGraph() {
  for(int i = 0; i < V*V; i++)
    _graph[i].clear();
  _graph.clear();
}

bool MatrixToGraph::verify(int id, int number) {

 for(int i = 0; i < _graph[id].size(); i++) {
   if (_graph[id][i]->get_number() == number){
     return false;
   }
 }
 return true;
}

Node* MatrixToGraph::findUnsignedLocation() {
  for(int i = 0; i < V*V; i++){
    for(int j = 0; j < _graph[i].size(); j++){
      if(_graph[i][j]->get_number() == 0)
        return _graph[i][j];
    }
  }
  return nullptr;
}

bool MatrixToGraph::solveSudoku() {
  Node *node = findUnsignedLocation();
  if(node == nullptr)
    return true;

  for(int num = 1; num <= V; num++){
    if(verify(node->get_id(), num)){
      bool assign = assignNumber(node->get_id(), num, node);
      if(!assign)
        continue;
      if(solveSudoku())
        return true;
      node->set_number(0);
    }
  }
  std::cout << "wtf";
  return false;
}

bool MatrixToGraph::assignNumber(int id, int number, Node* node) {
  if (!verify(id, number))
    return false;

      if(node->get_number() == 0)
        node->set_number(number);
     else
      return false;

  return true;
}

void MatrixToGraph::print(){
  for(int i = 0, j = 0, col = 0, row = 1; i < V*V; j++) {
    if (j % V == 0 && col == V && row % block_row != 0) {
      std::cout << std::endl;
      row++;
      i-= ((block_row-1)*col);
      col = 0;
    }else if(col == V && row % block_row == 0){
      std::cout << std::endl;
      row++;
      col = 0;
    }
    if(col % block_column == 0 && col != 0)
      i+=((block_row-1)*block_column);
    if(i < V*V) {
      int num = _graph[i][0]->get_number();
      std::cout << num << " ";
    }else {
      std::cout << 0 << "\n";
    }
    col++;
    i++;
  }
}
