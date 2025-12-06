#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value) {
    if (top >= MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = value;
    printf("PUSH -> %d\n", value);
}

void pop() {
    if (top < 0) {
        printf("POP -> Stack is empty\n");
        return;
    }
    printf("POP -> %d\n", stack[top--]);
}

void printStack() {
    printf("STACK: ");
    for (int i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("\n");
}

int main() {
    FILE *file = fopen("simulation.txt", "r");
    if (!file) {
        printf("Error: could not open simulation.txt\n");
        return 1;
    }

    char command[20];
    int value;

    while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "PUSH") == 0) {
            fscanf(file, "%d", &value);
            push(value);
        }
        else if (strcmp(command, "POP") == 0) {
            pop();
        }
        else if (strcmp(command, "PRINT") == 0) {
            printStack();
        }
        else {
            printf("Unknown command: %s\n", command);
        }
    }

    fclose(file);
    return 0;
}

