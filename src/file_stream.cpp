#include"file_stream.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>

FileStream::FileStream() {
}

void FileStream::read(const string& fileName) {
    std:: ifstream file(fileName);
    int run = 0;
    string line;
    
    if(file) {
        while(std::getline(file, line)) {
            if (file.eof()) break;
            if (run < 6) {
                ++run;
                continue;
            }
            std::cout << line << std::endl;
            m_citiesVector.push_back(split_xy(line));
        }
        file.close();
    }
    else {
        std::cout << "file open fail" << std::endl;
        exit(0);
    }
}

void FileStream::write(const string& fileName, const vector<City>& nearPoints) {
    std::ofstream fout(fileName);
    for (auto it = nearPoints.begin(); it != nearPoints.end(); it++) {
        fout << it->x << ", " << it->y << "\n";
    }

    fout.close();
}

City FileStream::split_xy(const string& str) {
    City city;
    
    city.x = std::stoi(str.substr(4, 3));
    city.y = std::stoi(str.substr(8, 3));
    
    return city;
}

vector<City>& FileStream::get_cities() {
    return m_citiesVector;
}