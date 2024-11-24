#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000 // Define maximum stack size

int stack[MAX];
int top = -1;

// Function to push a value onto the stack
void push(int value)
{
    if (top < MAX - 1)
    {
        stack[++top] = value;
    }
}

// Function to pop a value from the stack and print it
void pop()
{
    if (top == -1)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d\n", stack[top--]);
    }
}

int main()
{
    char command[10];
    int value;

    // Read commands until encountering "#"
    while (1)
    {
        scanf("%s", command);

        if (strcmp(command, "#") == 0)
        {
            break;
        }

        if (strcmp(command, "PUSH") == 0)
        {
            scanf("%d", &value);
            push(value);
        }
        else if (strcmp(command, "POP") == 0)
        {
            pop();
        }
    }

    return 0;
}
