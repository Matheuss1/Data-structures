#ifndef LIST_H
#define LIST_H

#define ID_SIZE 5

typedef struct {
    char id[ID_SIZE];
    int group;
} Box;
// box pointer
typedef Box* p_box;

// Creates a newbox with its group and ID
p_box newBox(char identification[], int group);

char *getId(p_box box);

int getBatch(p_box box);

#endif