#include "include/lib.h"
#include <iostream>  
#include <vector>

Lib::Lib(int N, int M) : _N(N), _M(M) {} 

Lib::~Lib() = default;


void Lib::set_islands(std::map<int, int, classcomp> *island){
  _islands = *island;
}

void Lib::set_cost_benefit(){
  int temp = 0;
  for(auto it = _islands.begin(); it != _islands.end(); it++){
    temp = it->first / it->second; //1000, 25 -> 40, 1000
    int value = it->first;
    _sorted[temp] = value;
   // std::cout << it->first << " " << it->second << "\n";
  }
 // std::cout << _islands.size() << "\n";
 // std::cout << _sorted.size() << "\n";
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
      _total_points += _islands[it->second];
    }
  }
}

void Lib::set_matrix(int N, int M){
  std::vector<int> W, Val;
  std::vector<std::vector<int>> _matrix = std::vector<std::vector<int>>(M+1);
  for(int i = 0; i < M+1; i++)
    _matrix[i] = std::vector<int>(N+1);

  int k = 0;
  for(auto it = _sorted.begin(); it != _sorted.end(); ++it, k++){
    W.push_back(it->second);
    Val.push_back(_islands[it->second]);
  }

  for(int i = 0; i <= M; i++){
    for(int j = 0; j <= N; j++){
      if(i == 0 || j == 0)
        _matrix[i][j] = 0; 
      else if(W[i-1] > j)
        _matrix[i][j] = _matrix[i-1][j];
      else
        _matrix[i][j] = std::max(_matrix[i-1][j], Val[i-1] + _matrix[i-1][j - W[i-1]]);
    }
  }

  _total_points_pd = _matrix[M][N];

  int i = M;
  int j = N;
  while(i >= 1 && j >= 0){
    if(_matrix[i][j] > _matrix[i-1][j]){
      _days_pd++;
      j = j - W[i-1];
      i--;
    }else{
      i--;
    }
  }
}

int Lib::get_total_points(){
  return _total_points;
}

int Lib::get_days(){
  return _days;
}

int Lib::get_days_pd(){
  return _days_pd;
}

int Lib::get_total_points_pd(){
  return _total_points_pd;
}
