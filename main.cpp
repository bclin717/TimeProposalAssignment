#include <iostream>
#include "Param.h"

using namespace std;

vector<Chromosome> chromosomes;

void generation() {
    for(int i = 0; i < NumberOfChromosome; i++) {
        chromosomes.emplace_back(Chromosome(i != 0));
    }
}

void algorithm2() {
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

    for (int i = 0; i < NumberOfGeneration; i++) {
        int size = parent[0]._timeWindows.size();
        int cutBegin = -1, cutEnd = -1;
        do {
            cutBegin = (std::rand() % size - 1) + 1;
            cutEnd = (std::rand() % size - 1) + 1;
        } while (cutBegin == cutEnd);

//        if (cutBegin > cutEnd) {
//            int temp = cutBegin;
//            cutBegin = cutEnd;
//            cutEnd = temp;
//        }
//
//        for (int i = 0; i < 2; i++) {
//            for (int i2 = cutBegin; i2 < cutEnd; i2++) {
//                child[i]._timeWindows.emplace_back(parent[i]._timeWindows.at(i2));
//            }
//        }
//
//        for (int i = cutBegin; i < parent[0]._timeWindows.size(); i++) {
//            if (!child[1].isExists(parent[0]._timeWindows.at(i).getCase()))
//                child[1]._timeWindows.emplace_back(parent[0]._timeWindows.at(i));
//        }
//
//        for (int i = cutBegin; i < parent[1]._timeWindows.size(); i++) {
//            if (!child[0].isExists(parent[1]._timeWindows.at(i).getCase()))
//                child[0]._timeWindows.emplace_back(parent[1]._timeWindows.at(i));
//        }
//
//
//        for (int i = 1; i < cutBegin; i++) {
//            if (!child[1].isExists(parent[0]._timeWindows.at(i).getCase()))
//                child[1]._timeWindows.insert(child[1]._timeWindows.begin(), parent[0]._timeWindows.at(i));
//            if (!child[0].isExists(parent[1]._timeWindows.at(i).getCase()))
//                child[0]._timeWindows.insert(child[0]._timeWindows.begin(), parent[1]._timeWindows.at(i));
//        }
//
//        for (int i = 0; i < 2; i++) {
//            child[i]._timeWindows.insert(child[i]._timeWindows.begin(), 0);
//            child[i].calculateFitnessValue();
//            parent[i] = Chromosome(child[i]);
//            chromosomes.emplace_back(Chromosome(child[i]));
//            child[i]._timeWindows.clear();
//        }
//        sort(chromosomes.begin(), chromosomes.end(), Chromosome::cmp);
//        for (int i = 0; i < 2; i++)
//            chromosomes.pop_back();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    generation();
    algorithm2();


    for (int i = 0; i < chromosomes.size(); i++) {
        chromosomes.at(i).getTimeWindowCases();
        chromosomes.at(i).getNumberOfTimeWindows();
    }

    return 0;
}