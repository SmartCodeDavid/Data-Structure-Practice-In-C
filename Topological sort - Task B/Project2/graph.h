typedef struct edge{
	int toVertex;
	int weight;
} Edge;

typedef struct edgeNode {
	Edge edge;
	struct edgeNode *next;
} *EdgeList;

typedef struct graph
{
	int V;
	int *state;
	EdgeList *edges;
} Graph;