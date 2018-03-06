/**
*	Project Name: Part A(DFS-Topological sort)
*	Author: Tianxiang Lan
*	Description: All function on part A was implemented. All the result calculated by this program is corrct.
*                
*	Date: 10/5/2016
*/

#define _CRT_SECURE_NO_DEPRECATE
#include "stdlib.h"
#include <stdio.h>
#include "graph.h"
#include "queue.h"

//check function is used to enqueue the vertex whose indegree is 0
void check(int in_degrees[], int num_vertex);

Graph *G;
int num_vertex = 0;
int num_edges = 0;
int toVertex = 0;
int weight = 0;
int error = 0;

//init Queue
qNode queue = NULL;
int *flag = NULL;

int main(){
	//init graph
	G = (Graph *)malloc(sizeof(Graph));

	//input the number of vertex
	scanf("%d", &num_vertex);
	
	//allocate memory for each array
	int *in_degrees = (int *)malloc(sizeof(int) * num_vertex);
	int *out_degrees = (int *)malloc(sizeof(int) * num_vertex);
	int *input = (int *)malloc(sizeof(int) * num_vertex);
	flag = (int *)malloc(sizeof(int) * num_vertex);
	int *state = (int *)malloc(sizeof(int) * num_vertex);
	G->state = state;

	//initialise in degrees, out degrees and state for each vertex
	for (int i = 0; i < num_vertex; i++){
		in_degrees[i] = 0;
		out_degrees[i] = 0;
		G->state[i] = 0;
		input[i] = 0;
	}

	//V is the number of vertex
	G->V = num_vertex;
	G->edges = (EdgeList *)malloc(sizeof(EdgeList) * num_vertex);
	
	for (int i = 0; i < num_vertex; i++){
		G->edges[i] = NULL;
	}

	//circle for traverse each vertex and input data
	for (int i = 0; i < num_vertex; i++){
		scanf("%d", &(G->state[i]));
		scanf("%d", &num_edges);
		EdgeList *temp = &(G->edges[i]);

		for (int j = 0; j < num_edges; j++){
			scanf("%d,%d", &toVertex, &weight);
			in_degrees[toVertex]++;
			if (G->edges[i] == NULL && j == 0){
				G->edges[i] = (EdgeList)malloc(sizeof(struct graph));
				G->edges[i]->edge.toVertex = toVertex;
				G->edges[i]->edge.weight = weight;
				G->edges[i]->next = NULL;
				temp = &(G->edges[i]->next);
				out_degrees[i]++;
			}
			else{
				*temp = (EdgeList)malloc(sizeof(struct graph));
				(*temp)->edge.toVertex = toVertex;
				(*temp)->edge.weight = weight;
				(*temp)->next = NULL;
				temp = &((*temp)->next);
				out_degrees[i]++;
			}
		}
	}

	//print out every vertex and the vertex which is link to
	for (int i = 0; i < num_vertex; i++){
		EdgeList temp = G->edges[i];
		printf("vertex %d\n", i);
		while (temp){
			printf("(%d, %d)", i ,temp->edge.toVertex);
			temp = temp->next;
		}
		printf("\n");
	}

	//printf the degrees in each vertex
	for (int i = 0; i < num_vertex; i++){
		printf("the vertex %d in_degrees : %d",i, in_degrees[i]);
		printf(" out_degrees : %d", out_degrees[i]);
		printf("\n");
	}
	
	//printf initial state 
	printf("\nThe initial state: ");
	for (int i = 0; i < num_vertex; i++){
		printf("%d", G->state[i]);
	}


	//-----------------------------------------------------------------------------
	//calculate a new state for each vertex through topological sort
	
	//check which vertex's indegree is 0 if there exist then enqueue through call check funtion
	check(in_degrees, num_vertex);
	if (queue != NULL){
		for (int i = 0; i < num_vertex; i++){
			if (queue == NULL){
				error = 1;
				break;
			}
			int vertex = deQueue(&queue);
			EdgeList elist = G->edges[vertex];
			while (elist != NULL){
				input[elist->edge.toVertex] += elist->edge.weight * G->state[vertex];
				if (input[elist->edge.toVertex] > 0){
					G->state[elist->edge.toVertex] = 1;
				} else{
					G->state[elist->edge.toVertex] = 0;
				}
				in_degrees[elist->edge.toVertex]--;
				elist = elist->next;
			}
			check(in_degrees, num_vertex);
		}
	}

	if (error == 1){ //if there is a error then print it out
		printf("\n error");
	} else {
		printf("\n Output of new state: ");
		for (int i = 0; i < num_vertex; i++){
			//printf("%d", state[i]);
			printf("%d", G->state[i]);
		}
	}
	return 0;
}

//check function is used to enqueue the vertex whose indegree is 0
void check(int in_degrees[], int num_vertex){
	for (int i = 0; i < num_vertex; i++){
		if (in_degrees[i] == 0 && flag[i] != 1){	// if indegree is 0 then return this vetex number 
			enQueue(&queue, i);
			flag[i] = 1;
		}
	}
}








