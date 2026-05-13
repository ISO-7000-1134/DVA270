#include <stdint.h>
#include "list.h"

#ifndef SORTING_H
#define SORTING_H
List random_linked_list(int size);
void random_array(int array[], int size);
int is_sorted(List list);
int is_sorted_array(int array[], int size);

void bubble_sort(List *list);
void MergeSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b));
void QuickSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b));
void SectionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b));
void InsertionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void a, void b));

typedef struct radixNode
{
	int32_t data;
	struct radixNode* next;
}RadixNode;
typedef RadixNode* RadixList;

RadixList ArrayToRadixList(int32_t data[], size_t length);
int32_t* RadixListToArray(RadixList data, size_t* lengthPtr);

void RadixSort(RadixList* data);

#endif