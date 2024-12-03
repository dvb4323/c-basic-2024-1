// Instead of searching the tree every time with findNode, store pointers to all nodes in a hash table.
// This reduces the time complexity of node lookup from
// 𝑂(𝑛) to O(1) on average.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of nodes
#define MAX_NODES 50000

// Definition of the tree node
typedef struct Node
{
    int id;
    struct Node *left;
    struct Node *right;
} Node;

// Node pointers array for O(1) lookup
Node *nodeTable[MAX_NODES];
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

// Function to compute the height and check if the tree is balanced
int isBalanced(Node *current, int *height)
{
    if (!current)
    {
        *height = 0;
        return 1;
    }

    int leftHeight = 0, rightHeight = 0;
    int leftBalanced = isBalanced(current->left, &leftHeight);
    int rightBalanced = isBalanced(current->right, &rightHeight);

    *height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    if (!leftBalanced || !rightBalanced)
        return 0;
    if (abs(leftHeight - rightHeight) > 1)
        return 0;

    return 1;
}

int main()
{
    // Initialize the node lookup table
    memset(nodeTable, 0, sizeof(nodeTable));

    char command[50];
    while (1)
    {
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strcmp(command, "*") == 0)
            break;

        if (strncmp(command, "MakeRoot", 8) == 0)
        {
            int id;
            sscanf(command, "MakeRoot %d", &id);
            makeRoot(id);
        }
        else if (strncmp(command, "AddLeft", 7) == 0)
        {
            int u, v;
            sscanf(command, "AddLeft %d %d", &u, &v);
            addLeft(u, v);
        }
        else if (strncmp(command, "AddRight", 8) == 0)
        {
            int u, v;
            sscanf(command, "AddRight %d %d", &u, &v);
            addRight(u, v);
        }
    }

    int height = 0;
    int balanced = isBalanced(root, &height);
    printf("%d %d\n", balanced, height);

    return 0;
}
