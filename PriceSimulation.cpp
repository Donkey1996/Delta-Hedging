//
// Created by Mengxiao Li on 10/21/19.
//
//#include <boost/random/random_number_generator.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include "PriceSimulation.h"
using namespace std;


boost::mt19937 rng(time(0));
boost::normal_distribution<> norm(0,1);
boost::variate_generator< boost::mt19937, boost::normal_distribution<>> rv(rng, norm);

vector<double> PriceSimulation::calculate()
{

    for (int i = 0; i<n; i++){
        Z.push_back(rv());
//        cout<< Z[i] << endl;
    }
    price.push_back(S0);
    double dt = T/n;
    for (int i = 1; i<n; i++){
        price.push_back(price[i-1]+price[i-1]*mu*dt+sig*price[i-1]*sqrt(dt)*Z[i-1]);
//        cout << price[i] << endl;
    }
    return price;
}
PriceSimulation::PriceSimulation(){}

PriceSimulation::PriceSimulation(double T, double s, double mu, double sig, double r, double n)
{
    this->T = T;
    this->S0 = s;
    this->mu = mu;
    this->sig = sig;
    this->r = r;
    this->n = n;
}
PriceSimulation::~PriceSimulation()
{}
//vector<double> PriceSimulation::getPriceVector()
//{
//    return price;
//}