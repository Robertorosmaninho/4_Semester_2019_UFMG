#ifndef GREEDY_H
#define GREEDY_H

#include <map>

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

class Greedy{
private:
  int _N, _M; //max_Cash and #Islands
  std::map<int, int, classcomp> _islands, _sorted; //points, cost  |  cost/points, cost
  int *_trip = nullptr;
  int _days = 0;
  int _total_points = 0;

public:
  Greedy(int N, int M);
  ~Greedy();

  void set_islands(std::map<int, int, classcomp> island);
  void set_cost_benefit();
  int  get_days();
  int  get_total_points();
};

#endif
