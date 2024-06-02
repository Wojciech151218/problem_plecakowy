//
// Created by wojciech on 13.05.24.
//

#include "Knapsack.h"
#include <fstream>
#include <string>
#include <sstream>

std::vector<std::string> splitStringBySpaces(const std::string& str) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}


Item Knapsack::getPropertiesFromItemIndices(std::vector<bool> vector){
    Item result={0,0};
    for (int i = 0; i < vector.size(); ++i) {
        if(!vector[i]) continue;
        result.weight += items[i].weight;
        result.value += items[i].value;
    }
    return result;
}

Knapsack::Knapsack(std::string filePath) {
    std::ifstream inputFile(filePath);
    std::string line;
    bool isFirstLine = true;
    while (std::getline(inputFile, line)) {
        if(isFirstLine){
            capacity = std::stoi(line);
            isFirstLine = false;
            continue;
        }
        std::vector<std::string> stringVector = splitStringBySpaces(line);
        int weight = std::stoi(stringVector[0]);
        int value = std::stoi(stringVector[1]);
        items.push_back({weight,value});
    }
}

std::vector<std::vector<int>> Knapsack::knapsackMatrix() {
    std::vector<std::vector<int>> V(items.size()+1,std::vector<int>(capacity+1,0));

    for (int i = 1; i < items.size()+1; ++i) {
        for (int j = 1; j < capacity+1; ++j) {
            int itemWeight = items[i-1].weight;
            int itemValue = items[i-1].value;
            if(itemWeight>j){
                V[i][j] = V[i-1][j];
            }else{
                V[i][j] = std::max<int>(V[i-1][j],V[i-1][j-itemWeight]+itemValue);
            }
        }
    }
    int i = items.size();
    int j = capacity;
    std::vector<bool> outcomeItems(items.size(), false);
    while(i> 0 && j> 0){
        if(V[i][j] != V[i-1][j]){
            outcomeItems[i-1] = true;
            j = j  - items[i-1].weight;

        }
        i--;
    }
    printItems(outcomeItems);
    return V;
}
void Knapsack::bruteForceUtil(std::vector<bool> itemIndexSet, int *result, std::vector<bool> *outcomeSet) {

    Item currentBagProperties =  getPropertiesFromItemIndices(itemIndexSet);
    if(currentBagProperties.weight<=capacity){
        if(*result<currentBagProperties.value){
            *result = currentBagProperties.value;
            *outcomeSet = std::vector<bool>(itemIndexSet);
        }
        return ;
    }

    for (int i = 0; i < itemIndexSet.size(); ++i) {
        if(!itemIndexSet[i]) continue;
        std::vector<bool> copiedItemIndexVector(itemIndexSet);
        copiedItemIndexVector[i] = false;
        bruteForceUtil(copiedItemIndexVector, result, outcomeSet);
    }


}
void Knapsack::knapsackBruteForce() {

    std::vector<bool> vector(items.size(), true);

    std::vector<bool> outcomeVector;
    int result = 0;
    bruteForceUtil(vector, &result, &outcomeVector);

    printItems(outcomeVector);
}


void Knapsack::printItems(std::vector<bool> itemsVector) {
    printf("----------------------------------\n");
    Item outcomeBagProperties = getPropertiesFromItemIndices(itemsVector);
    printf("max capacity: %d\n", capacity);
    printf("capacity used: %d\n", outcomeBagProperties.weight);
    printf("value: %d\n", outcomeBagProperties.value);
    printf("items in the bag:\n");
    for (int i = 0; i < itemsVector.size(); ++i) {
        if(!itemsVector[i]) continue;
        printf("%d ", i + 1);
    }
    printf("\n----------------------------------\n");
}

Item Knapsack::getPropertiesFromItemIndices(std::vector<Item> vector) {
    Item result={0,0};
    for (auto it:vector) {
        result.weight += it.weight;
        result.value += it.value;
    }
    return result;
}

