#include "include/lib.h"
#include <iostream>  

Lib::Lib(int N, int M) : _N(N), _M(M) {} 

Lib::~Lib() = default;


void Lib::set_islands(std::map<int, int, classcomp> island){
  _islands = island;
}

void Lib::set_cost_benefit(){
  int temp = 0;
  for(auto it = _islands.begin(); it != _islands.end(); ++it){
    temp = it->second / it->first; //25, 1000 -> 40, 1000
    _sorted[temp] =  it->second;
  }

  temp = _N; //Cash that I have
  _trip = new int[_M]; //Cost of islands
  auto it = _sorted.begin(); //Island

  while(temp > 0 && it != _sorted.end()){
    while(it->second > temp && it != _sorted.end()){
      it++;
 //   std::cout << it->second << "\n";
    }

    if(it == _sorted.end())
      break;

    if(it != _sorted.end()){
      temp -= it->second;
      _trip[_days] = it->second;
      _days++;
      _total_points += it->second / it->first;
    }
  }
}

int Lib::set_matrix(){
  int _matrix[_M][_N];
  int W[_M], Val[_M];
  int k = 0;
  for(auto it = _sorted.begin(); it != _sorted.end(); ++it, k++){
    W[k] = it->second;
    Val[k] = it->second / it->first;
  }


  for(int i = 0; i < _N; i++)
    _matrix[0][i] = 0;

  for(int j = 0; j < _M; j++)
    _matrix[j][0] = 0;

  for(int i = 1; i < _M; i++){
    for(int j = 0; j < _N; j++){
      if(W[i] > _N)
        _matrix[i][j] = _matrix[i-1][j];
      else
        _matrix[i][j] = std::max(_matrix[i-1][j], Val[i] + _matrix[i-1][_N - W[i]]);
    }
  }
//std::cout << _matrix[_M - 3, _N - 3] << "\n";
return _matrix[_M][_N];

}


int Lib::get_total_points(){
  return _total_points;
}

int Lib::get_days(){
  return _days;
}
