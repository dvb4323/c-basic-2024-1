#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int id;
    struct Node *firstChild;
    struct Node *nextSibling;
} Node;

Node *root = NULL;

// Function to create a new node
Node *createNode(int id)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = id;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// MakeRoot u: Creates a root node with id `u`
void makeRoot(int u)
{
    root = createNode(u);
}

// Find a node with id `u` in the tree (DFS search)
Node *findNode(Node *current, int u)
{
    if (current == NULL)
        return NULL;
    if (current->id == u)
        return current;
    Node *found = findNode(current->firstChild, u);
    if (found != NULL)
        return found;
    return findNode(current->nextSibling, u);
}

// Insert u v: Insert node `u` as the last child of node `v`
void insert(int u, int v)
{
    Node *parent = findNode(root, v);
    if (parent == NULL)
        return; // If parent node not found, do nothing
    Node *newNode = createNode(u);
    if (parent->firstChild == NULL)
    {
        parent->firstChild = newNode;
    }
    else
    {
        Node *child = parent->firstChild;
        while (child->nextSibling != NULL)
        {
            child = child->nextSibling;
        }
        child->nextSibling = newNode;
    }
}

// Pre-order traversal
void preOrder(Node *current)
{
    if (current == NULL)
        return;
    printf("%d ", current->id);
    preOrder(current->firstChild);
    preOrder(current->nextSibling);
}

// In-order traversal
void inOrder(Node *current)
{
    if (current == NULL)
        return;

    if (current->firstChild)
    {
        inOrder(current->firstChild);
    }
    printf("%d ", current->id);
    if (current->firstChild)
    {
        Node *sibling = current->firstChild->nextSibling;
        while (sibling)
        {
            inOrder(sibling);
            sibling = sibling->nextSibling;
        }
    }
}

// Post-order traversal
void postOrder(Node *current)
{
    if (current == NULL)
        return;

    if (current->firstChild)
    {
        postOrder(current->firstChild);
        Node *sibling = current->firstChild->nextSibling;
        while (sibling)
        {
            postOrder(sibling);
            sibling = sibling->nextSibling;
        }
    }
    printf("%d ", current->id);
}

// Main function
int main()
{
    char command[10];
    int u, v;

    while (1)
    {
        scanf("%s", command);
        if (command[0] == '*')
            break;

        if (strcmp(command, "MakeRoot") == 0)
        {
            scanf("%d", &u);
            makeRoot(u);
        }
        else if (strcmp(command, "Insert") == 0)
        {
            scanf("%d %d", &u, &v);
            insert(u, v);
        }
        else if (strcmp(command, "PreOrder") == 0)
        {
            preOrder(root);
            printf("\n");
        }
        else if (strcmp(command, "InOrder") == 0)
        {
            inOrder(root);
            printf("\n");
        }
        else if (strcmp(command, "PostOrder") == 0)
        {
            postOrder(root);
            printf("\n");
        }
    }

    return 0;
}
