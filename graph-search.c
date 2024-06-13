#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

// 정점을 가지는 노드
typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

// 인접 리스트와 방문 여부를 따지는 그래프
typedef struct Graph
{
    Node *adjLists[10]; // 인접리스트 (포인터 배열)
    int visited[10];
} Graph;

// 인접 리스트와 배열을 초기화하는 Initialize 함수
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
    // Vertex 번호는 0부터 9까지 부여되므로 유효성을 검사하여
    if (vertex >= 0 && vertex < 10)
    { // 유효하면서
        if (graph->adjLists[vertex] == NULL)
        {                                                           // 리스트가 비어있다면
            graph->adjLists[vertex] = (Node *)malloc(sizeof(Node)); // 동적할당하여
            graph->adjLists[vertex]->vertex = vertex;               // 해당 값을 넣어줌.
            graph->adjLists[vertex]->next = NULL;                   // 추가된 인접리스트의 끝을 정의.
        }
        else
        { // 리스트가 이미 차있는 값이라면
            printf("이미 존재하는 값입니다.\n");
        }
    }
    else
    { // 유효하지 않은 값이 입력으로 들어온다면
        printf("유효한 값의 범위를 초과합니다.\n");
    }
}

// 시점과 종점 사이에 간선을 만들어주는 함수
void InsertEdge(Graph *graph, int src, int dest)
{
    // 시점 또는 종점 번호가 유효한 범위라면
    if (src < 0 || src >= 10 || dest < 0 || dest >= 10)
    {
        printf("정점 %d 또는 %d이 유효하지 않은 값의 범위에 속합니다.\n", src, dest);
        return;
    }
    // 정점이 존재하지 않는 경우
    if (graph->adjLists[src] == NULL || graph->adjLists[dest] == NULL)
    {
        printf("시점 또는 종점의 정점이 존재하지 않습니다.\n");
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node)); // 동적 할당하여
    newNode->vertex = dest;                       // 종점의 번호를 저장.
    // 시점 기준으로 인접 리스트에 연결,
    newNode->next = graph->adjLists[src]->next;
    graph->adjLists[src]->next = newNode;

    newNode = (Node *)malloc(sizeof(Node)); // 동적 할당하여
    newNode->vertex = src;                  // 시점의 번호를 저장.
    // 종점을 기준으로 인접 리스트에 연결.
    newNode->next = graph->adjLists[dest]->next;
    graph->adjLists[dest]->next = newNode;
}

void DFS(Graph *graph, int startVertex)
{
    // 유효 범위가 아니거나 존재하지 않는 경우
    if (startVertex < 0 || startVertex >= 10 || graph->adjLists[startVertex] == NULL)
    {
        printf("유효하지 않은 정점입니다.\n");
        return;
    }

    Node *stack[10];
    int top = -1;

    // 해당 정점을 방문했다고 표시하고 출력.
    graph->visited[startVertex] = TRUE;
    printf("%d ", startVertex);

    stack[++top] = graph->adjLists[startVertex]; // 정점을 스택에 추가.

    // 스택이 공백이 될 때까지 수행.
    while (top != -1)
    {
        Node *vertexList = stack[top--]; // 스택에서 정점을 pop.
        Node *temp = vertexList->next;   // 인접한 정점을 탐색하기 위한 포인터로

        while (temp)
        {                                       // 값이 존재하는 동안
            int connectedVertex = temp->vertex; // 연결된 정점 번호를 설정하여

            // 아직 방문하지 않은 정점이면
            if (graph->visited[connectedVertex] == FALSE)
            {
                // 방문했다고 표시하고
                graph->visited[connectedVertex] = TRUE;
                printf("%d ", connectedVertex); // 해당 정점을 출력한 후에.
                // 그리고 스택에 추가.
                stack[++top] = graph->adjLists[connectedVertex];
            }
            temp = temp->next; // 다음 정점으로 이동.
        }
    }
    printf("\n");

    // 다음 탐색을 위해 방문 플래그 초기화.
    for (int i = 0; i < 10; i++)
    {
        graph->visited[i] = FALSE;
    }
}

void BFS(Graph *graph, int startVertex)
{
    // 유효 범위가 아니거나 존재하지 않는 경우
    if (startVertex < 0 || startVertex >= 10 || graph->adjLists[startVertex] == NULL)
    {
        printf("유효하지 않은 정점입니다.\n");
        return;
    }

    // 큐 초기화
    Node *queue[10];
    int front = 0;
    int rear = 0;

    graph->visited[startVertex] = TRUE;           // 시작 정점을 방문했다고 표시하고
    printf("%d ", startVertex);                   // 해당 값을 출력한 후에
    queue[rear++] = graph->adjLists[startVertex]; // 큐에 추가.

    // 큐가 빌 때까지
    while (front < rear)
    {
        Node *vertexList = queue[front++]; // 큐에서 정점을 꺼내어
        Node *temp = vertexList->next;     // 해당 정점의 인접 리스트 탐색하는 포인터로

        // 인접 정점이 있으면
        while (temp)
        {
            int connectedVertex = temp->vertex; // connectedVertex는 연결된 정점

            // 아직 방문하지 않았다면
            if (graph->visited[connectedVertex] == FALSE)
            {
                // 방문했다고 표시해주고
                graph->visited[connectedVertex] = TRUE;
                printf("%d ", connectedVertex); // 값을 출력한 후에
                // 해당 값을 큐에 추가.
                queue[rear++] = graph->adjLists[connectedVertex];
            }
            temp = temp->next; // 다음 정점으로 이동
        }
    }
    printf("\n");

    // 다음 탐색을 위해 방문 플래그 초기화
    for (int i = 0; i < 10; i++)
    {
        graph->visited[i] = 0;
    }
}

void PrintGraph(Graph *graph)
{
    for (int i = 0; i < 10; i++)
    {                                    // 정점의 수만큼
        Node *temp = graph->adjLists[i]; // 인접 리스트의 시작 노드에서부터
        if (temp)
        {                             // 인접한 정점이 존재한다면
            printf("Vertex %d: ", i); // 정점의 값을 출력하고
            // 모든 인접한 정점을 순회하여 출력.
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

    printf("\n2021041069 조형준");
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
            printf("그래프가 초기화됨.\n");
            break;
        case 'v':
            printf("정점을 입력하세요 : ");
            scanf("%d", &vertex);
            InsertVertex(&graph, vertex);
            break;
        case 'e':
            printf("시점과 종점의 정점을 각각 입력해주세요 : ");
            scanf("%d %d", &src, &dest);
            InsertEdge(&graph, src, dest);
            break;
        case 'd':
            printf("DFS 탐색을 시작할 정점을 입력하세요 : ");
            scanf("%d", &vertex);
            DFS(&graph, vertex);
            break;
        case 'b':
            printf("BFS 탐색을 시작할 정점을 입력하세요 : ");
            scanf("%d", &vertex);
            BFS(&graph, vertex);
            break;
        case 'p':
            PrintGraph(&graph);
            break;
        case 'q':
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("유효하지 않은 값입니다. 다시 입력하세요.\n");
            break;
        }
    } while (command != 'q');

    return 0;
}
