#pragma once

#include<vector>
#include<map>
#include "city.h"

using std::vector;
using std::map;

class HeuristicAlgorithm {
    private:
        vector<City> m_cities;

    
    public:
        HeuristicAlgorithm();  
        ~HeuristicAlgorithm();  
        
        
    
        void selection(const vector<vector<int>>& chromosomes);
        vector<int> crossover(const vector<int>& gene1, const vector<int>& gene2);
    private:
        vector<vector<int>> initialize_chromosome(const int& population);
    
        double evaluation(const vector<int>& chromosome);
        void check_same_value(vector<int>& edge, const int& value);
        // void check_same_value(vector<int>& edge, const int& number);
        void erase_value_from_edge(map<int, vector<int>>& edge, const int& value);
        // void erase_value_from_edge(vector<vector<int>>& edge, const int& value);
        
        
        void generate_cities();
        
};