/*
Binary Search
*/
// [first, last) is ASC, return the minimum j s.t. a[j] >= val
// If a[last-1] < val, return last
int l_ul( int a[], int first, int last, int val ){
    int it, step, cnt = last-first;
    while( cnt > 0 ){
        it = first; step=cnt>>1; it+=step;
        if( a[it] < val ) 
        { first=++it;  cnt -=(step+1);}
        else cnt=step;
    }
    return first;
}

// [first, last) is ASC, return minimum j s.t. a[j] > val
// If a[last-1] <= val, return last
int l_l( int a[], int first, int last, int val ){
    int it, step, cnt = last-first;
    while( cnt > 0 ){
        it = first; step=cnt>>1; it+=step;
        if( a[it] <= val )
        { first=++it;  cnt -=(step+1);}
        else cnt=step;
    }
    return first;
}

// (first, last] is ASC, return maximum j s.t. a[j] < val
// If a[first+1] >= val, return first;
int uless( int a[], int first, int last, int val ){
    int it, step, cnt = last-first;
    while( cnt > 0 ){
        it = last; step=cnt>>1; it-=step;
        if( a[it] >= val )
        { last=--it;  cnt -=(step+1);}
        else cnt=step;
    }
    return last;
}