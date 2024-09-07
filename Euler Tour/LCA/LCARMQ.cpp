//For the sake of cleanliness, I will not be using my usual template

vi adj[MAXN]; //vi: Vector of Integers, Adjacency List
int N, timer = 0;
int RMQ[20][2*MAXN+1]; //Sparse Table
int *eulerTour, *start; //Euler Tour: Self Explanatory
                        //start: Time In
 
void dfs(int u, int e = -1, int h = 1) {
    start[u] = timer;
    RMQ[0][timer] = h;
    eulerTour[timer++] = u;
 
    for(int v : adj[u]) {
        if(v != e) {
            dfs(v, u, h+1);
            RMQ[0][timer] = h;
            eulerTour[timer++] = u;
        }
    }
}

//For Sparse Tables Check the "Sparse Tables/RMQ" section
void sparseTable() { //Preprocessing. Must be called before answering queries
    dfs(1); //Root
    for(int i = 1; i <= std::__lg(2*N-1)+1; ++i) {
        for(int j = 0; j + (1 << i) <= 2*N-1; ++j) {
            RMQ[i][j] = std::min(RMQ[i-1][j], RMQ[i-1][j + (1 << (i - 1))]);
        }
    }
}
 
int Query(int l, int r) {
    int i = std::__lg(r-l+1);
    return std::min(RMQ[i][l], RMQ[i][r - (1 << i) + 1]);
}