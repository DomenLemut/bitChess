#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Queue
{
    struct Node *front;
    struct Node *rear;
};

struct Queue *initQueue()
{
    struct Queue *new = (struct Queue *)malloc(sizeof(struct Queue));
    new->front = NULL;
    new->rear = NULL;
}

void enqueue(struct Queue *queue, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if (queue->rear == NULL)
        queue->front = queue->rear = newNode;

    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(struct Queue *queue)
{
    if (queue->front == NULL)
        return -1;

    int value = queue->front->data;
    struct Node *temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    if (queue->front == NULL)
        queue->rear = NULL;

    return value;
}

void display(struct Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements are:\n");
    struct Node *temp = queue->front;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    struct Queue *new = initQueue();
    for (int i = 0; i < 200; i++)
    {
        enqueue(new, i);
    }
    display(new);
    return 0;
}
