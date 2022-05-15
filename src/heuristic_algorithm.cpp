#include "heuristic_algorithm.h"
#include "file_stream.h"

#include<iostream>
#include<fstream>
#include<sstream>

#include<random>
#include<map>
#include<algorithm>

using std::map;
using std::next_permutation;

HeuristicAlgorithm::HeuristicAlgorithm(const int& populationNumber) {
    generate_cities();
    vector<vector<int>> populations = initialize_chromosome(populationNumber);
    vector<pair<float, vector<int>>> evaluationResult = evaluation(populations);
    vector<pair<float, vector<int>>> selectionPopulations = selection(evaluationResult);
    vector<pair<float, vector<int>>> crossoverPopulations = crossover(selectionPopulations);
        
    int b = 0;
}

HeuristicAlgorithm::~HeuristicAlgorithm() {
    
}

// improved edge recombination crossover
vector<pair<float, vector<int>>> HeuristicAlgorithm::crossover(vector<pair<float, vector<int>>>& selectionPopulations) {
        vector<int> a;
        vector<int> b;
        
    std::ifstream file("../data/tempData.txt");
    string line;
    
    if(file) {
        while(std::getline(file, line)) {
            if (file.eof()) break;

            a.push_back(std::stoi(line));
        }
        file.close();
    }
    std::ifstream file2("../data/tempData2.txt");
    string line2;
    
    if(file2) {
        while(std::getline(file2, line2)) {
            if (file2.eof()) break;

            b.push_back(std::stoi(line2));
        }
        file2.close();
    }
    
    
    
    vector<int> selectChromosome;
    
    map<int, vector<int>> edge;
    
    vector<pair<float, vector<int>>*> selectParents = select_parents(selectionPopulations);
    
    while (selectParents.size() > 1) {
        vector<int> gene1 = a;
        vector<int> gene2 = b;
        pair<float, vector<int>> offspring1;
        pair<float, vector<int>> offspring2;
        
        for (int i = 0; i < gene1.size(); ++i) {
            int previous, next;
            if (i == 0) {
                previous = gene1.size() - 1;
                next = i + 1;
            } else if (i == gene1.size() - 1) {
                previous = i - 1;
                next = 0;
            } else {
                previous = i - 1;
                next = i + 1;
            }

            check_same_value(edge[gene1[i]], gene1[previous]);
            check_same_value(edge[gene1[i]], gene1[next]);
            check_same_value(edge[gene2[i]], gene2[previous]);
            check_same_value(edge[gene2[i]], gene2[next]);
        }

        for (int start = 0; start < 2; ++start) {
            vector<int> offspring;
            int currPos = 0;
            erase_value_from_edge(edge, currPos);
            offspring.push_back(currPos);

            for (int i = 0; i < gene1.size() - 1; ++i) {
                multimap<int, int> candidate;
                multimap<int, int> minusCandidate;
           

                for (int n = 0; n < edge[currPos].size(); ++n) {
                    int chromosome = edge[currPos][n];
                    int hasEdgesToNumber = edge[abs(chromosome)].size();

                    if (chromosome >= 0) {
                        candidate.insert({hasEdgesToNumber, chromosome});
                    }

                    else if (chromosome < 0) {
                        minusCandidate.insert({hasEdgesToNumber, chromosome});
                    }
                }

                edge.erase(currPos);

                if (minusCandidate.size() > 0) {
                    if (minusCandidate.size() > 1) {
                        auto it = minusCandidate.begin();
                        if (it->first == (++it)->first) {
                            int num = generate_random_int(0, 1);
                            if (num == 0) {
                                currPos = abs(it->second);
                            } 
                            else {
                                currPos = abs(minusCandidate.begin()->second);
                            }
                        }
                    } 
                    else {
                        currPos = abs(minusCandidate.begin()->second);
                    }
                }

                else if (candidate.size() > 0) {
                    if (candidate.size() > 1) {
                        auto it = candidate.begin();
                        if (it->first == (++it)->first) {
                            int num = generate_random_int(0, 1);
                            if (num == 0) {
                                currPos = abs(it->second);
                            } 
                            else {
                                currPos = abs(candidate.begin()->second);
                            }
                        }
                    }
                    else {
                        currPos = abs(candidate.begin()->second);
                    }
                }

                else {
                    currPos = edge.begin()->first;
                }
                offspring.push_back(currPos);
                erase_value_from_edge(edge, currPos);
            }
            if (start == 0) {
                offspring1 = {evaluate_function(offspring), offspring};
            } 
            else {
                offspring2 = {evaluate_function(offspring), offspring};
            }
        }
        *selectParents[selectParents.size() - 2] = offspring1;
        *selectParents[selectParents.size() - 1] = offspring2;
        selectParents.pop_back();
        selectParents.pop_back();
    }
    return selectionPopulations;
}

