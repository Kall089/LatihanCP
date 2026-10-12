/*
============================================================
Template Day 146: Subset Sum & Partition Problem
============================================================
Pola utama:
- bool DP untuk "bisa atau tidak"
- counting DP untuk "berapa banyak cara"
- bitset untuk semua reachable sum dengan cepat
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1000000007LL;

vector<char> subset_sum_bool(const vector<int>& a, int target) {
    vector<char> can(target + 1, 0);
    can[0] = 1;

    for (int x : a) {
        for (int s = target; s >= x; s--) {
            can[s] |= can[s - x];
        }
    }

    return can;
}

vector<ll> subset_sum_count(const vector<int>& a, int target) {
    vector<ll> ways(target + 1, 0);
    ways[0] = 1;

    for (int x : a) {
        for (int s = target; s >= x; s--) {
            ways[s] += ways[s - x];
            if (ways[s] >= MOD) ways[s] %= MOD;
        }
    }

    return ways;
}

int minimum_partition_difference(const vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    vector<char> can = subset_sum_bool(a, total);

    for (int s = total / 2; s >= 0; s--) {
        if (can[s]) return total - 2 * s;
    }

    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, target;
    cin >> n >> target;

    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<char> can = subset_sum_bool(a, target);
    cout << (can[target] ? "YES" : "NO") << '\n';

    return 0;
}
