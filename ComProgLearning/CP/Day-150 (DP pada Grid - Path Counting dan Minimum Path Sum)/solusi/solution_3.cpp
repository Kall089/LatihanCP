/*
============================================================
✅ Solution 3: Jumlah Jalur Minimum
============================================================
Approach: DP grid dengan operator min
Complexity: Time O(R*C) | Space O(R*C)
Key Insight: Kerangkanya identik dengan penghitungan jalur; yang berubah hanya
             operator gabung (+ menjadi min) dan cara biaya sel dimasukkan.
             Ini pola yang sama seperti Day 120: satu kerangka, banyak
             pertanyaan.

📖 REKURENS:
   dp[i][j] = a[i][j] + min(dp[i-1][j], dp[i][j-1])
   dp[0][0] = a[0][0]
   Biaya sel ditambahkan DI LUAR min, karena sel (i,j) pasti diinjak apa pun
   arah datangnya.

⚠️ long long WAJIB. Grid 1000x1000 dengan nilai 10^9 memberi jalur sepanjang
   ~2000 sel -> 2*10^12. Sampel 3 menguji ini dengan angka kecil tapi jelas:
   3 * 10^9 sudah melewati int.

⚠️ SEL AWAL. dp[0][0] = a[0][0], BUKAN 0. Biaya sel awal ikut dihitung
   (baca soal -- beberapa soal tidak menghitungnya).

⚠️ TEPI. Baris 0 hanya bisa datang dari kiri; kolom 0 hanya dari atas.
   Kalau memakai padding, isi tepi dengan INF (identitas min) -- BUKAN 0,
   karena 0 akan menang di min dan merusak seluruh baris pertama.
   Solusi di bawah memakai penjagaan eksplisit, yang lebih mudah dibaca.

⚠️ GERAKAN 4 ARAH? Rumus ini TIDAK BERLAKU. Grafnya jadi bersiklus dan tidak
   punya urutan topologis. Pakai Dijkstra (Day 127). Ini pembatas terpenting
   dari seluruh materi hari ini.

VERIFIKASI SAMPEL 1:
   grid       dp
   1 3 1      1  4  5
   1 5 1  ->  2  7  6
   4 2 1      6  8  7
   dp[2][2] = 7  ✓  (1 -> 3 -> 1 -> 1 -> 1)
   Perhatikan dp[1][2] = 6, bukan 5+1 = 8: datang dari ATAS (5) lebih murah
   daripada dari KIRI (7).

VERIFIKASI SAMPEL 2 (satu kolom): 5 + 2 + 8 = 15  ✓

🔄 ALTERNATIVE APPROACHES:
- ROLLING ARRAY O(C): dp[j] = a + min(dp[j], dp[j-1]), j dari kiri ke kanan.
- Untuk MAKSIMUM: ganti min -> max. Untuk jalur maksimum dengan halangan,
  sentinelnya -INF (Solution 5).
- LC 174 (Dungeon Game) tampak mirip tapi harus di-DP dari TUJUAN KE AWAL --
  contoh bahwa arah DP tidak selalu maju.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    cin >> R >> C;
    vector<vector<ll>> a(R, vector<ll>(C));
    for (auto& row : a) for (auto& x : row) cin >> x;

    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i-1][j]);
            if (j > 0) best = min(best, dp[i][j-1]);
            dp[i][j] = a[i][j] + best;
        }

    cout << dp[R-1][C-1] << '\n';
    return 0;
}
