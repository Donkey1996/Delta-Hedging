//
// Created by Mengxiao Li on 10/21/19.
//Class for options pricing

#ifndef PROJECT_1_BS_H
#define PROJECT_1_BS_H
#include <math.h>
#include <vector>
using namespace std;

class BS{
private:
    double T; //
    double r; //risk_free_rate
    double S; //stock price
    double K; //strike
    double sig; //volatility
    double d; //dividend
    double put_call; //0->call, 1->put

public:
    BS();
    BS(double T, double r, double S, double K, double sig, double d, double pc);//initialize BS object
    BS(double T, double r, double S, double K, double d, double pc);
    ~BS();
    double calculateValue();//calculate the option price using black scholes equations
    double calculateDelta();//calculate the option delta dv/ds
    double calculateVega();
    vector<double> getter();//get option parameters
    double calculateImpliedVolatility(double marketPrice);
};

#endif //PROJECT_1_BS_H
