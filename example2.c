#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Graph {
    int num_vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

//====================== Utilities ======================

Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

Graph *create_graph(int num_vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adjacency_lists = malloc(num_vertices * sizeof(Node *));
    graph->visited = malloc(num_vertices * sizeof(int));

    for (int i = 0; i < num_vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(Graph *graph, int num_vertices, int num_edges) {
    int src, dest;
    printf("Adauga %d muchii (indexate de la 0 la %d):\n", num_edges, num_vertices - 1);
    for (int i = 0; i < num_edges; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

//====================== BFS Utilities ======================

int is_empty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int value) {
    Node *new_node = create_node(value);
    if (*queue == NULL) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

int dequeue(Node **queue) {
    if (*queue == NULL) return -1;
    int value = (*queue)->value;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return value;
}

void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        graph->visited[i] = 0;
    }
}

//====================== Traversals ======================

void dfs(Graph *graph, int vertex) {
    Node *temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d -> ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->value;
        if (graph->visited[connected_vertex] == 0)
            dfs(graph, connected_vertex);
        temp = temp->next;
    }
}

void bfs(Graph *graph, int start_vertex) {
    Node *queue = NULL;
    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(queue)) {
        int current_vertex = dequeue(&queue);
        printf("%d ", current_vertex);

        Node *temp = graph->adjacency_lists[current_vertex];
        while (temp != NULL) {
            int neighbor = temp->value;
            if (graph->visited[neighbor] == 0) {
                graph->visited[neighbor] = 1;
                enqueue(&queue, neighbor);
            }
            temp = temp->next;
        }
    }
}

//====================== Main ======================

int main() {
    int num_vertices;
    int num_edges;
    int start_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &num_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &num_edges);

    Graph *graph = create_graph(num_vertices);
    insert_edges(graph, num_vertices, num_edges);

    printf("De unde plecam in DFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere cu DFS: ");
    dfs(graph, start_vertex);

    reset_visited(graph);
    printf("\n");

    printf("De unde plecam in BFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere cu BFS: ");
    bfs(graph, start_vertex);

    return 0;
}
