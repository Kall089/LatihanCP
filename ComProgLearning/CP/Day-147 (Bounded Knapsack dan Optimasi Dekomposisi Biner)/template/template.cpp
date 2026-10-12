/*
============================================================
📦 TEMPLATE BOILERPLATE: Bounded Knapsack & Dekomposisi Biner
============================================================
Day: 147 | Topic: Bounded Knapsack & Binary Decomposition Suite
Standard: C++17 Competitive Programming Template

Fungsi-fungsi pembantu yang tersedia di template ini:
1. `boundedKnapsackMax(W, items)`:
   Menghitung nilai keuntungan maksimum dengan kapasitas <= W.
2. `boundedKnapsackMinCoins(target, coins)`:
   Menghitung jumlah keping koin minimum untuk membentuk target nominal.
3. `boundedReachability(S, items)`:
   Menghitung boolean ketercapaian setiap nominal dari 0 s.d. S.
4. `hybridBoundedKnapsack(W, items)`:
   Optimasi otomatis: jika count * weight >= W, pakai Unbounded loop maju;
   jika tidak, pakai Dekomposisi Biner loop mundur.
5. `exactTargetBoundedKnapsack(W, items)`:
   Menghitung nilai maksimum dengan total bobot TEPAT sama dengan W.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9 + 7;

struct Item {
    int weight;
    ll value;
    ll count;
};

// 1. Bounded Knapsack Maksimum Nilai (Dekomposisi Biner Standar)
ll boundedKnapsackMax(int W, const vector<Item>& items) {
    vector<ll> dp(W + 1, 0);

    for (const auto& it : items) {
        if (it.weight <= 0 || it.count <= 0 || W <= 0) continue;
        ll c_eff = min(it.count, (ll)(W / it.weight));

        ll p = 1;
        while (c_eff > 0) {
            ll q = min(p, c_eff);
            c_eff -= q;

            int pkg_w = q * it.weight;
            ll pkg_v = q * it.value;

            for (int s = W; s >= pkg_w; s--) {
                dp[s] = max(dp[s], dp[s - pkg_w] + pkg_v);
            }
            p *= 2;
        }
    }
    return dp[W];
}

// 2. Bounded Coin Change Minimum Keping
int boundedKnapsackMinCoins(int target, const vector<pair<int, ll>>& coins) {
    vector<int> dp(target + 1, INF);
    dp[0] = 0;

    for (const auto& c : coins) {
        int weight = c.first;
        ll count = c.second;
        if (weight <= 0 || count <= 0) continue;

        ll c_eff = min(count, (ll)(target / weight));
        ll p = 1;

        while (c_eff > 0) {
            ll q = min(p, c_eff);
            c_eff -= q;

            int pkg_w = q * weight;
            int pkg_cost = q;

            for (int s = target; s >= pkg_w; s--) {
                if (dp[s - pkg_w] != INF) {
                    dp[s] = min(dp[s], dp[s - pkg_w] + pkg_cost);
                }
            }
            p *= 2;
        }
    }
    return (dp[target] == INF ? -1 : dp[target]);
}

// 3. Bounded Reachability (Boolean Subset Sum)
vector<bool> boundedReachability(int S, const vector<pair<int, ll>>& items) {
    vector<bool> can(S + 1, false);
    can[0] = true;

    for (const auto& it : items) {
        int weight = it.first;
        ll count = it.second;
        if (weight <= 0 || count <= 0) continue;

        ll c_eff = min(count, (ll)(S / weight));
        ll p = 1;

        while (c_eff > 0) {
            ll q = min(p, c_eff);
            c_eff -= q;

            int pkg_w = q * weight;
            for (int s = S; s >= pkg_w; s--) {
                if (can[s - pkg_w]) can[s] = true;
            }
            p *= 2;
        }
    }
    return can;
}

// 4. Hybrid Bounded Knapsack (Unbounded Shortcut + Binary Splitting)
ll hybridBoundedKnapsack(int W, const vector<Item>& items) {
    vector<ll> dp(W + 1, 0);

    for (const auto& it : items) {
        if (it.weight <= 0 || it.count <= 0 || W <= 0) continue;

        if (it.count * (ll)it.weight >= W) {
            // Unbounded Forward Loop O(W)
            for (int s = it.weight; s <= W; s++) {
                dp[s] = max(dp[s], dp[s - it.weight] + it.value);
            }
        } else {
            // Bounded Binary Backward Loop O(W log C)
            ll p = 1, sisa = it.count;
            while (sisa > 0) {
                ll q = min(p, sisa);
                sisa -= q;

                int pkg_w = q * it.weight;
                ll pkg_v = q * it.value;

                for (int s = W; s >= pkg_w; s--) {
                    dp[s] = max(dp[s], dp[s - pkg_w] + pkg_v);
                }
                p *= 2;
            }
        }
    }
    return dp[W];
}

// 5. Exact Target Bounded Knapsack (Sentinel -1)
ll exactTargetBoundedKnapsack(int W, const vector<Item>& items) {
    vector<ll> dp(W + 1, -1);
    dp[0] = 0;

    for (const auto& it : items) {
        if (it.weight <= 0 || it.count <= 0 || W < 0) continue;
        ll c_eff = min(it.count, (ll)(W / it.weight));

        ll p = 1;
        while (c_eff > 0) {
            ll q = min(p, c_eff);
            c_eff -= q;

            int pkg_w = q * it.weight;
            ll pkg_v = q * it.value;

            for (int s = W; s >= pkg_w; s--) {
                if (dp[s - pkg_w] != -1) {
                    dp[s] = max(dp[s], dp[s - pkg_w] + pkg_v);
                }
            }
            p *= 2;
        }
    }
    return dp[W];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (cin >> n >> W) {
        vector<Item> items(n);
        for (int i = 0; i < n; i++) {
            cin >> items[i].weight >> items[i].value >> items[i].count;
        }
        cout << hybridBoundedKnapsack(W, items) << "\n";
    }

    return 0;
}
