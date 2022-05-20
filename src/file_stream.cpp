#include"file_stream.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>

FileStream::FileStream() {
}

void FileStream::read(const string& fileName) {
    std::ifstream file(fileName);
    int run = 0;
    string line;
    
    if(file) {
        while(std::getline(file, line)) {
            if (file.eof()) break;
            if (run < 6) {
                ++run;
                continue;
            }
            // std::cout << line << std::endl;
            m_citiesVector.push_back(split_xy(line));
        }
        file.close();
    }
    else {
        std::cout << "file open fail" << std::endl;
        exit(0);
    }
}

void FileStream::write(const string& fileName, const pair<float, vector<int>>& bestSolution, const vector<float>& info) {
    std::ofstream fout(fileName);
    // for (auto it = cities.begin(); it != cities.end(); it++) {
    //     fout << it->x << ", " << it->y << "\n";
    // }
    fout << "fitness : " << bestSolution.first << "\n";
    fout << "selection pressure : " << info[0] << "\n";
    fout << "crossover parameter : " << info[1] << "\n";
    fout << "mutation parameter : " << info[2] << "\n";
    fout << "population : " << info[3] << "\n";
    fout << "generation : " << info[4] << "\n";
    fout << "time : " << info[5] << "\n";
    for (auto it = bestSolution.second.begin(); it != bestSolution.second.end(); it++) {
        fout << *it << "\n";
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