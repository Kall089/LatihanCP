/*
============================================================
✅ Solution 6: Rekonstruksi Subsekuens Naik Terpanjang (LIS Reconstruction)
============================================================
Approach: 1D Dynamic Programming + Parent Array Tracking
Complexity: Time O(N^2) | Space O(N)
Key Insight:
1. Definisi State:
   dp[i] = panjang LIS terpanjang yang berakhir di elemen a[i].
   parent[i] = indeks elemen pendahulu a[j] yang dipilih sebelum a[i] dalam LIS.
   Inisialisasi: parent[i] = -1 untuk semua i.

2. Pengisian Tabel (O(N^2)):
   Untuk setiap i dari 0 sampai N - 1:
     dp[i] = 1;
     Untuk setiap j dari 0 sampai i - 1:
       Jika a[j] < a[i] dan dp[j] + 1 > dp[i]:
         dp[i] = dp[j] + 1;
         parent[i] = j;

3. Temukan Akhir Rantai Optimal:
   Cari indeks `best_idx` dengan nilai dp[best_idx] maksimum.

4. Penelusuran Mundur (Backtracking Rantai Pointer):
   cur = best_idx
   Selama cur != -1:
     lis_elements.push_back(a[cur])
     cur = parent[cur]
   Balikkan (reverse) array `lis_elements` karena penelusuran bergerak mundur dari elemen akhir ke awal.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == 0) {
        cout << 0 << "\n\n";
        return 0;
    }

    vector<int> dp(n, 1);
    vector<int> parent(n, -1);

    int max_len = 1;
    int best_idx = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            best_idx = i;
        }
    }

    // Rekonstruksi dari best_idx
    vector<int> lis;
    int cur = best_idx;
    while (cur != -1) {
        lis.push_back(a[cur]);
        cur = parent[cur];
    }

    reverse(lis.begin(), lis.end());

    cout << max_len << "\n";
    for (size_t i = 0; i < lis.size(); i++) {
        cout << lis[i] << (i + 1 == lis.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
