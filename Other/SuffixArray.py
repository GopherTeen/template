def sa_naive(s):
    n = len(s)
    sa = list(range(n))
    sa.sort(key=lambda x: s[x:])
    return sa


def sa_doubling(s):
    n = len(s)
    sa = list(range(n))
    rnk = s
    tmp = [0] * n
    k = 1
    while k < n:
        sa.sort(key=lambda x: (rnk[x], rnk[x + k]) if x + k < n else (rnk[x], -1))
        tmp[sa[0]] = 0
        for i in range(1, n):
            tmp[sa[i]] = tmp[sa[i - 1]]
            if sa[i - 1] + k < n:
                x = (rnk[sa[i - 1]], rnk[sa[i - 1] + k])
            else:
                x = (rnk[sa[i - 1]], -1)
            if sa[i] + k < n:
                y = (rnk[sa[i]], rnk[sa[i] + k])
            else:
                y = (rnk[sa[i]], -1)
            if x < y:
                tmp[sa[i]] += 1
        k *= 2
        tmp, rnk = rnk, tmp
    return sa


def sa_is(s, upper):
    n = len(s)
    if n == 0:
        return []
    if n == 1:
        return [0]
    if n == 2:
        if s[0] < s[1]:
            return [0, 1]
        else:
            return [1, 0]
    if n < 10:
        return sa_naive(s)
    if n < 50:
        return sa_doubling(s)
    ls = [0] * n
    for i in range(n - 2, -1, -1):
        ls[i] = ls[i + 1] if s[i] == s[i + 1] else s[i] < s[i + 1]
    sum_l = [0] * (upper + 1)
    sum_s = [0] * (upper + 1)
    for i in range(n):
        if ls[i]:
            sum_l[s[i] + 1] += 1
        else:
            sum_s[s[i]] += 1
    for i in range(upper):
        sum_s[i] += sum_l[i]
        if i < upper:
            sum_l[i + 1] += sum_s[i]
    lms_map = [-1] * (n + 1)
    m = 0
    for i in range(1, n):
        if not ls[i - 1] and ls[i]:
            lms_map[i] = m
            m += 1
    lms = []
    for i in range(1, n):
        if not ls[i - 1] and ls[i]:
            lms.append(i)
    sa = [-1] * n
    buf = sum_s.copy()
    for d in lms:
        if d == n:
            continue
        sa[buf[s[d]]] = d
        buf[s[d]] += 1
    buf = sum_l.copy()
    sa[buf[s[n - 1]]] = n - 1
    buf[s[n - 1]] += 1
    for i in range(n):
        v = sa[i]
        if v >= 1 and not ls[v - 1]:
            sa[buf[s[v - 1]]] = v - 1
            buf[s[v - 1]] += 1
    buf = sum_l.copy()
    for i in range(n - 1, -1, -1):
        v = sa[i]
        if v >= 1 and ls[v - 1]:
            buf[s[v - 1] + 1] -= 1
            sa[buf[s[v - 1] + 1]] = v - 1
    if m:
        sorted_lms = []
        for v in sa:
            if lms_map[v] != -1:
                sorted_lms.append(v)
        rec_s = [0] * m
        rec_upper = 0
        rec_s[lms_map[sorted_lms[0]]] = 0
        for i in range(1, m):
            l = sorted_lms[i - 1]
            r = sorted_lms[i]
            end_l = lms[lms_map[l] + 1] if lms_map[l] + 1 < m else n
            end_r = lms[lms_map[r] + 1] if lms_map[r] + 1 < m else n
            same = True
            if end_l - l != end_r - r:
                same = False
            else:
                while l < end_l:
                    if s[l] != s[r]:
                        break
                    l += 1
                    r += 1
                if l == n or s[l] != s[r]:
                    same = False
            if not same:
                rec_upper += 1
            rec_s[lms_map[sorted_lms[i]]] = rec_upper
        rec_sa = sa_is(rec_s, rec_upper)
        for i in range(m):
            sorted_lms[i] = lms[rec_sa[i]]
        sa = [-1] * n
        buf = sum_s.copy()
        for d in sorted_lms:
            if d == n:
                continue
            sa[buf[s[d]]] = d
            buf[s[d]] += 1
        buf = sum_l.copy()
        sa[buf[s[n - 1]]] = n - 1
        buf[s[n - 1]] += 1
        for i in range(n):
            v = sa[i]
            if v >= 1 and not ls[v - 1]:
                sa[buf[s[v - 1]]] = v - 1
                buf[s[v - 1]] += 1
        buf = sum_l.copy()
        for i in range(n - 1, -1, -1):
            v = sa[i]
            if v >= 1 and ls[v - 1]:
                buf[s[v - 1] + 1] -= 1
                sa[buf[s[v - 1] + 1]] = v - 1
    return sa


def suffix_array(s, upper=255):
    if type(s) is str:
        s = [ord(c) for c in s]
    return sa_is(s, upper)


class SuffixArray:
    def __init__(self, s):
        self.sa = suffix_array(s)
        self.rk = self._rk(self.sa)
        self.height = self._height(s)

    def _count_sort(self, ls):
        c = defaultdict(list)
        for i, v in enumerate(ls):
            c[v].append(i)
        ans = []
        for v in sorted(list(c.keys())):
            for k in c[v]:
                ans.append((k, v))
        return ans

    def _rk(self, sa):
        rk = [0 for _ in sa]
        for i in range(len(sa)):
            rk[sa[i]] = i
        return rk

    def _height(self, s):
        sa, rk = self.sa, self.rk
        ht = [0] * len(sa)
        k = 0
        for sai in range(0, len(s)):
            if k:
                k -= 1
            while True:
                ai, bi = sai + k, sa[rk[sai] - 1] + k
                if not (0 <= ai < len(s) and 0 <= bi < len(s)):
                    break
                if max(ai, bi) >= len(s):
                    break
                elif s[ai] == s[bi]:
                    k += 1
                else:
                    break
            ht[rk[sai]] = k
        return ht
