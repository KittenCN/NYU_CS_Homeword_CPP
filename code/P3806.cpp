#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
#include<string>
#include<cstring>
using namespace std;
#define ffor(i,d,u) for(int i=(d);i<=(u);++i)
#define _ffor(i,u,d) for(int i=(u);i>=(d);--i)
#define NUM 10005
#define MAXN 10000005
int n, m;
int head[NUM] = {}, edge_num = 0;
struct edge
{
    int to, next, l;
} e[NUM << 1];
bool judge[MAXN] = {}, vis[NUM] = {}, test[105] = {};
int save[NUM], leng[NUM], query[105], root;
int tot, num[NUM], ss[NUM], min_max_len;
template <typename T>
void read(T& x)
{
    x=0;
    char c;T t=1;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c=='-'){t=-1;c=getchar();}
    do(x*=10)+=(c-'0');while((c=getchar())>='0'&&c<='9');
    x*=t;
}
template <typename T>
void write(T x)
{
    int len=0;char c[21];
    if(x<0)putchar('-'),x*=(-1);
    do{++len;c[len]=(x%10)+'0';}while(x/=10);
    _ffor(i, len, 1) putchar(c[i]);
}
void get_root(const int &vertex, const int &pre)
{
    int x, max_len = 0;
    num[vertex] = 1;
    for (int i = head[vertex]; i; i = e[i].next)
    {
        x = e[i].to;
        if (x == pre || vis[x])
            continue;
        get_root(x, vertex);
        num[vertex] += num[x];
        max_len = max(max_len, num[x]);
    }
    max_len = max(max_len, tot - num[vertex]);
    if (max_len < min_max_len)
        root = vertex, min_max_len = max_len;
}
void get_length(const int &vertex, const int &pre)
{
    int x;
    save[++save[0]] = leng[vertex], num[vertex] = 1;
    for (int i = head[vertex]; i; i = e[i].next)
    {
        x = e[i].to;
        if (x == pre || vis[x])
            continue;
        leng[x] = leng[vertex] + e[i].l;
        get_length(x, vertex);
        num[vertex] += num[x];
    }
}
inline void calc(const int &vertex)
{
    int x, sum = 0;
    num[vertex] = 0;
    for (int i = head[vertex]; i; i = e[i].next)
    {
        x = e[i].to;
        if (vis[x])
            continue;
        leng[x] = e[i].l;
        get_length(x, vertex);
        num[vertex] += num[x];
        ffor(j, 1, save[0]) ffor(k, 1, m) if (query[k] >= save[j]) test[k] |= judge[query[k] - save[j]];
        do
            ss[++sum] = save[save[0]], judge[save[save[0]]] = true;
        while (--save[0]);
    }
    ffor(i, 1, sum) judge[ss[i]] = false;
}
void solve(const int &vertex)
{
    int x;
    judge[0] = vis[vertex] = true, calc(vertex);
    for (int i = head[vertex]; i; i = e[i].next)
    {
        x = e[i].to;
        if (vis[x])
            continue;
        tot = num[x], root = 0, min_max_len = n;
        get_root(x, 0), solve(root);
    }
}
inline void add(const int &x, const int &y, const int &length)
{
    e[++edge_num] = edge{y, head[x], length}, head[x] = edge_num;
}
inline void AC()
{
    int x, y, l;
    read(n), read(m);
    ffor(i, 2, n)
    {
        read(x), read(y), read(l);
        add(x, y, l), add(y, x, l);
    }
    ffor(i, 1, m)read(query[i]);
    tot = n, save[0] = 0, min_max_len = n;
    get_root(1, 0);
    solve(root);
    ffor(i, 1, m) puts(test[i] ? "AYE" : "NAY");
}
int main()
{
    AC();
    // system("pause");
    return 0;
}