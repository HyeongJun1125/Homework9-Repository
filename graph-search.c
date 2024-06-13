#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

// ������ ������ ���
typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

// ���� ����Ʈ�� �湮 ���θ� ������ �׷���
typedef struct Graph
{
    Node *adjLists[10]; // ��������Ʈ (������ �迭)
    int visited[10];
} Graph;

// ���� ����Ʈ�� �迭�� �ʱ�ȭ�ϴ� Initialize �Լ�
void InitializeGraph(Graph *graph)
{
    for (int i = 0; i < 10; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
}

void InsertVertex(Graph *graph, int vertex)
{
    // Vertex ��ȣ�� 0���� 9���� �ο��ǹǷ� ��ȿ���� �˻��Ͽ�
    if (vertex >= 0 && vertex < 10)
    { // ��ȿ�ϸ鼭
        if (graph->adjLists[vertex] == NULL)
        {                                                           // ����Ʈ�� ����ִٸ�
            graph->adjLists[vertex] = (Node *)malloc(sizeof(Node)); // �����Ҵ��Ͽ�
            graph->adjLists[vertex]->vertex = vertex;               // �ش� ���� �־���.
            graph->adjLists[vertex]->next = NULL;                   // �߰��� ��������Ʈ�� ���� ����.
        }
        else
        { // ����Ʈ�� �̹� ���ִ� ���̶��
            printf("�̹� �����ϴ� ���Դϴ�.\n");
        }
    }
    else
    { // ��ȿ���� ���� ���� �Է����� ���´ٸ�
        printf("��ȿ�� ���� ������ �ʰ��մϴ�.\n");
    }
}

// ������ ���� ���̿� ������ ������ִ� �Լ�
void InsertEdge(Graph *graph, int src, int dest)
{
    // ���� �Ǵ� ���� ��ȣ�� ��ȿ�� �������
    if (src < 0 || src >= 10 || dest < 0 || dest >= 10)
    {
        printf("���� %d �Ǵ� %d�� ��ȿ���� ���� ���� ������ ���մϴ�.\n", src, dest);
        return;
    }
    // ������ �������� �ʴ� ���
    if (graph->adjLists[src] == NULL || graph->adjLists[dest] == NULL)
    {
        printf("���� �Ǵ� ������ ������ �������� �ʽ��ϴ�.\n");
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node)); // ���� �Ҵ��Ͽ�
    newNode->vertex = dest;                       // ������ ��ȣ�� ����.
    // ���� �������� ���� ����Ʈ�� ����,
    newNode->next = graph->adjLists[src]->next;
    graph->adjLists[src]->next = newNode;

    newNode = (Node *)malloc(sizeof(Node)); // ���� �Ҵ��Ͽ�
    newNode->vertex = src;                  // ������ ��ȣ�� ����.
    // ������ �������� ���� ����Ʈ�� ����.
    newNode->next = graph->adjLists[dest]->next;
    graph->adjLists[dest]->next = newNode;
}

void DFS(Graph *graph, int startVertex)
{
    // ��ȿ ������ �ƴϰų� �������� �ʴ� ���
    if (startVertex < 0 || startVertex >= 10 || graph->adjLists[startVertex] == NULL)
    {
        printf("��ȿ���� ���� �����Դϴ�.\n");
        return;
    }

    Node *stack[10];
    int top = -1;

    // �ش� ������ �湮�ߴٰ� ǥ���ϰ� ���.
    graph->visited[startVertex] = TRUE;
    printf("%d ", startVertex);

    stack[++top] = graph->adjLists[startVertex]; // ������ ���ÿ� �߰�.

    // ������ ������ �� ������ ����.
    while (top != -1)
    {
        Node *vertexList = stack[top--]; // ���ÿ��� ������ pop.
        Node *temp = vertexList->next;   // ������ ������ Ž���ϱ� ���� �����ͷ�

        while (temp)
        {                                       // ���� �����ϴ� ����
            int connectedVertex = temp->vertex; // ����� ���� ��ȣ�� �����Ͽ�

            // ���� �湮���� ���� �����̸�
            if (graph->visited[connectedVertex] == FALSE)
            {
                // �湮�ߴٰ� ǥ���ϰ�
                graph->visited[connectedVertex] = TRUE;
                printf("%d ", connectedVertex); // �ش� ������ ����� �Ŀ�.
                // �׸��� ���ÿ� �߰�.
                stack[++top] = graph->adjLists[connectedVertex];
            }
            temp = temp->next; // ���� �������� �̵�.
        }
    }
    printf("\n");

    // ���� Ž���� ���� �湮 �÷��� �ʱ�ȭ.
    for (int i = 0; i < 10; i++)
    {
        graph->visited[i] = FALSE;
    }
}

