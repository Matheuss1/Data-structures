#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

p_hash newHash(int n)
{
    p_hash table = malloc(sizeof(Hash));
    if (table == NULL)
        exit(1);

    // Starts the hashtable wih NULL values
    table->hashTable = calloc((n * 2), sizeof(Node));
    if (table->hashTable == NULL)
        exit(1);

    table->hashSize = n * 2;

    return table;
}


int hash(char *key, int size)
{
    int i, n = 0;
    int a = strlen(key);
    for (i = 0; i < a; i++) {
        n = (256 * n + key[i]) % size;
    }

    return n;
}


void push(p_hash table, char *key, int index)
{
    int n = hash(key, table->hashSize);

    // creates a new item to put in the hash
    p_node tempNode = malloc(sizeof(Node));
    if (tempNode == NULL)
        exit(1);

    strcpy(tempNode->sequence, key);
    tempNode->index = index;

    // traverses the list until to find an empty index in the table
    while(table->hashTable[n]) {
        if (table->hashSize == n) {
            n = 0;
            continue;
        }

        n++;
    }

    table->hashTable[n] = tempNode;
    
}


int searchPattern(p_hash table, char *key)
{
    int n = hash(key, table->hashSize);
    int aux = n;

    // searchs the key in the hashtable until find a NULL value or a match
    while (table->hashTable[aux]) {
        if (strcmp(table->hashTable[aux]->sequence, key) == 0) {
            int pos = table->hashTable[aux]->index;
            
            return pos;
        }

        if (aux == table->hashSize)
            aux = 0;
        else
            aux++;
    }

    return -1;   
}


void removeHash(p_hash table)
{
    for (int i = 0; i <= table->hashSize; i++)
        free(table->hashTable[i]);
    
    free(table->hashTable);
    free(table);
}