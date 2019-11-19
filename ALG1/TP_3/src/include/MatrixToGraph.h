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
  int _number, _line, _column;
public:
  Node( int number, int line, int column) : _number(number), _line(line),
                                            _column(column) {}
  ~Node() = default;

  /*int get_id(){ return _id; }*/
  int get_number(){ return _number; }
  int get_line(){ return _line; }
  int get_column(){ return _column; }
};

class MatrixToGraph {
private:
  int block_column, block_line;
  std::vector<Node> nodes;
  std::vector<Node>* _graph;

public:
  MatrixToGraph(int V, int I, int J, std::vector<int>* matrix);
  ~MatrixToGraph();

  bool verify_line(int line);
  bool verify_column(int column);
  bool verify_block(std::vector<int>* block);

  bool verify(int V, int number);

  bool verify_all();
};


#endif //UNTITLED_MATRIXTOGRAPH_H
