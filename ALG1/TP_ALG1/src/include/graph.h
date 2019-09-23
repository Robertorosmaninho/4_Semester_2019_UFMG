#ifndef TP_ALG1_INCLUDE_GRAPH_H
#define TP_ALG1_INCLUDE_GRAPH_H

#include <vector>

class Graph{
private:
  int V, A;
  std::vector<int> *_adj;
  int *_age;
  std::vector<int> _visited;
  std::vector<int> _order;
  int _min = 100;
  int _cycle = 0;
public:
  Graph(int V, int A);
  ~Graph();
 
  void addNode(int id, int age);
  void addEdge(int idA, int idB);
  int swap(int idA, int idB, Graph *G);
  bool swapEdge(int idA, int idB);
  void reset_visited();
  bool DFS(int idA);
  void deleteNode(std::vector<int> *G,int idA);
  bool hasCicle(int idA); //Roda uma DFS no idA, se encontrar o idA return 1
  std::vector<int> Meeting(std::vector<int> *G);
  std::vector<int>* getList();
  int Commander(int idA);
};


#endif
