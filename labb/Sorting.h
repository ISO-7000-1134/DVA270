#include <stdint.h>

#ifndef SORTING_H
#define SORTING_H

void MergeSort(void* data, size_t sizeOfType, size_t length, int (*compare)(int a, int b));
void QuickSort(void* data, size_t sizeOfType, size_t length, int (*compare)(int a, int b));
void SectionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(int a, int b));
void InsertionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(int a, int b));

typedef struct radixNode
{
	int32_t data;
	struct radixNode* next;
}RadixNode;
typedef RadixNode* RadixList;

RadixList ArrayToRadixList(int32_t data[], size_t length);
int32_t* ArrayToRadixList(RadixList data, size_t* lengthPtr);

void RadixSort(RadixList* data);

#endif