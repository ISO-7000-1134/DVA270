#ifndef SORTING_H
#define SORTING_H

void MergeSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b));
void QuickSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b));
void SectionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b));
void InsertionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b));

typedef struct radixNode
{
	int data;
	struct radixNode* next;
} RadixNode;
typedef RadixNode* RadixList;

RadixList ArrayToRadixList(int data[], size_t length);
int* ArrayToRadixList(RadixList data, size_t* lengthPtr);

void RadixSort(RadixList* data);

#endif