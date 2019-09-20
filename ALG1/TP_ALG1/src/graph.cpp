#include "include/graph.h"

Graph::Graph(int V, int A){
  this->V = V;
  this->A = A;
  this->_adj = new std::vector<int>[V];
  this->_age = new int[V];
  this->_visited = std::vector<int>(V, 0);
  this->_order = nullptr;
}

Graph::~Graph(){}

void Graph::addNode(int id, int idAge){
  this->_age[id] = idAge;
}

void Graph::addEdge(int idA, int idB){
  _adj[idA].push_back(idB); 
}

bool Graph::swapEdge(int idA, int idB){
  //Verifica se há uma aresta entre A e B
  int temp = -1;
  for(int i = 0; i < _adj[idA].size(); i++){
    if(_adj[idA][i] == idB){
      temp = i;
      break;
    }
  }

  for(int i = 0; i < _adj[idA].size(); i++){
    if(_adj[idA][i] == idB){
      temp = i;
      break;
    }
  }

  if(temp == -1)
    return false;
  
  //Faz a troca
  if(temp == idB){
    _adj[idB].push_back(idA);
    _adj[idA].erase(_adj[idA].begin() + temp);
  }else if(temp == idA){
    _adj[idA].push_back(idB);
    _adj[idB].erase(_adj[idA].begin() + temp);
  }

  //Verifica se gerou ciclo
  if(!DFS(idA)){
    return true;
  }else{ //Se gerou, desfaz a troca e returna falso
    if(temp == idB){
     _adj[idB].pop_back();
     _adj[idA].push_back(idB);
    }else if(temp == idA){
      _adj[idA].pop_back();
      _adj[idB].push_back(idA);
    } 
    return false;
  }
}

bool Graph::DFS(int idA){
  _visited[idA] = 1;
  int idB, cycle = 0;

  for(int i = 0; i < _adj[idA].size(); i++){
    idB = _adj[idA][i];
    if(_visited[idB] != 1){
      if(min > _age[idB])
        min = _age[idB];
      DFS(idB);
    }else{
      cycle = 1;
    }
  }
  if(cycle)
    return false;
  else
    return true;
}

void Graph::deleteNode(std::vector<int> *G, int idA){
  G->erase(G->begin() + idA);
  
  for(int i = 0; i < G->size(); i++){
    for(int j = 0; j < G[i].size(); j++)
      if(G[i][j] == idA)
        G[i].erase(G[i].begin() + j);
  }
}

std::vector<int>* Graph::Meeting(std::vector<int> *G){
  if(G->empty())
    return _order;

  std::vector<int> noincoming;

  for(int i = 0; i < V; i++){
    if(_adj[i].size() == 0)
      noincoming.push_back(i);
  }

  int temp = noincoming.back();
  noincoming.pop_back();

  _order->push_back(temp);
  deleteNode(G, temp);
  Meeting(G);
   
  return nullptr;
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
    G->DFS(idA);
    return G->min;
}
