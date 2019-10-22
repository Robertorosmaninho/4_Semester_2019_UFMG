#include "include/lib.h"
#include <iostream>  
#include <vector>

Lib::Lib(int N, int M) : _N(N), _M(M) {} 

Lib::~Lib() = default;


void Lib::set_islands(std::vector<std::tuple<float, int, int>> island){
  _islands = island;
}

void Lib::set_greedy(){
  int temp = 0, i = 0;

 std::stable_sort(_islands.begin(), _islands.end());

  temp = _N; //Cash that I have


  while(temp > 0 && i < _islands.size()){
    while( std::get<1>(_islands[i]) > temp && i < _islands.size()){
      i++;
    }

    if(i >= _islands.size())
      break;
    // The money that i have - cost of the island
    temp -= std::get<1>(_islands[i]);

    _days++;
    _total_points += std::get<2>(_islands[i]);

  }
}

void Lib::set_dynamic_programming(int N, int M){
  std::vector<int> Cost, Points;
  std::vector<std::vector<int>> _matrix = std::vector<std::vector<int>>(M+1);
  for(int i = 0; i < M+1; i++)
    _matrix[i] = std::vector<int>(N+1);

  for(int i = 0, k = 0; i < _islands.size(); i++, k++){
    Cost.push_back(std::get<1>(_islands[i]));
    Points.push_back(std::get<2>(_islands[i]));
  }

  for(int i = 0; i <= M; i++){
    for(int j = 0; j <= N; j++){
      if(i == 0 || j == 0)
        _matrix[i][j] = 0; 
      else if(Cost[i-1] > j)
        _matrix[i][j] = _matrix[i-1][j];
      else
        _matrix[i][j] = std::max(_matrix[i-1][j], Points[i-1] + _matrix[i-1][j - Cost[i-1]]);
    }
  }

  _total_points_pd = _matrix[M][N];

  int i = M;
  int j = N;
  while(i >= 1 && j >= 0){
    if(_matrix[i][j] > _matrix[i-1][j]) {
      _days_pd++;
      j = j - Cost[i - 1];
    }
    i--;
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
