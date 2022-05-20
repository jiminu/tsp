#include "heuristic_algorithm.h"
#include "file_stream.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>

#include<random>
#include<map>
#include<algorithm>

using std::map;
using std::next_permutation;

HeuristicAlgorithm::HeuristicAlgorithm() {
    clock_t start, end;
    float result;
    
    start = clock();
    generate_cities();
    vector<pair<float, vector<int>>> populations = initialize_chromosome(m_population);
    for (int i = 0; i < m_generation; ++i) {
        // vector<pair<float, vector<int>>> evaluationResult = evaluation(populations);
        populations = selection(populations);
        populations = crossover(populations);
        // populations = mutation(populations);
        // // vector<pair<float, vector<int>>> evaluationResult = evaluation(populations);
        // vector<pair<float, vector<int>>> selectionPopulations = selection(populations);
        // vector<pair<float, vector<int>>> crossoverPopulations = crossover(selectionPopulations);
        // vector<pair<float, vector<int>>> mutationPopulations = mutation(crossoverPopulations);
        
        std::cout << "Generation " << i << " : " << find_best_fitness(populations).first << std::endl;
    }
    end = clock();
    result = end - start;
    vector<float> info = {m_selectionPressure, m_crossoverParameter, m_mutationParameter, float(m_population), float(m_generation), result / CLOCKS_PER_SEC};
    
    std::cout << "fitness : " << m_bestSolution.first << std::endl;
    for (const auto& it : m_bestSolution.second) {
        std::cout << it << " -> ";
    }
    std::cout << m_bestSolution.second[0] << std::endl;
    std::cout << "runtime : " << result / CLOCKS_PER_SEC << "s" << std::endl;
    save_best_solution(info);
    
    for (auto it : populations) {
        map<int, int> test;
        for (auto pop : it.second) {
            auto check = test.insert({pop, 0});
            if (!check.second) {
                std::cout << "same!!!!! : " << pop << std::endl;
            }
        }
    }
}

HeuristicAlgorithm::~HeuristicAlgorithm() {
    
}

