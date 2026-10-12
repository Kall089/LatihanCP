/*
============================================================
✅ Solution 6: Count Submatrices with Target Sum K
============================================================
Approach: Prefix Sum 2D + Hash Map (Row Compression)
Complexity: Time O(N^2 × M) atau O(N^2 × M log M) | Space O(N × M)
Key Insight:
Fixkan baris r1 dan r2. Masalah tereduksi menjadi 1D Subarray Sum Equal to K:
Diberikan array 1D col[1..M], cari berapa pasangan (c1, c2) sedemikian sehingga
sum(col[c1..c2]) = K.
Kita dapat menggunakan Hash Map (frekuensi prefix sum 1D) untuk menyelesaikan
per pasang (r1, r2) dalam waktu O(M).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long target_k;
    if (!(cin >> n >> m >> target_k)) return 0;

    vector<vector<long long>> psum(n + 1, vector<long long>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            long long val;
            cin >> val;
            psum[i][j] = val + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
        }
    }

    long long count_submatrices = 0;

    // Iterasi seluruh pasangan baris r1 dan r2
    for (int r1 = 1; r1 <= n; r1++) {
        for (int r2 = r1; r2 <= n; r2++) {
            // Hash map untuk menyimpan frekuensi prefix sum 1D pada kompresi kolom
            unordered_map<long long, int> pref_freq;
            pref_freq[0] = 1; // Base case: prefix sum = 0 muncul 1 kali

            long long current_pref = 0;
            for (int c = 1; c <= m; c++) {
                // Sum dari submatriks (r1, 1) ke (r2, c)
                current_pref = psum[r2][c] - psum[r1 - 1][c];

                // Cek apakah ada (current_pref - target_k) sebelumnya
                if (pref_freq.count(current_pref - target_k)) {
                    count_submatrices += pref_freq[current_pref - target_k];
                }

                pref_freq[current_pref]++;
            }
        }
    }

    cout << count_submatrices << "\n";

    return 0;
}
