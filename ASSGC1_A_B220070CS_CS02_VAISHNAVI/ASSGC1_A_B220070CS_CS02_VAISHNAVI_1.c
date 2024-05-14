//Vaishnavi B220070CS: Cycle 1 Part 1 - Question 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arr_stack
{
    int top;
    int capacity;
    char* arr;
};

typedef struct arr_stack* stack;

stack create_stack (int max)
{
    stack new = (stack)malloc(sizeof(struct arr_stack));
    new->arr = (char*)malloc(sizeof(sizeof(char) * max));
    new->top = -1;
    new->capacity = max;
    return new;
}

int empty_stack (stack check)
{
    if (check->top == -1)
       return 1;
    return 0;
}

void push (stack hello, char x)
{
    if (hello->top < hello->capacity -1)
    {
        hello->top++;
        hello->arr[hello->top] = x;
    }
}

char pop (stack world)
{
    if (world->top >= 0)
    {
        char val = world->arr[world->top];
        world->top--;
        return val;
    }
    else if (empty_stack(world) == 1)
        return '\0';
}

int operand (char x)
{
    if (x >= 'a' && x <= 'z')
       return 1;
    return 0;
}

int operator (char x)
{
    if (x=='+' || x=='-' || x=='*' || x=='/' || x=='^' || x=='%')
       return 1;
    return 0;
}

int main ()
{
    int n;
    scanf ("%d", &n);

    char exp[1000];
    getchar();
    fgets(exp, sizeof(exp), stdin);

    int len = strlen(exp);
    if (len>0 && exp[len-1] == '\n')
    {  exp[len-1] = '\0';  }

    stack parentheses = create_stack(n);

    for (int i=0; i<n; i++)
    {
        if (operand(exp[i]))
           continue;

        else if (exp[i] == '(' || operator(exp[i]))
           push(parentheses, exp[i]);

        else if (exp[i] == ')')
        {
            char top_element = pop (parentheses);

            if (top_element == '(')          //Sub-expression without operators is in between parentheses
            {
                printf("1\n");  
                return 0;
            }

            while (top_element != '(')     //Sub-expression has operators so popping them out
            {
                top_element = pop(parentheses);
            }
        }
    }
    printf ("0\n");
    return 0;
}