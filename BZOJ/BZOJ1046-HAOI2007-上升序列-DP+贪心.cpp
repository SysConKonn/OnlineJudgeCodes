/**
 * Copyright (c) 2017, xehoth
 * All rights reserved.
 * 「BZOJ 1046」上升序列 10-10-2017
 * DP+贪心
 * @author xehoth
 */
#include <bits/stdc++.h>

namespace IO {

inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}

template <typename T>
inline bool read(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == -1) return false;
        c == '-' ? iosig = true : 0;
    }
    for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
    iosig ? x = -x : 0;
    return true;
}

inline void read(char &c) {
    while (c = read(), isspace(c) && c != -1)
        ;
}

inline int read(char *buf) {
    register int s = 0;
    register char c;
    while (c = read(), isspace(c) && c != -1)
        ;
    if (c == -1) {
        *buf = 0;
        return -1;
    }
    do
        buf[s++] = c;
    while (c = read(), !isspace(c) && c != -1);
    buf[s] = 0;
    return s;
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

struct InputOutputStream {
    template <typename T>
    inline InputOutputStream &operator>>(T &x) {
        read(x);
        return *this;
    }

    template <typename T>
    inline InputOutputStream &operator<<(const T &x) {
        print(x);
        return *this;
    }

    ~InputOutputStream() { flush(); }
} io;
}

namespace {

using IO::io;

const int MAXN = 10000;

const int INF = 0x3f3f3f3f;

int a[MAXN + 1], f[MAXN + 1], g[MAXN + 1], n;

inline void solve(int x) {
    register int last = INT_MIN;
    for (register int i = 1; i <= n && x; i++) {
        if (f[i] >= x && a[i] > last) {
            x--;
            io << a[i];
            if (x) io << ' ';
            last = a[i];
        }
    }
    io << '\n';
}

inline void solve() {
    io >> n;
    memset(g, 0x3f, sizeof(int) * (n + 1));
    for (register int i = 1; i <= n; i++) io >> a[i];
    for (register int i = n, pos; i; i--) {
        f[i] = (pos = std::lower_bound(g + 1, g + n + 1, -a[i]) - g);
        g[pos] = -a[i];
    }
    register int max = std::lower_bound(g + 1, g + n + 1, INF) - g - 1;
    register int m, x;
    io >> m;
    while (m--) {
        io >> x;
        if (x > max)
            io << "Impossible\n";
        else
            solve(x);
    }
}
}

int main() {
    solve();
    return 0;
}