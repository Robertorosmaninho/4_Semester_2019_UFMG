#include "include/linked_list.h"

LinkedList::LinkedList(){ //Check if start with a node is better than this way.
  this->_first = nullptr;
  this->_size = 0;
}

LinkedList::~LinkedList(){
  Node* actual = nullptr;
  Node* temp = this->_first;
  while(temp != nullptr){
    actual = temp;
    temp -> actual->_next;
    delete actual;
  }
}

void LinkedList::insert(int id, int age){
  Node* A = new Node(id,age);

  if(_fisrt == nullptr){
    this->_first = A;
    this->_last = A;
  }else{
    this->_last->_next = A;
    this->last = A;
  }
  
  this->_size++;
}

void LinkedList::erase(int id){
  Node* actual = nullptr;
  Node* temp = this->_first;

  while(temp->_id != id){
    actual = temp;
    temp = temp->_next;
 }

  if(actual != nullptr){
    if(temp->_id == id){
      actual->_next = temp->_next;
      delete temp;
      this->_size--;
    }else{
      std::cout << "This element does'n exist!" << std::endl;
    }
  }else if(temp->_id == id){
    this->_first = temp->_next;
    delete temp;
    this->_size--;
  }else{
    std::cout << "This element does'n exist!" << std::endl;
  }
}

int LinkedList::get_age(int id){
  Node* temp = this->_first;
  
  while(temp != nullptr){
    if(temp->_id == id)
      return temp->_age;
    else
      temp = temp->_next;
  }

  std::cout << "This element doesn't exist!" << std::endl;
  return 0;
}

bool LinkedList::is_empty(){
  if(this->_first == nullptr)
    return true;
  else
    return false
}
