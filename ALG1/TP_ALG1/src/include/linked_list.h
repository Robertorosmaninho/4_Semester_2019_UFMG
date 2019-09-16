#ifndef TP_ALG1_INCLUDE_LINKED_LIST_H
#define TP_ALG1_INCLUDE_LINKED_LIST_H

#include <iostream>

class Node{
private:
 int _id, _age;
 Node *_next;

public:
  Node(int id, int age) : _id(id), _age(age), *_next(nullptr) {};
  ~Node();
}


class LinkedList{
private:
  Node* _first;
  Node* _last;
  int _size;

public:
  LinkedList();
  ~LinkedList();
  
  void insert(int id, int age);
  void erase(int id);
  int get_age(int id); //Check if is usefull
  bool is_empty();
};

#endif
