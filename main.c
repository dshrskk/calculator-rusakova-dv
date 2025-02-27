#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_INPUT 1024

int evaluate_expression(const char *expr) {
    int stack[MAX_INPUT];
    int top = -1;
    int num = 0;
    int i = 0;

    while (expr[i] != '\0') {
        if (isdigit(expr[i])) {
            num = num * 10 + (expr[i] - '0');
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            if (top >= 1) { // Убедитесь, что стек содержит хотя бы два элемента
                int b = stack[top--];
                int a = stack[top--];
                switch (expr[i]) {
                    case '+':
                        stack[++top] = a + b;
                        break;
                    case '-':
                        stack[++top] = a - b;
                        break;
                    case '*':
                        stack[++top] = a * b;
                        break;
                    case '/':
                        stack[++top] = a / b;
                        break;
                }
            } else {
                stack[++top] = num;
                num = 0;
            }
        } else if (expr[i] == '(') {
            stack[++top] = num;
            num = 0;
        } else if (expr[i] == ')') {
            stack[++top] = num;
            num = 0;
        }
        i++;
    }

    return stack[top];
}

int main() {
    char input[MAX_INPUT];
    fgets(input, MAX_INPUT, stdin);
    int result = evaluate_expression(input);
    printf("%d\n", result);
    return 0;
}
