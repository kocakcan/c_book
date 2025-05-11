/* An alternate organization uses getline to read an entire input line; this
 * makes getch and ungetch unnecessary. Revise the calculator to use this
 * approach. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP   100    // Max size of operand or operator
#define NUMBER  '0'    // Signal that a number was found
#define BUFSIZE 100    // Input buffer size
#define MAXVAL  100    // Maximum depth of val stack

char buf[BUFSIZE];     // Input line buffer
int bufp = 0;     // Current position in buf

// Stack
int sp = 0;             // Next free stack position
double val[MAXVAL];     // Value stack

// Function declarations
int getop(char []);
void push(double);
double pop(void);
int getline_(void);

int main(void) {
    int type;
    double op1, op2;
    char s[MAXOP];

    while (getline_() > 0) {
        bufp = 0;  // Reset input buffer position at start of line

        while ((type = getop(s)) != '\0') {
            switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                op1 = pop();
                if ((int)op2 != 0)
                    push((int)op1 % (int)op2);
                else
                    printf("error: zero divisor for modulus\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
        }
    }

    return 0;
}

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// Reads next operator or numeric operand into s
int getop(char s[]) {
    int i = 0;
    int c;

    // Skip whitespace
    while ((c = buf[bufp++]) == ' ' || c == '\t')
        ;

    if (c == '\0')
        return '\0';

    s[0] = c;
    s[1] = '\0';

    // Not a number
    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    // Handle negative numbers
    if (c == '-') {
        int next = buf[bufp];
        if (!isdigit(next) && next != '.') {
            return '-';  // Minus operator
        }
        c = buf[bufp++];
        s[++i] = c;
    }

    // Integer part
    while (isdigit(c = buf[bufp++]))
        s[++i] = c;

    // Fractional part
    if (c == '.') {
        s[++i] = c;
        while (isdigit(c = buf[bufp++]))
            s[++i] = c;
    }

    s[++i] = '\0';

    if (c != '\0')
        bufp--;  // Unread one character

    return NUMBER;
}

// Reads a line of input into buf
int getline_() {
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n' && i < BUFSIZE - 1)
        buf[i++] = c;

    if (c == '\n')
        buf[i++] = c;

    buf[i] = '\0';
    return i;
}
