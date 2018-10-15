#include <iostream>
#include "Param.h"

using namespace std;

void generation() {
    vector<Chromosome> chromosomes;
    for(int i = 0; i < NumberOfChromosome; i++) {
        chromosomes.emplace_back(Chromosome(i != 0));
        chromosomes.at(i).getTimeWindowCases();
        chromosomes.at(i).getNumberOfTimeWindows();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    generation();
    return 0;
}