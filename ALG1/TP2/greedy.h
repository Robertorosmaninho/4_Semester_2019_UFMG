#ifndef GREEDY_H
#define GREEDY_H

#include <vector>

class Greedy{
private:
  int _N, _M; //max_Cash and #Islands
  std::map<int, int> _islands, _sorted_array; //points, cost
  int *_trip = nullptr;
  int _days = 0;
  int _total_points = 0;

public:
  Greedy(int N, int M);
  ~Greedy();
  
  void set_islands(std::map<int, int> island);
  void set_cost_benefit();
  int  get_days();
  int  get_total_points();
};

#endif
