#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm> // max
#include <chrono>

class EulerMaruyama
{
public:
  EulerMaruyama( double today_stock_price,
                 int strike_e,
                 double time_to_expiry,
                 double volatility,
                 double risk_free_interest_rate,
                 int number_of_simulation,
                 int number_of_sample_data);
  ~EulerMaruyama();
  void generateW();
  double AfixedStrike(bool call_option);
  double AfloatingStrike(bool call_option);
  double GfixedStrike(bool call_option);
  double GfloatingStrike(bool call_option);
  void makePayoffVector();
  void payoffsFunctionVerify();
  double getRiskNeualDensityQ(double payoff);
  void runSimulation();
  void showSimResult();

private:
  double s0, T, sigma, r, dt, st_mean, st_ln_mean, payoff_wight;
  double sim_result_v[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
  int E, N, N_sim;
  std::vector<double> w;
  std::vector<double> payoff_v;
};
