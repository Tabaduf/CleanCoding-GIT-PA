#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Graph {
    int num_vertices;
    int *visited;
    Node **adjacency_list;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int *items;
} Stack;

Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_list[src];
    graph->adjacency_list[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_list[dest];
    graph->adjacency_list[dest] = new_node;
}

Graph *create_graph(int num_vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adjacency_list = malloc(sizeof(Node *) * num_vertices);
    graph->visited = malloc(sizeof(int) * num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

Stack *create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->items = malloc(sizeof(int) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack *stack, int value) {
    stack->top++;
    stack->items[stack->top] = value;
}

void dfs(Graph *graph, Stack *stack, int start_vertex) {
    Node *current = graph->adjacency_list[start_vertex];
    graph->visited[start_vertex] = 1;
    printf("%d ", start_vertex);
    push(stack, start_vertex);

    while (current != NULL) {
        int neighbor = current->value;
        if (!graph->visited[neighbor]) {
            dfs(graph, stack, neighbor);
        }
        current = current->next;
    }
}

void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        graph->visited[i] = 0;
    }
}

void insert_edges(Graph *graph, int num_edges) {
    int src, dest;
    printf("Adauga %d muchii (indexate de la 0 la %d):\n", num_edges, graph->num_vertices - 1);
    for (int i = 0; i < num_edges; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void check_path(Graph *graph, Stack *stack1, Stack *stack2) {
    int path_exists = 0;

    for (int i = 0; i < graph->num_vertices; i++) {
        dfs(graph, stack1, i);
        reset_visited(graph);

        for (int j = 0; j < graph->num_vertices; j++) {
            dfs(graph, stack2, j);

            for (int x = 0; x <= stack1->top && !path_exists; x++) {
                for (int y = 0; y <= stack2->top && !path_exists; y++) {
                    if (stack1->items[x] == j && stack2->items[y] == i) {
                        path_exists = 1;
                    }
                }
            }

            reset_visited(graph);
            stack2->top = -1;
        }

        stack1->top = -1;
    }

    printf("\nExista drum direct? %s\n", path_exists ? "DA" : "NU");
}

int main() {
    int num_vertices, num_edges;

    printf("Cate noduri are graful? ");
    scanf("%d", &num_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &num_edges);

    Graph *graph = create_graph(num_vertices);
    Stack *stack1 = create_stack(2 * num_vertices);
    Stack *stack2 = create_stack(2 * num_vertices);

    insert_edges(graph, num_edges);
    check_path(graph, stack1, stack2);

    return 0;
}
