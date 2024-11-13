#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000        // Định nghĩa kích thước tối đa của hàng đợi
#define MAX_OUTPUT 1000 // Định nghĩa kích thước tối đa cho kết quả POP

typedef struct
{
    int data[MAX];
    int front;
    int rear;
} Queue;

// Hàm khởi tạo hàng đợi
void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

// Hàm kiểm tra hàng đợi có rỗng không
int isEmpty(Queue *q)
{
    return q->front == q->rear;
}

// Hàm kiểm tra hàng đợi có đầy không
int isFull(Queue *q)
{
    return (q->rear + 1) % MAX == q->front;
}

// Hàm thêm phần tử vào hàng đợi
void push(Queue *q, int value)
{
    if (isFull(q))
    {
        printf("Queue is full!\n");
        return;
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX;
}

// Hàm loại bỏ phần tử khỏi hàng đợi và lưu kết quả vào mảng output
void pop(Queue *q, int *output, int *outputSize)
{
    if (isEmpty(q))
    {
        output[(*outputSize)++] = -1; // Lưu -1 khi hàng đợi rỗng (thay cho NULL)
    }
    else
    {
        output[(*outputSize)++] = q->data[q->front];
        q->front = (q->front + 1) % MAX;
    }
}

int main()
{
    Queue q;
    initQueue(&q);

    char command[10];
    int value;
    int output[MAX_OUTPUT];
    int outputSize = 0;

    while (1)
    {
        scanf("%s", command);

        if (strcmp(command, "#") == 0)
        {
            break;
        }

        if (strcmp(command, "PUSH") == 0)
        {
            scanf("%d", &value);
            push(&q, value);
        }
        else if (strcmp(command, "POP") == 0)
        {
            pop(&q, output, &outputSize);
        }
    }

    // In kết quả của các thao tác POP sau khi gặp dấu #
    for (int i = 0; i < outputSize; i++)
    {
        if (output[i] == -1)
        {
            printf("NULL\n");
        }
        else
        {
            printf("%d\n", output[i]);
        }
    }

    return 0;
}
