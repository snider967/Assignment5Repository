/* The first vertex is held in v, the second is w. Wt is the weight,
*  although we don't care about it in this example. This Edge is the
*  Edge between v and w.
*/
typedef struct {
	int v;
	int w;
	int wt;
} Edge;

/* initialize graph with n vertices.
Returns 1 if successful, 0 otherwise */
int GRAPHinit(int n);
/* add edge to graph.
 Returns 1 if successful, 0 otherwise */
int GRAPHinsertE(Edge);
//Destroy graph
void GRAPHdestroy();
/* compute SSSP of graph from vertex s
Returns distance array or NULL if malloc failed */
int *SSSP(int s);
/* Returns 1 if simple path between v and w exists, 0 otherwise,
using the algorithm in the assignment requirements. Also prints
edges along path, if it exists. */
int GRAPHpath(int v, int w, int visited[]);
/* Prints graph, with each adjacency list printed on one line,
to filehandle f.*/
//void GRAPHprint(FILE *f);

int GRAPHpathHelp(int v, int w);
