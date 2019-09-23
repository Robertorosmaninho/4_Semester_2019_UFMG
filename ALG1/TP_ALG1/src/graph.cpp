#include "include/graph.h"
#include <iostream>

Graph::Graph(int V, int A){
  this->V = V;
  this->A = A;
  this->_adj = new std::vector<int>[V];
  this->_age = new int[V];
  this->_visited = std::vector<int>(V, 0);
  this->_cycle = 0;
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
  this->_min = 100;
  this->_cycle = 0;
  this->_visited = std::vector<int>(V, 0);
}

int Graph::swap(int idA, int idB, Graph *G){
  //Verifica se há uma aresta entre A e B
  int temp = -1;
  for(int i = 0; i < G->_adj[idA].size(); i++){
    if(G->_adj[idA][i] == idB){
      temp = i;
      break;
    }
  }
 
  for(int i = 0; i < G->_adj[idB].size(); i++){
    if(G->_adj[idB][i] == idA){
      temp = i;
      break;
    }
  }

  if(temp == -1){
    std::cout << "\n*** Error ***\n";  
    return -1;
  }

  //Faz a troca
  if(idB == G->_adj[idA][temp]){
    G->_adj[idB].push_back(idA);
    G->_adj[idA].erase(_adj[idA].begin() + temp);
  }else if(idA == G->_adj[idB][temp]){
    G->_adj[idA].push_back(idB);
    G->_adj[idB].erase(_adj[idA].begin() + temp);
  }
  return temp;
}

bool Graph::swapEdge(int idA, int idB){
  //Verifica se existe uma aresta e a inverte
  int iterator = swap(idA,idB, this);
  
  if(iterator == -1)
    return false;
   

  //Verifica se gerou ciclo
  this->reset_visited();
  if(!this->DFS(idA)){
    this->reset_visited();
    if(!this->DFS(idB))
      return true;
  }
  std::cout << "\n*** Cycle ***\n";  
  //Se gerou, desfaz a troca e returna falso
  if(idB == this->_adj[idA][iterator]){
    this->_adj[idB].pop_back();
    this->_adj[idA].push_back(idB);
  }else if(idA == _adj[idB][iterator]){
    this->_adj[idB].pop_back();
    this->_adj[idA].push_back(idB);
  }
   
  return false;
 
}

bool Graph::DFS(int idA){
  _visited[idA] = 1;
  int idB;

  for(int i = 0; i < _adj[idA].size(); i++){
    idB = _adj[idA][i];
    if(_visited[idB] != 1){
      if(_min > _age[idB])
        _min = _age[idB];
      DFS(idB);
    }else{
      this->_cycle = 1;
    }
  }
  if(_cycle)
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
  G->_age = this->_age;
  
  std::cout << "============ Before ==============\n";
  for(int j = 0; j < V; j++){
    std::cout << j+1 << " -> ";
    for(int i = 0; i < _adj[j].size(); i++){
      std::cout << _adj[j][i] + 1 << " ";
    }
  std::cout << "\n";
  }
  
  //Inverte todas as arestas do grafo
  for(int i = 0; i < G->_adj->size(); i++){
    for(int j = 0; j < G->_adj[i].size(); j++){
      G->swap(i, G->_adj[i][j], G);
    }
  }

  std::cout << "============ After ==============\n";
  for(int j = 0; j < V; j++){
    std::cout << j+1 << " -> ";
    for(int i = 0; i < _adj[j].size(); i++){
      std::cout << _adj[j][i] + 1 << " ";
    }
  std::cout << "\n";
  }

  //Busca em profundidade para descobrir o nó com menor idade
    if(G->_adj[idA].empty())
      return -1;
    else
      G->DFS(idA);

    return G->_min;
}
