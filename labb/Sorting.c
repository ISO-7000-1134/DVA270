#include "Sorting.h"
#include "list.h"
#include "labb-1.h"
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

List random_linked_list(int size)
{	 
	List list = NULL;
	for (int i = 0; i < size; i++)
		add_last(&list, rand() % 10 + 1);
	return list;
}

void random_array(int array[], int size)
{ 
	for (int i = 0; i < size; i++)
		array[i] = rand() % 10 + 1;
}

int is_sorted_helper(List list)
{
	List current = list;

	if (current == NULL || current->next == NULL)
		return 1;
	else if (current->data > current->next->data)
		return 0;

	is_sorted_helper(current->next);
}

int is_sorted(List list)
{
	// find head
	while (list->previous != NULL)
		list = list->previous;

	return is_sorted_helper(list);

}

int is_sorted_array(int array[], int size)
{
	for (int i = 0; i < size-1; i++)
	{
		if(array[i] > array[i+1])
			return 0;
	}
	return 1;
}

void swap_nodes(Node* first)
{
	if (first == NULL )
		return;

	if(first->next == NULL)
		return;

	//skapa temporär pekare för nästa element (next)
	Node* next = first->next;
	Node* after_next = next->next;
	Node* before_first = first->previous;

	// Koppla om länkarna mellan first och next
	//sätt nästa element för (first) att vara nästa element för (next)
	first->next = after_next;//next->next;
	//sätt nästa element för (next) att vara (first)
	next->next = first;
	// sätt föregående element för (next) att vara föregående element för (first)
	next->previous = before_first;//first->previous;
	//sätt föregående element för (first) att vara (next)
	first->previous = next;

	//sätt det nästa elementet för det föregående element för (next) (next->previous->next) till (next)
	if (before_first != NULL)
		before_first->next = next;
	//sätt det föregående elementet för nästa element för (first) (first->next->previous) till (first)
	if (after_next != NULL)
		after_next->previous = first;

}

void bubble_sort(List *list)
{	
	if (*list == NULL)
		return;

	int swapped; 
	
	do // sorterar så länge man gjort en swap
	{
		swapped = 0; // antar listan redan är sorterad
		Node* current = *list;
		while (current->next != NULL) // går igenom listan
		{
			if (current->data > current->next->data) // byter plats
			{
				Node* temp_current = current; //  chat. sätter current till en tillfällig pekare
				swap_nodes(current);
				swapped = 1;

				// chat
				current = temp_current->previous;
				if (current->previous == NULL)
                    *list = current;
			}
			else
				current = current->next; // om ingen swap gjordes
		}
	}while (swapped);
	
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
    //    data_a = data
    void* data_b = data + (sizeOfType * (length / 2));
    
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