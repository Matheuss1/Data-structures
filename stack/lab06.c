#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"

#define SIZE 1000

void removeDigit(char digits[], st_ptr stack, int toBeRemoved);
void printStackReverse(st_ptr stack);

int main()
{
	int m, n;

	scanf("%d", &m);

	int i;
	char digits[SIZE];
	st_ptr greatestNumber = newStack();

	for (i = 0; i < m; i++) {
		scanf("%s %d", digits, &n);
		removeDigit(digits, greatestNumber, n);
		printStackReverse(greatestNumber);
	}
	removeStack(greatestNumber);


	return EXIT_SUCCESS;
}


// Builds the greatest number removing n digits
void removeDigit(char digits[], st_ptr stack, int toBeRemoved)
{
	int i; // Aux
	// GreatestNumber will never be this low, but needs a value to be initialized
	int greatestNumber = -1, index; 

	// If the len of the given array it's equal the digits to be removed, then
	// we "delete" the entire array
	if (strlen(digits) == toBeRemoved)
		return;

	// if there is not to be removed, we push all the remaining elements in the given array
	if (toBeRemoved == 0) {
		for (i = 0; i < strlen(digits); i++) {
			push(stack, digits[i]);
		}
		return;
	}


	for (i = 0; i < toBeRemoved + 1; i++) {
		if ((digits[i] - '0') > greatestNumber) {
			greatestNumber = digits[i] - '0';
			index = i;
		}
	}
	if (index == 0) {
		push(stack, digits[0]);
		removeDigit(&digits[1], stack, toBeRemoved);
	}
	else {
		push(stack, digits[index]);
		removeDigit(&digits[index + 1], stack, toBeRemoved - index);
	}
}


void printStackReverse(st_ptr stack)
{
	st_ptr temp = newStack();

	while(!isEmpty(stack))
		push(temp, pop(stack));
	
	while(!isEmpty(temp))
		printf("%d", pop(temp) - '0');
	printf("\n");
	removeStack(temp);
}