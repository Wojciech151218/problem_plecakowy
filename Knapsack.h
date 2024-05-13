//
// Created by wojciech on 13.05.24.
//

#ifndef PROBLEM_PLECAKOWY_KNAPSACK_H
#define PROBLEM_PLECAKOWY_KNAPSACK_H
#include "vector"
#include "set"
#include "map"
#include "bitset"

struct Item{
    int weight;
    int value;


};
class Knapsack {
public:
    Item getPropertiesFromItemIndices(std::vector<bool> vector);
    std::vector<std::vector<int>> knapsackMatrix();
    explicit Knapsack(int capacity,std::vector<Item> &items) : capacity(capacity), items(items) {}
    void knapsackBruteForce();
private:
    void bruteForceUtil(std::vector<bool> itemIndexSet, int *result, std::vector<bool> *outcomeSet);
    int capacity;
    std::vector<Item> items;
};


#endif //PROBLEM_PLECAKOWY_KNAPSACK_H
