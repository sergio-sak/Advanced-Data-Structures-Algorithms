//For the sake of cleanliness, I will not be using my usual template

/*
The essence of Binary Lifting is to store for every node n, all of its ancestors which are in powers of 2. For ex. 2^0, 2^1, 2^2, ..., 2^j
Why this works?
    - Any number can be rewritten as powers of two. For ex. 13 = 2^3 + 2^2 + 2^0 = 8 + 4 + 1
    - Therefore, to get the 13th ancestor of node, all that is needed is to move up the 8 ancestors, then up 4 and lastly move up 1. 
*/

int N, logn, *par;
dvi binLift(MAXN, vi(20, -1)); //dvi: Double Vector of Integers, 2d
                               //vi: Vector of Integers
                               //binLift: Stores the (2^j)th ancestor of any i 

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

int kthAncestor(int node, int k) {
    for(int pow = 0; pow <= logn; ++pow) {
        if(k & (1 << pow)) { //Checks if current bit of k is on. For explanation take a look at the end of the file.
            node = binLift[node][pow];
            if(node == -1) return -1;
        }
    }
    return node;
}

signed main()
{
    si(N); //si: Scanf Integer
    par = new int[N+1];
    logn = std::__lg(N); //Only works for gcc compilers, same but better than log2

    par[1] = -1;
    for(int v = 2; v <= N; ++v) { //Assuming that the input is the parent array
        int u; si(u); u;
        par[v] = u;
    }

    binaryLifting(); //Preprocessing

    //Queries

    delete[] par;
    return 0;
}
