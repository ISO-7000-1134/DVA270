#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 10

// “Bucket” enligt kursens definition (key-value-par)
typedef struct Bucket
{
    int key;
    char value[20];
} Bucket;

// Nod i länkad lista
typedef struct Node
{
    Bucket data;
    struct Node* next;
} Node;

// Hashtabell: array av pekare till listor
typedef struct HashTable
{
    Node* table[TABLE_SIZE];
} HashTable;

// Funktioner
void initTable(HashTable* ht);

int hash(int key);

void insert(HashTable* ht, int key, const char* value);

char* get(HashTable* ht, int key);

int removeKey(HashTable* ht, int key);

void printTable(HashTable* ht); // valfri, men bra för debug

#endif