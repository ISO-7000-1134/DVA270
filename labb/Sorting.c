#include "Sorting.h"
#include "list.h"
#include "labb-1.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

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

// swap funktion efter pseudokoden från labb 2
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
				Node* temp_current = current; // sätter current till en tillfällig pekare
				swap_nodes(current);
				swapped = 1;

				current = temp_current->previous;
                // om current blir den första moden (head) uppdaterar vi list
				if (current->previous == NULL)
                    *list = current;
			}
			else
				current = current->next; // om ingen swap gjordes
		}
	}while (swapped);
	
}

/// Swaps two blocks of data of size (sizeOfType) at the pointers (a) and (b)
static void swap(void* a, void* b, size_t sizeOfType) {
    void* temp = malloc(sizeOfType);
    assert(temp != NULL);

    memcpy(temp, a, sizeOfType);
    memcpy(a, b, sizeOfType);
    memcpy(b, temp, sizeOfType);
}

/// Recursivly sorts (data) using the merge sort algorythem, which consists of (length) blocks with size (sizeOfType), and uses (compare) to determine order
    // (compare(a, b)) returns a value greater than 0 if (a) "is larger" than (b), 0 if "equal" and a value lsser than 0 if (a) is "smaller"
void MergeSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*)) {
    // Pre conditions
    if (data == NULL)
        return;
    if (sizeOfType == 0)
        return;
    if (compare == NULL)
        return;

    // Handle trivial cases
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

    // Merge sub arrays
    void* data_a = malloc(sizeOfType * (length / 2)); // Copy of data_a in separate memory
    assert(data != NULL);
    memcpy(data_a, data, sizeOfType * (length / 2));
    void* data_a_ptr = data_a;

    size_t i = 0;
    for (; i < length; i++) {
        if (compare(data_a_ptr, data_b) > 0) {
            memcpy(data + (sizeOfType * i), data_b, sizeOfType);
            data_b += sizeOfType;
        } else {
            memcpy(data + (sizeOfType * i), data_a_ptr, sizeOfType);
            data_a_ptr += sizeOfType;
        }

        // Stop merging if data_a or data_b buffer is empty
        if(data_a_ptr >= data_a + sizeOfType * (length / 2))
            break;
        if(data_b > data + (sizeOfType * length)) {
            memcpy(data + (sizeOfType * i), data_a_ptr, data_a + sizeOfType * (length / 2) - data_a_ptr); // Copy rest of data_a into data
            break;
        }
    } 
    free(data_a);
}

/// Shuffles three blocks of data of size (sizeOfType) at the pointers (a), (b) and (c)
    // a <- b <- c
    // |_________^
static void shuffle(void* a, void* b, void* c, size_t sizeOfType) {
    void* temp = malloc(sizeOfType);
    assert(temp != NULL);

    memcpy(temp, a, sizeOfType);
    memcpy(a, b, sizeOfType);
    memcpy(b, c, sizeOfType);
    memcpy(c, temp, sizeOfType);
}
/// Recursivly sorts (data) using the quick sort algorythem, which consists of (length) blocks with size (sizeOfType), and uses (compare) to determine order
    // (compare(a, b)) returns a value greater than 0 if (a) "is larger" than (b), 0 if "equal" and a value lsser than 0 if (a) is "smaller"
void QuickSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*)) {
    // Pre conditions
    if (data == NULL)
        return;
    if (sizeOfType == 0)
        return;
    if (compare == NULL)
        return;

    // Handle trivial cases
    if (length <= 1)
        return;
    if (length == 2) {
        if (compare(data, data + sizeOfType) > 0) 
            swap(data, data + sizeOfType, sizeOfType);
        return; 
    }

    // Chose pivot element as the first element
    size_t pivot = 0;

    // Sort pivot element into array
    for (; pivot < length; pivot++) {
        // Find the last element smaller than pivot 
        size_t i = length - 1;
        for(; i >= pivot + 1; i--) 
            if (compare(data + (sizeOfType * pivot), data + (sizeOfType * (i))) > 0) 
                break;
        if (i == pivot)
            break;
        else
            shuffle(data + (sizeOfType * i), data + (sizeOfType * (pivot + 1)), data + (sizeOfType * pivot), sizeOfType);
    }

    // Sort sub arrays
    QuickSort(data, sizeOfType, pivot, compare);
    QuickSort(data + (sizeOfType * (pivot + 1)), sizeOfType, length - pivot - 1, compare);
}

