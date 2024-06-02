#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll value;
    ll weight;
    double ratio;
} Item;

int compare(const void *a, const void *b) {
    double r1 = ((Item *)a)->ratio;
    double r2 = ((Item *)b)->ratio;
    if (r1 > r2) return -1;
    if (r1 < r2) return 1;
    return 0;
}

ll greedy_knapsack(Item items[], int n, ll capacity) {
    qsort(items, n, sizeof(Item), compare);
    
    ll max_value = 0;
    ll current_weight = 0;

    for (int i = 0; i < n; i++) {
        if (current_weight + items[i].weight <= capacity) {
            current_weight += items[i].weight;
            max_value += items[i].value;
        }
    }

    return max_value;
}

int main() {
    int n;
    ll capacity;

    scanf("%lld %d", &capacity, &n);

    Item *items = (Item *)malloc(n * sizeof(Item));

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &items[i].weight, &items[i].value);
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    ll max_value = greedy_knapsack(items, n, capacity);
    printf("%lld\n", max_value);

    free(items);

    return 0;
}
