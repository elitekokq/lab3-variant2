#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "lab3.h"

#define LINE_SIZE 1000

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int get_choice() {
    char line[100];
    int choice;
    char extra;

    while (1) {
        printf("выберите пункт 1-3: ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 3;
        }
        if (sscanf(line, " %d %c", &choice, &extra) == 1 && choice >= 1 && choice <= 3) {
            return choice;
        }
        printf("ошибка: введите 1, 2 или 3\n");
    }
}

int input_numbers(int **numbers, int *count) {
    char line[LINE_SIZE];
    char *p;
    int *a = NULL;
    int n = 0;
    int capacity = 0;

    printf("введите целые числа через пробел: ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }
    int has_newline = 0;
    for (p = line; *p != '\0'; p++) {
        if (*p == '\n') {
            has_newline = 1;
            break;
        }
    }
    if (!has_newline) {
        if (!feof(stdin)) {
            clear_buffer();
            printf("слишком длинная строка\n");
            return 0;
        }
    }

    p = line;
    while (*p != '\0') {
        char *end;
        long value;
        int *temp;

        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        value = strtol(p, &end, 10);
        if (p == end || value < INT_MIN || value > INT_MAX ||
            (*end != '\0' && !isspace((unsigned char)*end))) {
            printf("ошибка: нужны только целые числа через пробел\n");
            free(a);
            return 0;
        }

        if (n == capacity) {
            if (capacity == 0) {
                capacity = 8;
            } else {
                capacity = capacity * 2;
            }
            temp = realloc(a, (size_t)capacity * sizeof(int));
            if (temp == NULL) {
                printf("не хватает памяти\n");
                free(a);
                return 0;
            }
            a = temp;
        }
        a[n++] = (int)value;
        p = end;
    }

    if (n == 0) {
        printf("вы не ввели ни одного числа\n");
        free(a);
        return 0;
    }

    *numbers = a;
    *count = n;
    return 1;
}
