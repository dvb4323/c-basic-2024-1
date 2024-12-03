#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of nodes
#define MAX_NODES 100000

// Definition of the tree node
typedef struct Node
{
    int id;
    struct Node *left;
    struct Node *right;
} Node;

// Node pointers array for O(1) lookup
Node *nodeTable[MAX_NODES + 1];
Node *root = NULL;

// Function to create a new node
Node *createNode(int id)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = id;
    newNode->left = NULL;
    newNode->right = NULL;
    nodeTable[id] = newNode; // Store the node for O(1) lookup
    return newNode;
}

// Function to add the root node
void makeRoot(int id)
{
    root = createNode(id);
}

// Function to add a left child
void addLeft(int u, int v)
{
    if (nodeTable[u] != NULL)
        return; // Node with id u already exists
    Node *parent = nodeTable[v];
    if (!parent || parent->left)
        return; // Parent doesn't exist or already has a left child
    parent->left = createNode(u);
}

// Function to add a right child
void addRight(int u, int v)
{
    if (nodeTable[u] != NULL)
        return; // Node with id u already exists
    Node *parent = nodeTable[v];
    if (!parent || parent->right)
        return; // Parent doesn't exist or already has a right child
    parent->right = createNode(u);
}

// Function to check if a subtree is a max-heap
int isMaxHeap(Node *current)
{
    if (!current)
        return 1;
    if ((current->left && current->id < current->left->id) ||
        (current->right && current->id < current->right->id))
        return 0;
    return isMaxHeap(current->left) && isMaxHeap(current->right);
}

// Function to count nodes having two children in a subtree
int countNodesWithTwoChildren(Node *current)
{
    if (!current)
        return 0;
    int count = (current->left && current->right) ? 1 : 0;
    return count + countNodesWithTwoChildren(current->left) + countNodesWithTwoChildren(current->right);
}

int main()
{
    // Initialize the node lookup table
    memset(nodeTable, 0, sizeof(nodeTable));

    // First block: Construct the tree
    char command[50];
    while (1)
    {
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strcmp(command, "*") == 0)
            break;

        if (strncmp(command, "make-root", 9) == 0)
        {
            int id;
            sscanf(command, "make-root %d", &id);
            makeRoot(id);
        }
        else if (strncmp(command, "add-left", 8) == 0)
        {
            int u, v;
            sscanf(command, "add-left %d %d", &u, &v);
            addLeft(u, v);
        }
        else if (strncmp(command, "add-right", 9) == 0)
        {
            int u, v;
            sscanf(command, "add-right %d %d", &u, &v);
            addRight(u, v);
        }
    }

    // Second block: Process queries
    while (1)
    {
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strcmp(command, "***") == 0)
            break;

        if (strncmp(command, "is-max-heap", 11) == 0)
        {
            int u;
            sscanf(command, "is-max-heap %d", &u);
            Node *subRoot = nodeTable[u];
            printf("%d\n", isMaxHeap(subRoot));
        }
        else if (strncmp(command, "count-nodes-having-2-children", 29) == 0)
        {
            int u;
            sscanf(command, "count-nodes-having-2-children %d", &u);
            Node *subRoot = nodeTable[u];
            printf("%d\n", countNodesWithTwoChildren(subRoot));
        }
    }

    return 0;
}
