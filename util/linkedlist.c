#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a Node structure

struct Node
{
    int data;
    struct Node *next;
};

typedef struct
{
    struct Node *front;
    struct Node *end;
} LinkedList;

LinkedList initList()
{
    LinkedList list;
    list.front = NULL;
    list.end = NULL;
}

bool isEmpty(LinkedList list);

// Function to print the contents of the linked list
void printList(LinkedList list)
{
    struct Node *current = list.front;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void insertAtBeginning(LinkedList list, int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = list.front;
    list.front = new_node;

    if (isEmpty(list))
        list.end = new_node;
}

int pop(LinkedList list)
{
    if (isEmpty(list))
        return 0;

    struct Node *save = list.front;
    list.front = list.front->next;

    int saveData = list.front->data;
    free(save);

    return saveData;
}

// Function to insert a new node at the end of the linked list
void insertAtEnd(LinkedList list, int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;

    if (isEmpty(list))
        list.front = new_node;
    list.end = new_node;
}

bool isEmpty(LinkedList list)
{
    return (list.front == NULL && list.end == NULL);
}

int main()
{
    LinkedList list = initList();
    printf("%d\n", isEmpty(list));
    insertAtBeginning(list, 1);
    insertAtBeginning(list, 2);
    insertAtBeginning(list, 3);
    insertAtBeginning(list, 4);
    insertAtBeginning(list, 5);
    insertAtBeginning(list, 6);
    insertAtBeginning(list, 7);
    insertAtBeginning(list, 8);

    printf("%d\n", isEmpty(list));
}
