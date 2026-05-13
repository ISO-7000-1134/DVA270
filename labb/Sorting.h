#include <stdint.h>
#include <stdlib.h>

#ifndef SORTING_H
#define SORTING_H

void MergeSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*));
void QuickSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*));
void SectionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*));
void InsertionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*));

typedef struct radixNode
{
	int32_t data;
	struct radixNode* next;
}RadixNode;
typedef RadixNode* RadixList;

RadixList ArrayToRadixList(int32_t data[], size_t length);
size_t RadixListToArray(RadixList data, int32_t array[], size_t length);

void RadixSort(RadixList* data);

#endif