//
// Created by wojciech on 13.05.24.
//

#include "Knapsack.h"
Item Knapsack::getPropertiesFromItemIndices(std::vector<bool> vector){
    Item result={0,0};
    for (int i = 0; i < vector.size(); ++i) {
        if(!vector[i]) continue;
        result.weight += items[i].weight;
        result.value += items[i].value;
    }
    return result;
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
    while(i> 0 && j> 0){
        if(V[i][j] != V[i-1][j]){
            printf("%d ",i);
            j = j  - items[i-1].weight;

        }
        i--;
    }
    printf("\n");
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
    for (int i = 0; i < items.size(); ++i)
        vector[i] = true;
    std::vector<bool> outcomeVector;
    int result = 0;
    bruteForceUtil(vector, &result, &outcomeVector);
    for (int i = 0; i < outcomeVector.size(); ++i) {
        if(!outcomeVector[i]) continue;
        printf("%d ", i+1);
    }
    printf("\n");

}


