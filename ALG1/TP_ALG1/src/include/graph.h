#ifndef TP_ALG1_INCLUDE_GRAPH_H
#define TP_ALG1_INCLUDE_GRAPH_H

#include <vector>
#include <stack> 

class Graph{
private:
  int V, A;
  std::vector<int> *_adj;
  std::vector<int> *_reverse_adj;
  int *_age;
  std::vector<int> _visited;
  int _min = 100;
  int _cycle = 0;
public:
  Graph(int V, int A);
  ~Graph();
 
  void addNode(int id, int age);
  void addEdge(int idA, int idB);
  int swap(int idA, int idB);
  bool swapEdge(int idA, int idB);
  void reset_visited();
  bool DFS(int idA);
  void BuildStack(std::stack<int>* order, int idA);
  bool hasCicle(int idA); //Roda uma DFS no idA, se encontrar o idA return 1
  std::stack<int>* Meeting();
  std::vector<int>* getList();
  int Commander(int idA);
  void print();
};


#endif