void BFS(Graph *graph, int startVertex)
{
    // ��ȿ ������ �ƴϰų� �������� �ʴ� ���
    if (startVertex < 0 || startVertex >= 10 || graph->adjLists[startVertex] == NULL)
    {
        printf("��ȿ���� ���� �����Դϴ�.\n");
        return;
    }

    // ť �ʱ�ȭ
    Node *queue[10];
    int front = 0;
    int rear = 0;

    graph->visited[startVertex] = TRUE;           // ���� ������ �湮�ߴٰ� ǥ���ϰ�
    printf("%d ", startVertex);                   // �ش� ���� ����� �Ŀ�
    queue[rear++] = graph->adjLists[startVertex]; // ť�� �߰�.

    // ť�� �� ������
    while (front < rear)
    {
        Node *vertexList = queue[front++]; // ť���� ������ ������
        Node *temp = vertexList->next;     // �ش� ������ ���� ����Ʈ Ž���ϴ� �����ͷ�

        // ���� ������ ������
        while (temp)
        {
            int connectedVertex = temp->vertex; // connectedVertex�� ����� ����

            // ���� �湮���� �ʾҴٸ�
            if (graph->visited[connectedVertex] == FALSE)
            {
                // �湮�ߴٰ� ǥ�����ְ�
                graph->visited[connectedVertex] = TRUE;
                printf("%d ", connectedVertex); // ���� ����� �Ŀ�
                // �ش� ���� ť�� �߰�.
                queue[rear++] = graph->adjLists[connectedVertex];
            }
            temp = temp->next; // ���� �������� �̵�
        }
    }
    printf("\n");

    // ���� Ž���� ���� �湮 �÷��� �ʱ�ȭ
    for (int i = 0; i < 10; i++)
    {
        graph->visited[i] = 0;
    }
}

void PrintGraph(Graph *graph)
{
    for (int i = 0; i < 10; i++)
    {                                    // ������ ����ŭ
        Node *temp = graph->adjLists[i]; // ���� ����Ʈ�� ���� ��忡������
        if (temp)
        {                             // ������ ������ �����Ѵٸ�
            printf("Vertex %d: ", i); // ������ ���� ����ϰ�
            // ��� ������ ������ ��ȸ�Ͽ� ���.
            while (temp)
            {
                printf("%d -> ", temp->vertex);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

int main()
{
    Graph graph;
    char command;
    int vertex, src, dest;

    printf("\n2021041069 ������");
    do
    {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                          Graph Searches                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph     = z                                       \n");
        printf(" Insert Vertex        = v      Insert Edge                  = e \n");
        printf(" Depth First Search   = d      Breath First Search          = b \n");
        printf(" Print Graph          = p      Quit                         = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Enter command: ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
            InitializeGraph(&graph);
            printf("�׷����� �ʱ�ȭ��.\n");
            break;
        case 'v':
            printf("������ �Է��ϼ��� : ");
            scanf("%d", &vertex);
            InsertVertex(&graph, vertex);
            break;
        case 'e':
            printf("������ ������ ������ ���� �Է����ּ��� : ");
            scanf("%d %d", &src, &dest);
            InsertEdge(&graph, src, dest);
            break;
        case 'd':
            printf("DFS Ž���� ������ ������ �Է��ϼ��� : ");
            scanf("%d", &vertex);
            DFS(&graph, vertex);
            break;
        case 'b':
            printf("BFS Ž���� ������ ������ �Է��ϼ��� : ");
            scanf("%d", &vertex);
            BFS(&graph, vertex);
            break;
        case 'p':
            PrintGraph(&graph);
            break;
        case 'q':
            printf("���α׷��� �����մϴ�.\n");
            break;
        default:
            printf("��ȿ���� ���� ���Դϴ�. �ٽ� �Է��ϼ���.\n");
            break;
        }
    } while (command != 'q');

    return 0;
}
