/* 
    Binary Search of k in V[N]
    Complexity: T(N) = O(logN)
    
    V is a SORTED vector
 */

int BinarySearch(int *V, int N, int k) {
    int l = 0, r = N-1 , m, found = 0;

    while (!found && l <= r) {
        m = (l+r)/2;
        if (V[m] == k)
            found = 1;
        if (V[m] < k)
            l = m+1;
        else
            r = m-1;
    }

    if (found)
        return m;
    else
        return -1;
}