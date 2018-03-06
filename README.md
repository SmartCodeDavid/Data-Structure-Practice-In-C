# Data-Structure-Practice-In-C



Introduction of task:
You are a computational neuroscientist working on simulations of neural networks. You have
data representing a very large feed-forward network and wish to create a computer
simulation for further study. The network can be modelled as a graph with vertices
representing neurons and directed edges representing connections between them. In order
to calculate the output of a neuron, you need to first calculate the output of all neurons that
connect to it (note: this particular feed-forward network has no cycles). So a topological sort
will give a possible evaluation order for the network.

Part A

For this part, you will be given a network and a starting state. Your program
will then calculate the subsequent state of the network. For neurons that have no inputs, the
new state will be the same as the current state. For other neurons, a very simple neuron
model will be used:

for each neuron v:

 input = 0
 
 for each edge uv:
 
 input += weight(uv)*state(u)
 
 if input>0:
 
 state(v) = 1
 
 else:
 
 state(v) = 0
 
You must use the following data structures to represent the graph as an adjacency list:

typedef struct edge{
int toVertex;
int weight;
} Edge;

typedef struct edgeNode{
Edge edge;
struct edgeNode *next;
} *EdgeList;

typedef struct graph{
 int V;
 int *state;
 EdgeList *edges;
 } Graph;
 
For testing purposes you will input the graph data from the keyboard and/or using input
redirection. The input format is as follows:

The first line will contain the number of vertices (neurons) in the graph

Then for each vertex:

the first line contains the initial state of that vertex

The second line contains the number of edges from that vertex

The third line contains a list of toVertex,weight pairs separated by spaces

(if there are no edges, this line is omitted)

For example, the following text would define a 7 vertex graph:

7

1

2

6,1 3,-2

0

1

4,4

1

3

4,-2 3,1 0,3

1

0

1

1

3,2

0

4

6,2 3,-4 2,1 0,-3

1

3

5,2 4,-1 3,4


The edge weights will be in the range -100 to +100; states will be either 0 or 1.
Your program should use the queue based topological sort method based on in-degrees to
determine an evaluation order for the graph. Then working through the vertices in this
topologically sorted order to calculate the next state of each neuron. The output should be
the new state of all neurons after this calculation (on a single line). So the initial state of the
vertex above would be printed as:

1011101





Part B

You find that the topological sort can take a long time for some graphs, and you would also
like to be able to detect cycles. So you decide to test whether a depth first search based
topological sort gives better performance.

For this part, you will implement DFS for the input graph, and use the postorder
numbering of the DFS spanning tree to determine if there are any cycles. [Note: you
don’t have to actually build a separate DFS spanning tree to calculated the post-order 
numbering] If there are no cycles, you should then use the post-order numbering to calculate
a topological sort and calculate and print the new state of the graph as for part A. Otherwise,
the program should print an error message: “this graph contains at least one cycle”.
