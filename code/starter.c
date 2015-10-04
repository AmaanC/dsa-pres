#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

struct stack {
    int top;
    char arr[MAX];
} s;

void initialize(struct stack *s) {
    s->top = -1;
}

void push(struct stack *s, int value) {
    s->top++;
    int top = s->top;
    if (top >= MAX - 1) {
        printf("Cannot push, stack is full.\n");
        return;
    }
    s->arr[top] = value;
}

char seeTop(struct stack *s) {
    int top = s->top;
    if (top < 0) {
        return '\0';
    }
    char retVal = s->arr[top];
    return retVal;
}

char pop(struct stack *s) {
    int top = s->top;
    if (top < 0) {
        printf("Underflow.\n");
        return '\0';
    }
    char retVal = s->arr[top];
    //printf("%d", s->arr[0]);
    s->top--;
    return retVal;
}

int main() {

}