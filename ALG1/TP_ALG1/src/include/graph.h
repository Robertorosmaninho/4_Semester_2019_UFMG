#ifndef TP_ALG1_INCLUDE_GRAPH_H
#define TP_ALG1_INCLUDE_GRAPH_H

#include <vector>

class Graph{
private:
  int V, A;
  std::vector<int> *_adj;
  int *_age;
  std::vector<int> _visited;
  std::vector<int>* _order;
public:
  Graph(int V, int A);
  ~Graph();
 
  void addNode(int id, int age);
  void addEdge(int idA, int idB);
  bool swapEdge(int idA, int idB);
  bool DFS(int idA);
  void deleteNode(std::vector<int> *G,int idA);
  bool hasCicle(int idA); //Roda uma DFS no idA, se encontrar o idA return 1
  std::vector<int>* Meeting(std::vector<int> *G);
  int Commander(int idA);
};


#endif
