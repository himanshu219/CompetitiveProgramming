#define MAXV 2000
int q[MAXV];
struct flow_network {
    struct edge {
        int v, cap, nxt;
        edge() { }
        edge(int v, int cap, int nxt) : v(v), cap(cap), nxt(nxt) { }
    };
    int n, ecnt, *head, *curh, *d;
    edge *e;
    flow_network(int n, int m) : n(n), ecnt(0) {
        e = new edge[2*m];
        head = new int[n];
        curh = new int[n];
        d = new int[n];
        memset(head, -1, n * sizeof(int));
    }
    void add_edge(int u, int v, int uv, int vu = 0) {
        e[ecnt] = edge(v, uv, head[u]), head[u] = ecnt++;
        e[ecnt] = edge(u, vu, head[v]), head[v] = ecnt++;
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = curh[v], ret; i != -1; i = e[i].nxt)
            if (e[i].cap > 0 && d[e[i].v] + 1 == d[v])
                if ((ret = dfs(e[i].v, t, min(f, e[i].cap))) > 0)
                    return (e[i].cap -= ret, e[i^1].cap += ret, ret);
        return 0;
    }
    int max_flow(int s, int t) {
        int f = 0, x, l, r;
        while (true) {
            memset(d, -1, n * sizeof(int));
            l = r = 0, d[q[r++] = t] = 0;
            while (l < r)
                for (int v = q[l++], i = head[v]; i != -1; i = e[i].nxt)
                    if (e[i^1].cap > 0 && d[e[i].v] == -1)
                        d[q[r++] = e[i].v] = d[v]+1;
            if (d[s] == -1) break;
            memcpy(curh, head, n * sizeof(int));
            while ((x = dfs(s, t, INF)) != 0) f += x;
        }
        return f;
    }
};