#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

p_hash newHash(int n)
{
    p_hash table = malloc(sizeof(Hash));

    if (table == NULL)
        exit(1);
    n *= 2;
    table->hashTable = calloc(n, sizeof(Node));
    if (table->hashTable == NULL)
        exit(1);

    table->hashSize = 2 * n;

    for (int i = 0; i < table->hashSize; i++)
        table->hashTable[i] = NULL;

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


void push(p_hash table, char *key, int index)
{
    int n = hash(key, table->hashSize);

    p_node temp = malloc(sizeof(Node));
    if (temp == NULL)
        exit(1);

    strcpy(temp->sequence, key);
    temp->index = index;

    while(table->hashTable[n] != NULL) {
        if (n == table->hashSize) {
            n = 0;
            continue;
        }

        n++;
    }
    table->hashTable[n] = temp;
}


void searchPattern(p_hash table, int *ocurrences, int size, char *key)
{
    int j;
    char *temp = malloc((1 + size) * sizeof(char));

    for (j = 0; strlen(&key[j]) >= size; j++) {
        strncpy(temp, &key[j], size);
        temp[size] = '\0';

        int n = hash(temp, table->hashSize);
        int aux = n;

        while (table->hashTable[aux] != NULL) {
            if (strcmp(table->hashTable[aux]->sequence, temp) == 0) {
                int pos = table->hashTable[aux]->index;
                ocurrences[pos] += 1;
                break;
            }
            if (aux == table->hashSize)
                aux = 0;
            else
                aux++;
        }
    }

    free(temp);
}