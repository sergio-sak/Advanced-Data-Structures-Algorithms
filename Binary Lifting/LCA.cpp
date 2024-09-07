//For the sake of cleanliness, I will not be using my usual template

/*
The essence of Binary Lifting is to store for every node n, all of its ancestors which are in powers of 2. For ex. 2^0, 2^1, 2^2, ..., 2^j
Why this works?
    - Any number can be rewritten as powers of two. For ex. 13 = 2^3 + 2^2 + 2^0 = 8 + 4 + 1
    - Therefore, to get the 13th ancestor of node, all that is needed is to move up the 8 ancestors, then up 4 and lastly move up 1. 

The essence of LCA Queries using Binary Lifting is that we first move the deepest node to the ancestor which is on the same level as the second one(For the sake of simplicity, depth[node1] > depth[node2]),
and then we gradually move both nodes to its ancestors until, the parent of both nodes is the same. Then, we've found the LCA.
*/

int N, logn;
vi adj[MAXN]; //Adjacency List
int *depth, *par;
dvi binLift(MAXN, vi(20, -1));//dvi: Double Vector of Integers, 2d
                               //vi: Vector of Integers
                               //binLift: Stores the (2^j)th ancestor of any i 

void dfs(int u, int e = -1) { //Dfs to calculate depth and parent array
    if(u != 1)
        depth[u] = depth[e]+1;
    for(int v : adj[u]) {
        if(v == e) continue;
        dfs(v, u);
        par[v] = u;
    }
}

void binaryLifting() {
    for(int i = 1; i <= N; ++i) {
        binLift[i][0] = par[i];
    }   

    for(int pow = 1; pow <= logn; ++pow) { //Pow: Power
        for(int node = 1; node <= N; ++node) {
            if(binLift[node][pow-1] != -1)
                binLift[node][pow] = binLift[binLift[node][pow-1]][pow-1];
        }
    }
}

int kth(int node, int k) {
    for(int pow = 0; pow <= logn; ++pow) {
        if(k & (1 << pow)) { //Checks if current bit of k is on. For explanation take a look at the end of the file.
            node = binLift[node][pow];
            if(node == -1) return -1;
        }
    }
    return node;
}

int lca(int node1, int node2) {
    if(depth[node1] < depth[node2]) return lca(node2, node1);

    node1 = kth(node1, depth[node1] - depth[node2]);
    if(node1 == node2) return node1;

    for(int pow = logn; pow >= 0; --pow) {
        if(binLift[node1][pow] != binLift[node2][pow]) {
            node1 = binLift[node1][pow];
            node2 = binLift[node2][pow];
        }
    }

    return binLift[node1][0];
}

signed main()
{
    si(N); //si: Scanf Integer
    logn = std::__lg(N); //Only works for gcc compilers, same but better than log2
    par = new int[N+1]();
    depth = new int[N+1]();

    par[1] = -1;
    depth[1] = 1;
    for(int v = 2; v <= N; ++v) { //Assuming that the input is adjcacency list
        int u; si(u);
        adj[v].pb(u);
        adj[u].pb(v);
    }

    //Preprocessing
    dfs(1); //Root
    binaryLifting();

    delete[] par;
    delete[] depth;
    return 0;
}
