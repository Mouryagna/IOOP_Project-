#ifndef SEARCH_H
#define SEARCH_H
#include<iostream>
#include<fstream>
#include"accounts.h"
using namespace std;

class Search{
    public:
    void SearchById(int id);
    void SearchByName(string n);
};
#endif
