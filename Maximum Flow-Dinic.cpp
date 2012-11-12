/*DINIC Algorithm for Maximum Flow (without lowerbound on flow)
 * Each arc has 3 propertites. f,c,r: flow, capacity, residual capacity
 * Graph *gr;  gr = new Graph();        new statement in main function
 * gr->init( s, t, N);                  N is the # of nodes
 * gr->add_edge( u, v, c1, c2 );        For arc c1=c, c2=0; For edge, c1=c2=c;
 * gr->dinic();                         calculate maximum flow
 * gr->mincut_s();                      calculate a cut [s]. If sv[k]=1, then k is in [s]. Recorded in array "cuts"
 * gr->mincut_t();                      calculate a cut [t]. If tv[k]=1, then k is in [t]. Recorded in array "cutt"
 * gr->cute();                          calculate arcs across a cut. Recurd the label(id) of arcs in array "cut_e"
 * Nodes are numbered from 1
 */

const int maxn = 100 + 5, maxm = 20000 + 5, INFI = 0x3fffffff;
const double eps = 1e-8;

inline int compd(double a, double b) {
    if (fabs(a - b) < eps) return 0;
    if (a + eps < b) return -1;
    return 1;
}

struct Graph {

    struct Edge {
        int x, y, next, op, f, c, r;
        int idx;

        Edge(int _x, int _y, int _next, int _op, int _c, int _f, int _r) : x(_x), y(_y), next(_next), op(_op), c(_c), f(_f), r(_r) {
        };

        Edge() {
        };
    };
    typedef int sz[maxn + 5];
    Edge g[2 * maxm + 5];
    int sn, tn;
    sz first, first1, p, level, prt;
    bool visited[maxn + 1];
    int n, m, tot, vs, vt, maxflow;
    bool sv[maxn], tv[maxn];
    vector<int> cut_e, cuts, cutt;

    inline bool ok(Edge * ed) {
        return ( ed->f < ed->c || ed->r > 0);
    }

    inline void minup(int &a, const int &b) {
        a = a > b ? b : a;
    }

    inline void add_edge(int a, int b, int c1, int c2, int idx=0) {
        ++tot;
        g[tot] = Edge(a, b, first[a], tot + 1, c1, 0, 0);
        first[a] = tot;
        g[tot].idx = idx;
        ++tot;
        g[tot] = Edge(b, a, first[b], tot - 1, c2, 0, 0);
        first[b] = tot;
        g[tot].idx = idx;
    }

    void make_level() {
        int i, head, tail, id, tp;
        Edge *pe;
        for (i = 1; i <= n; ++i) level[i] = INFI;
        head = tail = 0;
        p[tail++] = vs;
        level[vs] = 1;
        while (head < tail) {
            tp = p[head++];
            if (tp == vt) return;
            id = first[tp];
            while (id != -1) {
                pe = &g[id];
                if (level[pe->y] > level[tp] + 1 && ok(pe)) {
                    p[tail++] = pe->y;
                    level[pe->y] = level[tp] + 1;
                }
                id = g[id].next;
            }
        }
    }

    void dfs_maxflow() {
        int i, j, top, mint, id, tp, tj;
        Edge *pe;
        for (i = 1; i <= n; ++i) {
            first1[i] = first[i];
            visited[i] = prt[i] = 0;
        }
        top = 1;
        p[1] = vs;
        while (top > 0) {
            if (p[top] == vt) {
                mint = INFI;
                for (j = top; j >= 2; --j) {
                    pe = &g[prt[p[j]]];
                    if (pe->f < pe->c) minup(mint, pe->c - pe->f);
                    else minup(mint, pe->r);
                }
                for (j = top; j >= 2; --j) {
                    pe = &g[prt[p[j]]];
                    if (pe->f < pe->c) {
                        pe->f += mint;
                        g[pe->op].r += mint;
                        if (pe->f == pe->c) tj = j;
                    } else {
                        pe->f -= mint;
                        g[pe->op].r -= mint;
                        if (pe->f == 0) tj = j;
                    }
                }
                top = tj - 1;
            } else {
                id = first1[p[top]];
                tp = p[top];
                while (id != -1) {
                    pe = &g[id];
                    if (!visited[pe->y] && level[pe->y] == level[tp] + 1 && ok(pe)) {
                        first1[p[top++]] = pe->next;
                        p[top] = pe->y;
                        prt[p[top]] = id;
                        break;
                    }
                    id = g[id].next;
                }
                if (id == -1) {
                    visited[p[top]] = 1;
                    --top;
                }
            }
        }
    }

    void init(int _vs, int _vt, int _n) {
        vs = _vs;
        vt = _vt;
        n = _n;
        for (int i = 1; i <= n; ++i) first[i] = -1;
        tot = 0;
        cut_e.clear();
        cuts.clear();
        cutt.clear();
    }

    void dinic() {
        int id;
        while (1) {
            make_level();
            if (level[vt] == INFI) break;
            dfs_maxflow();
        }
        maxflow = 0;
        id = first[vs];
        while (id != -1) {
            maxflow += g[id].f;
            id = g[id].next;
        }
    }

    void mincut_s() {
        int i, id, cur, head, tail;
        Edge *pe;
        for (i = 1; i <= n; ++i) sv[i] = 0;
        head = tail = 0;
        p[tail++] = vs;
        sn = 1;
        sv[vs] = 1;
        while (head < tail) {
            cur = p[head++];
            id = first[cur];
            while (id != -1) {
                pe = &g[id];
                if (!sv[pe->y] && ok(pe)) {
                    p[tail++] = pe->y;
                    sv[pe->y] = 1;
                    sn++;
                    cuts.push_back(pe->y);
                }
                id = g[id].next;
            }
        }
    }

    void mincut_t() {
        int i, id, cur, head, tail;
        Edge *pe;
        for (i = 1; i <= n; ++i) tv[i] = 0;
        head = tail = 0;
        p[tail++] = vt;
        tn = 1;
        tv[vt] = 1;
        while (head < tail) {
            cur = p[head++];
            id = first[cur];
            while (id != -1) {
                pe = &g[g[id].op];
                if (!tv[pe->x] && ok(pe)) {
                    p[tail++] = pe->x;
                    tv[pe->x] = 1;
                    tn++;
                    cutt.push_back(pe->x);
                }
                id = g[id].next;
            }
        }
    }

    void cute() {
        int i, id;
        mincut_s();
        for (i = 1; i <= n; ++i) {
            if (!sv[i]) continue;
            id = first[i];
            while (id != -1) {
                if (sv[g[id].y] == 0 && g[id].f <= g[id].c) cut_e.push_back(g[id].idx);
                id = g[id].next;
            }
        }
    }
};