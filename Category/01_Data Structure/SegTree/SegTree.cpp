static constexpr ll inf = 9e18;

template <class Info, class Tag>
class SegTree {
private:
    int n;
    vector<Info> info;
    vector<Tag> tag;

    void apply(int o, const Tag& t) { tag[o].apply(t), info[o].apply(t); }
    void push(int o) { apply(o << 1, tag[o]), apply(o << 1 | 1, tag[o]), tag[o] = Tag(); }
    void pull(int o) { info[o] = info[o << 1] + info[o << 1 | 1]; }

public:
    SegTree() : n(0) {}
    SegTree(int n, Info v = Info{}) { init(vector(n, v)); }
    template <class T>
    SegTree(vector<T>& _init) {
        init(_init);
    }

    template <class T>
    void init(const vector<T>& _init) {
        n = _init.size();
        info.assign(4 << __lg(n), Info{});
        tag.assign(4 << __lg(n), Tag());

        auto build = [&](auto&& self, int o, int l, int r) -> void {
            if (l == r) {
                info[o] = _init[l];
                return;
            }
            int m = l + (r - l) / 2;
            self(self, o << 1, l, m);
            self(self, o << 1 | 1, m + 1, r);
            pull(o);
        };
        build(build, 1, 0, n - 1);
    }

public:
    void modify(int id, const Info& info, int o, int l, int r) {
        if (l == r) {
            info[o] = info;
            return;
        }
        push(o);
        int m = l + (r - l) / 2;
        if (id <= m) {
            modify(id, info, o << 1, l, m);
        } else {
            modify(id, info, o << 1 | 1, m + 1, r);
        }
        pull(o);
    }
    void modify(int id, const Info& info) { modify(id, info, 1, 0, n - 1); }

    void modify(int L, int R, const Tag& tag, int o, int l, int r) {
        if (L <= l && r <= R) {
            apply(o, tag);
            return;
        }
        push(o);
        int m = l + (r - l) / 2;
        if (L <= m) {
            modify(L, R, tag, o << 1, l, m);
        }
        if (m < R) {
            modify(L, R, tag, o << 1 | 1, m + 1, r);
        }
        pull(o);
    }
    void modify(int L, int R, const Tag& tag) { modify(L, R, tag, 1, 0, n - 1); }

    Info query(int id, int o, int l, int r) {
        if (l == r) {
            return info[o];
        }
        push(o);
        int m = l + (r - l) / 2;
        if (id <= m) {
            return query(id, o << 1, l, m);
        }
        return query(id, o << 1 | 1, m + 1, r);
    }
    Info query(int id) { return query(id, 1, 0, n - 1); }

    Info query(int L, int R, int o, int l, int r) {
        if (L <= l && r <= R) {
            return info[o];
        }
        push(o);
        int m = l + (r - l) / 2;
        if (R <= m) {
            return query(L, R, o << 1, l, m);
        }
        if (m < L) {
            return query(L, R, o << 1 | 1, m + 1, r);
        }
        return query(L, R, o << 1, l, m) + query(L, R, o << 1 | 1, m + 1, r);
    }
    Info query(int L, int R) { return query(L, R, 1, 0, n - 1); }

    Info queryAll() { return info[1]; }

    int findFirst(int L, int R, auto&& pred, int o, int l, int r) {
        if (l > R || r < L || !pred(info[o])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = l + (r - l) / 2;
        push(o);
        int idx = findFirst(L, R, pred, o << 1, l, m);
        if (idx == -1) {
            idx = findFirst(L, R, pred, o << 1 | 1, m + 1, r);
        }
        return idx;
    }
    int findFirst(int l, int r, auto&& pred) { return findFirst(l, r, pred, 1, 0, n - 1); }

    int findLast(int L, int R, auto&& pred, int o, int l, int r) {
        if (l > R || r < L || !pred(info[o])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = l + (r - l) / 2;
        push(o);
        int idx = findLast(L, R, pred, o << 1 | 1, m + 1, r);
        if (idx == -1) {
            idx = findLast(L, R, pred, o << 1, l, m);
        }
        return idx;
    }
    int findLast(int l, int r, auto&& pred) { return findLast(l, r, pred, 1, 0, n - 1); }
};

struct Tag {
    ll add = 0;
    Tag() {}
    Tag(ll v) : add(v) {}
    void apply(const Tag& t) {
        if (t.add) {
            add += t.add;
        }
    }
};
struct Info {
    ll sum = 0, len = 0;
    void apply(const Tag& t) {
        if (t.add) {
            sum += len * t.add;
        }
    }
};
Info operator+(const Info& a, const Info& b) {
    Info info;
    info.sum = a.sum + b.sum;
    info.len = a.len + b.len;
    return info;
}
