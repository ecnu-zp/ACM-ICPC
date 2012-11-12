/**
*  For All-Pair Shortest Path
*  Floyd Algorith. g[i][j] is the cost of arc(i,j), f[i][j] is the shortest path from i to j.
*/
void floyd(){
	int i, j, k;
	for( i=1; i<=n; i++)
		for( j=1; j<=n; j++)
			f[i][j]=g[i][j];
	for( k=1; k<=n; k++)
		for( i=1; i<=n; i++)
			for( j=1; j<=n; j++){
				if( f[i][k]==INFI || f[k][j]==INFI ) continue;
				if( f[i][k]+f[k][j]<f[i][j] )
					f[i][j]=f[i][k]+f[k][j];
			}
}

/**
Dijkstra Algorithm via binary heap.
*/
typedef unsigned long long I;
const int maxn=20, maxm =50;				// uperbound of number of nodes and arcs(edges)
int n, m, tot;								// number of nodes and edges. tot: number of arcs.
const I INFI = (I)1<<60;					// Infinity

struct Edge {								// arc type：< x, y>=len. next: pointer to next arc
	int x, y, next, len;
};
Edge g[maxm];								
int first[maxn];							// first[x]:  the index of the fist arc emanate from node x
I value[maxn];								// distance label used by Dijkstra.
bool done[maxn];							// If the shortest path from s to x has been calculated, then done[x]=true;
int n2h[maxn], h2n[maxn];					// node to heap and heap to node 
int size;									// size of the binary heap. heap array is indexed from 1 to size
int prev[maxn];

int num_updates;

// Shift Up
void update( int r ){
	int q=n2h[r], p=q>>1;
	while( p && value[ h2n[p] ]>value[r] )
		n2h[h2n[p]]=q, h2n[q]=h2n[p], q=p, p=q>>1;
	h2n[q]=r; n2h[r]=q;
}

// return the heap top , and delete the top. Then Shift Down
int getmin(){
	int ret=h2n[1], p=1, q=2,  r=h2n[size--];
	while( q<=size ){
		if( q<size && value[h2n[q+1]]<value[h2n[q]] ) ++q;
		if( value[h2n[q]] < value[r] )
			n2h[h2n[q]]=p, h2n[p]=h2n[q], p=q, q=p<<1;
		else break;
	}
	h2n[p]=r; n2h[r]=p;
	return ret;
}

// 
void dijkstra( int src  ){
	int i, j, u, v;
	I temp;
	for( i=1; i<=n; ++i) value[i]=INFI, done[i]=n2h[i]=0;
	value[src]=0;	h2n[size=1]=src;	n2h[src]=1;
	while( 1 ){						// while( !done[dst] ) 
		if( size==0 ) return;
		u=getmin();		done[u]=1;
		j=first[u];
		printf("now S %d\n", u);
		while( j!=-1 ){
			v=g[j].y;
			if( !done[v] && (temp=value[u]+g[j].len)<value[v] ) {
				if( n2h[v]==0 ) h2n[++size]=v, n2h[v]=size;
				prev[v]=u;
				printf("d[%d] d[%d], %d, %d, %d\n", u, v, value[u], temp-value[u], value[v] );
				value[v]=temp;
				update( v ); 
				num_updates++;
			}
			j=g[j].next;
		}
	}
}

void init(){
	tot = num_updates = 0;
	for( int i=1; i<=n; ++i ) first[i]=prev[i]=-1;
}

//	each arc <a, b>=c;
void addarc( int a, int b, int c){
	++tot;
	g[tot].x=a; g[tot].y=b; g[tot].len=c; g[tot].next=first[a]; first[a]=tot;
}



