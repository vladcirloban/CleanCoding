/* Parcurgerea unui graf cu DFS/BFS */

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
    struct Node **adjacency_list;
} GRAPH;

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
    new_node->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = new_node;

    new_node = create_node(source);
    new_node->next = graph->adjacency_list[destination];
    graph->adjacency_list[destination] = new_node;
}

GRAPH *create_graph(int number_of_vertices)
{
    GRAPH *graph = (GRAPH*)malloc(sizeof(GRAPH));
    
    graph->vertices = number_of_vertices;
    graph->adjacency_list = (NODE**)malloc(number_of_vertices * sizeof(NODE*));
    graph->visited = (int*)malloc(number_of_vertices * sizeof(int));
    
    for (int i = 0; i < number_of_vertices; i++)
    {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }
    
    return graph;
}

// Utilitare pentru BFS
int is_empty(NODE *queue)
{
    return (queue == NULL);
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = create_node(data);

    if (is_empty(*queue))
        *queue = new_node;
    else
    {
        NODE *temporary = *queue;
        
        while (temporary->next)
        {
            temporary = temporary->next;
        }
        
        temporary->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    if (is_empty(*queue))
    {
        return -1;
    }

    int data = (*queue)->data;
    NODE *temporary = *queue;
    
    *queue = (*queue)->next;
    
    return data;
}

void print_graph(GRAPH *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        NODE *temporary = graph->adjacency_list[i];

        while (temporary != NULL)
        {
            printf("%d ", temporary->data);
            temporary = temporary->next;
        }

        printf("\n");
    }
}

void wipe_visited_list(GRAPH *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

// Parcurgerile DFS și BFS
void DFS(GRAPH *graph, int vertex_number)
{
    NODE *adjacency_list = graph->adjacency_list[vertex_number];
    NODE *temporary = adjacency_list;

    graph->visited[vertex_number] = 1;
    printf("%d ", vertex_number);

    while (temporary != NULL)
    {
        int connected_vertex = temporary->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        
        temporary = temporary->next;
    }
}

void BFS(GRAPH *graph, int starting_vertex)
{
    NODE *queue = NULL;

    graph->visited[starting_vertex] = 1;
    enqueue(&queue, starting_vertex);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temporary = graph->adjacency_list[current];

        while (temporary != NULL)
        {
            int adjacent_vertex = temporary->data;

            if (graph->visited[adjacent_vertex] == 0)
            {
                graph->visited[adjacent_vertex] = 1;
                enqueue(&queue, adjacent_vertex);
            }

            temporary = temporary->next;
        }
    }
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

    int starting_vertex;
    
    printf("\nIntroduceti nodul din care plecam in DFS: ");
    scanf("%d", &starting_vertex);
    
    printf("Parcurgerea grafului cu DFS: ");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph);
    
    printf("\n\nIntroduceti nodul din care plecam in BFS: ");
    scanf("%d", &starting_vertex);
    
    printf("Parcurgerea grafului cu BFS: ");
    BFS(graph, starting_vertex);
    
    return 0;
}
