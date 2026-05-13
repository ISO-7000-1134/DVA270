#include <stdint.h>
#include <stdlib.h>
#include "list.h"

#ifndef SORTING_H
#define SORTING_H
List random_linked_list(int size);
void random_array(int array[], int size);
int is_sorted(List list);
int is_sorted_array(int array[], int size);

void MergeSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*));
void QuickSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*));
void SectionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*));
void InsertionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*));
void bubble_sort(List *list);

typedef struct radixNode
{
	int32_t data;
	struct radixNode* next;
}RadixNode;
typedef RadixNode* RadixList;

RadixList ArrayToRadixList(int32_t data[], size_t length);
size_t RadixListToArray(const RadixList data, int32_t array[], size_t length);

void RadixSort(RadixList* data);

#endif