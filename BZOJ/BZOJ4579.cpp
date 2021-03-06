/*******************************************************************************
 * Copyright (c) 2016-2017, xehoth
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name xehoth, nor the names of its contributors may be used
 *       to endorse or promote products derived from this software without
 *       specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY XEHOTH AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEHOTH AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/
#include <bits/stdc++.h>

namespace IO {

inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}

template <typename T>
inline void read(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == -1) return;
        c == '-' ? iosig = true : 0;
    }
    for (x = 0; isdigit(c); c = read()) x = (x + (x << 2) << 1) + (c ^ '0');
    iosig ? x = -x : 0;
}

const int OUT_LEN = 1000000;

char obuf[OUT_LEN], *oh = obuf;

inline void print(char c) {
    oh == obuf + OUT_LEN ? (fwrite(obuf, 1, OUT_LEN, stdout), oh = obuf) : 0;
    *oh++ = c;
}

template <typename T>
inline void print(T x) {
    static int buf[30], cnt;
    if (x == 0) {
        print('0');
    } else {
        x < 0 ? (print('-'), x = -x) : 0;
        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
        while (cnt) print((char)buf[cnt--]);
    }
}

inline void print(const char *s) {
    for (; *s; s++) print(*s);
}

inline void flush() { fwrite(obuf, 1, oh - obuf, stdout); }
}  // namespace IO

namespace UnionFindSet {

const int MAXN = 200005;

int fa[MAXN];

inline int get(int x) {
    while (x != fa[x]) x = fa[x] = fa[fa[x]];
    return x;
}

int cnt;

inline void put(int x, int y) {
    (x = get(x)) != (y = get(y)) ? (fa[x] = y, cnt--) : 0;
}

std::vector<int> edge[MAXN];

inline void addEdge(const int u, const int v) {
    edge[u].push_back(v);
    edge[v].push_back(u);
}

inline void solve() {
    using namespace IO;
    register int n, m;
    read(n), read(m);
    for (register int i = 0, u, v; i < m; i++) read(u), read(v), addEdge(u, v);
    static int q[MAXN], ans[MAXN];
    static bool vis[MAXN];
    for (register int i = 1; i <= n; i++) read(q[i]), fa[i] = i;
    for (register int i = n, v; i; i--) {
        cnt++;
        for (std::vector<int>::iterator it = edge[q[i]].begin(),
                                        end = edge[q[i]].end();
             it != end; it++)
            if (vis[v = *it]) put(q[i], v);
        vis[q[i]] = true;
        if (cnt == 1) ans[i] = 1;
    }
    for (register int i = 1; i <= n; i++)
        ans[i] ? print("YES\n") : print("NO\n");
}
}  // namespace UnionFindSet

int main() {
#ifdef DBG
    freopen("in.in", "r", stdin);
#else
// freopen("closing.in", "r", stdin);
// freopen("closing.out", "w", stdout);
#endif
    UnionFindSet::solve();
    IO::flush();
    return 0;
}
