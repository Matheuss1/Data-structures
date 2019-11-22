#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"


// Creates a new box and returns a pointer to it
p_box newBox(char identification[], int group)
{
    p_box newBox = malloc(sizeof(Box));
    strcpy(newBox->id, identification);
    newBox->group = group;
    return newBox;
}


// Returns the string that identifies the box (id field)
char *getId(p_box box)
{
    return box->id;
}


// Returns the current box batch
int getBatch(p_box box)
{
    return box->group;
}
