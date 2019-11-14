#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MAX_SIZE 40001


typedef struct{
    char sequence[MAX_SIZE];
    int data;
} Node;

typedef Node* p_node;


typedef struct {
    int ocurrences;
    int size;
} HashItemInfos;

typedef HashItemInfos* p_item;


typedef struct {
    p_node *hashTable;
    p_item *items;
    int hashSize;
} Hash;

typedef Hash* p_hash;


p_hash newHash(int n);

int hash(char *key, int size);

void push(p_hash table, char *key, int i);


#endif
