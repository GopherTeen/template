struct Combinatorics {
    int n;
    std::vector<MI> _fac, _invfac, _inv;

    Combinatorics() : n {0}, _fac {1}, _invfac {1}, _inv {0} {}
    Combinatorics(int n) : Combinatorics() { init(n); }

    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    MI fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    MI invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    MI inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    MI comb(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
    MI perm(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(n - m);
    }
} C;


// 预处理
namespace Comb {
    const int MX = 2e5 + 1;

    ll F[MX]; // F[i] = i!
    ll INV_F[MX]; // INV_F[i] = i!^-1

    ll qpow(ll a, ll b, int p) {
        ll res = 1;
        a = (a % p + p) % p;
        for (; b; b >>= 1, a = a * a % p) {
            if (b & 1) {
                res = a * res % p;
            }
        }
        return res;
    }

    auto init = [] {
        F[0] = 1;
        for (int i = 1; i < MX; i++) {
            F[i] = F[i - 1] * i % MOD;
        }

        // 连续阶乘的逆元 从右往左 线性递推
        INV_F[MX - 1] = qpow(F[MX - 1], MOD - 2, MOD);
        for (int i = MX - 1; i; i--) {
            INV_F[i - 1] = INV_F[i] * i % MOD;
        }
        return 0;
    }();

    ll comb(int n, int m) {
        return n < m ? 0 : F[n] * INV_F[m] % MOD * INV_F[n - m] % MOD;
    }
};

// 直接实现
ll comb(int x, int y) {
    if (y > x) {
        return 0;
    }
    ll res = 1;
    for (int i = 0; i < y; i++) {
        res = res * (x - i) / (i + 1);
    }
    return res;
}
