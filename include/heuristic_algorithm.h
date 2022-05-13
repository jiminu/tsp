#pragma once

#include<vector>
#include<map>
#include "city.h"

using std::vector;
using std::map;
using std::pair;

class HeuristicAlgorithm {
    private:
        vector<City> m_cities;
        
        float m_crossoverParameter = 0.7;
        float m_mutationParameter = 0.001;

    
    public:
        HeuristicAlgorithm(const int& populationNumber);  
        ~HeuristicAlgorithm();  
        
        
    private:
        vector<vector<int>> initialize_chromosome(const int& population);
        vector<pair<float, vector<int>>> selection(const vector<pair<float, vector<int>>>& chromosomes);
        vector<pair<float, vector<int>>> evaluation(const vector<vector<int>>& populations);
        vector<pair<float, vector<int>>> crossover(vector<pair<float, vector<int>>>& selectionPopulations);
        vector<vector<int>> mutation(vector<pair<float, vector<int>>>& crossoverPopulations);
    
        void check_same_value(vector<int>& edge, const int& value);
        void erase_value_from_edge(map<int, vector<int>>& edge, const int& value);
        vector<pair<float, vector<int>>*> select_parents(vector<pair<float, vector<int>>>& selectionPopulations);
        float evaluate_function(const vector<int>& population);
        
        void generate_cities();
        
        int generate_random_int(const int& min, const int& max);
        float generate_random_float(const float& min, const float& max);
        
};