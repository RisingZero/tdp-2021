/* 
    Optimized Linear Search of k in V[N]
    Complexity: T(N) = O(N)
 */

int LinearSearchOptimized(int *V, int N, int k) {
    int i, index = -1;

    for (i = 0; i < N && index == -1; ++i)
        if (V[i] == k)
            index = i;
    return index;
}