// improved edge recombination crossover
vector<pair<float, vector<int>>> HeuristicAlgorithm::crossover(vector<pair<float, vector<int>>>& selectionPopulations) { 
    vector<pair<float, vector<int>>*> selectParents = select_parents(selectionPopulations);
    
    while (selectParents.size() > 1) {
        // vector<int> gene1 = a;
        // vector<int> gene2 = b;
        vector<int> gene1 = selectParents[selectParents.size()-2]->second;
        vector<int> gene2 = selectParents[selectParents.size()-1]->second;
        pair<float, vector<int>> offspring1;
        pair<float, vector<int>> offspring2;   

        for (int start = 0; start < 2; ++start) {
            // ------------- make edge
            map<int, vector<int>> edge;
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
            // ------------- make edge
            vector<int> offspring;
            int currPos = generate_random_int(0, gene1.size()-1);
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
                        else {
                            currPos = abs(minusCandidate.begin()->second);
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
                        else {
                             currPos = abs(candidate.begin()->second);
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
                displacement_mutation(offspring1);
                // inversion_mutation(offspring1);
            } 
            else {
                offspring2 = {evaluate_function(offspring), offspring};
                displacement_mutation(offspring2);
                // inversion_mutation(offspring2);
            }
        }
        *selectParents[selectParents.size() - 2] = offspring1;
        *selectParents[selectParents.size() - 1] = offspring2;
        selectParents.pop_back();
        selectParents.pop_back();
    }
    return selectionPopulations;
}

vector<pair<float, vector<int>>> HeuristicAlgorithm::mutation(vector<pair<float, vector<int>>>& crossoverPopulations) {
    int count = 0;
    for (auto& it : crossoverPopulations) {
        count++;
        float randomNum = generate_random_float(0, 1);
        if (randomNum <= m_mutationParameter) {
            int start = generate_random_int(0, it.second.size() - 1);
            int end = generate_random_int(start, it.second.size() - 1);
            std::reverse(it.second.begin() + start, it.second.begin() + end);
            it.first = evaluate_function(it.second);
        }
    }
    
    return crossoverPopulations;
}

void HeuristicAlgorithm::inversion_mutation(pair<float, vector<int>>& crossoverPopulations) {
    float randomProb = generate_random_float(0, 1);
    if (randomProb < m_mutationParameter) {
        int start = generate_random_int(0, crossoverPopulations.second.size() - 1);
        int end = generate_random_int(start, crossoverPopulations.second.size() - 1);
        std::reverse(crossoverPopulations.second.begin() + start, crossoverPopulations.second.begin() + end);
        crossoverPopulations.first = evaluate_function(crossoverPopulations.second);
    }    
}

void HeuristicAlgorithm::displacement_mutation(pair<float, vector<int>>& crossoverPopulations) {
    float randomProb = generate_random_float(0, 1);
    if (randomProb < m_mutationParameter) {
        int start = generate_random_int(0, crossoverPopulations.second.size() - 1);
        int end = generate_random_int(start, crossoverPopulations.second.size() - 1);
        vector<int> temp;
        temp.assign(crossoverPopulations.second.begin()+start, crossoverPopulations.second.begin()+end);
        crossoverPopulations.second.erase(crossoverPopulations.second.begin()+start, crossoverPopulations.second.begin()+end);
        
        int position = generate_random_int(0, crossoverPopulations.second.size() - 1);
        crossoverPopulations.second.insert(crossoverPopulations.second.begin() + position, temp.begin(), temp.end());
        
        crossoverPopulations.first = evaluate_function(crossoverPopulations.second);
    }   
}

vector<pair<float, vector<int>>> HeuristicAlgorithm::initialize_chromosome(const int& population) {
    vector<pair<float, vector<int>>> chromosomes;
    vector<int> chromosome;
    for (int i = 0; i < m_cities.size(); ++i) {
        chromosome.push_back(i);
    }
    
    chromosomes.resize(population);    
    
    for (int i = 0; i < population; ++i) {
        vector<int> tempVector = chromosome;
        for (int j = 0; j < chromosome.size(); ++j) {
            int num = generate_random_int(0, tempVector.size() - 1);
            chromosomes[i].second.push_back(tempVector[num]);
            tempVector.erase(tempVector.begin() + num);
        }
        chromosomes[i].first = evaluate_function(chromosomes[i].second);
    }
    
    return chromosomes;
}

vector<pair<float, vector<int>>> HeuristicAlgorithm::selection(const vector<pair<float, vector<int>>>& chromosomes) {
    vector<pair<float, vector<int>>> selectionChromosome;
    map<float, vector<int>> test;
    float maxFitness = 0;
    float bestFitness = 0;
    float worstFitness = 0;
    
    for (auto it = chromosomes.begin(); it != chromosomes.end(); ++it) {
        test.insert({it->first, it->second});
    }
    
    bestFitness = test.begin()->first;
    worstFitness = test.rbegin()->first;
    
    for (auto it = chromosomes.begin(); it != chromosomes.end(); ++it) {
        maxFitness += (worstFitness - it->first) + ((worstFitness - bestFitness) / (m_selectionPressure - 1));
    }
    
    // for (auto it = chromosomes.begin(); it != chromosomes.end(); ++it) {
    //     maxFitness += 1 / it->first;
    //     if (worstFitness < it->first) worstFitness = it->first;
    //     if (bestFitness > it->first || bestFitness == 0) bestFitness = it->first;
    // }
    
    for (int i = 0; i < chromosomes.size(); ++i) {
        float randomNumber = generate_random_float(0, maxFitness);
        float sum          = 0;
        
        for (auto it = chromosomes.begin(); it != chromosomes.end(); ++it) {
            float fitness = (worstFitness - it->first) + ((worstFitness - bestFitness) / (m_selectionPressure - 1));

            sum += fitness;

            if (randomNumber < sum) {
                selectionChromosome.push_back({it->first, it->second});
                break;
            }
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

// vector<pair<float, vector<int>>*> HeuristicAlgorithm::select_parents(vector<pair<float, vector<int>>>& selectionPopulations) {
//     vector<pair<float, vector<int>>*> result;
//     float max = 0;
//     for (auto it = selectionPopulations.begin(); it != selectionPopulations.end(); ++it) {
//         max += 1 / it->first;
//     }
    
//     for (auto& chromosome : selectionPopulations) {
//         float randomNum = generate_random_float(0, max);
//         if (randomNum <= m_crossoverParameter) {
//             result.push_back(&chromosome);
//         }
//     }
    
//     return result;
// }

vector<pair<float, vector<int>>*> HeuristicAlgorithm::select_parents(vector<pair<float, vector<int>>>& selectionPopulations) {
    vector<pair<float, vector<int>>*> result;

    for (auto& chromosome : selectionPopulations) {
        float randomNum = generate_random_float(0, 1);
        if (randomNum <= m_crossoverParameter) {
            result.push_back(&chromosome);
        }
        else if (chromosome.first <= m_bestSolution.first) {
            result.push_back(&chromosome);
        }
    }
    
    return result;
}

 pair<float, vector<int>> HeuristicAlgorithm::find_best_fitness(const vector<pair<float, vector<int>>>& populations) {
     for (const auto& it : populations) {
         if (it.first < m_bestSolution.first || m_bestSolution.first == 0) {
             m_bestSolution = it;
         }
     }
     return m_bestSolution;
 }


void HeuristicAlgorithm::generate_cities() {
    FileStream file;
    file.read(m_tspFile);
    m_cities = file.get_cities();
}

void HeuristicAlgorithm::save_best_solution(const vector<float>& info) {    
    FileStream file;
    m_savePath = m_savePath + std::to_string(m_bestSolution.first) + ".txt";
    file.write(m_savePath, m_bestSolution, info);
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