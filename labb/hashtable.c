#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "list.h"
#include "labb-1.h"
#include "labb-1.h"

// Initiera hashtabellen genom att sätta alla pekare till NULL
void initTable(HashTable* ht)
{
    for (int i = 0; i < TABLE_SIZE; i++) 
        ht->table[i] = NULL;
}

// Enkel hashfunktion som beräknar en position i arrayen beroende på key
int hash(int key)
{
    return ((key % TABLE_SIZE) + TABLE_SIZE) % TABLE_SIZE; // make sure hash is in valid range
}


// Insert
void insert(HashTable* ht, int key, const char* value)
{
    // // TODO:
    // // 1. Beräkna index
    // // 2. Gå igenom listan
    // //    - Om key finns: uppdatera value
    // // 3. Annars: lägg till ny nod (förslagsvis i början)
    
    int index = hash(key);
    Node* current = ht->table[index];
    Node** previous_next_ptr = &(ht->table[index]);
    while (current != NULL)
    {
        if (current->data.key == key) {
            strcpy(current->data.value, value);
            return;
        }
        previous_next_ptr = &(current->next);
        current = current->next;
    }

    current = (Node*)malloc(sizeof(Node));

    if (current == NULL)
        return;

    Bucket data;
    data.key = key;
    strcpy(data.value, value);

    current->data = data;
    current->next = NULL;
    
    *previous_next_ptr = current;    
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
            free(current);
            return 1;
        }
        previous_next_ptr = &(current->next);
        current = current->next;
    }
    
    return 0;
}

// Debugfunktion som skriver ut allt som finns i tabellen
#define BUCKET_STRING_BUFFER_SIZE 64
void printTable(HashTable* ht)
{
    char strBuffer[BUCKET_STRING_BUFFER_SIZE];
    Node* node;

    if (ht == NULL) {
        sprintf(strBuffer, "no hash table found.\n\r");
        uarte_write(strBuffer, strlen(strBuffer));
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        sprintf(strBuffer, "\n\rid: %d\n\r", i);
        uarte_write(strBuffer, strlen(strBuffer));

        node = ht->table[i];
        while(node != NULL) {
            sprintf(strBuffer, "    key: %d, value: %s\n\r", node->data.key, node->data.value);
            uarte_write(strBuffer, strlen(strBuffer));
            node = node->next;
        }
    }
}