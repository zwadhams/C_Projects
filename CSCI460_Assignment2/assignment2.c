#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 50
#define MAX_VALUE 100

// Node structure for the doubly linked list
typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

// Doubly Linked List structure
typedef struct {
    Node *head, *tail;
    int size;
} LinkedList;

// Initialize mutex and condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// Function prototypes
void add_node(LinkedList *list, int value);
void remove_node(LinkedList *list, int odd);
void *producer_1(void *arg);
void *producer_2(void *arg);
void *consumer_1(void *arg);
void *consumer_2(void *arg);
void print_list(LinkedList *list, const char *filename);

// Initialize the linked list
LinkedList buffer = {NULL, NULL, 0};

// Main function
int main() {
    srand(time(NULL));

    pthread_t prod1, prod2, cons1, cons2;

    // Create producer and consumer threads
    pthread_create(&prod1, NULL, producer_1, NULL);
    pthread_create(&prod2, NULL, producer_2, NULL);
    pthread_create(&cons1, NULL, consumer_1, NULL);
    pthread_create(&cons2, NULL, consumer_2, NULL);

    // Wait for threads to finish
    pthread_join(prod1, NULL);
    pthread_join(prod2, NULL);
    pthread_join(cons1, NULL);
    pthread_join(cons2, NULL);

    return 0;
}

// Add a node to the sorted linked list
void add_node(LinkedList *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = new_node->prev = NULL;

    pthread_mutex_lock(&mutex);

    while (list->size == BUFFER_SIZE) {
        pthread_cond_wait(&not_full, &mutex);
    }

    // Insert node in sorted order
    Node *current = list->head;
    if (current == NULL) {
        list->head = list->tail = new_node;
    } else {
        while (current != NULL && current->data < value) {
            current = current->next;
        }
        if (current == NULL) {
            new_node->prev = list->tail;
            list->tail->next = new_node;
            list->tail = new_node;
        } else {
            new_node->next = current;
            new_node->prev = current->prev;
            if (current->prev) {
                current->prev->next = new_node;
            } else {
                list->head = new_node;
            }
            current->prev = new_node;
        }
    }
    list->size++;
    print_list(list, value % 2 == 0 ? "producer_2_output.txt" : "producer_1_output.txt");

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
}

// Remove a node from the head of the linked list based on odd/even condition
void remove_node(LinkedList *list, int odd) {
    pthread_mutex_lock(&mutex);

    while (list->size == 0) {
        pthread_cond_wait(&not_empty, &mutex);
    }

    Node *head = list->head;
    if ((odd && head->data % 2 == 1) || (!odd && head->data % 2 == 0)) {
        list->head = head->next;
        if (list->head) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL;
        }
        list->size--;
        free(head);
        print_list(list, odd ? "consumer_1_output.txt" : "consumer_2_output.txt");
    }

    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);
}

// Producer 1 (generates odd numbers)
void *producer_1(void *arg) {
    while (1) {
        int num = rand() % MAX_VALUE + 1;
        if (num % 2 == 1) {
            add_node(&buffer, num);
        }
        sleep(1);
    }
    return NULL;
}

// Producer 2 (generates even numbers)
void *producer_2(void *arg) {
    while (1) {
        int num = rand() % MAX_VALUE + 1;
        if (num % 2 == 0) {
            add_node(&buffer, num);
        }
        sleep(1);
    }
    return NULL;
}

// Consumer 1 (consumes odd numbers)
void *consumer_1(void *arg) {
    while (1) {
        remove_node(&buffer, 1);
        sleep(1);
    }
    return NULL;
}

// Consumer 2 (consumes even numbers)
void *consumer_2(void *arg) {
    while (1) {
        remove_node(&buffer, 0);
        sleep(1);
    }
    return NULL;
}

// Print the current state of the linked list to a file
void print_list(LinkedList *list, const char *filename) {
    FILE *f = fopen(filename, "a");
    Node *current = list->head;
    fprintf(f, "Buffer: ");
    while (current != NULL) {
        fprintf(f, "%d ", current->data);
        current = current->next;
    }
    fprintf(f, "\n");
    fclose(f);
}
