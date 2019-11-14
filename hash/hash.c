#include <stdlib.h>
#include <string.h>

#include "hash.h"

p_hash newHash(int n)
{
    p_hash table = malloc(sizeof(Hash));

    if (table == NULL)
        exit(1);
    
    table->hashTable = malloc(n * sizeof(Node));
    if (table->hashTable == NULL)
        exit(1);

    table->items = malloc(n * sizeof(p_item));
    if (table->items == NULL)
        exit(1);

    for (int i = 0; i < n; i++)
        table->hashTable[i] = NULL;
    
    table->hashSize = n;

    return table;
}


int hash(char *key, int size)
{
    int i, n = 0;

    for (i = 0; i < strlen(key); i++) {
        n = (256 * n + key[i]) % size;
    }

    return n;
}


void push(p_hash table, char *key, int i)
{
    int n = hash(key, table->hashSize);

    p_node k = malloc(sizeof(Node));
    if (k == NULL)
        exit(1);

    strcpy(k->sequence, key);

    if (table->hashTable[n] == NULL)
        table->hashTable[n] = k;
    else {
        while (table->hashTable[n] != NULL)
            n++;

        table->hashTable[n] = k;
    }

    p_item x = malloc(sizeof(HashItemInfos));
    if (x == NULL)
        exit(1);

    x->size = strlen(key);
    table->items[i] = x;
}


p_node search(p_hash table, char *key)
{
    
}

