#include "include/greedy.h"
#include <iostream>  

Greedy::Greedy(int N, int M) : _N(N), _M(M) {} 

Greedy::~Greedy() = default;


void Greedy::set_islands(std::map<int, int, classcomp> island){
  _islands = island;
}

void Greedy::set_cost_benefit(){
  int temp = 0;
  for(auto it = _islands.begin(); it != _islands.end(); ++it){
    temp = it->second / it->first; //25, 1000 -> 40, 1000
    _sorted[temp] =  it->second;
  }

//  for(auto it = _sorted.begin(); it != _sorted.end(); ++it)
//    std::cout << it->first << " - " << it->second << "\n";

  temp = _N; //Cash that I have
  _trip = new int[_M]; //Cost of islands
  auto it = _sorted.begin(); //Island

  while(temp > 0){
    while(it->second > temp && it != _sorted.end()){
      it++;
    std::cout << it->second << "\n";
    }

    if(it == _sorted.end())
      break;


    if(it != _sorted.end()){
//      std::cout << "Days: " << _days << "\nTotal Points: " << _total_points << "\n Cost: " << it->second << "\n";
      temp -= it->second;
      _trip[_days] = it->second;
      _days++;
      _total_points += it->second / it->first;
    }
  }
}

int Greedy::get_total_points(){
  return _total_points;
}

int Greedy::get_days(){
  return _days;
}
