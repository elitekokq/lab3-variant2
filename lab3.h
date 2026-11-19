#ifndef LAB3_H
#define LAB3_H

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int get_choice();
int input_numbers(int **numbers, int *count);

Node *push(Node *top, int value);
Node *create_stack(int *numbers, int count);
void free_stack(Node *head);
Node *insertion_sort(Node *head);
Node *merge_sort(Node *head);

void print_numbers(int *a, int n);
void print_stack(Node *head);
int save_numbers(char *filename, int *a, int n, Node *sorted);
void show_file(char *filename);
int load_test(char *filename, int **numbers, int *count);
double measure_time(int *a, int n, int use_merge);
void benchmark();
void sort_input();

void run_program(int argc, char *argv[]);

#endif
