#include "include/graph.h"
#include <iostream>

Graph::Graph(int V, int A){
  this->V = V;
  this->A = A;
  this->_adj = new std::vector<int>[V];
  this->_age = new int[V];
  this->_visited = std::vector<int>(V, 0);
  this->cycle = 0;
 // this->_order = nullptr;
}

Graph::~Graph(){}

void Graph::addNode(int id, int idAge){
  this->_age[id] = idAge;
}

void Graph::addEdge(int idA, int idB){
  _adj[idA].push_back(idB); 
}

std::vector<int>* Graph::getList(){
  return this->_adj;
}

void Graph::reset_visited(){
  this->cycle = 0;
  this->_visited = std::vector<int>(V, 0);
}

void Graph::solve_cycle(int idA, int idB, int i){
  if(idB == _adj[idA][i]){
    _adj[idB].pop_back();
    _adj[idA].push_back(idB);
  }else if(idA == _adj[idB][i]){
    _adj[idB].pop_back();
    _adj[idA].push_back(idB);
  }
}

bool Graph::swapEdge(int idA, int idB){
  //Verifica se há uma aresta entre A e B
  int temp = -1;
  std::cout << "Testing swap of " << idA + 1<< " and " << idB + 1 << ":\n";
  std::cout << "Test - IdA:\n";
  for(int i = 0; i < _adj[idA].size(); i++){
    std::cout << _adj[idA][i] + 1<< " ";
    if(_adj[idA][i] == idB){
      std::cout << "\nMatch IdA\n";
      temp = i;
      break;
    }
  }
 
  std::cout << "\nTest - IdB:\n";
  for(int i = 0; i < _adj[idB].size(); i++){
    std::cout << _adj[idB][i] + 1<< " ";
    if(_adj[idB][i] == idA){
      std::cout << "\nMatch IdB\n";
      temp = i;
      break;
    }
  }

  std::cout << "\n";
  if(temp == -1)
    return false;
  
  //Faz a troca
  if(idB == _adj[idA][temp]){
    std::cout << "Swaping idB\n";
    _adj[idB].push_back(idA);
    _adj[idA].erase(_adj[idA].begin() + temp);
  }else if(idA == _adj[idB][temp]){
    std::cout << "Swaping idA\n";
    _adj[idA].push_back(idB);
    _adj[idB].erase(_adj[idA].begin() + temp);
  }

  //Verifica se gerou ciclo
  reset_visited();
  if(!DFS(idA)){
    reset_visited();
    if(!DFS(idB)){ std::cout << "\nPassou no test B\n";
      return true;}
  }
  
  //Se gerou, desfaz a troca e returna falso
  std::cout << "Cycle founded in " << idA + 1 << " and " << idB + 1 << "\n"; 
  solve_cycle(idA,idB, temp);
  return false;
 
}

bool Graph::DFS(int idA){
  _visited[idA] = 1;
  int idB;

  for(int i = 0; i < _adj[idA].size(); i++){
    idB = _adj[idA][i];
    if(_visited[idB] != 1){
      if(min > _age[idB])
        min = _age[idB];
      DFS(idB);
    }else{
      this->cycle = 1;
    }
  }
  if(cycle)
    return true;
  else
    return false;
}

void Graph::deleteNode(std::vector<int> *G, int idA){
std::cout << "G possui ";//  << G->size();
// << " int, mas vc está tentando deletear o nó " << G->begin() + idA << "\n";
 // G->erase(G->begin() + idA);
std::cout << "Deletou o nó!\n";
  /*
  for(int i = 0; i < G->size(); i++){
    for(int j = 0; j < G[i].size(); j++)
      if(G[i][j] == idA)
        G[i].erase(G[i].begin() + j);
  }*/
}

std::vector<int> Graph::Meeting(std::vector<int> *G){
  if(G->empty()){
   std::cout << "G is Empty!\n"; 
    return _order;
}
  std::vector<int> noincoming;
  for(int i = 0; i < V; i++){
    if(_adj[i].size() == 0)
      noincoming.push_back(i);
  }

  int temp = noincoming.back();
  noincoming.pop_back();

  _order.push_back(temp - 1);
std::cout << "Passsou Aqui!\n";
  deleteNode(G, temp);
  Meeting(G);
   
  //return nullptr;
}

int Graph::Commander(int idA){
  Graph *G = new Graph(V, A);
  G->_adj = this->_adj;
  //Inverte todas as arestas do grafo
  for(int i = 0; i < G->_adj->size(); i++){
    for(int j = 0; j < G->_adj[i].size(); j++)
      swapEdge(G->_adj[i][0], G->_adj[i][j]);
  }

  //Busca em profundidade para descobrir o nó com menor idade
    if(G->_adj[idA].empty())
      return -1;
    else
      G->DFS(idA);

    return G->min;
}
