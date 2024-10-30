#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contact_t
{
    char name[20];
    char tel[11];
    char email[25];
} contact;

struct list_el
{
    contact el;
    struct list_el *next;
};
typedef struct list_el node;

node *root = NULL;
node *cur = NULL;
node *prev = NULL;

node *makeNewNode(contact ct)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->el = ct;
    new_node->next = NULL;
    return new_node;
}

contact readNode()
{
    contact tmp;
    printf("Input the full name: ");
    fgets(tmp.name, 20, stdin);
    removeEnter(tmp.name);

    printf("Input the telephone number: ");
    fgets(tmp.tel, 11, stdin);
    removeEnter(tmp.tel);

    printf("Input the email: ");
    fgets(tmp.email, 25, stdin);
    removeEnter(tmp.email);

    return tmp;
}

void removeEnter(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void insertAtHead(contact ct)
{
    node *new_item = makeNewNode(ct);
    new_item->next = root;
    root = new_item;
    cur = root;
}

void insertAfterCurrent(contact ct)
{
    node *new_node = makeNewNode(ct);
    if (root == NULL)
    {
        root = new_node;
        cur = root;
    }
    else if (cur == NULL)
        return;
    else
    {
        new_node->next = cur->next;
        cur->next = new_node;
        cur = cur->next;
    }
}

void insertBeforeCurrent(contact e)
{
    node *new_node = makeNewNode(e);
    if (root == NULL)
    { /* if there is no element */
        root = new_node;
        cur = root;
        prev = NULL;
    }
    else
    {
        new_node->next = cur;
        if (cur == root)
        {                    /* if cur pointed to first element */
            root = new_node; /* nut moi them vao tro thanh dau danh sach */
        }
        else
            prev->next = new_node; // assume prev pointer always point to the previous node
        cur = new_node;
    }
}

void displayNode(node *p)
{
    if (p == NULL)
    {
        printf("NULL Pointer error.\n");
        return;
    }
    printf("%-20s\t%-15s\t%-25s\n", p->el.name, p->el.tel, p->el.email);
}

void displayList()
{
    node *p = root;
    while (p != NULL)
    {
        displayNode(p);
        p = p->next;
    }
}

int main()
{
    contact tmp;
    int i, n, choice;

    printf("Input the number of contacts: ");
    scanf("%d", &n);
    getchar(); // clear newline character left in the buffer

    for (i = 0; i < n; i++)
    {
        tmp = readNode();

        printf("Choose insertion method:\n");
        printf("1. Insert at head\n");
        printf("2. Insert after current\n");
        printf("3. Insert before current\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline character

        if (choice == 1)
        {
            insertAtHead(tmp);
        }
        else if (choice == 2)
        {
            insertAfterCurrent(tmp);
        }
        else if (choice == 3)
        {
            insertBeforeCurrent(tmp);
        }
        else
        {
            printf("Invalid choice, skipping insertion.\n");
        }
    }

    printf("\nContact List:\n");
    displayList();

    return 0;
}
