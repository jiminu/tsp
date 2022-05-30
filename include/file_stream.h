#pragma once

#include"city.h"
#include<string>
#include<vector>
#include<map>

using std::string;
using std::vector;
using std::map;
using std::pair;
using distance = float; // == typedef float distance

class FileStream {
private :
    // member variable
    vector<City> m_citiesVector;

public :
    // method
    FileStream();
    ~FileStream() {};
    
    void read(const string& fileName);
    void write(const string& fileName, const pair<float, vector<int>>& bestSolution, const vector<float>& info);
    
    vector<City>& get_cities();

private :
    // method
    City split_xy(const string& str);
};