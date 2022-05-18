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
        
        const float m_selectionPressure = 3;
        const float m_crossoverParameter = 0.7;
        const float m_mutationParameter = 0.05;
        const int m_population = 1000;
                
        pair<float, vector<int>> m_bestSolution = {0, {}};

    
    public:
        HeuristicAlgorithm();  
        ~HeuristicAlgorithm();  
        
        
    private:
        vector<pair<float, vector<int>>> initialize_chromosome(const int& population);
        vector<pair<float, vector<int>>> selection(const vector<pair<float, vector<int>>>& chromosomes);
        vector<pair<float, vector<int>>> evaluation(const vector<vector<int>>& populations);
        vector<pair<float, vector<int>>> crossover(vector<pair<float, vector<int>>>& selectionPopulations);
        vector<pair<float, vector<int>>> mutation(vector<pair<float, vector<int>>>& crossoverPopulations);
        
        void inversion_mutation(pair<float, vector<int>>& crossoverPopulations);
    
        void check_same_value(vector<int>& edge, const int& value);
        void erase_value_from_edge(map<int, vector<int>>& edge, const int& value);
        vector<pair<float, vector<int>>*> select_parents(vector<pair<float, vector<int>>>& selectionPopulations);
        float evaluate_function(const vector<int>& population);
        void save_best_solution(const pair<float, vector<int>>& bestSolution);
        
        pair<float, vector<int>> find_best_fitness(const vector<pair<float, vector<int>>>& populations);
        
        void generate_cities();
        
        int generate_random_int(const int& min, const int& max);
        float generate_random_float(const float& min, const float& max);
        
};