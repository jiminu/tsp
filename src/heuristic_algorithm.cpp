#include "heuristic_algorithm.h"
#include "file_stream.h"

#include<iostream>
#include<fstream>
#include<sstream>

#include<random>
#include<map>
#include<algorithm>

using std::multimap;
using std::pair;
using std::next_permutation;

HeuristicAlgorithm::HeuristicAlgorithm() {
    generate_cities();
    vector<vector<int>> a = initialize_chromosome(100);
    
    selection(a);
    
    int b = 0;
}

HeuristicAlgorithm::~HeuristicAlgorithm() {
    
}

// improved edge recombination crossover
vector<int> HeuristicAlgorithm::crossover(const vector<int>& gene1, const vector<int>& gene2) {
    vector<vector<int>> edge;
    edge.resize(gene1.size());
    
    vector<int> offspring;
    
    for(int i = 0; i < gene1.size(); ++i) {
        int previous, next;
        if (i == 0) {
            previous = gene1.size() - 1;
            next     = i + 1;
        }
        else if (i == gene1.size() - 1) {
            previous = i - 1;
            next     = 0;
        }
        else {
            previous = i - 1;
            next     = i + 1;
        }

        check_same_value(edge[gene1[i]], gene1[previous]);
        check_same_value(edge[gene1[i]], gene1[next]);
        check_same_value(edge[gene2[i]], gene2[previous]);
        check_same_value(edge[gene2[i]], gene2[next]);
    }
    
    int currPos = 0;
    erase_value_from_edge(edge, currPos);
    offspring.push_back(currPos);
    
    for(int i = 0; i < gene1.size() - 1; ++i) {
        multimap<int, int> candidate;
        multimap<int, int> minusCandidate;
        
        for (int hasEdgesTo = 0; hasEdgesTo < edge[currPos].size(); ++hasEdgesTo) {
            int chromosome = edge[currPos][hasEdgesTo];
            int hasEdgesToNumber = edge[abs(chromosome)].size();
            
            if (chromosome >= 0) {
                candidate.insert({hasEdgesToNumber, chromosome});
            }

            else if (chromosome < 0) {
                minusCandidate.insert({hasEdgesToNumber, chromosome});
            }
        }
        if (minusCandidate.size() > 0) {
            offspring.push_back(abs(minusCandidate.begin()->second));
            currPos = abs(minusCandidate.begin()->second);
        }

        else if (candidate.size() > 0) {
            offspring.push_back(candidate.begin()->second);
            currPos = candidate.begin()->second;
        }
        else {
            for (const auto& it : edge) {
                std::cout << *it.begin() << std::endl;
            }
        }
        erase_value_from_edge(edge, currPos);
    }

    
    return offspring;
}

vector<vector<int>> HeuristicAlgorithm::initialize_chromosome(const int& population) {
    vector<vector<int>> chromosomes;
    vector<int> chromosome;
    for (int i = 0; i < m_cities.size(); ++i) {
        chromosome.push_back(i);
    }
    
    chromosomes.resize(m_cities.size());
    std::random_device rd;
    std::mt19937 gen(rd());
    
    
    for (int i = 0; i < population; ++i) {
        vector<int> tempVector = chromosome;
        for (int j = 0; j < chromosome.size(); ++j) {
            std::uniform_int_distribution<int> dis(0, tempVector.size() - 1);
            int num = dis(gen);
            chromosomes[i].push_back(tempVector[num]);
            tempVector.erase(tempVector.begin() + num);
        }
    }
    
    return chromosomes;
}

void HeuristicAlgorithm::selection(const vector<vector<int>>& chromosomes) {
    vector<double> evalValue;
    
    for(int i = 0; i < chromosomes.size(); ++i) {
        evalValue.push_back(evaluation(chromosomes[i]));
    }
    
    vector<int> a;
    vector<int> b;
        
    std::ifstream file("../data/tempData.txt");
    string line;
    
    if(file) {
        while(std::getline(file, line)) {
            if (file.eof()) break;

            // std::cout << line << std::endl;
            a.push_back(std::stoi(line));
        }
        file.close();
    }
    std::ifstream file2("../data/tempData2.txt");
    string line2;
    
    if(file2) {
        while(std::getline(file2, line2)) {
            if (file2.eof()) break;

            // std::cout << line2 << std::endl;
            b.push_back(std::stoi(line2));
        }
        file2.close();
    }
    
    
    
    crossover(a, b);
}

double HeuristicAlgorithm::evaluation(const vector<int>& chromosome) {
    double result = 0;
    
    for (int i = 0; i < chromosome.size(); ++i) {
        if (i != chromosome.size()-1) {
            result += m_cities[chromosome[i]].distance_to(m_cities[chromosome[i]+1]);
        }
        else {
            result += m_cities[chromosome[i]].distance_to(m_cities[chromosome[0]]);
        }
    }
    return result;
}

void HeuristicAlgorithm::check_same_value(vector<int>& edge, const int& number) {
    for (int i = 0; i < edge.size(); ++i) {
        if (abs(edge[i]) == number) {
            edge[i] = abs(number) * -1;
            return;
        }
    }
    edge.push_back(number);
    return;
}

void HeuristicAlgorithm::erase_value_from_edge(vector<vector<int>>& edge, const int& value) {
    for (int i = 0; i < edge.size(); ++i) {
        for (int hasEdgeTo = 0; hasEdgeTo < edge[i].size(); ++hasEdgeTo) {
            if (abs(edge[i][hasEdgeTo]) == value) {
                edge[i].erase(edge[i].begin() + hasEdgeTo);
            }
        }
    }
}

void HeuristicAlgorithm::generate_cities() {
    string tspFile = "../data/tsp_data.txt";
    
    FileStream file;
    file.read(tspFile);
    m_cities = file.get_cities();
    
    
    
}
