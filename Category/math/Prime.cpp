// 暴力
bool is_prime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return n >= 2;
}

// 埃氏筛 ErlichScreen
#define N 100'000
vector<int> isPrime(N + 1, 1);
auto init = []() {
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i <= N; ++i) {
        if (!isPrime[i]) {
            continue;
        }
        for (long long j = i * 1ll * i; j <= N; j += i) {
            isPrime[j] = 0;
        }
    }
    return 0;
}();
