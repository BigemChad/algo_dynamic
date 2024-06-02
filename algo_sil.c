#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
ll brute_force_knapsack(ll values[], ll weights[], int n, ll capacity) {
    ll max_value = 0;

    for (ll i = 0; i < (1LL << n); i++) {
        ll current_value = 0;
        ll current_weight = 0;

        for (int j = 0; j < n; j++) {
            if (i & (1LL << j)) {
                current_value += values[j];
                current_weight += weights[j];
            }
        }

        if (current_weight <= capacity && current_value > max_value) {
            max_value = current_value;
        }
    }

    return max_value;
}

int main() {
    int n;
    ll capacity;

    scanf("%lld %d", &capacity, &n);

    ll *values = (ll *)malloc(n * sizeof(ll));
    ll *weights = (ll *)malloc(n * sizeof(ll));

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &weights[i], &values[i]);
    }

    ll max_value = brute_force_knapsack(values, weights, n, capacity);
    printf("%lld\n", max_value);

    free(values);
    free(weights);

    return 0;
}
