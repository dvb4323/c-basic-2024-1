#include <stdio.h>
#include <stdlib.h>

// Khai báo các biến và cấu trúc dữ liệu
int mark[900][900] = {0};
int num[900][900] = {0};

struct node_t
{
    int x, y;
    struct node_t *next;
};
typedef struct node_t node;

node *head = NULL, *tail = NULL;

// Hàm tạo một nút mới
node *makeNode(int x, int y)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    return newNode;
}

// Hàm đẩy một nút vào hàng đợi
void push(int x, int y)
{
    node *newNode = makeNode(x, y);
    if (head == NULL)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

// Hàm lấy một nút ra khỏi hàng đợi
void pop()
{
    if (head == NULL)
        return;
    node *temp = head;
    head = head->next;
    if (head == NULL)
        tail = NULL;
    free(temp);
}

// Hàm trả về nút đầu tiên của hàng đợi
node *front()
{
    return head;
}

// Hàm BFS để tìm số bước tối thiểu để đạt được lượng nước c
int bfs(int a, int b, int c)
{
    // Khởi tạo ban đầu: không có nước trong hai bình
    push(0, 0);
    mark[0][0] = 1;
    num[0][0] = 0;

    while (head != NULL)
    {
        node *current = front();
        int x = current->x;
        int y = current->y;
        int steps = num[x][y];

        // Kiểm tra nếu đạt được lượng nước c
        if (x == c || y == c)
            return steps;
        pop();

        // Các thao tác có thể thực hiện
        int nx, ny;

        // Đổ đầy bình a
        nx = a, ny = y;
        if (!mark[nx][ny])
        {
            push(nx, ny);
            mark[nx][ny] = 1;
            num[nx][ny] = steps + 1;
        }

        // Đổ đầy bình b
        nx = x, ny = b;
        if (!mark[nx][ny])
        {
            push(nx, ny);
            mark[nx][ny] = 1;
            num[nx][ny] = steps + 1;
        }

        // Đổ cạn bình a
        nx = 0, ny = y;
        if (!mark[nx][ny])
        {
            push(nx, ny);
            mark[nx][ny] = 1;
            num[nx][ny] = steps + 1;
        }

        // Đổ cạn bình b
        nx = x, ny = 0;
        if (!mark[nx][ny])
        {
            push(nx, ny);
            mark[nx][ny] = 1;
            num[nx][ny] = steps + 1;
        }

        // Đổ từ bình a sang bình b cho đến khi bình b đầy hoặc bình a hết nước
        nx = x - (b - y);
        ny = b;
        if (nx < 0)
        {
            nx = 0;
            ny = y + x;
        }
        if (!mark[nx][ny])
        {
            push(nx, ny);
            mark[nx][ny] = 1;
            num[nx][ny] = steps + 1;
        }

        // Đổ từ bình b sang bình a cho đến khi bình a đầy hoặc bình b hết nước
        nx = a;
        ny = y - (a - x);
        if (ny < 0)
        {
            ny = 0;
            nx = x + y;
        }
        if (!mark[nx][ny])
        {
            push(nx, ny);
            mark[nx][ny] = 1;
            num[nx][ny] = steps + 1;
        }
    }
    return -1; // Không tìm thấy cách để đạt được c lít nước
}

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    // Kiểm tra điều kiện
    if (c > a && c > b)
    {
        printf("-1\n");
    }
    else
    {
        int result = bfs(a, b, c);
        printf("%d\n", result);
    }

    return 0;
}
