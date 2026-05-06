#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "list.h"

// Initiera hashtabellen genom att sätta alla pekare till NULL
void initTable(HashTable* ht)
{
    for (int i = 0; i < TABLE_SIZE; i++) 
        ht->table[i] = NULL;
}

// Enkel hashfunktion som beräknar en position i arrayen beroende på key
int hash(int key)
{
    return key % TABLE_SIZE;
}

// Från labb 2

// labb 3

// Insert
void insert(HashTable* ht, int key, const char* value)
{
    // TODO:
    // 1. Beräkna index
    int index = hash(key);
    // 2. Gå igenom listan
    //    - Om key finns: uppdatera value
    Node* current = (*ht).table[index];
    while (current != NULL)
    {
        if (current->data.key == key) // om key finns
        {
            // free(current->data.value);
            strcpy(current->data.value, value);
            return;
        }
        current = current->next;
    }
    // 3. Annars: lägg till ny nod (förslagsvis i början)
    add_first(&((*ht).table[index]), (Bucket){.key = key, .value = ""});
    Node* newNode = (*ht).table[index];
    strcpy(newNode->data.value, value);
}

// Get
char* get(HashTable* ht, int key)
{
    // TODO:
    // 1. Beräkna index
    // 2. Traversera listan
    // 3. Returnera value om hittad, annars NULL

    int index = hash(key);
    Node* current = ht->table[index];
    while (current != NULL)
    {
        if (current->data.key == key) 
            return current->data.value;
        current = current->next;
    }

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

    int index = hash(key);
    Node* current = ht->table[index];
    Node** previous_next_ptr = &(ht->table[index]);
    while (current != NULL)
    {
        if (current->data.key == key) {
            *previous_next_ptr = current->next;
            free(current)
            return 1;
        }
        previous_next_ptr = &(current->next);
        current = current->next;
    }
    
    return 0;
}

// Debugfunktion som skriver ut allt som finns i tabellen
void printTable(HashTable* ht)
{

}