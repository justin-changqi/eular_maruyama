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
  this->st_ln_mean = 0;
  for(int i=1; i<this->N; i++)
  {
    std::default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    double z = distribution(generator);
    // std::cout << z << std::endl;
    double s = w[i-1] + (this->r*w[i-1]*this->dt) + (this->sigma*w[i-1]*z*sqrt(this->dt));
    this->w.push_back(s);
    this->st_mean += s;
    this->st_ln_mean += log(s);
  }
  this->st_mean /= (double)this->N;
  this->st_ln_mean /= (double)this->N;
  this->payoff_wight = exp(-this->r);
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
    payoff = std::max( exp(this->st_ln_mean) - this->E, 0.0);
  }
  else
  {
    payoff = std::max(this->E - exp(this->st_ln_mean) , 0.0);
  }
  // std::cout << payoff << std::endl;
  return payoff;
}

double EulerMaruyama::GfloatingStrike(bool call_option)
{
  double payoff = 0;
  if (call_option)
  {
    payoff = std::max(  this->w[this->w.size()-1] - exp(this->st_ln_mean), 0.0);
  }
  else
  {
    payoff = std::max( exp(this->st_ln_mean) - this->w[this->w.size()-1] , 0.0);
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

void EulerMaruyama::payoffsFunctionVerify()
{
  this->generateW();
  std::cout  << "Call Option Arithmetic Fixed Strike: \t" << this->AfixedStrike(true) << std::endl;
  std::cout  << "Put Option Arithmetic Fixed Strike: \t" << this->AfixedStrike(false) << std::endl;
  std::cout  << "Call Option Arithmetic Floating Strike:\t" << this->AfloatingStrike(true) << std::endl;
  std::cout  << "Put Option Arithmetic Floating Strike: \t" << this->AfloatingStrike(false) << std::endl;
  std::cout  << "Call Option Geometric Fixed Strike: \t" << this->GfixedStrike(true) << std::endl;
  std::cout  << "Put Option Geometric Fixed Strike: \t" << this->GfixedStrike(false) << std::endl;
  std::cout  << "Call Option Geometric Floating Strike: \t" << this->GfloatingStrike(true) << std::endl;
  std::cout  << "Put Option Geometric Floating Strike: \t" << this->GfloatingStrike(false) << std::endl;
}

double EulerMaruyama::getRiskNeualDensityQ(double payoff)
{
  return payoff*this->payoff_wight;
}

void EulerMaruyama::runSimulation()
{

  for (int i=0; i<this->N_sim; i++)
  {
    this->generateW();
    this->sim_result_v[0] += this->getRiskNeualDensityQ(this->AfixedStrike(true));
    this->sim_result_v[1] += this->getRiskNeualDensityQ(this->AfixedStrike(false));
    this->sim_result_v[2] += this->getRiskNeualDensityQ(this->AfloatingStrike(true));
    this->sim_result_v[3] += this->getRiskNeualDensityQ(this->AfloatingStrike(false));
    this->sim_result_v[4] += this->getRiskNeualDensityQ(this->GfixedStrike(true));
    this->sim_result_v[5] += this->getRiskNeualDensityQ(this->GfixedStrike(false));
    this->sim_result_v[6] += this->getRiskNeualDensityQ(this->GfloatingStrike(true));
    this->sim_result_v[7] += this->getRiskNeualDensityQ(this->GfloatingStrike(false));
  }
  for (int i=0; i<8; i++)
  {
      this->sim_result_v[i] /= (double)this->N_sim;
  }
}

void EulerMaruyama::showSimResult()
{
  std::cout  << std::fixed << "Call Option Arithmetic Fixed Strike: \t"   << this->sim_result_v[0] << std::endl;
  std::cout  << std::fixed << "Put Option Arithmetic Fixed Strike: \t"    << this->sim_result_v[1] << std::endl;
  std::cout  << std::fixed << "Call Option Arithmetic Floating Strike:\t" << this->sim_result_v[2] << std::endl;
  std::cout  << std::fixed << "Put Option Arithmetic Floating Strike: \t" << this->sim_result_v[3] << std::endl;
  std::cout  << std::fixed << "Call Option Geometric Fixed Strike: \t"    << this->sim_result_v[4] << std::endl;
  std::cout  << std::fixed << "Put Option Geometric Fixed Strike: \t"     << this->sim_result_v[5] << std::endl;
  std::cout  << std::fixed << "Call Option Geometric Floating Strike: \t" << this->sim_result_v[6] << std::endl;
  std::cout  << std::fixed << "Put Option Geometric Floating Strike: \t"  << this->sim_result_v[7] << std::endl;
}

int main() {
  EulerMaruyama eular_maruyama_continuous = EulerMaruyama(100, 100, 1, 0.2, 0.05, 10000, 10000);
  EulerMaruyama eular_maruyama_discrete = EulerMaruyama(100, 100, 1, 0.2, 0.05, 10000, 100);
  // eular_maruyama.payoffsFunctionVerify();
  eular_maruyama_continuous.runSimulation();
  eular_maruyama_discrete.runSimulation();
  std::cout << "Continuous:" << std::endl;
  eular_maruyama_continuous.showSimResult();
  std::cout << "\nDiscrete:" << std::endl;
  eular_maruyama_discrete.showSimResult();
  return 0;
}
