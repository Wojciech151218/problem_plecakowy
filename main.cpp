#include <iostream>
#include "vector"
#include "Knapsack.h"
#include <random>
#include "chrono"


int getRandomInteger(int a, int b) {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(a, b);

    // Generate and return a random integer within the specified range
    return dis(gen);
}
std::vector<Item> itemGenerator(int capacity){
    std::vector<Item> result;
    int maxValue = 3*capacity/4;
    int maxElements = capacity;
    int minWeight = capacity/4;
    for (int i = 0; i < maxElements; ++i)
        result.push_back({getRandomInteger(1,maxValue/3),getRandomInteger(1,maxValue)});
    return result;
}



int main() {

    std::vector<Item> items = {
            {1,2},{1,1},{2,3},{3,7},{3,6},{4,8},{5,13},
            {6,16},{2,4},{3,6}
    };
    std::vector<Item> items1 = {
            {2,3},{3,7},{3,6}
    };
    int capacity = 12;
    std::vector<Item> items2 = itemGenerator(capacity);
    std::string filePath = R"(C:\Users\Wojciech\CLionProjects\problem_plecakowy\test1.txt)";
    Knapsack knapsack(filePath);

    DecisionMode decisionMode;
    char decisionSignature;
    std::cin>> decisionSignature;
    switch (decisionSignature) {
        case 'f':
            decisionMode = Front;
            break;
        case 'b':
            decisionMode = Back;
            break;
        default:
            decisionMode = Auto;
            break;
    }
    auto start = std::chrono::high_resolution_clock::now();
    knapsack.knapsackBruteForce(decisionMode);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl;

    return 0;
}
