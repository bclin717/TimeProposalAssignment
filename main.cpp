#include <iostream>
#include "Param.h"

using namespace std;

vector<Chromosome> chromosomes;
Chromosome solution;

void generation() {
    for(int i = 0; i < NumberOfChromosome; i++) {
        chromosomes.emplace_back(Chromosome(i != 0));
    }
    chromosomes.at(0).getTimeWindowCases();
}

void geneAlgorithm() {
    //Roulette Wheel Selection
    //Calculate probabilities of all Chromosome
    double total = 0;
    for (int i = 0; i < NumberOfChromosome; i++)
        total += chromosomes.at(i).calculateFitnessValue();

    chromosomes.at(0).setWheelProbability(0);

    for (int i = 1; i < NumberOfChromosome; i++)
        chromosomes.at(i).setWheelProbability(
                (chromosomes.at(i).calculateFitnessValue() / total) + chromosomes.at(i - 1).getWheelProbability());

    //Select
    double p;
    Chromosome parent[2] = {Chromosome(true), Chromosome(true)}, child[2] = {Chromosome(false), Chromosome(false)};

    int id[2] = {-1, -1};
    do {
        for (int i = 0; i < 2; i++) {
            p = static_cast<double>(rand() / (RAND_MAX + 1.0));
            for (int i2 = 0; i2 < NumberOfChromosome; i2++) {
                if (p > chromosomes.at(i2).getWheelProbability()) {
                    if (i2 == NumberOfChromosome - 1) {
                        parent[i] = Chromosome(chromosomes.at(i2));
                        id[i] = i2;
                        break;
                    } else if (p <= chromosomes.at(i2 + 1).getWheelProbability()) {
                        parent[i] = Chromosome(chromosomes.at(i2));
                        id[i] = i2;
                        break;
                    }

                }
            }
        }
    } while (id[0] == id[1]);


    int size = parent[0]._timeWindows.size();
    for (auto &c : child) c._timeWindows.clear();
    int cutBegin = -1, cutEnd = -1;
    do {
        cutBegin = std::rand() % size - 1 + 1;
        cutEnd = std::rand() % size - 1 + 1;
    } while (cutBegin == cutEnd);

    if (cutBegin > cutEnd) {
        int temp = cutBegin;
        cutBegin = cutEnd;
        cutEnd = temp;
    }

    for (int i = 0; i < 2; i++) {
        for (int i2 = cutBegin; i2 < cutEnd; i2++) {
            child[i]._timeWindows.emplace_back(parent[i]._timeWindows.at(i2));
        }
    }

    for (int i = cutEnd; i < parent[0]._timeWindows.size(); i++)
        child[0]._timeWindows.emplace_back(parent[1]._timeWindows.at(i));
    for (int i = cutEnd; i < parent[1]._timeWindows.size(); i++)
        child[1]._timeWindows.emplace_back(parent[0]._timeWindows.at(i));
    for (int i = 0; i < cutBegin; i++)
        child[0]._timeWindows.insert(child[0]._timeWindows.begin() + i, parent[1]._timeWindows.at(i));
    for (int i = 0; i < cutBegin; i++)
        child[1]._timeWindows.insert(child[1]._timeWindows.begin() + i, parent[0]._timeWindows.at(i));

    for (int i = 0; i < 2; i++) {
        child[i].calculateFitnessValue();
        parent[i] = Chromosome(child[i]);
        chromosomes.emplace_back(Chromosome(parent[i]));
    }

    sort(chromosomes.begin(), chromosomes.end(), Chromosome::cmp);
    for (int i = 0; i < 2; i++)
        chromosomes.pop_back();
}

void calculateCOST() {
    // Part 2
    solution = Chromosome(chromosomes.at(0));
    solution.getTimeWindowCases();

    // Calculate r = ai - ci
    vector<int> r;
    vector<vector<int>> timewindowProposalAndNumberOfCustomers;
    for (int i = 0; i < solution._timeWindows.size(); i++) {
        timewindowProposalAndNumberOfCustomers.emplace_back(vector<int>());
    }

    for (int i = 0; i < solution._timeWindows.size(); i++) {
        r.emplace_back(solution._timeWindows.at(i).getCase() - DefaultTimeWindow[i]);
    }

    // Calculate TimeWindow proposal m and y
    vector<int> m;
    vector<int> y;
    for (int i = 0; i < solution._timeWindows.size(); i++) {
        int p = 999999;
        if (r.at(i) == 0) {
            y.emplace_back(0);
            continue;
        } else if (r.at(i) > 2) {
            m.emplace_back(6);
            m.emplace_back(7);
        } else if (r.at(i) == 1) {
            m.emplace_back(2);
            m.emplace_back(4);
            m.emplace_back(5);
        } else if (r.at(i) == -1) {
            m.emplace_back(1);
            m.emplace_back(3);
            m.emplace_back(5);
        } else if (r.at(i) == 2) {
            m.emplace_back(4);
            m.emplace_back(6);
            m.emplace_back(7);
        } else if (r.at(i) == -2) {
            m.emplace_back(3);
            m.emplace_back(6);
            m.emplace_back(7);
        }

        // Calculate the smallest cost when customer changes timewindow
        int caseChosen = 0;
        for (int j = 0; j < m.size(); j++) {
            if (p > saleDemand[i][m.at(j)]) {
                p = saleDemand[i][m.at(j)];
                caseChosen = m.at(j);
            }
        }
        timewindowProposalAndNumberOfCustomers.at(caseChosen).emplace_back(i);
        y.emplace_back(p);
    }

    int cost = 0;
    for (int i = 0; i < NumberOfTimeWindowSaleCase; i++) {
        if (timewindowProposalAndNumberOfCustomers.at(i).size() == 1) {
            cost += saleDemand[timewindowProposalAndNumberOfCustomers.at(i).at(0)][i];
            continue;
        }
        
        for (int j = 1; j < timewindowProposalAndNumberOfCustomers.at(i).size(); j++) {
            int a = saleDemand[timewindowProposalAndNumberOfCustomers.at(i).at(0)][i];
            int b = saleDemand[timewindowProposalAndNumberOfCustomers.at(i).at(j)][i];
            cost += abs(a - b);
        }
    }

    cout << cost << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    generation();

    // Part 1
    for (int i = 0; i < NumberOfGeneration; i++)
        geneAlgorithm();

    calculateCOST();


    return 0;
}