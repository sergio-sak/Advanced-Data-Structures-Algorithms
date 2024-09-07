//For the sake of cleanliness, I will not be using my usual template

vi adj[MAXN]; //Adjacency List
int N, Q, timer = 0;
int *eulerTour, *start, *end;
                             //start: Time In
                             //end: Time Out

void dfs(int u, int e = -1) { //Create Euler Tour with T.I. T.O
    start[u] = timer;
    eulerTour[timer++] = u;
    for(int v : adj[u])
        if(v != e) dfs(v, u);
    end[u] = timer-1;
}