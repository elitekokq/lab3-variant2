#include <stdlib.h>
#include "lab3.h"

Node *create_stack(int *numbers, int count) {
    Node *top = NULL;

    for (int i = 0; i < count; i++) {
        Node *node = malloc(sizeof(Node));
        if (node == NULL) {
            free_stack(top);
            return NULL;
        }
        node->value = numbers[i];
        node->next = top;
        top = node;
    }
    return top;
}

void free_stack(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

Node *insertion_sort(Node *head) {
    Node *sorted = NULL;

    while (head != NULL) {
        Node *next = head->next;

        if (sorted == NULL || head->value < sorted->value) {
            head->next = sorted;
            sorted = head;
        } else {
            Node *p = sorted;
            while (p->next != NULL && p->next->value <= head->value) {
                p = p->next;
            }
            head->next = p->next;
            p->next = head;
        }
        head = next;
    }
    return sorted;
}

Node *merge(Node *a, Node *b) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (a != NULL && b != NULL) {
        if (a->value <= b->value) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a != NULL ? a : b;
    return dummy.next;
}

Node *merge_sort(Node *head) {
    Node *slow;
    Node *fast;
    Node *middle;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    slow = head;
    fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    middle = slow->next;
    slow->next = NULL;
    return merge(merge_sort(head), merge_sort(middle));
}
