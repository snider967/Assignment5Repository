#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph.h"

typedef struct graphnode{
	int v;
	int wt;
	struct graphnode *next;
} Node;

typedef struct graph{
	int V; //number of vertices
	int E; //number of edges
	Node **adj;  //array of ptrs to linked lists
}Graph;

Graph *G;

int GRAPHinit(int V){
	G = malloc(sizeof(Graph));
	if(G == NULL)
		return 0;
	G->V = V;
	G->E = 0;
	G->adj = calloc(V, sizeof(Node *));;
	if(G->adj == NULL){
		free(G);
		return 0;
	}
	return 1;
}

static Node *constructEdge(int v, int wt, Node *next){
	Node *p = malloc(sizeof(Node));
	if(p == NULL)
		return NULL;
	p->v = v;
	p->wt = wt;
	p->next = next;
	return p;
}

int GRAPHinsertE(Edge e){
	int v = e.v;
	G->adj[v] = constructEdge(e.w, e.wt, G->adj[v]);
	if(G->adj[v] == NULL)
		return 0;
	G->E++;
	return 1;
}

void GRAPHdestroy(){
	for(int v=0; v < G->V; v++){
		Node *t = G->adj[v];
		while(t != NULL){
			Node *temp = t;
			t = t->next;
			free(temp);
		}
	}
	free(G->adj);
	free(G);
}

//Solve SSSP using Bellman Ford with FIFO queue
int *SSSP(int s){
  int n = G->V;
  int *queue;//circular buffer to hold FIFO queue
  int *inQueue;//sparse representation of queue
  int front = 0; //index of front of queue
  int size = 1; //size of list (has source vertex initially)
  int *D;//distance to each vertex

  if((queue = malloc(n*sizeof(int))) == NULL) return NULL;
  if((inQueue = malloc(n*sizeof(int))) == NULL) return NULL;
  if((D = malloc(n*sizeof(int))) == NULL) return NULL;

  for(int i=0; i <n; i++){
	  D[i] = INT_MAX;
	  inQueue[i] = 0;
  }
  D[s] = 0;
  queue[0] = s;
  inQueue[s] = 1;
  while(size > 0){
    int i = queue[front];
		front = (front+1)%n;
		size--;
		inQueue[i] = 0;
		//printf("extract %d\n", i);
		for(Node *t = G->adj[i]; t!= NULL; t = t->next){
			int j = t->v;
			int wt = t->wt;
			if(D[j] > D[i]+wt){
				D[j] = D[i] + wt;
				if(!inQueue[j]){
					//printf("insert %d\n", j);
					queue[(front+size)%n] = j;
					size++;
					inQueue[j] = 1;
				}
			}
		}
  }
  return D;
}

int GRAPHpath(int v, int w, int visited[]){
	if(v == w){
		return 1;
	}
	visited[v] = 1;
	for(Node *t = G->adj[v]; t!= NULL; t = t->next){
		if((visited[t -> v] != 1) && (GRAPHpath(t -> v, w, visited) == 1)){
				printf("%d-%d ", t -> v , v);
				return 1;
		}
	}
	return 0;
}

int GRAPHpathHelp(int v1, int w1){
	int * visitArr = calloc((G -> V), sizeof(int));
	return GRAPHpath(v1 , w1, visitArr);
}
/*
void GRAPHprint(FILE *f){

}
*/

int main(int argc, char ** argv){
	if(GRAPHinit(4) == 1){
		printf("Graph initialized\n");
	}
	Edge * e1 = malloc(sizeof(Edge));
	e1 -> v = 0;
	e1 -> w = 1;
	e1 -> wt = 1;
	Edge * e2 = malloc(sizeof(Edge));
	e2 -> v = 1;
	e2 -> w = 2;
	e2 -> wt = 1;
	Edge * e3 = malloc(sizeof(Edge));
	e3 -> v = 2;
	e3 -> w = 3;
	e3 -> wt = 1;
	if(GRAPHinsertE(*e1) == 1){
		printf("Edge 1 entered.\n");
	}
	if(GRAPHinsertE(*e2) == 1){
		printf("Edge 2 entered.\n");
	}
	if(GRAPHinsertE(*e3) == 1){
		printf("Edge 3 entered.\n");
	}
	if(GRAPHpathHelp(0, 3) == 1){
		printf("It works\n");
	}
	GRAPHdestroy();

}
