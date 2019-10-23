#include <iostream>
#include <boost/date_time.hpp>
#include "BS.h"
#include "DeltaHedge.h"
#include "PriceSimulation.h"

using namespace std;
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

bool helper1(string st)
{
    if (st.length() == 10){
        return true;
    } else {
        return false;
    }
}


double helper2(string cp){
    if (cp == "C"){
        return 0;
    } else {
        return 1;
    }
}






int main() {
//    BS c1(0.210, 0.0019, 532.44, 500, 0.257, 0, 0);
//    cout << c1.calculateDelta() << endl;
//    BS c2(0.416,0.02, 36, 40, 0.3, 0,1);
//    cout << c2.calculateValue() << endl;
//    cout << c1.calculateValue() << endl;
//    BS c3(0.1295,0.025, 15248, 15000, 0,0);
//    cout << c3.calculateImpliedVolatility(640) << endl;
    vector<PriceSimulation> PS;

    //part I
    //simulate 1000 sample paths of price movements
    for (int i = 0; i<1000; i++){
        PriceSimulation p(0.4, 100, 0.05, 0.24, 0.025,100);
        PS.push_back(p);
    }


    //get the price movement vector data for 1000 paths
    vector<vector<double>> data1;
    for (int i = 0;i<1000;i++){
        data1.push_back(PS[i].calculate());
    }

    vector<DeltaHedge> dh;
    for (int i = 0; i< 1000;i++){
        int n = data1[i].size();
        vector<BS> bs;
        for (int j = 0; j<n;j++){
            double price1 = data1[i][j];
            double dt = 0.4/(n-1);
//            cout << price1 << endl;
            bs.push_back(BS(0.4 - j*dt , 0.025, price1, 105, 0.24, 0, 0));
        }
        dh.push_back(bs);
    }

    vector<double> hedgingError;
    vector<vector<double>> callOptionPrice;
    for (int i=0; i<dh.size(); i++){
        hedgingError.push_back(dh[i].calculateHedgingError());
        callOptionPrice.push_back(dh[i].calculatePrice());
//        cout << hedgingError[i] << endl;
//        cout << callOptionPrice[i][0] << callOptionPrice[i][99]<< endl;
    }
    ofstream result1 ("result1.csv");
    result1 << "Hedging error" << endl;
    for (int i = 0;  i<hedgingError.size(); i++){
        result1 << hedgingError[i] << endl;
    }

    ofstream result2 ("result2.csv");
    for (int j = 0; j<100; j++){
        result2 << "call option price" + to_string(j) << "," << "stockprice"+to_string(j) << endl;
        for (int i = 0 ; i < 100 ; i++){
            result2 << callOptionPrice[j][i] << "," << data1[j][i] << endl;
        }
    }





    //part II
    //read in data
    ifstream interest;
    vector<date> interest_date;
    vector<double> interest_rate;
    interest.open("interest.csv");
    //cout << interest.is_open() <<endl;
    string m;
    string ir;
    while (interest.good())
    {
        getline(interest, m, ',');
        getline(interest, ir, '\n');
        if (helper1(m) == true)
            //check if the header is parsed already
        {
            interest_date.push_back(from_simple_string(m));// Converting Simple Format (YYYY-MM-DD) String to date object
            interest_rate.push_back(stod(ir)/100);//convert string to double and push to rate vector
        }
    }
    //cout << interest_date[0] << from_simple_string("2011-01-03") <<endl;
    interest.close();

    ifstream stock;
    vector<date> stock_date;
    vector<double> stock_price;
    stock.open("sec_GOOG.csv");
    //cout << stock.is_open() <<endl;
    string d;
    string pr;
    while (stock.good())
    {
        getline(stock, d, ',');
        getline(stock, pr, '\n');
        if (helper1(d) == true)
            //check if the header is parsed already
        {
            stock_date.push_back(from_simple_string(d));// Converting Simple Format (YYYY-MM-DD) String to date object
            stock_price.push_back(stod(pr));//convert string to double and push to rate vector
        }
    }
//    cout  << (stock_date == interest_date) <<endl;
    stock.close();


    ifstream option;
    vector<date> option_date;
    vector<date> option_exdate;
    vector<double> option_cp;
    vector<double> option_K;
    vector<double> option_V;
    option.open("op_GOOG.csv");
    //cout << option.is_open() <<endl;
    string od;
    string oxd;
    string cp;
    string k;
    string Best_bid;
    string Best_ask;
    while (option.good())
    {
        getline(option, od, ',');
        getline(option, oxd, ',');
        getline(option, cp, ',');
        getline(option, k, ',');
        getline(option, Best_bid, ',');
        getline(option, Best_ask, '\n');
        if (helper1(od) == true)
            //check if the header is parsed already
        {
            option_date.push_back(from_simple_string(od));// Converting Simple Format (YYYY-MM-DD) String to date object
            option_exdate.push_back(from_simple_string(oxd));
            option_cp.push_back(helper2(cp));//convert string to double and push to rate vector
            option_K.push_back(stod(k));
            option_V.push_back(0.5*(stod(Best_ask)+stod(Best_bid)));
        }
    }
//    cout <<option_date[0] << option_V[0]  << option_cp[14] <<endl;
    //2011-Jan-03 63.35 1
    option.close();

    //specify inputs
    //
    string t0, tn, T;
    double K;
    double pc;
    t0 = "2011-07-05";
    tn = "2011-07-29";
    T = "2011-09-17";
    K = 500;
    pc = 0;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    for(int i = 0; i< 252; i++){
        if (interest_date[i] == from_simple_string(t0)){
            n1 = i;
        }
        if (interest_date[i] == from_simple_string(tn)){
            n2 = i;
        }
        if (i >= 1 && interest_date[i] > from_simple_string(T) && interest_date[i-1] < from_simple_string(T)){
            n3=i;
        }
    }
    double time_to_maturity = n3 - n1;
    time_to_maturity /= 252;
//    cout << time_to_maturity << endl;

    int n = n2-n1+1;//business day between start and end time
//    cout << n <<","<< n1<<"," << n2 << endl;

    //vectors that represent the desired quantities
    vector<date> Date;
    vector<double> stockPrice;
    vector<double> optionPrice;
    vector<double> impliedVolatility;
    vector<double> optionDelta;
    vector<double> HedgingError;
    vector<double> PNL;
    for (int i =0; i<n ; i++) {
        Date.push_back(interest_date[i + n1]);
        stockPrice.push_back(stock_price[i + n1]);
        for (int j = 0; j < option_date.size(); j++) {
            if (option_cp[j] == pc && option_date[j] == Date[i] && option_K[j] == K &&
                option_exdate[j] == from_simple_string(T)) {
                optionPrice.push_back(option_V[j]);
                break;
            }
        }
    }
    for (int i =0; i<n ; i++) {
        cout << optionPrice[i] << endl;
    }
    double increment = 1.0/252.0;
//    cout << increment << endl;

    //
    for (int i =0; i<n ; i++) {
        double increment = 1.0/252.0;
        double r = interest_rate[i+n1];
        BS b1(time_to_maturity-increment*i, r, stockPrice[i], K, 0, pc);
        double imp_vol = b1.calculateImpliedVolatility(optionPrice[i]);
        impliedVolatility.push_back(imp_vol);
        BS b2(time_to_maturity-increment*i, r, stockPrice[i],  K, imp_vol,0, pc);

        optionDelta.push_back(b2.calculateDelta());
        vector<BS> dh1;
        for (int k =0; k<impliedVolatility.size();k++){
            dh1.push_back(BS(time_to_maturity - increment*k, interest_rate[k+n1], stockPrice[k], K, impliedVolatility[k], 0, pc));
        }
        HedgingError.push_back(DeltaHedge(dh1).calculateHedgingError());
        PNL.push_back(optionPrice[0] - optionPrice[i]);
    }

    //cout << n <<  endl;

    //write output table
    ofstream result3 ("result3.csv");
    result3<<"Results"<< endl;            //creating headers in file
    result3<<"Start date ,"<< t0 <<endl;
    result3<<"End date ,"<< tn <<endl;
    result3<<"Option Type ,"<< pc <<endl;
    result3<<"Expiry date ,"<< T <<endl;
    result3<<"Strike price ,"<< K <<endl;
    result3<<endl;
    result3<<"\nDate"<<","<<"Stock Price"<<","<<"Option Price"<<","<<"Implied Volatility"<<","<<"Delta"<<","<<"Cumulative hedging error"<<","<<"PNL"<<endl;
    for (int i = 0; i<n; i++){
        result3<<Date[i] << "," << stockPrice[i] << "," << optionPrice[i]<<"," << impliedVolatility[i] << "," << optionDelta[i] << "," << HedgingError[i] << "," << PNL[i]<<endl;
    }



    return 1;
}

