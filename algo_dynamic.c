#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll maxVal(ll a, ll b) {
    return (a > b) ? a : b;
}

ll knapsack(ll values[], ll weights[], int n, ll capacity) {
    ll **_arr = (ll **)malloc((n + 1) * sizeof(ll *));
    for(int i = 0; i <= n; i++) {
        _arr[i] = (ll *)malloc((capacity + 1) * sizeof(ll));
    }
    
    for(int i = 0; i <= n; i++){
        for(ll w = 0; w <= capacity; w++) {
            if(i == 0 || w == 0) {
                _arr[i][w] = 0;
            } else if(weights[i - 1] <= w) {
                _arr[i][w] = maxVal(values[i - 1] + _arr[i - 1][w - weights[i - 1]], _arr[i - 1][w]);
            } else {
                _arr[i][w] = _arr[i - 1][w];
            }
        }
    }

    ll max_val = _arr[n][capacity];
    for(int i = 0; i <= n; i++){
        free(_arr[i]);
        }
    free(_arr);

    return max_val;
}

int main() {
    int n;
    ll capacity;

    scanf("%lld %d", &capacity, &n);

    ll *values = (ll *)malloc(n * sizeof(ll));
    ll *weights = (ll *)malloc(n * sizeof(ll));
    for(int i = 0; i < n; i++) 
        scanf("%lld %lld", &weights[i], &values[i]);
    ll max_val = knapsack(values, weights, n, capacity);
    printf("%lld\n", max_val);

    free(values);
    free(weights);

    return 0;
}
