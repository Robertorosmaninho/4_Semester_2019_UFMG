//
// Created by Roberto Rosmaninho on 17/11/19.
//

#ifndef UNTITLED_MATRIXTOGRAPH_H
#define UNTITLED_MATRIXTOGRAPH_H


#include <utility>
#include <vector>
#include <map>

class Node{
private:
  int _id, _number, _row, _column;
public:
  Node(int id, int number, int row, int column) : _id(id), _number(number),
                                                  _row(row), _column(column){}
  ~Node() = default;

  int get_id(){ return _id; }
  int get_number(){ return _number; }
  void set_number(int number) { _number = number; }
  int get_row(){ return _row; }
  int get_column(){ return _column; }
};

class MatrixToGraph {
private:
  int block_column, block_row;
  int V, _id = 0;
  std::vector<Node*> _nodes;
  std::vector<std::vector<Node*>> _graph;
  std::vector<std::vector<int>> _matrix;

public:
  MatrixToGraph(int V, int I, int J, std::vector<std::vector<int>> matrix);
  ~MatrixToGraph();

  void set_block();
  void set_row();
  void set_column();

  std::vector<std::vector<Node*>> get_graph(){ return _graph; }

  bool verify(int id, int number);
  bool assignNumber(int id, int number, Node* node);

  bool solveSudoku();
  Node* findUnsignedLocation();

  void print();
};


#endif //UNTITLED_MATRIXTOGRAPH_H
