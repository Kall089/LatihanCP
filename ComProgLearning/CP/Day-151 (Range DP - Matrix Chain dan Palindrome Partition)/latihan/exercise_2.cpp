/*
============================================================
🏋️ Exercise 2: Menggabungkan Gudang Kopi (Stone Merging / Slimes)
============================================================
Day: 151 | Difficulty: Medium | Topic: Range DP + Prefix Sum
Source: AtCoder Educational DP Contest N (Slimes) / Classic Stone Merging
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N karung kopi yang diletakkan berjajar dalam satu baris lurus.
Karung ke-i memiliki berat a[i] kg.
Dalam satu kali operasi, kamu boleh memilih DUA kelompok karung yang saling BERSEBELAHAN
lalu menggabungkannya menjadi satu kelompok baru.
Biaya yang harus dibayar untuk penggabungan tersebut adalah TOTAL BERAT dari kedua kelompok
karung yang digabungkan tersebut.

Urutan barisan karung kopi TIDAK BOLEH diubah.
Tentukan total biaya minimum yang diperlukan untuk menggabungkan seluruh N karung kopi
menjadi tepat satu kelompok tunggal.
Jika N = 1, tidak ada penggabungan yang diperlukan (biaya = 0).

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N, menyatakan banyak karung kopi.
- Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: total biaya minimum untuk menggabungkan seluruh karung kopi.

📏 CONSTRAINTS:
- 1 <= N <= 180
- 0 <= a[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3
10 20 30

📎 SAMPLE OUTPUT 1:
90

[Penjelasan Sample 1:
Pilihan 1: Gabungkan karung 0 dan 1 dulu (berat 10 + 20 = 30, biaya 30).
Lalu gabungkan dengan karung 2 (berat 30 + 30 = 60, biaya 60).
Total biaya = 30 + 60 = 90.
Pilihan 2: Gabungkan karung 1 dan 2 dulu (berat 20 + 30 = 50, biaya 50).
Lalu gabungkan dengan karung 0 (berat 10 + 50 = 60, biaya 60).
Total biaya = 50 + 60 = 110.
Pilihan minimum adalah 90.]

📎 SAMPLE INPUT 2:
1
999

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2: Hanya ada 1 karung, biaya 0.]

📎 SAMPLE INPUT 3:
3
0 0 0

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Gunakan Prefix Sum 1D untuk menghitung total berat pada sembarang interval [l, r] dalam O(1):
  weight(l, r) = pref[r + 1] - pref[l].
- Biaya penggabungan terakhir untuk interval [l, r] adalah weight(l, r),
  yang independen terhadap titik pecah k!
- Transisi: dp[l][r] = min_{l <= k < r} (dp[l][k] + dp[k + 1][r]) + weight(l, r).

🎯 Learning Goals:
- [ ] Menggabungkan Range DP dengan teknik Prefix Sum untuk efisiensi transisi.
- [ ] Memahami sifat asosiatif penggabungan bersebelahan (adjacent merging).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    // TODO: Selesaikan Stone Merging dengan Range DP
    // 1. vector<vector<ll>> dp(n, vector<ll>(n, 0))
    // 2. Loop len dari 2 s.d. n
    // 3. dp[l][r] = min_{k} (dp[l][k] + dp[k+1][r]) + (pref[r+1] - pref[l])
    // 4. Cetak dp[0][n-1]

    return 0;
}
