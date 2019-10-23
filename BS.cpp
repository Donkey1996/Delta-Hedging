//
// Created by Mengxiao Li on 10/21/19.
//class for option pricing using black scholes model

#include <iostream>
#include <math.h>
#include <boost/math/distributions.hpp>
#include "BS.h"
using namespace std;

boost::math::normal_distribution<> N(0,1);

BS::BS()
{
}

BS::~BS(){

}

BS::BS(double T, double r, double S, double K, double sig, double d, double pc)
{
    this->T = T;
    this->r = r;
    this->S = S;
    this->K = K;
    this->sig = sig;
    this->d = d;
    this->put_call = pc;
}

double BS::calculateValue()
{
    double V;
    long double d1 = ((log(S/K)+(r-d+0.5*sig*sig)*T))/(sig*sqrt(T)); //normal distribution factor
    long double d2 = d1-sig*sqrt(T); //normal distribution factor
//    cout <<"d1"<< d1 <<"d2" <<d2 << endl;
    if (put_call == 0){
        V = S*exp(-d*T)*cdf(N,d1)-K*exp(-r*T)*cdf(N, d2);
    } else {
        V = -S*exp(-d*T)*cdf(N,-d1)+K*exp(-r*T)*cdf(N,-d2);
    }


    return V;
}



double BS::calculateDelta()
{
    double delta;
    long double d1 = ((log(S/K)+(r-d+0.5*sig*sig)*T))/(sig*sqrt(T)); //normal distribution factor
    //cout << d1  << endl;
    if (put_call == 0){
        delta = cdf(N,d1);
    } else {
        delta = cdf(N,d1)- 1;
    }
    return delta;
}

vector<double> BS::getter()
{
    vector<double> parameters;
    parameters.push_back(T);
    parameters.push_back(r);
    parameters.push_back(S);
    parameters.push_back(K);
    parameters.push_back(r);
    parameters.push_back(d);
    parameters.push_back(put_call);
    return parameters;
}
//calculate implied volatility using newton's method

double BS::calculateImpliedVolatility(double marketPrice)
{
    vector<double> price;
    vector<double> vol;
    vector<double> vega;
    vol.push_back(0.3);
//    cout << "market price" << marketPrice << endl;
    double K = this->K;
    double T = this->T;
    double r = this->r;
    double S = this->S;
    double pc = this->put_call;
    double d= this->d;
//    cout << K <<","<< T <<","<< r <<","<< S <<","<< pc<<","<<d<< endl;

    int i = 0;
    do{
        i++;
        double vol_0 = vol[i-1];
        BS bs(T, r, S,K, vol_0,d,pc);
        vega.push_back(bs.calculateVega());
        price.push_back(bs.calculateValue());

        double v = vol[i-1] - (price[i-1] - marketPrice)/vega[i-1];
        vol.push_back(v);

//        cout << bs.calculateVega() << endl;
//        cout << bs.calculateValue() << endl;
//        cout << "vol" << v << endl;
//        cout << i << endl;

    } while(abs(vol[i]-vol[i-1]) >= 0.0001 && i<= 100);

    return vol[i];
}

//double BS::Difference(double marketPrice, double guess){
//    BS b(T, r, S, K, guess, d, put_call);
//    return b.calculateValue() - marketPrice;
//}
//double BS::calculateImpliedVolatility(double marketPrice){
//    double m = 0.01;
//    double increment = 0.0001;
//    do{
//        m+=increment;
//    } while(abs(Difference(marketPrice, m)) >= 0.1);
//
//
//    return m;
//}
//double BS::calculateImpliedVolatility(double marketPrice)
//{
//    double low = 0.01;
//    double high = 1.0;
//    double guess;
//    int i = 0;
//    do{
//        guess = 0.5*(high+low);
//        BS bs_guess(T, r, S, K, guess, d, put_call);
//        BS bs_high(T, r, S, K, high, d, put_call);
//        BS bs_low(T, r, S, K, low, d, put_call);
//        double v_guess = bs_guess.calculateValue();
//        double v_high = bs_high.calculateValue();
//        double v_low = bs_low.calculateValue();
//
//        if (marketPrice-v_guess < 0.0){
//            high = guess;
//            cout << high << endl;
//
//        }else{
//            low = guess;
//            cout << low << endl;
//        }
//        i++;
//    }while(high-low > 0.0001 && i <= 100);
//
//    return guess;
//}
double BS::calculateVega(){
    long double d1 = ((log(S/K)+(r-d+0.5*sig*sig)*T))/(sig*sqrt(T)); //normal distribution factor
    return S*cdf(N, d1)*sqrt(T);
}
//constructor without initializing volatility
// to calculate implied volatility
BS::BS(double T, double r, double S, double K, double d, double pc)
{
    this->T = T;
    this->r = r;
    this->S = S;
    this->K = K;
    this->d = d;
    this->put_call = pc;

}