#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab3.h"

void print_numbers(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void print_stack(Node *head) {
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int save_numbers(char *filename, int *a, int n, Node *sorted) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return 0;
    }

    fprintf(file, "исходный ряд: ");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", a[i]);
    }
    fprintf(file, "\nотсортированный ряд: ");
    while (sorted != NULL) {
        fprintf(file, "%d ", sorted->value);
        sorted = sorted->next;
    }
    fprintf(file, "\n");

    if (fclose(file) != 0) {
        return 0;
    }
    return 1;
}

void show_file(char *filename) {
    FILE *file = fopen(filename, "r");
    int c;
    if (file == NULL) {
        printf("не удалось открыть файл %s\n", filename);
        return;
    }
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    fclose(file);
}

void sort_input() {
    int *numbers = NULL;
    int count = 0;
    Node *stack;

    if (!input_numbers(&numbers, &count)) {
        return;
    }
    stack = create_stack(numbers, count);
    if (stack == NULL) {
        printf("не удалось создать стек.\n");
        free(numbers);
        return;
    }

    printf("исходный ряд: ");
    print_numbers(numbers, count);
    printf("стек (с вершины): ");
    print_stack(stack);

    stack = insertion_sort(stack);
    printf("отсортированный ряд: ");
    print_stack(stack);

    if (save_numbers("numbers.txt", numbers, count, stack)) {
        printf("результат сохранён в numbers.txt\n");
    } else {
        printf("не удалось сохранить файл.\n");
    }
    free_stack(stack);
    free(numbers);
}

void run_program(int argc, char *argv[]) {
    if (argc == 3 && strcmp(argv[1], "--file") == 0) {
        show_file(argv[2]);
        return;
    }
    if (argc != 1) {
        printf("использование: ./lab3 или ./lab3 --file numbers.txt\n");
        return;
    }

    while (1) {
        int choice;
        printf("\n1. ввести числа и отсортировать\n");
        printf("2. показать сохранённый файл\n");
        printf("3. выход\n");
        choice = get_choice();

        if (choice == 1) {
            sort_input();
        } else if (choice == 2) {
            show_file("numbers.txt");
        } else {
            break;
        }
    }
}
