#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

typedef struct PriorityQueue {
    Node* front;
} PriorityQueue;

// Function to create a new node
Node* createNode(int data, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->front = NULL;
    return pq;
}

// Function to check if the priority queue is empty
int isEmpty(PriorityQueue* pq) {
    return (pq->front == NULL);
}

// Function to insert an element into the priority queue
void enqueue(PriorityQueue* pq, int data, int priority) {
    Node* newNode = createNode(data, priority);

    // If the priority queue is empty or the new node has higher priority than the front node
    if (isEmpty(pq) || priority < pq->front->priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        Node* current = pq->front;

        // Traverse the priority queue to find the appropriate position to insert the new node
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to remove the element with the highest priority from the priority queue
int dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty.\n");
        return -1;
    }

    Node* temp = pq->front;
    int data = temp->data;
    pq->front = pq->front->next;
    free(temp);
    return data;
}

// Function to display the elements in the priority queue
void display(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty.\n");
        return;
    }

    Node* current = pq->front;
    printf("Priority Queue: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    PriorityQueue* pq = createPriorityQueue();

    enqueue(pq, 5, 2);
    enqueue(pq, 10, 1);
    enqueue(pq, 15, 3);
    enqueue(pq, 20, 2);

    display(pq);

    printf("Dequeued element: %d\n", dequeue(pq));
    printf("Dequeued element: %d\n", dequeue(pq));

    display(pq);

    return 0;
}
