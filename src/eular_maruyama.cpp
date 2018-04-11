#include "eular_maruyama.hpp"


EulerMaruyama::EulerMaruyama( double today_stock_price,
                              int strike_e,
                              double time_to_expiry,
                              double volatility,
                              double risk_free_interest_rate,
                              int number_of_sample_data)
{
  this->s0 = today_stock_price;
  this->E = strike_e;
  this->T = time_to_expiry;
  this->sigma = volatility;
  this->r = risk_free_interest_rate;
  this->N = number_of_sample_data;
  this->dt =   this->T / (double)this->N;
}

EulerMaruyama::~EulerMaruyama()
{

}

void EulerMaruyama::generateW()
{
  std::default_random_engine generator(time(0));
  std::normal_distribution<double> distribution(0, 1.0);
  this->w.clear();
  this->w.push_back(this->s0);
  for(int i=1; i<this->N; i++)
  {
    double z = distribution(generator);
    // std::cout << z << std::endl;
    double s = w[i-1] + (this->r*w[i-1]*this->dt) + (this->sigma*w[i-1]*z*sqrt(this->dt));
    this->w.push_back(s);
  }
  for(int i=0; i<this->w.size(); i++)
  {
    std::cout << this->w[i] << ", ";
  }
  std::cout << std::endl;
}

std::vector<double> EulerMaruyama::AfixedStrike(bool call_option)
{
  std::vector<double> result;
  for (int i=0; i<this->N; i++)
  {
    // result.push_back(std::max(this->st_mean - this->E, 0.0));
    // std::cout << std::max( - this->E, 0.0) << ", ";
  }
  std::cout << std::endl;
  return result;
}

std::vector<double> EulerMaruyama::AfloatingStrike(bool call_option)
{

}

std::vector<double> EulerMaruyama::GfixedStrike(bool call_option)
{

}

std::vector<double> EulerMaruyama::GfloatingStrike(bool call_option)
{

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
  EulerMaruyama eular_maruyama = EulerMaruyama(100, 100, 1, 0.2, 0.05, 10);
  eular_maruyama.generateW();
  eular_maruyama.AfixedStrike(true);
  return 0;
}
