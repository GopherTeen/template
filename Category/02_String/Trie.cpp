// 字典树（前缀树、单词查找树）

// Trie 是一棵 “非典型” 的多叉树模型
// TrieNode 中并没有直接保存字符值的数据成员，而是通过字母映射表 next 和一个父节点预知所有子节点

// 字典树应用：
//   · 检索字符串
//   · AC自动机（trie 是AC自动机的一部分）
//   · 维护异或极值 ———— 将数的二进制看作一个字符串，建构 01-trie
//   · 维护异或和

// 练习题目：
// https://atcoder.jp/contests/abc377/tasks/abc377_g

class Trie {
private:
    Trie* children[70] {}; // todo 根据 |Σ| 调整
    bool isEnd = false;
    int cnt = 0;

    int get(char x) {
        if (x >= 'A' && x <= 'Z') {
            return x - 'A';
        } else if (x >= 'a' && x <= 'z') {
            return x - 'a' + 26;
        }
        return x - '0' + 52;
    }

public:
    Trie() = default;

    void insert(const string& s) {
        Trie* node = this;
        for (char ch : s) {
            if (node->children[get(ch)] == nullptr) {
                node->children[get(ch)] = new Trie();
            }
            node = node->children[get(ch)];
            node->cnt++;
        }
        node->isEnd = true;
    }

    // 查询 s 是否在模式串中出现
    bool find(const string& s) {
        Trie* node = this;
        for (char ch : s) {
            if (node->children[get(ch)] == nullptr) {
                return false;
            }
            node = node->children[get(ch)];
        }
        return node->isEnd;
    }

    // 查询 s 是否是某个模式串的前缀
    bool startsWith(const string& s) {
        Trie* node = this;
        for (char ch : s) {
            if (node->children[get(ch)] == nullptr) {
                return false;
            }
            node = node->children[get(ch)];
        }
        return true;
    }

    // 以 s 为前缀的模式串的个数
    int getCnt(const string& s) {
        Trie* node = this;
        for (char ch : s) {
            if (node->children[get(ch)] == nullptr) {
                return 0;
            }
            node = node->children[get(ch)];
        }
        return node->cnt;
    }
};


// 01-Trie
struct TrieNode {
    TrieNode* son[2] {};
    int cnt = 0;
    int mn = numeric_limits<int>::max(); // 子树最小值
};
template <integral T>
class Trie {
    const int N = 31; // 30 for 1e9, 63 for i64
    TrieNode* root = new TrieNode();

public:
    auto bin(T v) {
        string s(N, ' ');
        for (int i = 0; i < s.size(); ++i) {
            s[i] = (v >> (N - 1 - i) & 1) + '0';
        }
        return s;
    }

    auto insert(T v) {
        auto o = this->root;
        if (v < o->mn) {
            o->mn = v;
        }
        for (int i = N - 1; i >= 0; --i) {
            int b = v >> i & 1;
            if (o->son[b] == nullptr) {
                o->son[b] = new TrieNode();
            }
            o = o->son[b];
            o->cnt++;
            if (v < o->mn) {
                o->mn = v;
            }
        }
        return o;
    }

    auto remove(T v) {
        auto o = this->root;
        for (int i = N - 1; i >= 0; --i) {
            o = o->son[v >> i & 1];
            o->cnt--;
        }
        return o;
    }

    //// 采用上面的 remove 时，注意判断条件的修改，如：o->son[b] == nullptr || o->son[b]->cnt == 0
    // void remove(T v) {
    //     vector<pair<TrieNode*, int>> path;
    //     TrieNode* o = root;
    //     for (int i = N - 1; i >= 0; --i) {
    //         int b = (v >> i) & 1;
    //         path.emplace_back(o, b);
    //         if (o->son[b] == nullptr) {
    //             return;
    //         }
    //         o = o->son[b];
    //         o->cnt--;
    //     }
    //     for (int i = path.size() - 1; i >= 0; --i) {
    //         auto [pa, b] = path[i];
    //         TrieNode* child = pa->son[b];
    //         if (child->cnt == 0) {
    //             delete child;
    //             pa->son[b] = nullptr;
    //             pa->mn = numeric_limits<int>::max();
    //             for (int j : {0, 1}) {
    //                 if (pa->son[j] != nullptr) {
    //                     if (pa->son[j]->mn < pa->mn) {
    //                         pa->mn = pa->son[j]->mn;
    //                     }
    //                 }
    //             }
    //         } else {
    //             // If child still exists, check if its mn needs update
    //             if (child->mn == v) {
    //                 // Recompute mn for the child if necessary
    //                 // This part might need a more sophisticated approach
    //                 // For simplicity, we assume mn is correctly maintained during insert/delete
    //             }
    //         }
    //     }
    //
    //     // Update root's mn in case all children were deleted
    //     root->mn = numeric_limits<int>::max();
    //     for (int j = 0; j < 2; ++j) {
    //         if (root->son[j]) {
    //             if (root->son[j]->mn < root->mn) {
    //                 root->mn = root->son[j]->mn;
    //             }
    //         }
    //     }
    // }

