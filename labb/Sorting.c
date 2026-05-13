#include "Sorting.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

static void swap(void* a, void* b, size_t sizeOfType) {
    void* temp = malloc(sizeOfType);
    assert(temp != NULL);

    memcpy(temp, a, sizeOfType);
    memcpy(a, b, sizeOfType);
    memcpy(b, temp, sizeOfType);
}

void MergeSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*)) {
    // handle trivial cases
    if (length <= 1)
        return;
    if (length == 2) {
        if (compare(data, data + sizeOfType) > 0) 
            swap(data, data + sizeOfType, sizeOfType);
        return; 
    }

    // Divide into sub arrays
    // data_a = data
    void* data_b = data + (sizeOfType * (length - (length / 2)));
    
    // Sort sub arrays
    MergeSort(data, sizeOfType, length / 2, compare);
    MergeSort(data_b, sizeOfType, length - (length / 2), compare);

    // Combine sub arrays
    for (size_t i = 0; i < length - 1; i++) {
        if (compare(data, data_b) > 0) {
            swap(data, data_b, sizeOfType);
            data += sizeOfType;
        } else 
            data_b += sizeOfType;
    } 
}

void QuickSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*)) {
    if (length <= 1) 
        return;

    // Sort povot element into array
    size_t pivot = 0;
    for (; pivot < length - 1; pivot++) {
        if (compare(data + (sizeOfType * pivot), data + (sizeOfType * (pivot + 1))) > 0) 
            swap(data + (sizeOfType * pivot), data + (sizeOfType * (pivot + 1)), sizeOfType);
        else 
            break;
    } 

    // Sort sub arrays
    QuickSort(data, sizeOfType, pivot, compare);
    QuickSort(data + (sizeOfType * (pivot + 1)), sizeOfType, length - pivot - 1, compare);
}

void SectionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*)) {
    void* min;
    for (size_t i = 0; i < length; i++) {
        min = data + (sizeOfType * i);
        for (size_t j = i; j < length; j++) {
            // Compare current data to the data before
            if (compare(min, data + (sizeOfType * j)) > 0)
                min = data + (sizeOfType * j);
        }
        swap(data + (sizeOfType * i), min, sizeOfType);
    }
}

void InsertionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*)) {
    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = i + 1; j > 0; j--) {
            // Compare current data to the data after
            if (compare(data + (sizeOfType * j), data + (sizeOfType * (j - 1))) < 0)
                swap(data + (sizeOfType * j), data + (sizeOfType * (j - 1)), sizeOfType);
            else 
                break;
        }
    }
}

// ---------------------------------------------------------

RadixList ArrayToRadixList(int32_t data[], size_t length) {
    RadixList list = NULL;

    RadixNode* currentNodePtr;
    RadixNode** previousNextPtr = &list;
    for (size_t i = 0; i < length; i++) {
        currentNodePtr = (RadixNode*)malloc(sizeof(RadixNode));
        currentNodePtr->data = data[i];
        *previousNextPtr = currentNodePtr;

        previousNextPtr = &(currentNodePtr->next);
        currentNodePtr = currentNodePtr->next;
    }

    return list;
}

// Returns used length
size_t RadixListToArray(RadixList data, int32_t array[], size_t length) {
    size_t len = 0;
    
    RadixNode* currentNodePtr = data;
    while (currentNodePtr != NULL && len < length) 
        array[len++] = currentNodePtr->data;

    return len;
}

static int radixHash(int32_t num, int itteration) {
    // Convert int to uint by maping -1 ... -(0x7fffffff) onto 0 ... 0x7fffffff and 0 ... 0x7fffffff into 0x80000000 ... 0xffffffff
    int u_num = num + 0x80000000;

    // Apply hash
        // use the n'th nibble for the n'th itteration
    return (u_num & (0xf0000000 >> itteration)) >> (7 - itteration);
}
void RadixSort(RadixList* data) {
    RadixList ht[16]; // heads
    RadixList* workingNextPtr[16]; // tails

    int i, j;
    // Init working pointers
    for(int i = 0; i < 16; i++) 
        workingNextPtr[i] = &(ht[i]);

    int index;
    RadixNode* currentNodePtr = *data;
    for(i = 0; i < 8; i++) {
        // Sort data into hash table (buckets)
        while (currentNodePtr != NULL) {
            index = radixHash(currentNodePtr->data, i * 2);
            *(workingNextPtr[index]) = currentNodePtr;
            workingNextPtr[index] = &(currentNodePtr->next);
        }
            
        // Link hash tables into one list and reset working next pointers to point at the hash
        currentNodePtr = ht[0];
        for(j = 0; j < 15; j++) { 
            *(workingNextPtr[j]) = ht[j + 1];
            workingNextPtr[j] = &(ht[j]);
        }
        *(workingNextPtr[15]) = NULL;
        workingNextPtr[15] = &(ht[15]);
    }
}