#ifndef LAB3_H
#define LAB3_H

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int get_choice(void);
int input_numbers(int **numbers, int *count);

Node *create_stack(int *numbers, int count);
void free_stack(Node *head);
Node *insertion_sort(Node *head);
Node *merge_sort(Node *head);

void run_program(int argc, char *argv[]);

#endif
