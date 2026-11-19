#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

int load_test(char *filename, int **numbers, int *count) {
    FILE *file = fopen(filename, "r");
    int *a = NULL;
    int n = 0;
    int capacity = 0;
    int value;

    if (file == NULL) {
        return 0;
    }
    while (fscanf(file, "%d", &value) == 1) {
        if (n == capacity) {
            int new_capacity;
            if (capacity == 0) {
                new_capacity = 100;
            } else {
                new_capacity = capacity * 2;
            }
            int *temp = realloc(a, new_capacity * sizeof(int));
            if (temp == NULL) {
                free(a);
                fclose(file);
                return 0;
            }
            capacity = new_capacity;
            a = temp;
        }
        a[n] = value;
        n++;
    }
    if (!feof(file) || n == 0) {
        free(a);
        fclose(file);
        return 0;
    }
    fclose(file);
    *numbers = a;
    *count = n;
    return 1;
}

double measure_time(int *a, int n, int use_merge) {
    int repeats = 10;
    double total = 0;

    for (int i = 0; i < repeats; i++) {
        Node *head = create_stack(a, n);
        clock_t start;
        clock_t finish;

        if (head == NULL) {
            return -1;
        }
        start = clock();
        if (use_merge) {
            head = merge_sort(head);
        } else {
            head = insertion_sort(head);
        }
        finish = clock();
        total += (double)(finish - start) / CLOCKS_PER_SEC;
        free_stack(head);
    }
    return total * 1000 / repeats;
}

void benchmark() {
    int sizes[] = {100, 250, 500};
    int total = 3;
    printf("\nколичество   вставками (мс)   слиянием (мс)\n");

    for (int i = 0; i < total; i++) {
        char filename[100];
        int *a;
        int n;
        double t1;
        double t2;

        snprintf(filename, sizeof(filename), "tests/test_%d.txt", sizes[i]);
        if (!load_test(filename, &a, &n)) {
            printf("ошибка чтения %s\n", filename);
            return;
        }
        t1 = measure_time(a, n, 0);
        t2 = measure_time(a, n, 1);
        free(a);

        if (t1 < 0 || t2 < 0) {
            printf("не хватает памяти для теста.\n");
            return;
        }
        printf("%-12d %-17.6f %.6f\n", n, t1, t2);
    }
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

    printf("\nисходный ряд: ");
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
        printf("корректные команды: ./lab3 или ./lab3 --file numbers.txt\n");
        return;
    }

    while (1) {
        int choice;
        printf("\n1. ввести числа и отсортировать\n");
        printf("2. сравнить время двух сортировок\n");
        printf("3. выход\n");
        choice = get_choice();

        if (choice == 1) {
            sort_input();
        } else if (choice == 2) {
            benchmark();
        } else {
            break;
        }
    }
}
