#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for a tree node
typedef struct Node
{
    int id;
    struct Node *parent;
    struct Node *leftMostChild;
    struct Node *rightSibling;
} Node;

Node *root = NULL;

// Function to create a new node
Node *makeNode(int u)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->id = u;
    p->parent = NULL;
    p->leftMostChild = NULL;
    p->rightSibling = NULL;
    return p;
}

// Function to find a node by ID in the tree
Node *find(Node *r, int u)
{
    if (r == NULL)
    {
        return NULL;
    }

    if (r->id == u)
    {
        return r;
    }

    // Check left subtree
    Node *leftResult = find(r->leftMostChild, u);
    if (leftResult != NULL)
    {
        return leftResult;
    }

    // Check right siblings
    return find(r->rightSibling, u);
}

// Function to insert a new node as a child of a specific node
void insert(Node *r, int u, int v)
{
    Node *p = find(r, v); // Find the parent node

    if (p == NULL)
    { // Parent node not found
        return;
    }

    // Check if the node already exists
    Node *q = find(r, u);
    if (q != NULL)
    {
        return;
    }

    // Create the new node and link it to the parent
    q = makeNode(u);
    q->parent = p;

    if (p->leftMostChild == NULL)
    {
        p->leftMostChild = q; // First child
    }
    else
    {
        Node *h = p->leftMostChild;
        while (h->rightSibling != NULL)
        {
            h = h->rightSibling;
        }
        h->rightSibling = q; // Append as right sibling
    }
}

// Function to calculate the height of a node
int height(Node *r)
{
    if (r == NULL)
    {
        return -1; // Empty node has height -1 (no edges)
    }

    int maxH = 0;
    Node *p = r->leftMostChild;
    while (p != NULL)
    {
        int h = height(p);
        if (h > maxH)
        {
            maxH = h;
        }
        p = p->rightSibling;
    }

    return maxH + 1; // Add 1 for the edge to the child
}

// Function to calculate the depth of a node
int depth(Node *r)
{
    if (r == NULL)
    {
        return -1; // Node not found
    }

    int d = 0;
    while (r != NULL)
    {
        d++;
        r = r->parent;
    }

    return d;
}

int main()
{
    char command[10];
    int u, v;

    while (1)
    {
        scanf("%s", command);
        if (strcmp(command, "*") == 0)
        {
            break;
        }

        if (strcmp(command, "MakeRoot") == 0)
        {
            scanf("%d", &u);
            root = makeNode(u);
        }
        else if (strcmp(command, "Insert") == 0)
        {
            scanf("%d %d", &u, &v);
            insert(root, u, v);
        }
        else if (strcmp(command, "Height") == 0)
        {
            scanf("%d", &u);
            Node *node = find(root, u);
            if (node != NULL)
            {
                printf("%d\n", height(node));
            }
            else
            {
                printf("-1\n"); // Node not found
            }
        }
        else if (strcmp(command, "Depth") == 0)
        {
            scanf("%d", &u);
            Node *node = find(root, u);
            if (node != NULL)
            {
                printf("%d\n", depth(node));
            }
            else
            {
                printf("-1\n"); // Node not found
            }
        }
    }

    return 0;
}
