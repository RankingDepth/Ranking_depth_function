#include <algorithm>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

// Test 1
int testFunc(){
    int a = 0;
    int b = a + 1;
    return 43;
}

// Test 2
int testFuncCmp(double* val, double* obj, int n, double* output){
    output[9] = (val[0] + obj[9]) * n;
    return 0;
}

// Calculate the Kendal-tau distance between two ranks
int distKendalTau(int* order1, int* order2, int d){
    int tmpDist = 0;
    // For all pairs of indices of the same orientation,
    for (int i = 0; i < d; i++){
        for (int j = i; j < d; j++){
            // append the concordane of the ranks
            tmpDist += (order1[i] - order1[j]) *
                (order2[i] - order2[j]) < 0 ? 1 : 0;
        }
    }
    return tmpDist;
}

// Calculate the depths of all objects w.r.t. data
int depthKendalTau(int* objects, int* data,
                int d, int nObjects, int nData,
                double* depths){
    // Loop through the objects
    for (int i = 0; i < nObjects; i++){
        // For each object: calculate the depth
        int tmpDepth = 0;
        for (int j = 0; j < nData; j++){
            tmpDepth += distKendalTau(&objects[i * d], &data[j * d], d);
        }
        // Return the depth of the current object
        depths[i] = (d * (d - 1) / 2 - tmpDepth / (double)nData) /
            (double)(d * (d - 1) / 2);
    }
    return 0;
}

// Calculate number of orders that posses the same depth for a data set
int depthCardsKendallTau(int* data, int d, int nData,
                     int* nDepths, double* depths, int* cards){
    // Allocate memory for all possible depths
    int maxDepths = nData * (d * (d - 1) / 2 + 1);
    int* subDepths = new int[maxDepths];
    int* counts = new int[maxDepths];
    // Initialize the counts
    for (int i = 0; i < maxDepths; i++){
        counts[i] = 0;
    }
    // Define the smallest (lexicographically) permutation
    int* tmpOrder = new int[d];
    for (int i = 0; i < d; i++){
        tmpOrder[i] = i;
    }
    // Address all permutations
    int nOrders = 0;
    do {
        nOrders++;
        // Logic processing the order
        int tmpDistance = 0;
        for (int i = 0; i < nData; i++){
            tmpDistance += distKendalTau(tmpOrder, &data[i * d], d);
        }
        // Save/count the order's depth
        counts[tmpDistance]++;
        // Check the condition
    } while (std::next_permutation(tmpOrder, tmpOrder + d));
    *nDepths = maxDepths;
    // Post-process counts
    for (int i = 0; i < maxDepths; i++){
        cards[i] = counts[i];
    }
    // Free the memory
    delete[] subDepths;
    delete[] counts;
    delete[] tmpOrder;
    //for (int i = 0; i < 7; i++){
    //    // Work with permutation
    //    memcpy(cards + i * d, tmpOrder, d * sizeof(int));
    //    // Go to the next permutation
    //    std::next_permutation(tmpOrder, tmpOrder + d);
    //}
    return 0;
}

#ifdef __cplusplus
}
#endif
