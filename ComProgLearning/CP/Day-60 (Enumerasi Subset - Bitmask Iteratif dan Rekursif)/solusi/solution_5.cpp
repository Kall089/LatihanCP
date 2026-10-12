/*
============================================================
  Solution 5: Enumerate Subsets of a Given Mask
============================================================
Pendekatan: Gunakan teknik for(sub=M; sub>0; sub=(sub-1)&M) untuk
mengiterasi semua subset dari M. Proses sub=0 (empty set) secara manual.
Simpan semua (sub, sum) ke vector, sort, lalu cetak.

Kompleksitas: O(2^popcount(M)) untuk iterasi, O(popcount(M)) per subset.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int M;
    cin >> M;

    auto calcSum = [&](int mask) -> long long {
        long long s = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s += a[i];
        return s;
    };

    auto binStr = [&](int mask) -> string {
        string s = "";
        for (int i = n - 1; i >= 0; i--)
            s += ((mask >> i) & 1) ? '1' : '0';
        return s;
    };

    vector<pair<int,long long>> subsets;

    // Empty set
    subsets.push_back({0, 0LL});

    // Semua subset tidak kosong dari M
    for (int sub = M; sub > 0; sub = (sub - 1) & M) {
        subsets.push_back({sub, calcSum(sub)});
    }

    sort(subsets.begin(), subsets.end());

    for (auto& [mask, sum] : subsets) {
        cout << binStr(mask) << " : { ";
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) cout << a[i] << " ";
        cout << "} | sum = " << sum << "\n";
    }

    cout << "Total subset (termasuk empty): " << (int)subsets.size() << "\n";

    // Subset sum max
    auto maxIt = max_element(subsets.begin(), subsets.end(),
                             [](auto& x, auto& y) { return x.second < y.second; });
    cout << "Subset sum maks: { ";
    for (int i = 0; i < n; i++)
        if ((maxIt->first >> i) & 1) cout << a[i] << " ";
    cout << "} (sum=" << maxIt->second << ")\n";

    // Subset sum min (non-empty)
    long long minSum = LLONG_MAX;
    int minMask = -1;
    for (auto& [mask, sum] : subsets) {
        if (mask == 0) continue;
        if (sum < minSum || (sum == minSum && mask < minMask)) {
            minSum = sum;
            minMask = mask;
        }
    }
    if (minMask != -1) {
        cout << "Subset sum min (non-empty): { ";
        for (int i = 0; i < n; i++)
            if ((minMask >> i) & 1) cout << a[i] << " ";
        cout << "} (sum=" << minSum << ")\n";
    }

    return 0;
}
