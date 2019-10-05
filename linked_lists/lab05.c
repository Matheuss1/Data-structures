#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void printHeap(n_ptr list);

int main()
{
	int i;
	int m, n;
	n_ptr list;

	scanf("%d %d", &m, &n);

	list = new_list(n);

	for (i = 0; i < m; i++) {
		char operator;
		scanf(" %c", &operator);
		switch (operator)
		{
		int adress, blockSize, newBlockSize;

		// Alloc operation
		case 'A':
			scanf("%d", &blockSize);
			list = memBlockAlloc(list, blockSize);
			break;

		// Dealloc operation
		case 'D':
			scanf("%d%d", &adress, &blockSize);
			list = memBlockDealloc(list, adress, blockSize);
			break;
	
		// Realloc operation
		case 'R':
			scanf("%d%d%d", &adress, &blockSize, &newBlockSize);
			list = memRealloc(list, adress, blockSize, newBlockSize);
			break;

		// Print operation
		case 'P':
			printHeap(list);
			break;

		}
	}
	return EXIT_SUCCESS;
}

// Print the heap
void printHeap(n_ptr list)
{
    n_ptr current;

	printf("heap:\n");
    for (current = list; current != NULL; current = current->next) {
		if (current->index < 0|| current->freeMemory);
        printf("%d %d\n", current->index, current->freeMemory);
    }
}