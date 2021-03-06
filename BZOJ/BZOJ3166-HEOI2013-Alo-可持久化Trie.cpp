/**
 * Copyright (c) 2017, xehoth
 * All rights reserved.
 * 「BZOJ 3166」Alo 25-11-2017
 * 可持久化 Trie
 * @author xehoth
 */
#include <bits/stdc++.h>

namespace {

inline char read() {
    static const int IN_LEN = 100000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}

struct InputStream {
    template <typename T>
    inline InputStream &operator>>(T &x) {
        static char c;
        static bool iosig;
        for (c = read(), iosig = false; !isdigit(c); c = read()) {
            if (c == -1) return *this;
            c == '-' ? iosig = true : 0;
        }
        for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
        iosig ? x = -x : 0;
        return *this;
    }
} io;

const int MAXN = 100000 + 9;
const int MAX_LOG = 31;

struct Node {
    Node *c[2];
    int size;
    inline void *operator new(size_t);

    Node();
};

const int NODE_SIZE = sizeof(Node);

char pool[MAXN * NODE_SIZE * MAX_LOG], *cur = pool;

Node *null = (Node *)pool, *root[MAXN];

Node::Node() : size(0) { c[0] = c[1] = null; }

inline void *Node::operator new(size_t) { return cur += NODE_SIZE; }

inline void insert(Node *&p, Node *pre, int v, int dep = MAX_LOG - 1) {
    p = new Node(*pre), p->size++;
    if (dep < 0) return;
    insert(p->c[v >> dep & 1], pre->c[v >> dep & 1], v, dep - 1);
}

inline int query(Node *l, Node *r, int v, int dep = MAX_LOG - 1) {
    if (dep < 0) return 0;
    register int d = v >> dep & 1;
    if (r->c[d ^ 1]->size - l->c[d ^ 1]->size)
        return (1 << dep) | query(l->c[d ^ 1], r->c[d ^ 1], v, dep - 1);
    return query(l->c[d], r->c[d], v, dep - 1);
}

struct Info {
    int v, id;

    inline bool operator<(const Info &p) const { return v > p.v; }
} a[MAXN];

const int INF = 1000000000;

std::set<int> pos;

inline void solve() {
    null->c[0] = null->c[1] = null, null->size = 0, root[0] = null;
    register int n;
    io >> n;
    for (register int i = 1; i <= n; i++)
        io >> a[i].v, a[i].id = i, root[i] = null;
    for (register int i = 1; i <= n; i++) insert(root[i], root[i - 1], a[i].v);
    std::sort(a + 1, a + n + 1);
    pos.insert(-1), pos.insert(-2), pos.insert(INF), pos.insert(INF + 1);
    pos.insert(a[1].id);
    register int ans = 0;
    register std::set<int>::iterator tmp, it, iPos;
    for (register int i = 2, l, r, x; i <= n; i++) {
        l = r = x = a[i].id;
        iPos = tmp = it = pos.lower_bound(x);
        r = std::min(*++tmp - 1, n), --it;
        l = std::max(1, *--it + 1);
        if (l != r) ans = std::max(ans, query(root[l - 1], root[r], a[i].v));
        pos.insert(iPos, x);
    }
    std::cout << ans;
}
}  // namespace

int main() {
    // freopen("sample/1.in", "r", stdin);
    solve();
    return 0;
}