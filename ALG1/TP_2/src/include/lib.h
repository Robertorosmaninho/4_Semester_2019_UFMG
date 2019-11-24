#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <tuple>

class Lib{
private:
  int _N  = 0, _M = 0; //max_Cash and #Islands
  std::vector<std::tuple<float, int, int>> _islands; //cost/points, cost, points
  int _days = 0;
  int _total_points = 0;
  int _days_pd = 0;
  int _total_points_pd = 0;

public:
  Lib(int N, int M);
  ~Lib();

  void set_islands(std::vector<std::tuple<float, int, int>> island);
  void set_greedy(); //Greedy
  void set_dynamic_programming(int N, int M); //PD
  int  get_days();
  int  get_total_points();
  int  get_days_pd();
  int  get_total_points_pd();
};

#endif
