//
// Created by Mengxiao Li on 10/21/19.
// implementation of delta heding strategies
// Given time series of underlying price, calculate the hedging positions; cumulative hedging error

#ifndef PROJECT_1_DELTAHEDGE_H
#define PROJECT_1_DELTAHEDGE_H
#include <iostream>
#include <vector>
#include "BS.h"
using namespace std;


class DeltaHedge{
private:
    vector<BS> DH;//vector of BS objects, used to calculate the hedging positions and error
public:
    DeltaHedge();
    DeltaHedge(vector<BS> dh); //initialize
    ~DeltaHedge();
    double calculateHedgingError();//calculating hedging error
    vector<double> calculatePrice();
};


#endif //PROJECT_1_DELTAHEDGE_H
