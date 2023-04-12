// Define the Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function prototypes
void printList(struct Node* head);
void insertAtBeginning(struct Node** headRef, int data);
void insertAtEnd(struct Node** headRef, int data);

