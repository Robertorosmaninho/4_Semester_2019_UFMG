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

int Graph::swap(int idA, int idB){
  //Verifica se há uma aresta entre A e B
  int temp = -1;
  for(int i = 0; i < _adj[idA].size(); i++){
    if(_adj[idA][i] == idB){
      temp = i;
      break;
    }
  }
 
  for(int i = 0; i < _adj[idB].size(); i++){
    if(_adj[idB][i] == idA){
      temp = i;
      break;
    }
  }

  if(temp == -1){
    std::cout << "\n*** Error ***\n";  
    return -1;
  }

  //Faz a troca
  if(idB == _adj[idA][temp]){
    _adj[idB].push_back(idA);
    _adj[idA].erase(_adj[idA].begin() + temp);
  }else if(idA == _adj[idB][temp]){
    _adj[idA].push_back(idB);
    _adj[idB].erase(_adj[idA].begin() + temp);
  }
  return temp;
}

bool Graph::swapEdge(int idA, int idB){
  //Verifica se existe uma aresta e a inverte
  int iterator = swap(idA,idB);
  
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
std::cout << "G possui ";//  << size();
// << " int, mas vc está tentando deletear o nó " << begin() + idA << "\n";
 // erase(begin() + idA);
std::cout << "Deletou o nó!\n";
  /*
  for(int i = 0; i < size(); i++){
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
  int size = 0;
  int temp = -1;
  std::vector<int> *reverse = new std::vector<int>[V];

  std::cout << "============ Before ==============\n";
  this->print();

  std::cout << "### Breakpoint ###\n";
  std::cout << "List Size: " << _adj->size() << "\n";
  std::cout << "List[0] Size: " << _adj[0].size() << "\n";
  
  //Inverte todas as arestas do grafo
  for(int i = 0; i < V; i++){
    size = _adj[i].size();
    for(int j = 0 ; j < size; j++){
       if(_adj[i][j] <= i && i < size - 1)
          i++;
       std::cout << i+1 << " ->" << _adj[i][j]+1 << "\n";
       temp = _adj[i][j];
       reverse[temp].push_back(i); 
    }
  }

  std::cout << "============ After ==============\n";
  this->print();

  std::cout << "============ Reverse ==============\n";
  for(int a = 0; a < V; a++){
    std::cout << a+1 << " -> ";
    for(int b = 0; b < reverse[a].size(); b++){
      std::cout << reverse[a][b] + 1 << " ";
    }
  std::cout << "\n";
  }

    Graph G = Graph(V,A);
    G._adj = reverse;
    G._age = this->_age;

    std::cout << "==========================\n";
    G.print();

  //Busca em profundidade para descobrir o nó com menor idade
    if(reverse[idA].empty())
      return -1;
    else
      G.DFS(idA);

    return G._min;
}

void Graph::print(){
   for(int j = 0; j < V; j++){
    std::cout << j+1 << " -> ";
    for(int i = 0; i < _adj[j].size(); i++){
      std::cout << _adj[j][i] + 1 << " ";
    }
  std::cout << "\n";
  } 
}
