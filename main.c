#include <stdio.h>  
#include <ctype.h>  
#include <stdlib.h> 


char ch;

void get_next_char() {
    ch = getchar(); 
}
void consume_whitespace() {
    while (isspace(ch)) { 
        get_next_char();  
    }
}

int parse_expression() {
    int value = parse_term(); 

    while (ch == '+' || ch == '-') {
        char op = ch;          
        get_next_char();       
        consume_whitespace();  

        if (op == '+') {      
            value += parse_term();
        } else if (op == '-') { 
            value -= parse_term();
        }
    }

    return value; 
}

int parse_term() {
    int value = parse_factor(); 

    while (ch == '*' || ch == '/') {
        char op = ch;           
        get_next_char();        
        consume_whitespace();   

        if (op == '*') {        // 
            value *= parse_factor();
        } else if (op == '/') { 
            int divisor = parse_factor(); 
            if (divisor == 0) {         
                fprintf(stderr, "Ошибка: Деление на ноль\n");
                exit(EXIT_FAILURE);      
            }
            value /= divisor;            
        }
    }

    return value; 
}

(F -> число | (E))
int parse_factor() {
    consume_whitespace(); 

    if (ch == '(') { 
        get_next_char();              
        int value = parse_expression(); 
        consume_whitespace();        

        if (ch != ')') { 
            fprintf(stderr, "Ошибка: Ожидается ')'\n");
            exit(EXIT_FAILURE); 
        }

        get_next_char(); 
        return value;   
    } else { 
        int value = 0;

        if (!isdigit(ch)) {
            fprintf(stderr, "Ошибка: Ожидается число\n");
            exit(EXIT_FAILURE); 
        }

        while (isdigit(ch)) {
            value = value * 10 + (ch - '0'); 
            get_next_char();                
        }

        return value; 
    }
}

int main() {
    get_next_char(); 
    int result = parse_expression();

    consume_whitespace();

    // Проверяем, что достигнут конец ввода
    if (!feof(stdin)) {
        fprintf(stderr, "Ошибка: Неожиданные символы после выражения\n");
        return EXIT_FAILURE; 
    }
    printf("%d\n", result);

    return 0; 
}
