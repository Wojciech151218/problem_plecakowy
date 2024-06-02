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

bool compareByWeight(const Item& a, const Item& b) {
    return static_cast<float>(a.value)/a.weight > static_cast<float>(b.value)/b.weight;
}
void Knapsack::sortItems() {
    std::sort(items.begin(), items.end(), compareByWeight);
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

std::vector<Item> Knapsack::knapsackMatrix() {
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
    std::vector<bool> outcomeItemsIndices(items.size(), false);
    while(i> 0 && j> 0){
        if(V[i][j] != V[i-1][j]){
            outcomeItemsIndices[i-1] = true;
            j = j  - items[i-1].weight;

        }
        i--;
    }
    printItems(outcomeItemsIndices);
    std::vector<Item> outcomeItems;
    for (int k = 0; k < outcomeItemsIndices.size(); ++k) {
        if(!outcomeItemsIndices[i]) continue;
        outcomeItems.push_back(items[i]);
    }

    return outcomeItems;
}

bool Knapsack::decideBruteForceAlgorithm() {
    Knapsack testKnapsack(capacity,items);
    std::vector<Item> outcomeItems = testKnapsack.knapsackMatrix();

    return (capacity/2 ) > outcomeItems.size();

    /*int itemsAmount = items.size();
    Item itemProperties = getPropertiesFromItemIndices(items);
    float averageWeight = static_cast<float>(itemProperties.weight)/itemsAmount;
    float averageValue = static_cast<float>(itemProperties.value)/itemsAmount;
    float capacityItemRatio = static_cast<float>(capacity)/itemsAmount;

    float valueToWeightRatio = (averageValue/averageWeight);

    return 2*capacityItemRatio > valueToWeightRatio;*/
}

void Knapsack::bruteForceUtilFront(std::vector<bool> itemIndexSet, int *result, std::vector<bool> *outcomeSet) {
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
        itemIndexSet[i] = false;
        bruteForceUtilFront(itemIndexSet, result, outcomeSet);
        itemIndexSet[i] = true;
    }


}

void Knapsack::bruteForceUtilBack(std::vector<bool> itemIndexSet, int *result, std::vector<bool> *outcomeSet) {
    Item currentBagProperties =  getPropertiesFromItemIndices(itemIndexSet);
    if(currentBagProperties.weight>capacity) return;

    for (int i = 0; i < itemIndexSet.size(); ++i) {
        if(itemIndexSet[i]) continue;
        itemIndexSet[i] = true;
        bruteForceUtilBack(itemIndexSet, result, outcomeSet);
        itemIndexSet[i] = false;
        if(*result<currentBagProperties.value){
            *result = currentBagProperties.value;
            *outcomeSet = std::vector<bool>(itemIndexSet);
        }
    }
}

void Knapsack::knapsackBruteForce(DecisionMode decisionMode) {
    bool algorithmDecision ;
    switch (decisionMode) {
        case Auto:
            algorithmDecision = decideBruteForceAlgorithm();
            break;
        case Front:
            algorithmDecision = true;
            break;
        case Back:
            algorithmDecision = false;
            break;
    }


    std::vector<bool> vector(items.size(), algorithmDecision);

    std::vector<bool> outcomeVector;
    int result = 0;

    sortItems();
    if(algorithmDecision) {
        printf("front mode\n");
        bruteForceUtilFront(vector, &result, &outcomeVector);
    }
    else {
        printf("back mode\n");
        bruteForceUtilBack(vector, &result, &outcomeVector);
    }

    printItems(outcomeVector);
}


void Knapsack::printItems(std::vector<bool> itemsVector) {
    Item outcomeBagProperties = getPropertiesFromItemIndices(itemsVector);
    int itemCount = std::count_if(itemsVector.begin(),itemsVector.end(),[](bool a){return a;});
    printf("----------------------------------\n");
    printf("max capacity: %d\n", capacity);
    printf("capacity used: %d\n", outcomeBagProperties.weight);
    printf("value: %d\n", outcomeBagProperties.value);
    printf("%d item(s) in the bag:\n",itemCount);
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

int Knapsack::getValueFromItems(std::vector<bool> vector) {
    int result = 0;
    for (int i = 0; i < vector.size(); ++i) {
        if(!vector[i]) continue;
        result += items[i].value;
    }
    return result;
}

int Knapsack::getWeightFromItems(std::vector<bool> vector) {
    int result = 0;
    for (int i = 0; i < vector.size(); ++i) {
        if(!vector[i]) continue;
        result += items[i].weight;
    }
    return result;
}

