#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm> // max

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
  std::vector<double> AfixedStrike(bool call_option);
  std::vector<double> AfloatingStrike(bool call_option);
  std::vector<double> GfixedStrike(bool call_option);
  std::vector<double> GfloatingStrike(bool call_option);
  void makePayoffVector();

private:
  double s0, T, sigma, r, dt;
  int E, N;
  std::vector<double> w;
  std::vector<std::vector<double>> payoff_v;
};
