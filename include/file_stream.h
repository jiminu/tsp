#pragma once

#include"point.h"
#include<string>
#include<vector>
#include<map>

using std::string;
using std::vector;
using std::multimap;
using std::map;
using std::pair;
using distance = float; // == typedef float distance

class FileStream {
private :
    // member variable
    vector<Point> m_pointsVector;

public :
    // method
    FileStream();
    ~FileStream() {};
    
    void read_from_file(const string& fileName);
    void write_to_file(const string& fileName, const vector<Point>& nearPoints);
    
    vector<Point>& get_points();

private :
    // method
    Point split_xy(const string& str);
};