//
// Created by Mengxiao Li on 10/21/19.
//

#include "DeltaHedge.h"
#include "BS.h"

DeltaHedge::DeltaHedge() {}
DeltaHedge::~DeltaHedge() {}

DeltaHedge::DeltaHedge(vector<BS> dh)
{
    DH = dh;
}

double DeltaHedge::calculateHedgingError()
{
    int n = DH.size();
    double T = DH[0].getter()[0];
    double dt = T/n;
    vector<double> hedgingShares;
    vector<double> stockPrice;
    vector<double> r;//interest rate
    for (int i =0;i<n;i++)
    {
        hedgingShares.push_back(DH[i].calculateDelta());

//        cout << "delta is" << hedgingShares[i] << endl;
        stockPrice.push_back(DH[i].getter()[2]);
//        cout << "stockprice is" << stockPrice[i] << endl;
        r.push_back(DH[i].getter()[1]);
//        cout << "interest is"<< r[i] << endl;
    }
    vector<double> V = calculatePrice();
    vector<double> B;
    vector<double> HedgingError;

    B.push_back(V[0] - stockPrice[0]*hedgingShares[0]);
    HedgingError.push_back(0);
    for (int i = 1; i<n; i++){
        B.push_back(hedgingShares[i-1]*stockPrice[i] + B[i-1]*exp(r[i-1]*dt)- hedgingShares[i]*stockPrice[i]);
        HedgingError.push_back(hedgingShares[i-1]*stockPrice[i]+B[i-1]*exp(r[i-1]*dt)-V[i]);
    }
    return HedgingError[n-1];
}
vector<double> DeltaHedge::calculatePrice()
{
    vector<double> price;
    for(int i=0;i<DH.size();i++){
        price.push_back(DH[i].calculateValue());
    }
    return price;
}