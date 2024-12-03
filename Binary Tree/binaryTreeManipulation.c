#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int id;
    struct Node *left;
    struct Node *right;
} Node;

Node *root = NULL;

Node *createNode(int id)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = id;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *findNode(Node *current, int id)
{
    if (!current)
        return NULL;
    if (current->id == id)
        return current;
    Node *leftResult = findNode(current->left, id);
    if (leftResult)
        return leftResult;
    return findNode(current->right, id);
}

void makeRoot(int id)
{
    root = createNode(id);
}

void addLeft(int u, int v)
{
    if (findNode(root, u))
        return; // Node with id u already exists
    Node *parent = findNode(root, v);
    if (!parent || parent->left)
        return; // Parent doesn't exist or already has a left child
    parent->left = createNode(u);
}

void addRight(int u, int v)
{
    if (findNode(root, u))
        return; // Node with id u already exists
    Node *parent = findNode(root, v);
    if (!parent || parent->right)
        return; // Parent doesn't exist or already has a right child
    parent->right = createNode(u);
}

void preOrder(Node *current)
{
    if (!current)
        return;
    printf("%d ", current->id);
    preOrder(current->left);
    preOrder(current->right);
}

void inOrder(Node *current)
{
    if (!current)
        return;
    inOrder(current->left);
    printf("%d ", current->id);
    inOrder(current->right);
}

void postOrder(Node *current)
{
    if (!current)
        return;
    postOrder(current->left);
    postOrder(current->right);
    printf("%d ", current->id);
}

int main()
{
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
