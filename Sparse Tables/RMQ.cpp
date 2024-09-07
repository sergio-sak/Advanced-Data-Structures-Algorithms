//For the sake of cleanliness, I will not be using my usual template

/*
The essence of Sparse Tables for Range Minimum Queries is that for every element, we calculate the minimum for the range [ind[N], ind[N] + 2^{1, 2, 4, 8...}]
Why this works?
    - Any number can be rewritten as powers of two. For ex. 13 = 2^3 + 2^2 + 2^0 = 8 + 4 + 1
    - Therefore, any range can be split into ranges of size of a power of 2. Then using the idempotence property (min(min(a,b),c)=min(a,b,c)),
    we can get the minimum of any range by splitting it in O(1)
*/

int N, RMQ[25][MAXN]; //Sparse Table

void preprocess() { //Preprocess the Sparse Table
    for(int i = 1; i <= std::__lg(N)+1; ++i) { //Only works for gcc compilers, same but better than log2
        for(int j = 0; j + (1 << i) <= N; ++j) {
            RMQ[i][j] = std::min(RMQ[i-1][j], RMQ[i-1][j + (1 << (i-1))]);
        }
    }
}

int Query(int L, int R) { //Answer Queries of the form, [L, R]
    int i = std::__lg(R-L+1);
    int minimum = std::min(RMQ[i][L], RMQ[i][R - (1 << i) + 1]);
}

signed main()
{
    si(N); //si: Scanf Integer
    
    for(int i = 0; i < N; ++i) { //Storing the Array
        si(RMQ[0][i]); //si: Scanf Integer
    }

    //Preprocessing
    preprocess();

    //Answer Queries
    return 0;
}