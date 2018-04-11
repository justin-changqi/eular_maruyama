#include "eular_maruyama.hpp"


EulerMaruyama::EulerMaruyama( double today_stock_price,
                              int strike_e,
                              double time_to_expiry,
                              double volatility,
                              double risk_free_interest_rate,
                              int number_of_simulation,
                              int number_of_sample_data)
{
  this->s0 = today_stock_price;
  this->E = strike_e;
  this->T = time_to_expiry;
  this->sigma = volatility;
  this->r = risk_free_interest_rate;
  this->N_sim = number_of_simulation;
  this->N = number_of_sample_data;
  this->dt =   this->T / (double)this->N;
}

EulerMaruyama::~EulerMaruyama()
{

}

void EulerMaruyama::generateW()
{
  std::normal_distribution<double> distribution(0, 1.0);
  this->w.clear();
  this->w.push_back(this->s0);
  this->st_mean = 0;
  this->st_log_mean = 0;
  for(int i=1; i<this->N; i++)
  {
    std::default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    double z = distribution(generator);
    // std::cout << z << std::endl;
    double s = w[i-1] + (this->r*w[i-1]*this->dt) + (this->sigma*w[i-1]*z*sqrt(this->dt));
    this->w.push_back(s);
    this->st_mean += s;
    this->st_log_mean += log10(s);
  }
  this->st_mean /= (double)this->N;
  this->st_log_mean /= (double)this->N;
  // // Print
  // std::cout << this->st_mean << std::endl;
  // for(int i=0; i<this->w.size(); i++)
  // {
  //   std::cout << this->w[i] << ", ";
  // }
  // std::cout << std::endl;
}

double EulerMaruyama::AfixedStrike(bool call_option)
{
  double payoff = 0;
  if (call_option)
  {
    payoff = std::max(this->st_mean - this->E, 0.0);
  }
  else
  {
    payoff = std::max(this->E - this->st_mean, 0.0);
  }
  // std::cout << payoff << std::endl;
  return payoff;
}

double EulerMaruyama::AfloatingStrike(bool call_option)
{
  double payoff = 0;
  if (call_option)
  {
    payoff = std::max(this->w[this->w.size()-1] - this->st_mean, 0.0);
  }
  else
  {
    payoff = std::max(this->st_mean - this->w[this->w.size()-1], 0.0);
  }
  // std::cout << payoff << std::endl;
  return payoff;
}

double EulerMaruyama::GfixedStrike(bool call_option)
{
  double payoff = 0;
  if (call_option)
  {
    payoff = std::max( exp(this->st_log_mean) - this->E, 0.0);
  }
  else
  {
    payoff = std::max(this->E - exp(this->st_log_mean) , 0.0);
  }
  // std::cout << payoff << std::endl;
  return payoff;
}

double EulerMaruyama::GfloatingStrike(bool call_option)
{
  double payoff = 0;
  if (call_option)
  {
    payoff = std::max(  this->w[this->w.size()-1] - exp(this->st_log_mean), 0.0);
  }
  else
  {
    payoff = std::max( exp(this->st_log_mean) - this->w[this->w.size()-1] , 0.0);
  }
  // std::cout << payoff << std::endl;
  return payoff;
}

void EulerMaruyama::makePayoffVector()
{
  this->payoff_v.push_back(this->AfixedStrike(true));
  this->payoff_v.push_back(this->AfloatingStrike(true));
  this->payoff_v.push_back(this->GfixedStrike(true));
  this->payoff_v.push_back(this->GfloatingStrike(true));
  this->payoff_v.push_back(this->AfixedStrike(false));
  this->payoff_v.push_back(this->AfloatingStrike(false));
  this->payoff_v.push_back(this->GfixedStrike(false));
  this->payoff_v.push_back(this->GfloatingStrike(false));
}

int main() {
  EulerMaruyama eular_maruyama = EulerMaruyama(100, 100, 1, 0.2, 0.05, 10000, 10);
  eular_maruyama.generateW();
  std::cout  << eular_maruyama.AfixedStrike(true) << std::endl;
  std::cout  << eular_maruyama.AfixedStrike(false) << std::endl;
  std::cout  << eular_maruyama.AfloatingStrike(true) << std::endl;
  std::cout  << eular_maruyama.AfloatingStrike(false) << std::endl;
  std::cout  << eular_maruyama.GfixedStrike(true) << std::endl;
  std::cout  << eular_maruyama.GfixedStrike(false) << std::endl;
  std::cout  << eular_maruyama.GfloatingStrike(true) << std::endl;
  std::cout  << eular_maruyama.GfloatingStrike(false) << std::endl;
  return 0;
}