vector<vector<int>> HeuristicAlgorithm::initialize_chromosome(const int& population) {
    vector<vector<int>> chromosomes;
    vector<int> chromosome;
    for (int i = 0; i < m_cities.size(); ++i) {
        chromosome.push_back(i);
    }
    
    chromosomes.resize(population);    
    
    for (int i = 0; i < population; ++i) {
        vector<int> tempVector = chromosome;
        for (int j = 0; j < chromosome.size(); ++j) {
            int num = generate_random_int(0, tempVector.size() - 1);
            chromosomes[i].push_back(tempVector[num]);
            tempVector.erase(tempVector.begin() + num);
        }
    }
    
    return chromosomes;
}

vector<pair<float, vector<int>>> HeuristicAlgorithm::selection(const vector<pair<float, vector<int>>>& chromosomes) {
    vector<pair<float, vector<int>>> selectionChromosome;
    float max = 0;
    for (auto it = chromosomes.begin(); it != chromosomes.end(); ++it) {
        max += 1 / it->first;
    }
    
    for (int i = 0; i < chromosomes.size(); ++i) {
        float randomNumber = generate_random_float(0, max);
        float preRange = 0;
        
        for (auto it = chromosomes.begin(); it != chromosomes.end(); ++it) {
            
            if (preRange <= randomNumber && randomNumber < preRange + (1 / it->first)) {
                selectionChromosome.push_back({it->first, it->second});
                break;
            }
            preRange += 1 / it->first;
        }
    }
    
    return selectionChromosome;

    // vector<int> b;
        
    // std::ifstream file("../data/tempData.txt");
    // string line;
    
    // if(file) {
    //     while(std::getline(file, line)) {
    //         if (file.eof()) break;

    //         a.push_back(std::stoi(line));
    //     }
    //     file.close();
    // }
    // std::ifstream file2("../data/tempData2.txt");
    // string line2;
    
    // if(file2) {
    //     while(std::getline(file2, line2)) {
    //         if (file2.eof()) break;

    //         b.push_back(std::stoi(line2));
    //     }
    //     file2.close();
    // }
    
    // crossover(a, b);
    // crossover(chromosomes[0], chromosomes[1]);
}

vector<pair<float, vector<int>>> HeuristicAlgorithm::evaluation(const vector<vector<int>>& populations) {
    vector<pair<float, vector<int>>> result;
    
    for (int i = 0; i < populations.size(); ++i) {
        float fitness = evaluate_function(populations[i]);
        result.push_back({fitness, populations[i]});
    }
    
    return result;
}

float HeuristicAlgorithm::evaluate_function(const vector<int>& population) {
    float result = 0;
    for (int chromosome = 0; chromosome < population.size(); ++chromosome) {
        if (chromosome != population.size() - 1) {
            result += m_cities[population[chromosome]].distance_to(m_cities[population[chromosome + 1]]);
        }

        else {
            result += m_cities[population[chromosome]].distance_to(m_cities[population[0]]);
        }
    };

    return result;
}

void HeuristicAlgorithm::check_same_value(vector<int>& edge, const int& value) {
    for (int i = 0; i < edge.size(); ++i) {
        if (abs(edge[i]) == abs(value)) {
            edge[i] = abs(edge[i]) * -1;
            return;
        }
    }
    
    edge.push_back(value);
    return;
}

void HeuristicAlgorithm::erase_value_from_edge(map<int, vector<int>>& edge, const int& value) {
    for (auto it = edge.begin(); it != edge.end(); ++it) {
        for (int i = 0; i < it->second.size(); ++i) {
            if (abs(it->second[i]) == value) {
                it->second.erase(it->second.begin() + i);
            }
        }
    }
}

vector<pair<float, vector<int>>*> HeuristicAlgorithm::select_parents(vector<pair<float, vector<int>>>& selectionPopulations) {
    vector<pair<float, vector<int>>*> result;

    for (auto& chromosome : selectionPopulations) {
        float randomNum = generate_random_float(0, 1);
        if (randomNum <= m_crossoverParameter) {
            result.push_back(&chromosome);
        }
    }
    
    return result;
}

void HeuristicAlgorithm::generate_cities() {
    string tspFile = "../data/tsp_data.txt";
    
    FileStream file;
    file.read(tspFile);
    m_cities = file.get_cities();
    
    
    
}

int HeuristicAlgorithm::generate_random_int(const int& min, const int& max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);

    return dis(gen);
}

float HeuristicAlgorithm::generate_random_float(const float& min, const float& max) {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    
    return dis(gen);
}