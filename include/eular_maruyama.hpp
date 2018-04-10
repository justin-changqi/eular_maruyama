#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <random>

class EulerMaruyama
{
public:
  EulerMaruyama( double today_stock_price,
                 int strike_e,
                 double time_to_expiry,
                 double volatility,
                 double risk_free_interest_rate,
                 int number_of_sample_data);
  ~EulerMaruyama();
  void generateW();

private:
  double s0;
  int E;
  double T;
  double sigma;
  double r;
  int N;
  double dt;
  std::vector<double> w;
};
