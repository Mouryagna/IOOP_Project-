#ifndef REPORT_H
#define REPORT_H

#include"accounts.h"
#include<vector>
using namespace std;

class report{
    public:
        report();

        void displayAllAccounts();
        void showTotalBalence();
        void showAverageBalence();
        void showTopCustomers(int topN=3);
        void showLowBalenceAccounts(double limit);
        void transactionReport();

};



#endif