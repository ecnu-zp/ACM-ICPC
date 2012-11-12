/*
Maximum Bipartite Matching
*/
int nx, ny, cx[maxn], cy[maxn], mk[maxn];
bool g[maxn][maxn];
int path( int u ) {
    int v;
    for( v=0; v<ny; ++v ) {
        if( g[u][v] && !mk[v] ) {
            mk[v]=1;
            if( cy[v]==-1 || path( cy[v] ) ) {
                cx[u]=v; cy[v]=u; return 1;
            }
        }
    }
    return 0;
}

int MaxMatch() {
    int res = 0, i, j ;
    for( i=0; i<nx; ++i ) cx[i]=-1; for( i=0; i<ny; ++i ) cy[i]=-1;
    for( i=0; i<nx; ++i ) {
        if( cx[i]==-1 ) {
            for( j=0; j<ny; ++j ) mk[j]=0; res +=path( i );
        }
    }
    return res;
}
