/*
============================================================
TEMPLATE Day 120 — DP pada DAG
============================================================
Semua versi 1-INDEXED, gaya PUSH (forward), memakai urutan topologis Kahn.
Ganti init + gabung + f untuk berpindah antar pertanyaan.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;
const ll NEG = LLONG_MIN / 4;      // sentinel untuk max
const ll POS = LLONG_MAX / 4;      // sentinel untuk min

// ------------------------------------------------------------------
// 0. URUTAN TOPOLOGIS (Kahn). Kosong -> graf punya siklus.
// ------------------------------------------------------------------
vector<int> topoOrder(int n, const vector<vector<pair<int,ll>>>& g) {
    vector<int> indeg(n + 1, 0), ord;
    for (int u = 1; u <= n; u++)
        for (auto& e : g[u]) indeg[e.first]++;
    queue<int> q;
    for (int u = 1; u <= n; u++) if (!indeg[u]) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ord.push_back(u);
        for (auto& e : g[u]) if (--indeg[e.first] == 0) q.push(e.first);
    }
    if ((int)ord.size() != n) return {};      // ADA SIKLUS
    return ord;
}

// ------------------------------------------------------------------
// 1. BANYAK JALUR dari s ke semua simpul (modulo)
// ------------------------------------------------------------------
vector<ll> countPaths(int n, const vector<vector<pair<int,ll>>>& g,
                      const vector<int>& ord, int s) {
    vector<ll> dp(n + 1, 0);
    dp[s] = 1;
    for (int u : ord) {
        if (!dp[u]) continue;                       // hemat, aman
        for (auto& e : g[u])
            dp[e.first] = (dp[e.first] + dp[u]) % MOD;
    }
    return dp;
}

// ------------------------------------------------------------------
// 2. JALUR TERPANJANG dari s. dp[v] == NEG artinya tak terjangkau.
//    par[] terisi untuk rekonstruksi.
// ------------------------------------------------------------------
vector<ll> longestPath(int n, const vector<vector<pair<int,ll>>>& g,
                       const vector<int>& ord, int s, vector<int>& par) {
    vector<ll> dp(n + 1, NEG);
    par.assign(n + 1, 0);
    dp[s] = 0;
    for (int u : ord) {
        if (dp[u] == NEG) continue;                 // WAJIB
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (dp[u] + w > dp[v]) {                // ">" bukan ">="
                dp[v] = dp[u] + w;
                par[v] = u;
            }
        }
    }
    return dp;
}

// ------------------------------------------------------------------
// 3. JALUR TERMURAH dari s. BOLEH bobot negatif (Dijkstra tidak boleh).
// ------------------------------------------------------------------
vector<ll> cheapestPath(int n, const vector<vector<pair<int,ll>>>& g,
                        const vector<int>& ord, int s, vector<int>& par) {
    vector<ll> dp(n + 1, POS);
    par.assign(n + 1, 0);
    dp[s] = 0;
    for (int u : ord) {
        if (dp[u] == POS) continue;                 // WAJIB
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (dp[u] + w < dp[v]) {
                dp[v] = dp[u] + w;
                par[v] = u;
            }
        }
    }
    return dp;
}

// ------------------------------------------------------------------
// 4. REKONSTRUKSI JALUR dari par[]. Kosong -> tak terjangkau.
// ------------------------------------------------------------------
vector<int> buildPath(int s, int t, const vector<int>& par, bool reachable) {
    if (!reachable) return {};
    vector<int> path;
    for (int v = t; v != 0; v = par[v]) {
        path.push_back(v);
        if (v == s) break;
    }
    if (path.empty() || path.back() != s) return {};
    reverse(path.begin(), path.end());
    return path;
}

// ------------------------------------------------------------------
// 5. TERMURAH + MENGHITUNG BERAPA BANYAK YANG TERMURAH
// ------------------------------------------------------------------
void cheapestAndCount(int n, const vector<vector<pair<int,ll>>>& g,
                      const vector<int>& ord, int s,
                      vector<ll>& dp, vector<ll>& cnt) {
    dp.assign(n + 1, POS);
    cnt.assign(n + 1, 0);
    dp[s] = 0; cnt[s] = 1;
    for (int u : ord) {
        if (dp[u] == POS) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (dp[u] + w < dp[v]) { dp[v] = dp[u] + w; cnt[v] = cnt[u]; }
            else if (dp[u] + w == dp[v]) cnt[v] = (cnt[v] + cnt[u]) % MOD;
        }
    }
}

// ------------------------------------------------------------------
// 6. KERANGKA MAIN
//    n m, lalu m baris "u v w"
// ------------------------------------------------------------------
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<pair<int,ll>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w = 1;
        cin >> u >> v;                  // >> w; kalau berbobot
        g[u].push_back({v, w});
    }

    vector<int> ord = topoOrder(n, g);
    if (ord.empty()) { cout << "SIKLUS\n"; return 0; }

    vector<int> par;
    vector<ll> dp = longestPath(n, g, ord, 1, par);
    cout << (dp[n] == NEG ? -1 : dp[n]) << '\n';
    return 0;
}
