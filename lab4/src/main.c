#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
typedef struct _stack{
    int vals[1001];
    int size;
} Stack;
 
void push (Stack *st, const int val){
    st->vals[st->size] = val;
    st->size++;
}
 
int pop (Stack *st){
    if (st->size == 0){
        printf("syntax error");
        exit(0);
    }
    st->size--;
    return st->vals[st->size];
}
 
int peek (Stack *st){
    if (st->size <= 0){
        printf("syntax error");
        exit(0);
    }
    return st->vals[st->size - 1];
}
 
bool isOperator (char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}
 
bool isDigit (char c){
    return c >= '0' && c <= '9';
}
 
bool goodSymb (char c){
    return isOperator(c) || isDigit(c) || c == '\n';
}
 
int priority (char c){
    if (c == '(' || c == ')') return 0;
    else
    if (c == '+' || c == '-') return 1;
    else
    if (c == '*' || c == '/') return 2;
    return 0;
}
 
void  shantinYard(char* str, int size, char* output){
    int outSize = 0;
    Stack stack;
    stack.size = 0;
 
    for (int i = 0; i < size; ++i){
        if (isDigit(str[i])){
            while (!isOperator(str[i])){
                output[outSize] = str[i];
                outSize++;
                i++;
                if (i == size) break;
            }
            output[outSize] = ' ';
            outSize++;
            i--;
        }
        if(isOperator(str[i])){
            if(str[i] == '('){
                push(&stack, (int)str[i]);
            } else
            if(str[i] == ')'){
                if(i == 0 || str[i-1] == '('){
                    printf("syntax error");
                    exit(0);
                }
                char c = (char)pop(&stack);
                while(c != '('){
                    output[outSize] = c;
                    output[outSize + 1] = ' ';
                    outSize += 2;
                    c = (char)pop(&stack);
                }
            }
            else{
                if(stack.size > 0 && priority(str[i]) <= priority((char)peek(&stack))){
                    output[outSize] = (char)pop(&stack);
                    output[outSize + 1] = ' ';
                    outSize += 2;
                }
                push(&stack, (int)str[i]);
            }
        }
    }
 
    while(stack.size > 0){
        output[outSize] = (char)pop(&stack);
        output[outSize + 1] = ' ';
        outSize += 2;
    }
    output[outSize] = '\0';
}
 
int count(char* str){
    int result = 0;
    Stack s;
    s.size = 0;
    int size = strlen(str);
 
    for(int i = 0; i < size; i++){
        if(isDigit(str[i])){
            int tmp = 0;
            while (!isOperator(str[i]) && str[i] != ' ') {
                tmp *= 10;
                tmp += (int)(str[i] - '0');
                i++;
                if (i == size) {
                    break;
                }
            }
            push(&s, tmp);
            i--;
        }
        else if(isOperator(str[i])){
            int a = pop(&s),
                    b = pop(&s);
 
            if(str[i] == '+'){
                result = b + a;
            }
            if(str[i] == '-'){
                result = b - a;
            }
            if(str[i] == '*'){
                result = b * a;
            }
            if(str[i] == '/'){
                if(a == 0){
                    printf("division by zero");
                    exit(0);
                }
                result = b / a;
            }
 
            push(&s, result);
        }
    }
    return peek(&s);
}
 
int main()
{
    FILE * in = fopen("in.txt", "r");
    char str[1001] = {0};
    if (fscanf(in, "%1000[^\n]s", str) == 0) {
        printf("syntax error");
        fclose(in);
        return 0;
    }
    int size = (int)strlen(str);
 
    for (int i = 0; i < size; i++) {
        if (!goodSymb(str[i])) {
            printf("syntax error");
            fclose(in);
            return 0;
        }
    }
 
    char postfix[2002] = {0};
    shantinYard(str, size, postfix);
    printf("%d", count(postfix));
    fclose(in);
    return 0;
}
