// ============================================================
// 📦 TEMPLATE — Day 4: STL Containers 2 (Set, Map, Multiset)
// ============================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define F first
#define S second

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const int MAXN = 2e5 + 5;

void solve() {
    // === SET SNIPPETS ===
    // set<int> s;
    // s.insert(x); s.erase(x); s.count(x);
    // auto it = s.lower_bound(x);  // >= x
    // auto it = s.upper_bound(x);  // > x
    // *s.begin() = min, *s.rbegin() = max

    // === MULTISET SNIPPETS ===
    // multiset<int> ms;
    // ms.insert(x);
    // ms.erase(ms.find(x));  // hapus SATU
    // ms.erase(x);           // hapus SEMUA (hati-hati!)

    // === MAP SNIPPETS ===
    // map<int,int> m;
    // m[key] = val; m.count(key); m.erase(key);
    // for (auto& [k,v] : m) { ... }

    // === UNORDERED_MAP SNIPPETS ===
    // unordered_map<int,int> um;
    // um[key]++; // frequency count
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
