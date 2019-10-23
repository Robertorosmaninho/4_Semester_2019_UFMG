#ifndef GREEDY_H
#define GREEDY_H

#include <map>

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

class Lib{
private:
  int _N, _M; //max_Cash and #Islands
  std::map<int, int, classcomp> _islands, _sorted; //points, cost  |  cost/points, cost
  int *_trip = nullptr;
  int _days = 0;
  int _total_points = 0;
  int _days_pd = 0;
  int _total_points_pd = 0;

public:
  Lib(int N, int M);
  ~Lib();

  void set_islands(std::map<int, int, classcomp> island);
  void set_cost_benefit(); //Greedy
  void  set_matrix(); //PD
  int  get_days();
  int  get_total_points();
  int  get_days_pd();
  int  get_total_points_pd();
};

#endif