#include <stdio.h>

#define MOD 1000000007
#define MAX_N 1000006
long long _arr[MAX_N][3];

int main() {
    _arr[1][1] = _arr[1][2] = 1;
    for (int i = 2; i < MAX_N; i++) {
        _arr[i][1] = (_arr[i-1][1] * 4 % MOD + _arr[i-1][2]) % MOD;
        _arr[i][2] = (_arr[i-1][1] + _arr[i-1][2] * 2 % MOD) % MOD;
    }
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", (_arr[n][1] + _arr[n][2]) % MOD);
    }
    return 0;
}
