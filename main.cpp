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
    int maxElements = capacity/2;
    int minWeight = capacity/4;
    for (int i = 0; i < maxElements; ++i)
        result.push_back({getRandomInteger(1,maxValue/2)+minWeight,getRandomInteger(1,maxValue)});
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
    int capacity = 10;
    std::vector<Item> items2 = itemGenerator(capacity);
    Knapsack knapsack(capacity,items2);
    Knapsack knapsack1(capacity,items2);
    knapsack1.knapsackMatrix();
    knapsack1.knapsackBruteForce();



    return 0;
}
