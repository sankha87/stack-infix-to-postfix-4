// C program to convert infix expression to postfix  
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <conio.h>

// Stack type 
struct Stack
{
	int top;
	unsigned capacity;
	int* array;
};

// Stack Operations 
struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));

	if (!stack)
		return NULL;

	stack->top = -1;
	stack->capacity = capacity;

	stack->array = (int*)malloc(stack->capacity * sizeof(int));

	return stack;
}
int isEmpty(struct Stack* stack)
{
	return stack->top == -1;
}
char peek(struct Stack* stack)
{
	return stack->array[stack->top];
}
char pop(struct Stack* stack)
{
	if (!isEmpty(stack))
		return stack->array[stack->top--];
	return '$';
}
void push(struct Stack* stack, char op)
{
	stack->array[++stack->top] = op;
}


// A utility function to check if the given character is operand 
int isOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// A utility function to return precedence of a given operator 
// Higher returned value means higher precedence 
int Prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}


// The main function that converts given infix expression 
// to postfix expression.  
int infixToPostfix(char* exp)
{
	int i, k;
	char postfix[30] = {};
	// Create a stack of capacity equal to expression size  
	struct Stack* stack = createStack(strlen(exp));
	if (!stack) // See if stack was created successfully  
		return -1;

	for (i = 0, k = 0; exp[i]; ++i)
	{
		// If the scanned character is an operand, add it to output. 
		if (isOperand(exp[i]))
		{
			postfix[k] = exp[i];
			k++;
		}
		// If the scanned character is an ‘(‘, push it to the stack. 
		else if (exp[i] == '(')
			push(stack, exp[i]);

		// If the scanned character is an ‘)’, pop and output from the stack  
		// until an ‘(‘ is encountered. 
		else if (exp[i] == ')')
		{
			while (!isEmpty(stack) && peek(stack) != '(')
			{
				postfix[k] = pop(stack);
				k++;
			}
			if (!isEmpty(stack) && peek(stack) != '(')
				return -1; // invalid expression              
			else
				pop(stack);
		}
		else // an operator is encountered 
		{
			while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
			{
				postfix[k] = pop(stack);
				k++;
			}
			push(stack, exp[i]);
		}
	}

	// pop all the operators from the stack 
	while (!isEmpty(stack))
	{
		postfix[k] = pop(stack);
		k++;
	}
	postfix[k] = '\0';
	printf("%s", postfix);
}

// Driver program to test above functions 
void main()
{
	char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
	infixToPostfix(exp);
	printf("\n\n");
	char exp2[] = "a-b/c*d)^e";
	infixToPostfix(exp2);
	_getch();
}