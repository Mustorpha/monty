#include "monty.h"

/**
 * _add - this function adds the top two elements of the stack.
 * @head: points to the head of stack
 * @counter: the line number
 * Return: void
*/
void _add(stack_t **head, unsigned int counter)
{
	stack_t *h;
	int len = 0, aux;

	h = *head;
	while (h)
	{
		h = h->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", counter);
		fclose(opc.file);
		free(opc.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	aux = h->n + h->next->n;
	h->next->n = aux;
	*head = h->next;
	free(h);
}

/**
 * addnode - fucntion that adds node to the head stack
 * @head: head of the stack
 * @n: new alue
 * Return: void
*/
void addnode(stack_t **head, int n)
{

	stack_t *new_node, *aux;

	aux = *head;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{ printf("Error\n");
		exit(0); }
	if (aux)
		aux->prev = new_node;
	new_node->n = n;
	new_node->next = *head;
	new_node->prev = NULL;
	*head = new_node;
}

/**
 * _push - this function adds node to the stack
 * @head: stack head
 * @counter: line_number
 * Return: void
*/
void _push(stack_t **head, unsigned int counter)
{
	int n, j = 0, flag = 0;

	if (opc.arg)
	{
		if (opc.arg[0] == '-')
			j++;
		for (; opc.arg[j] != '\0'; j++)
		{
			if (opc.arg[j] > 57 || opc.arg[j] < 48)
				flag = 1; }
		if (flag == 1)
		{ fprintf(stderr, "L%d: usage: push integer\n", counter);
			fclose(opc.file);
			free(opc.content);
			free_stack(*head);
			exit(EXIT_FAILURE); }}
	else
	{ fprintf(stderr, "L%d: usage: push integer\n", counter);
		fclose(opc.file);
		free(opc.content);
		free_stack(*head);
		exit(EXIT_FAILURE); }
	n = atoi(opc.arg);
	if (opc.sq_flag == 0)
		addnode(head, n);
	else
		addqueue(head, n);
}

/**
 * _pop - function that prints the top
 * @head: stack head
 * @counter: line_number
 * Return: void
*/
void _pop(stack_t **head, unsigned int counter)
{
	stack_t *h;

	if (*head == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", counter);
		fclose(opc.file);
		free(opc.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	*head = h->next;
	free(h);
}

/**
* _execute - this fuction executes the opcode
* @stack: head linked list - stack
* @counter: line_counter
* @file: points to monty file
* @content: line content
* Return: void
*/
int _execute(char *content, stack_t **stack, unsigned int counter, FILE *file)
{
	instruction_t opst[] = {
				{"push", _push}, {"pall", _pall}, {"pint", _pint},
				{"pop", _pop},
				{"swap", _swap},
				{"add", _add},
				{"nop", _nop},
				{"sub", _sub},
				{"div", _div},
				{"mul", _mul},
				{"mod", _mod},
				{"pchar", _putchar},
				{"pstr", _pstr},
				{"rotl", _rotl},
				{"rotr", _rotr},
				{"queue", _queue},
				{"stack", _stack},
				{NULL, NULL}
				};
	unsigned int i = 0;
	char *op;

	op = strtok(content, " \n\t");
	if (op && op[0] == '#')
		return (0);
	opc.arg = strtok(NULL, " \n\t");
	while (opst[i].opcode && op)
	{
		if (strcmp(op, opst[i].opcode) == 0)
		{	opst[i].f(stack, counter);
			return (0);
		}
		i++;
	}
	if (op && opst[i].opcode == NULL)
	{ fprintf(stderr, "L%d: unknown instruction %s\n", counter, op);
		fclose(file);
		free(content);
		free_stack(*stack);
		exit(EXIT_FAILURE); }
	return (1);
}