    // 要求 trie 树非空
    auto minXor(T v) {
        auto o = this->root;
        T ans {};
        for (int i = N - 1; i >= 0; --i) {
            int b = v >> i & 1;
            if (o->son[b] == nullptr) {
                ans |= 1 << i;
                b ^= 1;
            }
            o = o->son[b];
        }
        return ans;
    }

    // 要求 trie 树非空
    auto maxXor(T v) {
        auto o = this->root;
        T ans {};
        for (int i = N - 1; i >= 0; --i) {
            int b = v >> i & 1;
            if (o->son[b ^ 1] != nullptr) {
                ans |= 1 << i;
                b ^= 1;
            }
            o = o->son[b];
        }
        return ans;
    }

    // 返回 v 与 trie 上所有数的第 k 大异或值
    // k 从 1 开始
    // 如果 k 超过 trie 中元素个数，返回 0
    auto kth_maxXor(int v, int k) {
        auto o = this->root;
        T ans {};
        for (int i = N - 1; i >= 0; --i) {
            int b = v >> i & 1;
            if (o->son[b ^ 1] != nullptr) {
                if (k <= o->son[b ^ 1]->cnt) {
                    ans |= 1 << i;
                    b ^= 1;
                } else {
                    k -= o->son[b ^ 1]->cnt;
                }
            }
            o = o->son[b];
        }
        return ans;
    }

    // v 与 trie 上所有不超过 limit 的数的最大异或值
    // 不存在时返回 -1
    auto maxXorWithLimit(int v, int limit) {
        auto o = this->root;
        if (o->mn > limit) {
            return -1;
        }
        T ans {};
        for (int i = N - 1; i >= 0; --i) {
            int b = v >> i & 1;
            if (o->son[b ^ 1] != nullptr && o->son[b ^ 1]->mn <= limit) {
                ans |= 1 << i;
                b ^= 1;
            }
            o = o->son[b];
        }
        return ans;
    }

    // 求与 v 异或值不超过 limit 的元素个数
    // 核心原理是，当 limit+1 的某一位是 1 的时候，若该位异或值取 0，则后面的位是可以取任意数字的
    // 如果在 limit 上而不是 limit+1 上讨论，就要单独处理走到叶子的情况了（恰好等于 limit）
    auto cntXorWithLimit(int v, int limit) {
        limit++;
        auto o = this->root;
        T cnt {};
        for (int i = N - 1; i >= 0; --i) {
            int b = v >> i & 1;
            if (limit >> i & 1) {
                if (o->son[b] != nullptr) {
                    cnt += o->son[b]->cnt;
                }
                b ^= 1;
            }
            if (o->son[b] == nullptr) {
                return;
            }
            o = o->son[b];
        }
        return cnt;
    }

    // v 与 trie 上所有数异或不超过 limit 的最大异或值
    // 不存在时返回 -1
    // 原理同 cntXorWithLimit
    auto maxXorWithLimitXor(int v, int limit) {
        limit++;
        auto o = this->root;
        auto lastO = new Trie(), lastI = -2, lastAns = 0;
        T ans {};
        for (int i = N - 1; i >= 0; --i) {
            int b = v >> i & 1;
            if (limit >> i & 1) {
                if (o->son[b] != nullptr) {
                    lastO = o->son[b];
                    lastI = i - 1;
                    lastAns = ans;
                }
                if (o->son[b ^ 1] != nullptr) {
                    ans |= 1 << i;
                }
                b ^= 1;
            }
            if (o->son[b] == nullptr) {
                break;
            }
            o = o->son[b];
        }
        if (lastI < -1) {
            return -1;
        }

        ans = lastAns;
        o = lastO;
        for (int i = lastI; i >= 0; --i) {
            int b = v >> i & 1;
            if (o->son[b ^ 1] != nullptr) {
                ans |= 1 << i;
                b ^= 1;
            }
            o = o->son[b];
        }
        return ans;
    }

    // 完全图，边权为 a[u]^a[v]，求 MST
    // Boruvka 算法，分治连边
    auto xorMST(const vector<T>& a) {
        T ans {};
        auto f = [&](auto&& f, int p) -> void {
            if (a.empty() || p < 0) {
                return;
            }
            vector<T> b[2];
            for (auto& v : a) {
                b[v >> p & 1].push_back(v);
            }
            if (b[0].empty() && b[1].empty()) {
                auto t = new Trie();
                for (auto& v : b[0]) {
                    t->insert(v);
                }
                T minXor = numeric_limits<int>::max();
                for (auto& v : b[1]) {
                    minXor = min(minXor, t->minXor(v));
                }
                ans += minXor;
            }
            f(f, b[0], p - 1);
            f(f, b[1], p - 1);
        };
        f(f, N - 1);
        return ans;
    }
};
