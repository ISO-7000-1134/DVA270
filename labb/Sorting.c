#include "Sorting.h"
#include <stdlib.h>
#include <stdint.h>

static void swap(void* a, void* b) {
    void temp = *a;
    *a = *b;
    *b = temp;
}

void MergeSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b)) {
    if (length == 1) return;

    // Divide into sub arrays
    // data_a = data
    void* data_b = data + (sizeOfType * (length - (length / 2)));
    
    // Sort sub arrays
    MergeSort(data, sizeOfType, length / 2, compare);
    MergeSort(data_b, sizeOfType, length - (length / 2), compare);

    // Combine sub arrays
    for (size_t i = 0; i < length - 1; i++) {
        if (compare(*data, *data_b) < 0) {
            swap(data, data_b);
            data += sizeOfType;
        } else 
            data_b += sizeOfType;
    } 
}

void QuickSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b)) {
    if (length == 1) 
        return;

    // Sort povot element into array
    size_t pivot = 0;
    for (; pivot < length - 1; pivot++) {
        if (compare(*(data + (sizeOfType * pivot)), *(data + (sizeOfType * (pivot + 1)))) > 0) 
            swap(data + (sizeOfType * pivot), data + (sizeOfType * (pivot + 1)));
        else 
            break;
    } 

    // Sort sub arrays
    QuickSort(data, sizeOfType, pivot, compare);
    QuickSort(data + (sizeOfType * (pivot + 1)), sizeOfType, length - pivot - 1, compare);
}

void SectionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b)) {
    void* min;
    for (size_t i = 0; i < length; i++) {
        for (size_t j = i; j < length; j++) {
            // Compare current data to the data before
            if (compare(*min, *(data + (sizeOfType * (j - 1)))) > 0)
                min = data + (sizeOfType * (j - 1));
        }
        swap(data + (sizeOfType * i), min);
    }
}

void InsertionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b)) {
    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = i + 1; j > 0; j--) {
            // Compare current data to the data after
            if (compare(*(data + (sizeOfType * j)), *(data + (sizeOfType * (j - 1)))) > 0)
                swap(data + (sizeOfType * j), data + (sizeOfType * (j - 1)));
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

int32_t* RadixListToArray(RadixList data, size_t* lengthPtr) {
    size_t length = 0;
    int32_t* array = NULL;

    RadixNode* currentNodePtr = data;
    while (currentNodePtr != NULL) {
        realloc(array, sizeof(int32_t) * (length + 1));
        array[length] = currentNodePtr->data;
        length++;
    }

    return array;
}

static void radixHash(int32_t num, int itteration) {
    // Convert int to uint by making -1 ... -(0x7fffffff) into 0 to 0x7fffffff and 0 - 0x7fffffff into 0x80000000 - 0xffffffff
    int u_num = num + 0x80000000;

    // Apply hash
    return (u_num & (0xf0000000 >> itteration)) >> (7 - itteration);
}
void RadixSort(RadixList* data) {
    RadixList ht[16];
    RadixList* workingNextPtr[16];

    int i, j;
    for(int i = 0; i < 16; i++) 
        workingNextPtr[j] = &(ht[j]);

    RadixNode* currentNodePtr = *data;
    for(i = 0; i < 8; i++) {
        while (currentNodePtr != NULL) {
            *(workingNextPtr[radixHash(currentNodePtr->data, i * 2)]) = currentNodePtr;
            workingNextPtr[index] = &(currentNodePtr->next);
        }
            
        currentNodePtr = ht[0];
        for(j = 0; j < 15; j++) { 
            *(workingNextPtr[j]) = ht[j + 1];
            workingNextPtr[j] = &(ht[j]);
        }
        workingNextPtr[15] = &(ht[15]);
    }
}