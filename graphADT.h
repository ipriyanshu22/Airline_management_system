
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include "linkedList_func.h"

void createAdjList( linkedList* adjList[], int n)
{
    for (int i=0; i<n; i++)
    {
        adjList[i]=create();
        
    }
}



// Function to compare two dates
int compareDates(struct date *date1, struct date *date2) {
    if (date1->year < date2->year) {
        return -1;
    } else if (date1->year > date2->year) {
        return 1;
    } else {
        if (date1->month < date2->month) {
            return -1;
        } else if (date1->month > date2->month) {
            return 1;
        } else {
            if (date1->day < date2->day) {
                return -1;
            } else if (date1->day > date2->day) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

typedef struct queuenode{
    int source;
    int priority;
    struct queuenode* next;
} qnode;

typedef struct priorqueue {
    qnode* front;
} PriorityQueue;

// Function to create a new node
qnode* createNode(int source, int priority) {
    qnode* newq = (qnode*)malloc(sizeof(qnode));
    newq->source = source;
    newq->priority = priority;
    newq->next = NULL;
    return newq;
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
void enqueue(PriorityQueue* pq, int source, int priority) {
    qnode* newq = createNode(source, priority);

    // If the priority queue is empty or the new node has higher priority than the front node
    if (isEmpty(pq) || priority < pq->front->priority) {
        newq->next = pq->front;
        pq->front = newq;
    } 
    else{
        qnode* q2 = pq->front;

        // Traverse the priority queue to find the appropriate position to insert the new node
        while (q2->next != NULL && q2->next->priority < priority) {
            q2 = q2->next;
        }

        newq->next = q2->next;
        q2->next = newq;
    }
}

// Function to remove the element with the highest priority from the priority queue
int dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty.\n");
        return -1;
    }

    qnode* temp = pq->front;
    int s = temp->source;
    pq->front = pq->front->next;
    free(temp);
    return s;
}


struct path dja(enum places source, enum places dest, enum days day,linkedList* adj_list[]){
    int visited[10];
    struct p pa;
    struct path trip;
    trip.num = 0;
    pa.num = 0;
    int t[10];
    for (int i = 0; i < 10; i++) {
        visited[i] = 0;
        t[i] = 999999999;
    }
    t[source] = 0;
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, source, 0);
    while(!isEmpty(pq)){
        int s = dequeue(pq);
        if(visited[s] == 1){
            continue;
        }
        pa.fl[pa.num++] = s;
        int time;
        visited[s] = 1;
        linkedList* temp = adj_list[s]->next;
        while(temp != NULL){
            if(temp->fl.details.day != day && pa.num == 1){
                visited[temp->fl.details.dest] = 1;
                temp = temp->next;
                continue;
            }
            time = t[s] + timediff1(temp->fl.details.deptime, temp->fl.details.arrtime);
            if(visited[temp->fl.details.dest] == 0){
                t[temp->fl.details.dest] = time;
                enqueue(pq, temp->fl.details.dest, t[temp->fl.details.dest]);
            }
            else{
                if(time < t[temp->fl.details.dest]){
                    t[temp->fl.details.dest] = time;
                    enqueue(pq, temp->fl.details.dest, t[temp->fl.details.dest]);
                }
            }
            visited[temp->fl.details.dest] = 1;
            if(temp->fl.details.dest == dest){
                pa.fl[pa.num++] = dest;
                trip.route[trip.num++] = temp->fl;
                return trip;
            }
            temp = temp->next;
        }
        linkedList* temp2 = adj_list[s]->next;
        while(temp2 != NULL){
            if(temp2->fl.details.source == s && temp2->fl.details.dest == pa.fl[pa.num-1]){
                trip.route[trip.num] = temp2->fl;
                trip.num++;
                break;
            }
            temp2 = temp2->next;
        }
        
    }
    printf("Flight unavailable\n");
    trip.num = 0;
    return trip;
}

struct path dja_cost(enum places source, enum places dest, enum days day,linkedList* adj_list[],int p_arr[3]){
    int visited[10];
    struct p pa;
    struct path trip;
    trip.num = 0;
    pa.num = 0;
    int t[10][3];
    for (int i = 0; i < 10; i++) {
        visited[i] = 0;
        for(int j = 0; j < 3; j++){
            t[i][j] = 999999999;
        }
    }
    t[source][0] = 0;
    t[source][1] = 0;
    t[source][2] = 0;
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, source, 0);
    while(!isEmpty(pq)){
        int s = dequeue(pq);
        if(visited[s] == 1){
            continue;
        }
        pa.fl[pa.num++] = s;
        int cost,cost1;
        visited[s] = 1;
        linkedList* temp = adj_list[s]->next;
        while(temp != NULL){
            if(temp->fl.details.day != day && pa.num == 1){
                visited[temp->fl.details.dest] = 1;
                temp = temp->next;
                continue;
            }
            cost = t[s][0] + t[s][1] + t[s][2] + p_arr[0]*temp->fl.details.first + p_arr[1]*temp->fl.details.business + p_arr[2]*temp->fl.details.economy;
            cost1 = p_arr[0]*t[temp->fl.details.dest][0] + p_arr[1]*t[temp->fl.details.dest][1] + p_arr[2]*t[s][temp->fl.details.dest];
            if(visited[temp->fl.details.dest] == 0){
                t[temp->fl.details.dest][0] = p_arr[0]*temp->fl.details.first;
                t[temp->fl.details.dest][1] = p_arr[1]*temp->fl.details.business;
                t[temp->fl.details.dest][2] = p_arr[2]*temp->fl.details.economy;
                enqueue(pq, temp->fl.details.dest, cost);
            }
            else{
                if(cost < cost1){
                    t[temp->fl.details.dest][0] = p_arr[0]*temp->fl.details.first;
                    t[temp->fl.details.dest][1] = p_arr[1]*temp->fl.details.business;
                    t[temp->fl.details.dest][2] = p_arr[2]*temp->fl.details.economy;
                    enqueue(pq, temp->fl.details.dest, cost);
                }
            }
            visited[temp->fl.details.dest] = 1;
            if(temp->fl.details.dest == dest){
                pa.fl[pa.num++] = dest;
                trip.route[trip.num++] = temp->fl;
                return trip;
            }
            temp = temp->next;
        }
        linkedList* temp2 = adj_list[s]->next;
        while(temp2 != NULL){
            if(temp2->fl.details.source == s && temp2->fl.details.dest == pa.fl[pa.num-1]){
                trip.route[trip.num] = temp2->fl;
                trip.num++;
                break;
            }
            temp2 = temp2->next;
        }
        
    }
    printf("Flight unavailable\n");
    trip.num = 0;
    return trip;
}