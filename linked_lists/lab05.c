#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
	int i;
	int m, n;
	n_ptr list;

	scanf("%d %d", &m, &n);

	list = new_list();
	list = push(list, 0, n);

	for (i = 0; i < m; i++) {
		char operator;
		scanf(" %c", &operator);   // TODO: Verificar se a leitura de dados está sendo feita corretamente
		switch (operator)
		{
		int adress, blockSize, newBlockSize;

		// Alloc operation
		case 'A':
			scanf("%d", &blockSize);
			memBlockAlloc(list, blockSize);
			break;

		// Dealloc operation
		case 'D':
			scanf("%d%d", &adress, &blockSize);
			memBlockDealloc(list, adress, blockSize);
			break;

		// Realloc operation
		case 'R':
			scanf("%d%d%d", &adress, &blockSize, &newBlockSize);
			break;

		// Print operation
		case 'P':
			break;

		}
	}
	return EXIT_SUCCESS;
}
