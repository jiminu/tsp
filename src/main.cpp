#include <iostream>
#include "heuristic_algorithm.h"
int main(int, char**) {

    const int population = 100;
    
        
    HeuristicAlgorithm heuristic;

    
    // std::multimap<int, int> a;
    
    // a.insert({0,1});
    // a.insert({0,2});
    // a.insert({0,3});
    
    // std::multimap<int, int>::iterator itt = a.find(0);
    // itt++;
    // a.erase(itt);
    
    // for (auto it = a.begin(); it != a.end(); it++) {
    //     std::cout << it->first << ", " << it->second << std::endl;
    // }
    
    
    // vector<vector<int>> edge;
    // edge.resize(10);
    // edge[0].push_back(1);
    // edge[0].push_back(2);
    // edge[0].push_back(3);
    // edge[1].push_back(3);
    // edge[1].push_back(3);
    
    // std::multimap<int, int> a;
    
    // a.insert({1,2});
    // a.insert({3,2});
    // a.insert({5,2});
    
    // a.erase(9);

    // for (auto it : a) {
    //     std::cout << 1 << std::endl;
    // }







    // int population = 100;
    // vector<vector<int>> chromosomes;
    // vector<int> chromosome;
    // for (int i = 0; i < 280; ++i) {
    //     chromosome.push_back(i);
    // }
    
    // chromosomes.resize(280);
    // std::random_device rd;
    // std::mt19937 gen(rd());
    
    
    // for (int i = 0; i < population; ++i) {
    //     vector<int> tempVector = chromosome;
    //     for (int j = 0; j < chromosome.size(); ++j) {
    //         std::uniform_int_distribution<int> dis(0, tempVector.size() - 1);
    //         int num = dis(gen);
    //         chromosomes[i].push_back(tempVector[num]);
    //         tempVector.erase(tempVector.begin() + num);
    //     }
    // }
    
    
    // FileStream file;

    // file.write("../data/tempData2.txt", chromosomes[0]);
       
    std::cout << "Hello, world!" << std::endl;
}
