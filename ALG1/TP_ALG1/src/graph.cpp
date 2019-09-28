#include "include/graph.h"
#include <iostream>

Graph::Graph(int V, int A){
  this->V = V;
  this->A = A;
  this->_adj = new std::vector<int>[V];
  this->_age = new int[V];
  this->_visited = std::vector<int>(V, 0);
  this->_cycle = 0;
}

Graph::~Graph(){
  //delete this->_adj;
  //delete this->_age;
}

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

  //Verifica se o index requisitado é menor que o tamanho do vetor
  if(idA >= V || idB >= V){
    std::cout << "Invalid index!\n";
    return -1;
  }

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
  //Se gerou, desfaz a troca e returna falso
  if(idB == this->_adj[idA].back()){
    this->_adj[idB].pop_back();
    this->_adj[idA].push_back(idB);
  }else if(idA == _adj[idB].back()){
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

void Graph::BuildStack(std::stack<int>* order,int idA){
  //Marca o nó como visitado
  _visited[idA] = 1;
  
  //Chama BuildStack pra todos os vertices que idA aponta
  for(int i = 0; i < _adj[idA].size(); i++){
    //std::cout << "**\n"; 
    if(!_visited[i])
      BuildStack(order,i);
  }

  //Add idA na pilha 
  order->push(idA);
}

std::stack<int>* Graph::Meeting(){
  //Stack que contera a ordem topologica
  std::stack<int> *order = new std::stack<int>;
  reset_visited();

  //Para cada nó não visitada visitado, visita todos seus vizinhos em ordem de
  //profundidade
  for(int i = 0; i < V; i++){
    if(!_visited[i])
      BuildStack(order,i);
  }
  return order;
}

int Graph::Commander(int idA){
  //Flags só para deixar o codigo mais limpo
  int size[V];
  int temp = -1;

  //Vetor com os tamanhos originais para não iterarmos a mais. 
  //Ex: aresta já invertida ter que ser invertida novamente
  for(int i = 0; i < V; i++){
    size[i] = _adj[i].size();
  }

  //vetor com as arestas invertidas
  std::vector<int> *reverse = new std::vector<int>[V];

  //Inverte todas as arestas do grafo
  for(int i = 0; i < V; i++){
    for(int j = 0 ; j < size[i]; j++){
       temp = _adj[i][j];
       reverse[temp].push_back(i); 
    }
  }

  //Cria um grafo com as arestas inversas para rodar a DFS
  Graph G = Graph(V,A);
  G._adj = reverse;
  G._age = this->_age;

  //Busca em profundidade para descobrir o nó com menor idade
  if(reverse[idA].empty()){
   // delete reverse;
    return -1;
  }else{
    G.DFS(idA);
  }

 // delete reverse;
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
