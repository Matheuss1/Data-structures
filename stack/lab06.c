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

	// repeats m operations
	for (i = 0; i < m; i++) {
		scanf("%s %d", digits, &n);

		removeDigit(digits, greatestNumber, n);

		printStackReverse(greatestNumber);
	}
	// frees memory used to alloc the greatestNumber stack 
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

	// if there is nothing to be removed, we push to stack all remaining elements in the given array
	if (toBeRemoved == 0) {
		for (i = 0; i < strlen(digits); i++) {
			push(stack, digits[i]);
		}
		return;
	}

	// traverse the array until certain index, lookin for the greatest number and put it index in a variable
	for (i = 0; i < toBeRemoved + 1; i++) {
		if ((digits[i] - '0') > greatestNumber) {
			greatestNumber = digits[i] - '0';
			index = i;
		}
	}

	// if index of the greatest number it's equal to zero, we just continue to the next function call
	// without count a remotion, otherwise we call the function remove digit again with the number of
	// digits to be removed less the digits that came before the index
	if (index == 0) {
		push(stack, digits[0]);
		removeDigit(&digits[1], stack, toBeRemoved);
	}
	else {
		push(stack, digits[index]);
		removeDigit(&digits[index + 1], stack, toBeRemoved - index);
	}
}


// Push the items from an stack to a temp stack that starts from the greatest number to the lowest
// while pop the items from the original stack that will be empty in the end

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