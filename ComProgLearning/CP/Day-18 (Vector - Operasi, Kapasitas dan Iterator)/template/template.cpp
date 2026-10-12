// ============================================================
// 📦 TEMPLATE — Day 3: STL Containers 1 (Vector, String, Pair, Tuple)
// ============================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define vs vector<string>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vpii vector<pii>
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define F first
#define S second

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const int MAXN = 2e5 + 5;

void solve() {
    // === VECTOR SNIPPETS ===
    // vi v(n);            // vector ukuran n
    // vi v(n, 0);         // vector ukuran n, isi 0
    // v.pb(x);            // push_back
    // sort(all(v));       // sort ascending
    // v.erase(unique(all(v)), v.end()); // remove duplicates

    // === STRING SNIPPETS ===
    // string s; cin >> s;
    // reverse(all(s));
    // s.substr(pos, len);
    // s.find("pattern");  // npos jika tidak ada
    // to_string(123);     // int -> string
    // stoi("123");        // string -> int

    // === PAIR SNIPPETS ===
    // pii p = {a, b};
    // auto [x, y] = p;   // structured binding C++17

    // === TUPLE SNIPPETS ===
    // tuple<int,int,int> t = {a, b, c};
    // auto [x, y, z] = t; // structured binding C++17
    // get<0>(t);          // akses elemen
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;  // Uncomment jika multi test case
    while (t--) {
        solve();
    }

    return 0;
}
