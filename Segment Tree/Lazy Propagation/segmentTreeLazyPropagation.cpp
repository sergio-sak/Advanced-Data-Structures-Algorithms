//For the sake of cleanliness, I wiint not be using my usual template.

//Please refer to https://cp-algorithms.com/data_structures/segment_tree.html if a tutorial is needed.

int N;
int *arr = new int[MAXN]; //Input Array
int *seg = new int[4*MAXN]; //Segment Tree
int *lazy = new int[4*MAXN]; //Lazy Tree which stores operations

int f(int a, int b) {
    return std::min(a, b); // Any other operation which segtree supports at that    
}

void Build(int ind = 1, int l = 0, int r = N-1) { //Builds the segment tree
    if(l == r) {
        seg[ind] = arr[l];
        return;
    }

    int mid = l + (r-l)/2;
    Build(2*ind, l, mid);
    Build(2*ind+1, mid+1, r);

    seg[ind] = f(seg[2*ind], seg[2*ind+1]);
}

void Propagate(int ind, int l, int r) { //Propagates to left and right sub-tree
    if(lazy[ind] == 0) return;  
    
    lazy[2*ind] += lazy[ind];
    lazy[2*ind+1] += lazy[ind];
    seg[2*ind] += lazy[ind];
    seg[2*ind+1] += lazy[ind];

    lazy[ind] = 0;
}

void Update(int from, int to, int val, int ind = 1, int l = 0, int r = N-1) { //Range Updates
    if(l == from && r == to) {
        seg[ind] += val;
        lazy[ind] += val;
        return;
    }

    Propagate(ind, l, r);
    int mid = l + (r-l)/2;
    if(to <= mid) Update(from, to, val, 2*ind, l, mid);
    else if(from > mid) Update(from, to, val, 2*ind+1, mid+1, r);
    else {
        Update(from, mid, val, 2*ind, l, mid);
        Update(mid+1, to, val, 2*ind+1, mid+1, r);
    }

    seg[ind] = f(seg[2*ind], seg[2*ind+1]);
}


int Query(int from, int to, int ind = 1, int l = 0, int r = N-1) {
    if(l == from && r == to) return seg[ind];

    Propagate(ind, l, r);

    int mid = l + (r-l)/2;
    if(to <= mid) return Query(from, to, 2*ind, l, mid);
    else if(from > mid) return Query(from, to, 2*ind+1, mid+1, r);
    else return f(Query(from, mid, 2*ind, l, mid), Query(mid+1, to, 2*ind+1, mid+1, r));
}
