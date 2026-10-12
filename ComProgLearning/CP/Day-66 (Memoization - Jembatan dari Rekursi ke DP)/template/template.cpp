/*
============================================================
📦 TEMPLATE BOILERPLATE: Pola Umum Rekursi dengan Memoisasi (Top-Down)
============================================================
Day: 066 | Topic: Memoization - Jembatan dari Rekursi ke DP
Standard: C++17 Competitive Programming Master Template

Template ini menyediakan modul-modul boilerplate untuk berbagai kebutuhan memoisasi:
1. `memo_1D_sentinel`: Cache 1D berbasis vektor dengan nilai sentinel -1.
2. `memo_1D_seen`: Cache 1D dengan array boolean `seen` (untuk fungsi yang return value sahnya bisa 0 atau negatif).
3. `memo_2D_knapsack`: Cache 2D untuk masalah dengan 2 parameter integer rapat (indeks & kapasitas).
4. `memo_2D_strings`: Cache 2D untuk masalah perbandingan dua string.
5. `memo_map_sparse`: Cache berbasis `map` untuk state dengan koordinat jarang (*sparse*) atau besar (> 10^6).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

// 1. Pola Cache 1D dengan Sentinel -1
ll fib_memo(int n, vector<ll>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
}

// 2. Pola Cache 1D dengan Boolean Seen Terpisah (Aman untuk 0 dan Negatif)
ll frog_jump_memo(int i, const vector<ll>& h, vector<ll>& memo, vector<bool>& seen) {
    int n = h.size();
    if (i == n - 1) return 0;
    if (seen[i]) return memo[i];
    seen[i] = true;

    ll best = INF;
    if (i + 1 < n) best = min(best, llabs(h[i] - h[i + 1]) + frog_jump_memo(i + 1, h, memo, seen));
    if (i + 2 < n) best = min(best, llabs(h[i] - h[i + 2]) + frog_jump_memo(i + 2, h, memo, seen));

    return memo[i] = best;
}

// 3. Pola Cache 2D Knapsack Top-Down
ll knapsack_top_down(int i, int s, const vector<int>& w, const vector<ll>& v, vector<vector<ll>>& memo) {
    int n = w.size();
    if (i == n || s == 0) return 0;
    if (memo[i][s] != -1) return memo[i][s];

    ll res = knapsack_top_down(i + 1, s, w, v, memo); // Skip
    if (w[i] <= s) {
        res = max(res, v[i] + knapsack_top_down(i + 1, s - w[i], w, v, memo)); // Take
    }
    return memo[i][s] = res;
}

// 4. Pola Cache 2D Dua String (LCS)
int lcs_top_down(int i, int j, const string& s, const string& t, vector<vector<int>>& memo) {
    int n = s.size(), m = t.size();
    if (i == n || j == m) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    if (s[i] == t[j]) {
        return memo[i][j] = 1 + lcs_top_down(i + 1, j + 1, s, t, memo);
    } else {
        return memo[i][j] = max(lcs_top_down(i + 1, j, s, t, memo), lcs_top_down(i, j + 1, s, t, memo));
    }
}

// 5. Pola Cache Map untuk State Jarang / Koordinat Besar
map<pair<ll, ll>, ll> memo_sparse;

ll grid_large_sparse(ll r, ll c) {
    if (r == 0 && c == 0) return 1;
    if (r < 0 || c < 0) return 0;

    auto state = make_pair(r, c);
    if (memo_sparse.count(state)) return memo_sparse[state];

    return memo_sparse[state] = grid_large_sparse(r - 1, c) + grid_large_sparse(r, c - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== TEMPLATE MASTER REKURSI DENGAN MEMOISASI (TOP-DOWN) ===\n";
    cout << "Tersedia 5 modul cache: 1D Sentinel, 1D Seen, 2D Knapsack, 2D String, dan Map Sparse.\n";

    return 0;
}
