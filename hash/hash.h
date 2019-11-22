#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "list.h"

typedef struct {
    p_node *hashTable;
    int hashSize;
} Hash;

typedef Hash* p_hash;


// Creates a new hash
p_hash newHash(int n);

// Function used to calc the pos of an item in the hashtable
int hash(char *key, int size);

// Pushs an item in the hashtable
void push(p_hash table, char *key, int index);

// Makes the search of a pattern in the key string, if it founds a match, than returns
// it index field, otherwise returns -1
int searchPattern(p_hash table, char *key);

// Frees the memory allocated for the hash
void removeHash(p_hash Table);

#endif