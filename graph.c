#include <stdlib.h>
#include <limits.h>
#include "graph.h"

typedef struct graphnode{ 
	int v;
	int wt;
	struct graphnode *next; 
} Node;

typedef struct graph{
	int V;
	int E;
	Node **adj;  //array of ptrs to linked lists
}Graph;

Graph *G;

int GRAPHinit(int V){
	G = malloc(sizeof(Graph));
	if(G == NULL)
		return 0;
	G->V = V;
	G->E = 0;
	G->adj = calloc(V, sizeof(Node *));
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
