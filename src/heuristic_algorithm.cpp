#include "heuristic_algorithm.h"

#include<map>

using std::multimap;
using std::pair;

HeuristicAlgorithm::HeuristicAlgorithm() {
    
}

HeuristicAlgorithm::~HeuristicAlgorithm() {
    
}

// improved edge recombination crossover
vector<int> HeuristicAlgorithm::crossover(const vector<int>& gene1, const vector<int>& gene2) {
    multimap<int, int> edge;
    
    edge.insert(pair<int,int>(1,2));
    edge.insert(pair<int,int>(1,2));
    edge.insert(pair<int,int>(1,2));
    
    int a;
}
