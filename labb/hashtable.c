#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

// Initiera hashtabellen genom att sätta alla pekare till NULL
void initTable(HashTable* ht)
{
    for (int i = 0; i < TABLE_SIZE; i++) 
        ht->table[i] = NULL
}

// Enkel hashfunktion som beräknar en position i arrayen beroende på key
int hash(int key)
{
    return key % TABLE_SIZE
}


// Insert
void insert(HashTable* ht, int key, const char* value)
{
    // TODO:
    // 1. Beräkna index
    // 2. Gå igenom listan
    //    - Om key finns: uppdatera value
    // 3. Annars: lägg till ny nod (förslagsvis i början)
}

// Get
char* get(HashTable* ht, int key)
{
    // TODO:
    // 1. Beräkna index
    // 2. Traversera listan
    // 3. Returnera value om hittad, annars NULL

    return NULL;
}

// Remove
int removeKey(HashTable* ht, int key)
{
    // TODO:
    // 1. Beräkna index
    // 2. Ta bort nod från listan
    // 3. Frigör minne
    // 4. Returnera 1 om borttagen, annars 0

    return 0;
}

// Debugfunktion som skriver ut allt som finns i tabellen
void printTable(HashTable* ht)
{

}