#include <iostream>
#include "file_stream.h"
#include "heuristic_algorithm.h"

int main(int, char**) {
    string tspFile = "../data/tsp_data.txt";
    
    FileStream file;
    file.read(tspFile);
    vector<Point> point = file.get_points();
    
    const int population = 100;
    
    HeuristicAlgorithm heuristic;
    
    vector<int> a;
    heuristic.crossover(a,a);
    
    
    std::cout << "Hello, world!" << std::endl;
}
