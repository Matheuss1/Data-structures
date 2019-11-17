#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MAX_SIZE 40001


typedef struct{
    char sequence[MAX_SIZE];
    int index;
} Node;

typedef Node* p_node;


typedef struct {
    p_node *hashTable;
    int hashSize;
} Hash;

typedef Hash* p_hash;


p_hash newHash(int n);

int hash(char *key, int size);

void push(p_hash table, char *key, int index);

void searchPattern(p_hash table, int *ocurrences, int sizeOfPatterns, char *key);

#endif