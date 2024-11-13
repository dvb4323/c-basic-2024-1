#include <stdio.h>
#include <string.h>

typedef int elementtype;
struct node_t
{
    elementtype element;
    struct Node *next;
};
typedef struct node_t Node;
Node *root = NULL;
Node *cur = NULL;
Node *prev = NULL;

Node *makeNewNode(elementtype e)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->element = e;
    new_node->next = NULL;
    return new_node;
}
Node *find(Node *root, elementtype e)
{
}
void insertAtTail(elementtype e)
{
    Node *new = makeNewNode(e);
    if (root == NULL)
    {
        root = new;
        cur = new;
        prev = NULL;
        return;
    }
    Node *p = root;
    while (p->next != NULL)
        p = p->next;
    p->next = new;
    cur = new;
    prev = p;
}

Node *insertLastRecursive(Node *root, elementtype e)
{
    if (root == NULL)
    {
        return makeNewNode(e);
    }
    root->next = insertLastRecursive(root->next, e);
    return root;
}

void insertAtHead(elementtype e)
{
    Node *new_item = makeNewNode(e);
    new_item->next = root;
    root = new_item;
    cur = root;
}

Node *removeNodeRecursive(Node *root, elementtype e)
{
}
void solve()
{
    int n, i, u, v;
    int X[100];
    char command[20];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &X[i]);
    printf("\n n = %d", n);
    // for(i = 0; i < n; i++)
    //	printf("\n X[%d] = %d", i, X[i]);
    do
    {
        scanf("%s", command);
        if (strcmp(command, "addlast") == 0)
        {
            scanf("%d", &u);
            printf("\n ==> Lenh addlast %d \n", u);
        }
        else if (strcmp(command, "addafter") == 0)
        {
            scanf("%d%d", &u, &v);
            printf("\n ==> Lenh addafter %d %d \n", u, v);
        }
    } while (strcmp(command, "#") != 0);
}

int main()
{
    solve();
    return 0;
}