/* 
    Linear Search of k in V[N]
    Complexity: T(N) = Theta(N)
 */

int LinearSearch(int *V, int N, int k) {
    int i, index = -1;

    for (i = 0; i < N; i++)
        if (V[i] == k)
            index = i;
    return index;
}