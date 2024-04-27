/* Determinați dacă există sau nu drum direct între două restaurante dintr-o rețea de tip graf. */

/*
    Pentru simplitate, folosim int-uri pentru a numi restaurantele/locațiile
    Exemplu: 1 - restaurantul 1, și tot așa
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices, *visited;
    struct Node **adjacencyList;
} GRAPH;

typedef struct Stack
{
    int top, capacity, *array;
} STACK;

NODE *create_node(int vertex)
{
    NODE *new_node = (NODE*)malloc(sizeof(NODE));

    new_node->data = vertex;
    new_node->next = NULL;

    return new_node;
}

void add_edge(GRAPH *graph, int source, int destination)
{
    NODE *new_node = create_node(destination);
    new_node->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = new_node;

    new_node = create_node(source);
    new_node->next = graph->adjacencyList[destination];
    graph->adjacencyList[destination] = new_node;
}

GRAPH *create_graph(int number_of_vertices)
{
    GRAPH *graph = (GRAPH*)malloc(sizeof(GRAPH));

    graph->vertices = number_of_vertices;
    graph->adjacencyList = (NODE**)malloc(number_of_vertices * sizeof(NODE*));
    graph->visited = (int*)malloc(number_of_vertices * sizeof(int));

    for (int i = 0; i < number_of_vertices; i++)
    {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void wipe(GRAPH *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

STACK *create_stack(int capacity)
{
    STACK *stack = (STACK*)malloc(sizeof(STACK));

    stack->array = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(STACK *stack, int pushed)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushed;
}

int DFS(GRAPH *graph, STACK *stack, int vertex_number, int destination)
{
    NODE *adjacency_list = graph->adjacencyList[vertex_number];
    NODE *auxiliary = adjacency_list;
    
    graph->visited[vertex_number] = 1;
    
    push(stack, vertex_number);

    if (vertex_number == destination)
    {
        return 1; // Drum găsit
    }

    while (auxiliary != NULL)
    {
        int connected_vertex = auxiliary->data;

        if (graph->visited[connected_vertex] == 0)
        {
            int found = DFS(graph, stack, connected_vertex, destination);

            if (found)
            {
                return 1; // Drum găsit
            }
        }

        auxiliary = auxiliary->next;
    }

    return 0; // Nu a fost găsit drum
}

int is_path(GRAPH *graph, int source, int destination)
{
    STACK *stack = create_stack(graph->vertices);

    int found = DFS(graph, stack, source, destination);

    wipe(graph);

    return found; // 1 dacă există drum, 0 dacă nu
}

int main()
{
    int number_of_vertices, number_of_edges;

    printf("Introduceti numarul de noduri ale grafului: ");
    scanf("%d", &number_of_vertices);

    printf("Introduceti numarul de muchii ale grafului: ");
    scanf("%d", &number_of_edges);

    GRAPH *graph = create_graph(number_of_vertices);

    printf("Introduceti muchiile (sursa si destinatie):\n");
    
    for (int i = 1; i <= number_of_edges; i++)
    {
        int source, destination;

        scanf("%d %d", &source, &destination);
        add_edge(graph, source, destination);
    }

    int vertex_1, vertex_2;

    printf("\nIntroduceti doua noduri pentru a verifica daca exista drum intre ele: ");
    scanf("%d %d", &vertex_1, &vertex_2);

    printf("Exista drum intre cele doua noduri?\n");

    if (is_path(graph, vertex_1, vertex_2))
        printf("DA!");
    else
        printf("NU!");

    return 0;
}
