#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll maxVal(ll a, ll b) {
    return (a > b) ? a : b;
}

void knapsack(ll values[], ll weights[], int n, ll capacity) {
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

    int *selected = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        selected[i] = 0;

    ll remaining_capacity = capacity;
    for (int i = n; i > 0 && remaining_capacity > 0; i--) {
        if (_arr[i][remaining_capacity] != _arr[i - 1][remaining_capacity]) {
            selected[i - 1] = 1;
            remaining_capacity -= weights[i - 1];
        }
    }

    ll max_val = _arr[n][capacity];
    printf("%lld\n", max_val);

    for (int i = 0; i < n; i++) {
        if (selected[i]) {
            printf("%d ", i); 
        }
    }
    printf("\n");

    free(selected);
    
    for(int i = 0; i <= n; i++){
        free(_arr[i]);
    }
    free(_arr);

}

int main() {
    int n;
    ll capacity;

    scanf("%lld %d", &capacity, &n);

    ll *values = (ll *)malloc(n * sizeof(ll));
    ll *weights = (ll *)malloc(n * sizeof(ll));
    for(int i = 0; i < n; i++) 
        scanf("%lld %lld", &weights[i], &values[i]);
    
    knapsack(values, weights, n, capacity);

    free(values);
    free(weights);

    return 0;
}
