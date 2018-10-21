#include "Param.h"
using namespace std;

vector<Chromosome> chromosomes;
Chromosome D;
Chromosome solution;
int NumberOfDeterministicCustomers = 0;
int cost = 0;
vector<int> m;
vector<int> m2;
vector<int> y;
vector<int> b;

std::vector<int> DefaultTimeWindow = vector<int>(0);
std::vector<std::vector<int>> saleDemand = vector<vector<int>>(0);
std::vector<std::vector<int>> minimumCostForAssigningCustomer = vector<vector<int>>(0);

void readFiles() {
    int input;
    char c;

    // Read ci.txt
    FILE *ci;
    if ((ci = fopen("ci.txt", "r")) == NULL) {
        cout << "ci.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(ci, "%d%c", &input, &c) != EOF)
        DefaultTimeWindow.emplace_back(input);
    fclose(ci);
    // Read pim.txt
    FILE *pim;
    if ((pim = fopen("pim.txt", "r")) == NULL) {
        cout << "pim.txt does not exist!!" << endl;
        exit(1);
    }
    saleDemand.emplace_back(vector<int>());
    for (int i = 0; fscanf(pim, "%d%c", &input, &c) != EOF;) {
        if (c == '\n') {
            saleDemand.at(i).emplace_back(input);
            saleDemand.emplace_back(vector<int>());
            i++;
            continue;
        }
        saleDemand.at(i).emplace_back(input);
    }
    fclose(pim);

    // Read thetaIZ.txt
    FILE *thetaIZ;
    if ((thetaIZ = fopen("theta iz.txt", "r")) == NULL) {
        cout << "theta iz.txt does not exist!!" << endl;
        exit(1);
    }
    minimumCostForAssigningCustomer.emplace_back(vector<int>());
    for (int i = 0; fscanf(thetaIZ, "%d%c", &input, &c) != EOF;) {
        if (c == '\n') {
            minimumCostForAssigningCustomer.at(i).emplace_back(input);
            minimumCostForAssigningCustomer.emplace_back(vector<int>());
            i++;
            continue;
        }
        minimumCostForAssigningCustomer.at(i).emplace_back(input);
    }
    fclose(thetaIZ);
}

void outputFiles() {

    FILE *output;
    output = fopen("output.txt", "w");

    fprintf(output, "default : ");
    for (int i = 0; i < chromosomes.size(); i++) {
        fprintf(output, "%3d ", D._timeWindows[i].getCase());
    }
    if (chromosomes[0].calculateFitnessValue() < 1) fprintf(output, "Fitness Value : 0 \n");
    else fprintf(output, "Fitness Value : %5.3f \n", D.calculateFitnessValue());

    fprintf(output, "aiz/ai  : ");
    for (int i = 0; i < solution._timeWindows.size(); i++) {
        fprintf(output, "%3d ", solution._timeWindows[i].getCase());
    }
    if (solution.calculateFitnessValue() < 1) fprintf(output, "Fitness Value : 0 \n");
    else fprintf(output, "Fitness Value : %5.3f \n", solution.calculateFitnessValue());

    fprintf(output, "yim : ");
    for (int i = 0; i < y.size(); i++) {
        fprintf(output, "y%d/%d = %3d, ", i + 1, m2[i], y[i]);
    }
    fprintf(output, "\n");

    fprintf(output, "wim : ");
    for (int i = 0; i < solution._timeWindows.size(); i++) {
        fprintf(output, "w%d/%d = %3d, ", i + 1, m2[i], 1);
    }
    fprintf(output, "\n");

    fprintf(output, "bm  : ");
    for (int i = 0; i < b.size(); i++) {
        fprintf(output, "b%d : %d, ", i + 1, b[i]);
    }
    fprintf(output, "\n");

    fprintf(output, "Total Cost : %d \n", cost);
    fclose(output);
}

void generation() {
    for(int i = 0; i < NumberOfChromosome; i++) {
        chromosomes.emplace_back(Chromosome(i != 0));
    }
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

    for (int i = 0; i < solution._timeWindows.size(); i++) {
        int p = 999999;
        if (r.at(i) == 0) {
            m.emplace_back(0);
            m2.emplace_back(0);
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
        int mChosen = 0;
        for (int j = 0; j < m.size(); j++) {
            if (p > saleDemand[i][m.at(j) - 1]) {
                p = saleDemand[i][m.at(j) - 1];
                caseChosen = m.at(j);
                mChosen = j;
            }
        }
        timewindowProposalAndNumberOfCustomers.at(caseChosen).emplace_back(i);

        m2.emplace_back(mChosen);
        y.emplace_back(p);
    }

    int biggest = 0;
    for (int i = 0; i < NumberOfTimeWindowSaleCase; i++) {
        biggest = 0;
        if (timewindowProposalAndNumberOfCustomers.at(i).size() == 1) {
            biggest = saleDemand[timewindowProposalAndNumberOfCustomers.at(i).at(0)][i];
            b.emplace_back(biggest);
            continue;
        }

        for (int j = 1; j < timewindowProposalAndNumberOfCustomers.at(i).size(); j++) {
            int a = saleDemand[timewindowProposalAndNumberOfCustomers.at(i).at(0)][i];
            int bb = saleDemand[timewindowProposalAndNumberOfCustomers.at(i).at(j)][i];

            if (biggest < a) biggest = a;
            if (biggest < bb) biggest = bb;

            cost += abs(a - bb);
        }
        b.emplace_back(biggest);
    }
}

int main() {
    readFiles();
    NumberOfDeterministicCustomers = DefaultTimeWindow.size() + 1;

    srand(static_cast<unsigned int>(time(nullptr)));
    generation();

    D = Chromosome(chromosomes[0]);

//  Part 1
    for (int i = 0; i < NumberOfGeneration; i++)
        geneAlgorithm();
    calculateCOST();
    outputFiles();


    return 0;
}