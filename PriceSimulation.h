//
// Created by Mengxiao Li on 10/21/19.
// Using drift model to simulate the price movement of the option underlying


#ifndef PROJECT_1_PRICESIMULATION_H
#define PROJECT_1_PRICESIMULATION_H
#include <vector>
using namespace std;

class PriceSimulation {
private:
    double T;//
    double S0;
    double mu;
    double sig;
    double r;
    double n;
    vector<double> price;
    vector<double> Z;
public:
    PriceSimulation();
    PriceSimulation(double T, double s, double mu, double sig, double r, double n);
    ~PriceSimulation();

    vector<double> calculate();
//    vector<double> getPriceVector();
};


#endif //PROJECT_1_PRICESIMULATION_H
