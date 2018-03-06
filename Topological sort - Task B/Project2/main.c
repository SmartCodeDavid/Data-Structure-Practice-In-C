/**
*	Project Name: Part B(DFS-Topological sort)
*	Author: Tianxiang Lan
*	Description: All function on part B was implemented. All the result calculated by this program is corrct.
*              
*	Date: 10/5/2016
*/

#define _CRT_SECURE_NO_DEPRECATE
#include "stdlib.h"
#include <stdio.h>
#include "DFS.h"
#include "stack.h"
#include "graph.h"

//check function is used to enqueue the vertex whose indegree is 0
void check(int in_degrees[], int num_vertex);
int getStartVex(int arr[]);
void pushStack(stackNode *stack, int data);
int DFS(EdgeList edgeList, stackNode *stack, int preVex);
int popStack(stackNode *stack);
int IsNodeInStack(stackNode stack, int data);
int popStack(stackNode *stack);
int countElement(stackNode *stack);

Graph *G;
int num_vertex = 0;
int num_edges = 0;
int toVertex = 0;
int weight = 0;
int error = 0;
int startVertex = 0;
int **checkList;
int *visit;

int main(){
	//init graph
	G = (Graph *)malloc(sizeof(Graph));

	//input the number of vertex
	scanf("%d", &num_vertex);

	//allocate checklist
	checkList = (int **)malloc(sizeof(int *) * num_vertex);
	for (int i = 0; i < num_vertex; i++){
		checkList[i] = (int *)malloc(sizeof(int) * num_vertex);
	}

	//allocate memory for each array
	int *in_degrees = (int *)malloc(sizeof(int) * num_vertex);
	int *out_degrees = (int *)malloc(sizeof(int) * num_vertex);
	int *input = (int *)malloc(sizeof(int) * num_vertex);
	int *state = (int *)malloc(sizeof(int) * num_vertex);
	visit = (int *)malloc(sizeof(int) * num_vertex);

	G->state = state;

	//initialise in degrees, out degrees and state for each vertex
	for (int i = 0; i < num_vertex; i++){
		in_degrees[i] = 0;
		out_degrees[i] = 0;
		G->state[i] = 0;
		input[i] = 0;
		visit[i] = 0;
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
			printf("(%d, %d)", i, temp->edge.toVertex);
			temp = temp->next;
		}
		printf("\n");
	}

	//printf the degrees in each vertex
	for (int i = 0; i < num_vertex; i++){
		printf("the vertex %d in_degrees : %d", i, in_degrees[i]);
		printf(" out_degrees : %d", out_degrees[i]);
		printf("\n");
	}

	//printf initial state 
	printf("\nThe initial state: ");
	for (int i = 0; i < num_vertex; i++){
		printf("%d", G->state[i]);
	}



	//DFS ------- Topological sort 

	//get the vertex with indegree is 0
	int startVex = getStartVex(in_degrees);
	
	//init stack
	stackNode stack = NULL;

	//error -- no vertex with indegree 0 so ERROR
	if (startVex == -1){ 
		printf("\nERROR");
		return 0;
	}
	else{	//there is vertex with indegree 0
		for (;;){
			int result = DFS(G->edges[startVex], &stack, startVex); //go into DFS core function
			if (result == -1){
				printf("\nERROR--CIRCLE");
			//	system("pause");
				return 0;
			}
			startVex = getStartVex(in_degrees);
			if (startVex != -1){ continue; }
			else{
				break;
			}
		}

	}

	
	int num = countElement(&stack);
	
	//traverse stack we got above
	for (int i = 0; i < num; i++){
		int vertex = popStack(&stack);
		EdgeList elist = G->edges[vertex];
		while (elist != NULL){
			input[elist->edge.toVertex] += elist->edge.weight * G->state[vertex];
			if (input[elist->edge.toVertex] > 0){
				G->state[elist->edge.toVertex] = 1;
			}
			else{
				G->state[elist->edge.toVertex] = 0;
			}
			elist = elist->next;
		}
	}
	
	//print out new state
	printf("\n Output of new state: ");
	for (int i = 0; i < num_vertex; i++){
		printf("%d", G->state[i]);
	}
	//system("pause");
	return 0;
}

//The core function of DFS
int DFS(EdgeList edgeList, stackNode *stack, int preVex){
	EdgeList temp = edgeList;	//temp is used to traverse on the loop
	if (temp != NULL) {
		EdgeList temp = edgeList;
		while (temp != NULL){
			int toVertex = temp->edge.toVertex; //get vertex
			if (visit[toVertex] == -1){		//-1 indicates vertex still be used on loop if true then this grap exist circle
				return -1;					//return -1 ERROR
			}
			if (visit[toVertex] != 1){		
				visit[preVex] = -1;
				if (DFS(G->edges[toVertex], stack, toVertex) == -1){ //if any error then exit and return -1
					return -1;
				}
			}
			temp = temp->next;	//get the next element
		}
	}

	if (IsNodeInStack(*stack, preVex) == 0){ //is there not this vertex then push it into stack
		visit[preVex] = 1;
		pushStack(stack, preVex); //push it into stack
	}
	return 0;
}

//To indentify if there is a element stored in the stack 
int IsNodeInStack(stackNode stack, int data){
	if (stack){
		stackNode temp = stack;
		while (temp != NULL){
			if (temp->data == data){
				return 1;
			}
			temp = temp->next;
		}
	}
	return 0;
}

//count element in stack 
int countElement(stackNode *stack){
	if (*stack){
		int i = 0;
		stackNode temp = *stack;
		while (temp != NULL){
			i++;
			temp = temp->next;
		}
		return i;
	}
	return -1;
}

//pop element from stack
int popStack(stackNode *stack){
	if (*stack){
		int data = (*stack)->data;
		*stack = (*stack)->next;
		return data;
	}
	return -1;
}

//Push element into stack
void pushStack(stackNode *stack, int data){
	if (*stack == NULL){
		*stack = (stackNode)malloc(sizeof(struct Stack));
		(*stack)->data = data;
		(*stack)->next = NULL;

	}
	else{
		//create a new node
		stackNode newNode = (stackNode)malloc(sizeof(struct Stack));
		newNode->data = data;
		newNode->next = NULL;

		//stackNode temp = *stack;//point to head
		newNode->next = *stack;
		*stack = newNode;
	}
}

//get the vertex with indegree 0
int getStartVex(int arr[]){
	for (int i = 0; i < num_vertex; i++){
		if (arr[i] == 0){
			arr[i] = -2;//set as access already
			return i;
		}
	}
	return -1;
}
