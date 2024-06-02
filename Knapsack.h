//
// Created by wojciech on 13.05.24.
//

#ifndef PROBLEM_PLECAKOWY_KNAPSACK_H
#define PROBLEM_PLECAKOWY_KNAPSACK_H
#include "vector"
#include "set"
#include "map"
#include "bitset"
#include "algorithm"


enum DecisionMode{Auto,Front,Back};
struct Item{
    int weight;
    int value;


};
class Knapsack {
public:
    int getValueFromItems(std::vector<bool> vector);
    int getWeightFromItems(std::vector<bool> vector);
    Item getPropertiesFromItemIndices(std::vector<bool> vector);
    Item getPropertiesFromItemIndices(std::vector<Item> vector);
    std::vector<Item> knapsackMatrix();
    Knapsack(int capacity,std::vector<Item> &items) : capacity(capacity), items(items) {}
    Knapsack(std::string );
    void knapsackBruteForce(DecisionMode decisionMode);
private:
    void bruteForceUtilFront(std::vector<bool> itemIndexSet, int *result, std::vector<bool> *outcomeSet,int c,int v);
    void bruteForceUtilBack(std::vector<bool> itemIndexSet, int *result, std::vector<bool> *outcomeSet, int c, int v);
    void printItems(std::vector<bool> itemsVector);
    bool decideBruteForceAlgorithm();
    void sortItems();
    int capacity;
    std::vector<Item> items;
};




#endif //PROBLEM_PLECAKOWY_KNAPSACK_H
