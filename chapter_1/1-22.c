#include <stdio.h>
#define MAXCOL      10
#define TABSTOP     8

int rearrange(int pos);
int find_last_blank(int pos);
void print_line(int pos);

// Character array to store the current line
char line[MAXCOL];

int main() {
    int c;
    int pos = 0;
    
    while ((c = getchar()) != EOF) {
        line[pos] = c;
        ++pos;
        if (c == '\t') {
            --pos;
            while (pos < MAXCOL && pos % TABSTOP != 0) {
                line[pos] = ' ';
                ++pos;
            }
            
            if (pos >= MAXCOL) {
                print_line(pos);
                pos = 0;
            }
        } else if (c == '\n') {
            --pos;
            print_line(pos);
            pos = 0;
        } else if (pos >= MAXCOL) {
            pos = find_last_blank(pos);
            print_line(pos);
            pos = rearrange(pos);
        }
    }


    return 0;
}

void print_line(int pos) {
    for (int i = 0; i < pos; ++i) {
        putchar(line[i]);
    }
    
    if (pos != 0) {
        putchar('\n');
    }
}

int find_last_blank(int pos) {
    while (pos >= 0 && line[pos] != ' ') {
        --pos;
    }
    
    // No blanks found
    if (pos < 0) {
        return MAXCOL;
    } else {
        return pos + 1;
    }
}

int rearrange(int pos) {
    if (pos == MAXCOL) {
        return 0;
    } else {
        int i = 0;  // index into beginning of line
        for (int j = pos; j < MAXCOL; ++j) {
            line[i] = line[j];
            ++i;
        }
        return i;
    }
}
