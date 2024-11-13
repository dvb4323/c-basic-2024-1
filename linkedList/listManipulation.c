#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int key;
    struct Node *next;
} Node;

Node *head = NULL;

// Tạo một node mới với key cho trước
Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Kiểm tra xem key có tồn tại trong danh sách không
bool contains(int key)
{
    Node *current = head;
    while (current != NULL)
    {
        if (current->key == key)
            return true;
        current = current->next;
    }
    return false;
}

// Thêm phần tử vào đầu danh sách
void addFirst(int key)
{
    if (contains(key))
        return;
    Node *newNode = createNode(key);
    newNode->next = head;
    head = newNode;
}

// Thêm phần tử vào cuối danh sách
void addLast(int key)
{
    if (contains(key))
        return;
    Node *newNode = createNode(key);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

// Thêm phần tử u sau phần tử v
void addAfter(int u, int v)
{
    if (contains(u))
        return;
    Node *current = head;
    while (current != NULL && current->key != v)
    {
        current = current->next;
    }
    if (current == NULL)
        return;
    Node *newNode = createNode(u);
    newNode->next = current->next;
    current->next = newNode;
}

// Thêm phần tử u trước phần tử v
void addBefore(int u, int v)
{
    if (contains(u))
        return;
    if (head == NULL || head->key == v)
    {
        addFirst(u);
        return;
    }
    Node *current = head;
    Node *prev = NULL;
    while (current != NULL && current->key != v)
    {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    Node *newNode = createNode(u);
    prev->next = newNode;
    newNode->next = current;
}

// Xóa phần tử có key cho trước
void removeKey(int key)
{
    if (head == NULL)
        return;
    if (head->key == key)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        return;
    }
    Node *current = head;
    Node *prev = NULL;
    while (current != NULL && current->key != key)
    {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    prev->next = current->next;
    free(current);
}

// Đảo ngược danh sách
void reverse()
{
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

// In danh sách
void printList()
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    int n, key;
    printf("Input n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &key);
        addLast(key);
    }

    char command[20];
    int u, v;

    while (1)
    {
        scanf("%s", command);
        if (command[0] == '#')
            break;
        if (strcmp(command, "addlast") == 0)
        {
            scanf("%d", &key);
            addLast(key);
        }
        else if (strcmp(command, "addfirst") == 0)
        {
            scanf("%d", &key);
            addFirst(key);
        }
        else if (strcmp(command, "addafter") == 0)
        {
            scanf("%d %d", &u, &v);
            addAfter(u, v);
        }
        else if (strcmp(command, "addbefore") == 0)
        {
            scanf("%d %d", &u, &v);
            addBefore(u, v);
        }
        else if (strcmp(command, "remove") == 0)
        {
            scanf("%d", &key);
            removeKey(key);
        }
        else if (strcmp(command, "reverse") == 0)
        {
            reverse();
        }
    }

    printList();
    return 0;
}
