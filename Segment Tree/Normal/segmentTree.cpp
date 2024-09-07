//For the sake of cleanliness, I will not be using my usual template.

//Please refer to https://cp-algorithms.com/data_structures/segment_tree.html if a tutorial is needed.

int N;
int *arr = new int[MAXN]; //Input Array
int *seg = new int[4*MAXN]; //Segment Tree

int f(int a, int b) { //Most Operations
    return a + b;
}

void Build(int ind = 1, int l = 0, int r = N-1) { //Builds the Segment Tree
    if(l == r) {
        seg[ind] = arr[l];
        return;
    }

    int mid = l + (r-l)/2;
    Build(2*ind, l, mid);
    Build(2*ind+1, mid+1, r);

    seg[ind] = f(seg[2*ind], seg[2*ind+1]);
}

void Update(int pos, int val, int ind = 1, int l = 0, int r = N-1) { //Point-Update
    if(l == r) {
        seg[ind] = val;
        return;
    }

    int mid = l + (r-l)/2;
    if(pos <= mid) Update(pos, val, 2*ind, l, mid);
    else Update(pos, val, 2*ind+1, mid+1, r);

    seg[ind] = f(seg[2*ind], seg[2*ind+1]);
}

int Query(int from, int to, int ind = 1, int l = 0, int r = N-1) { //Answers Queries
    if(l == from && r == to) return seg[ind];

    int mid = l + (r-l)/2;
    if(to <= mid) return Query(from, to, 2*ind, l, mid);
    else if(from > mid) return Query(from, to, 2*ind+1, mid+1, r);
    else return f(Query(from, mid, 2*ind, l, mid), Query(mid+1, to, 2*ind+1, mid+1, r));
}