/// Sorts (data) using the selection sort algorythem, which consists of (length) blocks with size (sizeOfType), and uses (compare) to determine order
    // (compare(a, b)) returns a value greater than 0 if (a) "is larger" than (b), 0 if "equal" and a value lsser than 0 if (a) is "smaller"
void SelectionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*)) {
    // Pre conditions
    if (data == NULL)
        return;
    if (sizeOfType == 0)
        return;
    if (compare == NULL)
        return;
    if (length <= 1)
        return;

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

/// Sorts (data) using the insertion sort algorythem, which consists of (length) blocks with size (sizeOfType), and uses (compare) to determine order
    // (compare(a, b)) returns a value greater than 0 if (a) "is larger" than (b), 0 if "equal" and a value lsser than 0 if (a) is "smaller"
void InsertionSort(void* data, size_t sizeOfType, size_t length, int (*compare)(void*, void*)) {
    // Pre conditions
    if (data == NULL)
        return;
    if (sizeOfType == 0)
        return;
    if (compare == NULL)
        return;
    if (length <= 1)
        return;

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

/// Convert an array (data) of length (length) to a linked list (RadixList)
    // Returns the list
RadixList ArrayToRadixList(int32_t data[], size_t length) {
    // Pre conditions
    if (data == NULL)
        return NULL;
    if (length == 0)
        return NULL;

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
    *previousNextPtr = NULL;

    return list;
}

/// Convert a RadixList (data) to an array (array) of maximum length (length)
    // Returns used length
size_t RadixListToArray(const RadixList data, int32_t array[], size_t length) {
    // Pre conditions
    if (data == NULL)
        return 0;
    if (array == NULL)
        return 0;
    if (length == 0)
        return 0;

    size_t len = 0;
    
    RadixNode* currentNodePtr = data;
    while (currentNodePtr != NULL && len < length) {
        array[len++] = currentNodePtr->data;
        currentNodePtr = currentNodePtr->next;
    }

    return len;
}

/// Convert (data) and the itteration of the radix sort algorythm (iteration) to an index for the hash table in the radix sort algorythem
    // returns the index
static int radixHash(int32_t data, int itteration) {
    // Convert int to uint by maping -1 ... -(0x7fffffff) onto 0x7fffffff ... 0 and 0 ... 0x7fffffff into 0x80000000 ... 0xffffffff
    uint32_t u_data = data ^ 0x80000000;

    // Apply hash
        // use the n'th nibble for the n'th itteration
    return (u_data & (0xf0000000 >> (4 * itteration))) >> (4 * (7 - itteration));
}
/// Sort a RadixList (data) using the radix sort algorythm
void RadixSort(RadixList* data) {
    // Pre conditions
    if (data == NULL)
        return;

    RadixList ht[16]; // heads
    RadixNode** workingNextPtr[16]; // tails

    int i, j;
    // Init working pointers
    for(i = 0; i < 16; i++) {
        workingNextPtr[i] = &(ht[i]);
        ht[i] = NULL;
    }

    int index;
    RadixNode* currentNodePtr = *data;
    RadixNode* tailPtr;
    for(i = 0; i < 8; i++) {
        // Sort data into hash table (buckets)
        while (currentNodePtr != NULL) {
            index = radixHash(currentNodePtr->data, i);
            *(workingNextPtr[index]) = currentNodePtr;
            
            workingNextPtr[index] = &(currentNodePtr->next);
            currentNodePtr = currentNodePtr->next;
        }
            
        // Link hash table into one list
            // Find head 
        currentNodePtr = NULL;
        for(j = 0; currentNodePtr == NULL; j++)
            currentNodePtr = ht[j];
        workingNextPtr[0] = workingNextPtr[j - 1]; // use index 0 as dummy register
        for(; j < 16; j++) 
            // Link to next hash table if not empty
            if (ht[j] != NULL) {
                *(workingNextPtr[0]) = ht[j];
                workingNextPtr[0] = workingNextPtr[j];
            }
        *(workingNextPtr[0]) = NULL; // Define tail

        // Reset working pointers
        for(j = 0; j < 16; j++) {
            workingNextPtr[j] = &(ht[j]);
            ht[j] = NULL;
        }
    }

    // Set list refrence to head
    *data = currentNodePtr;
}