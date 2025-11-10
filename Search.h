#ifndef SEARCH_H
#define SEARCH_H
#include<iostream>
#include<fstream>
using namespace std;

class Search{
    public:
    bool SearchById(int id);
    bool SearchByName(string n);
};
#endif
