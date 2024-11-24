#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[50];
    struct Node *children[10]; // Assuming a person can have up to 10 children
    int childCount;
} Node;

Node *familyTree[10]; // Maximum 10 unique people in the family tree
int familyCount = 0;

// Find a node by name in the family tree
Node *findNode(const char *name)
{
    for (int i = 0; i < familyCount; i++)
    {
        if (strcmp(familyTree[i]->name, name) == 0)
        {
            return familyTree[i];
        }
    }
    return NULL;
}

// Add a node to the family tree, or return it if it already exists
Node *addOrGetNode(const char *name)
{
    Node *node = findNode(name);
    if (node == NULL)
    {
        node = (Node *)malloc(sizeof(Node));
        strcpy(node->name, name);
        node->childCount = 0;
        familyTree[familyCount++] = node;
    }
    return node;
}

// Count all descendants of a node
int countDescendants(Node *node)
{
    if (node == NULL)
        return 0;
    int count = 0;
    for (int i = 0; i < node->childCount; i++)
    {
        count += 1 + countDescendants(node->children[i]);
    }
    return count;
}

// Calculate the number of generations of descendants
int calculateGenerations(Node *node)
{
    if (node == NULL)
        return 0;
    int maxGenerations = 0;
    for (int i = 0; i < node->childCount; i++)
    {
        int childGenerations = calculateGenerations(node->children[i]);
        if (childGenerations > maxGenerations)
        {
            maxGenerations = childGenerations;
        }
    }
    return maxGenerations + (node->childCount > 0 ? 1 : 0);
}

int main()
{
    char input[100];
    char child[50], parent[50];

    // Read child-parent relations
    while (1)
    {
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "***\n") == 0)
            break;
        sscanf(input, "%s %s", child, parent);
        Node *parentNode = addOrGetNode(parent);
        Node *childNode = addOrGetNode(child);
        parentNode->children[parentNode->childCount++] = childNode;
    }

    // Process queries
    while (1)
    {
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "***\n") == 0)
            break;
        char command[20], name[50];
        sscanf(input, "%s %s", command, name);

        Node *node = findNode(name);
        if (strcmp(command, "descendants") == 0)
        {
            printf("%d\n", countDescendants(node));
        }
        else if (strcmp(command, "generation") == 0)
        {
            printf("%d\n", calculateGenerations(node));
        }
    }

    return 0;
}
