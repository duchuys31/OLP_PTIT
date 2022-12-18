
/* Created by Tran Duc Huy */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#pragma GCC optimize("O3")
#pragma GCC target("sse4")

using namespace std;
using namespace __gnu_pbds;

#define int long long
#define ll long long
#define ull unsigned long long
#define db double
#define fi first
#define se second
#define in binary_search
#define pb push_back
#define rev greater
#define umap unordered_map
#define all(a) a.begin(), a.end()
#define reset(a, val) memset(a, val, sizeof(a));
#define For(i, a, b) for (int i = a; i <= b; i++)
#define Ford(i, a, b) for (int i = a; i >= b; i--)
#define lb lower_bound
#define ub upper_bound
#define uniq(a) a.resize(unique(all(a)) - a.begin())
#define FILE                          \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define FAST                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);
template <typename T>
istream &operator>>(istream &in, vector<T> &a)
{
    for (auto &x : a)
        in >> x;
    return in;
};
template <typename T>
ostream &operator<<(ostream &out, vector<T> &a)
{
    for (auto &x : a)
        out << x << ' ';
    return out;
};
template <typename T>
istream &operator>>(istream &in, deque<T> &a)
{
    a.push_back(0);
    for (auto &x : a)
        in >> x;
    return in;
};
template <typename T>
ostream &operator<<(ostream &out, deque<T> &a)
{
    for (auto &x : a)
        out << x << ' ';
    return out;
};
template <typename T>
umap<T, int> compress(const vector<T> &vec)
{
    vector<T> sorted = vec;
    sort(all(sorted));
    int l = sorted.size();
    umap<T, int> m;
    for (int i = 0; i < l; i++)
        m[sorted[i]] = i;
    return m;
}
template <typename T>
T power(T a, int b)
{
    assert(b >= 0);
    T r = 1;
    while (b)
    {
        if (b & 1)
            r *= a;
        b >>= 1;
        a *= a;
    }
    return r;
}
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using maxpq = priority_queue<T, vector<T>>;
template <class A, class B>
using pq = priority_queue<A, vector<A>, B>;

typedef pair<int, int> ii;
typedef pair<db, db> dd;
typedef vector<ii> vii;
typedef vector<int> v;
typedef vector<string> vs;
typedef vector<char> vc;
typedef vector<v> vv;

int __lcm(int a, int b) { return a / __gcd(a, b) * b; }
int _max(int a, int b, int c) { return max(a, max(b, c)); }
int _min(int a, int b, int c) { return min(a, min(b, c)); }

template <typename T>
T random(const T &a, const T &b)
{
    T m = b - a + 1;
    return a + rand() % m;
}
string join(const vector<string> &vec, const string &t)
{
    int l = vec.size();
    string s;
    for (int i = 0; i < l; i++)
    {
        s += vec[i];
        if (i != l - 1)
            s += t;
    }
    return s;
}
void read(int a[], int n)
{
    For(i, 1, n) cin >> a[i];
}
void print(int a[], int n)
{
    For(i, 1, n) cout << a[i] << " ";
}
const ll oo = 999999999999999999;
const db PI = 3.14159265358979323846;
const int mod = 1e9 + 7;
const int N = 1e5 + 5;

int di[] = {-1, 0, 0, 1, -1, -1, 1, 1};
int dj[] = {0, -1, 1, 0, -1, 1, -1, 1};
/**/
int n, m;
v g[N];
int deep[N];
int dad[N][20];
/*Main*/
void dfs(int pre, int u)
{
    deep[u] = deep[pre] + 1;
    dad[u][0] = pre;
    for (auto x : g[u])
    {
        if (x != pre)
        {
            dfs(u, x);
        }
    }
}
int lca(int x, int y)
{
    if (deep[x] > deep[y])
        swap(x, y);
    Ford(i, 18, 0)
    {
        if (deep[y] - deep[x] >= (1 << i))
        {
            y = dad[y][i];
        }
    }
    Ford(i, 18, 0)
    {
        if (dad[x][i] != dad[y][i])
        {
            x = dad[x][i];
            y = dad[y][i];
        }
    }
    if (x != y)
        x = dad[x][0];
    return x;
}
void setup()
{
    dfs(0, 1);
    For(t, 1, 18)
    {
        For(i, 1, n)
        {
            int pre = dad[i][t - 1];
            dad[i][t] = dad[pre][t - 1];
        }
    }
}
int LCA(int x, int y, int root)
{
    int ans;
    int tu = lca(root, x);
    int tv = lca(root, y);
    if (deep[tu] >= deep[tv])
        ans = tu;
    else
        ans = tv;
    int tuv = lca(x, y);
    if (deep[ans] < deep[tuv])
        ans = tuv;
    return ans;
}
void init()
{
}
void solution()
{
    cin >> n;
    For(i, 1, n) g[i].clear();
    For(i, 1, n - 1)
    {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    setup();
    cin >> m;
    int root = 1;
    For(q, 1, m)
    {
        char type;
        cin >> type;
        if(type == '!'){
            int x;
            cin >> x;
            root = x;
        }
        else{
            int x, y;
            cin >> x >> y;
            cout << LCA(x, y, root) << endl;
        }
    }
}
/**/
main()
{
    FAST;
    int t = 1;
    // cin >> t;
    For(i, 1, t)
    {
        // cout<<"#Case "<<i<<" :\n";
        db start = (db)(clock());
        init();
        solution();
        db end = (db)(clock());
        // cout << "Time : " << (end - start) / CLOCKS_PER_SEC << "s" << endl;
    }
    return 0;
}
