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
    int i, n;

    printf("Input the number of contacts: ");
    scanf("%d", &n);
    getchar(); // clear newline character left in the buffer

    for (i = 0; i < n; i++)
    {
        tmp = readNode();
        insertAtHead(tmp);
    }

    printf("\nContact List:\n");
    displayList();

    return 0;
}
