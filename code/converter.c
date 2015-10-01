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

int operand(char c) {
    // Returns 0 if c is an operator
    // Returns 1 if c is an operand (like a or c)
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

int getValueForOperator(char op) {
    int val = 0;
    switch(op) {
        case '/':
            val = 4;
            break;
        case '*':
            val = 3;
            break;
        case '+':
            val = 2;
            break;
        case '-':
            val = 1;
            break;
        default:
            val = 0;
            break;
    }
    return val;
}

int higherPrecedence(char op1, char op2) {
    // Returns 1 if op1 has higher precedence. 0 otherwise
    int val1 = getValueForOperator(op1);
    int val2 = getValueForOperator(op2);
    return val1 > val2;
}

char* convertToPostfix(char* exp, int len) {
    char *result;
    result = malloc(len);
    int resultI = 0; // Iterates over result
    int i = 0; // Iterates over input
    char c;
    char temp;

    /* Modified Rules:
        1) If it is an operand, write it to the output string
        2) If it is an operator:
            a) if (c == '(')
                pushToStack
            b) else if (c == ')')
                pop and add to output till you find the '('
            c) if (stack.length == 0 || c == '(' || higherPrecedence(c, seeTop(stack)))
                pushToStack
            d) else
                pop all from stack and add to output
    */

    while (exp[i] != '\0' && i < len) {
        c = exp[i];
        if (operand(c)) {
            result[resultI] = c;
            resultI++;
        }
        else {
            if (c == '(') {
                push(&s, c);
            }
            else if (c == ')') {
                temp = pop(&s);
                while (temp != '(' && s.top >= 0) {
                    result[resultI] = temp;
                    resultI++;
                    temp = pop(&s);
                }
            }
            else if (s.top < 0 || higherPrecedence(c, seeTop(&s))) {
                push(&s, c);
            }
            else {
                while (s.top >= 0) {
                    temp = pop(&s);
                    result[resultI] = temp;
                    resultI++;
                }
            }
        }
        i++;
    }

    while (s.top >= 0) {
        temp = pop(&s);
        result[resultI] = temp;
        resultI++;
    }
    result[resultI] = '\0';
    printf("%s\n", result);
    return result;
}

void printTest(int result) {
    if (result == 1) {
        printf("Test passed.\n");
    }
    else {
        printf("----- Test failed! ------\n");
    }
}

void testFns() {
    printTest(operand('a'));
    printTest(operand('8'));
    printTest(!operand('+'));
    printTest(higherPrecedence('*', '-'));
    printTest(!higherPrecedence('-', '-'));

    printTest(
        strcmp(convertToPostfix("a+b", 4), "ab+") == 0
    );
    printTest(
        strcmp(convertToPostfix("a+b*c", 6), "abc*+") == 0
    );
    printTest(
        strcmp(convertToPostfix("(a+b)*c", 8), "ab+c*") == 0
    );
    printTest(
        strcmp(convertToPostfix("a+(b*c)", 8), "abc*+") == 0
    );
    printTest(
        strcmp(convertToPostfix("(a*b)+(b*c)", 11), "ab*bc*+") == 0
    );
    printTest(
        strcmp(convertToPostfix("(a*b)", 11), "ab*") == 0 // Making sure the wrong length works too
    );
}

int main() {
    initialize(&s);
    testFns();
    return 0;
}