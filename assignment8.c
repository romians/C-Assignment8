#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

#define size 50

typedef struct graph {
    int n; //노드의 값
    int adj_mat[size][size];
} graph;

int visited[size];

typedef struct {
    int queue[size];
    int front, rear;
} QueueType;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void queue_init(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

int is_full(QueueType* q) {
    return ((q->rear + 1) % size == q->front);
}

void enqueue(QueueType* q, int item) {
    if (is_full(q)) {
        error("Queue is full");
        return;
    }
    q->rear = (q->rear + 1) % size;
    q->queue[q->rear] = item;
}

int dequeue(QueueType* q) {
    if (is_empty(q)) {
        error("Queue is empty");
        return -1; // 오류를 표시하기 위한 임의의 값
    }
    q->front = (q->front + 1) % size;
    return q->queue[q->front];
}

// 그래프 생성
void init(graph* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < size; r++) {
        for (c = 0; c < size; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}

// 그래프 정점 생성 함수
void insert_vertex(graph* g, int v) {
    if ((g->n) + 1 > size) {
        error("Graph is full");
        return;
    }
    g->n++;
}

// 그래프 간선 생성 함수
void insert_edge(graph* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        error("Graph index error");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

// DFS 탐색 및 출력
void dfs_mat(graph* g, int start, int want, int* count) {
    int w;
    (*count)++;
    visited[start] = True;
    printf("%d ->", start);

    if (start == want) {
        printf("\n탐색 성공 : %d\n", start);
        return;
    }

    for (w = 0; w < g->n; w++) {
        if (g->adj_mat[start][w] && !visited[w]) {
            dfs_mat(g, w, want, count);
        }
    }
}

// BFS 탐색 및 출력
void bfs_mat(graph* g, int start, int want, int* count) {
    int w;
    QueueType q;

    queue_init(&q);
    visited[start] = True;

    printf("%d -> ", start);
    enqueue(&q, start);

    while (!is_empty(&q)) {
        start = dequeue(&q);
        for (w = 0; w < g->n; w++) {
            if (g->adj_mat[start][w] && !visited[w]) {
                visited[w] = True;
                printf("%d -> ", w);
                enqueue(&q, w);
                (*count)++;
                if (w == want) {
                    printf("\n탐색 성공 : %d\n", w);
                    return;
                }
            }
        }
    }

    printf("\n탐색 성공 : %d\n", start);
}

int main() {

    // 그래프 설정
    graph* g;
    g = (graph*)malloc(sizeof(graph));
    init(g);
    for (int i = 0; i < 12; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 5);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 6);
    insert_edge(g, 0, 9);

    insert_edge(g, 5, 3);
    insert_edge(g, 5, 4);
    insert_edge(g, 5, 1);

    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);

    insert_edge(g, 6, 4);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);

    insert_edge(g, 9, 8);

    insert_edge(g, 4, 1);
    insert_edge(g, 4, 7);

    insert_edge(g, 7, 1);
    insert_edge(g, 7, 10);

    insert_edge(g, 8, 10);

    printf("-----------------------------\n");
    printf("1   : 깊이 우선 탐색(DFS)    |\n");
    printf("2   : 너비 우선 탐색(BFS)    |\n");
    printf("3   : 종료                   |\n");
    printf("-----------------------------\n");

    while (1) {

        int num = 0, count = 0;
        printf("메뉴 입력 : ");
        scanf("%d", &num);

        for (int i = 0; i < g->n; i++) {
            visited[i] = False;
        }

        if (num == 1) {
            int start, want;
            printf("시작 번호와 탐색할 값 입력 : ");
            scanf("%d %d", &start, &want);
            dfs_mat(g, start, want, &count);
            printf("방문한 노드 수 : %d\n\n", count);
        }

        else if (num == 2) {
            int start, want;
            printf("시작 번호와 탐색할 값 입력 : ");
            scanf("%d %d", &start, &want);
            bfs_mat(g, start, want, &count);
            printf("방문한 노드 수 : %d\n\n", count);
        }

        else if (num == 3) {
            printf("종료\n");
            break;
        }
    }

    free(g);

    return 0;
}