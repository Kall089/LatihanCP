/*
============================================================
✅ Solution 2: Jalur dengan Halangan
============================================================
Approach: DP grid + sentinel 0 untuk sel terhalang
Complexity: Time O(R*C) | Space O(R*C)
Key Insight: Halangan tidak memerlukan logika bercabang sama sekali. Cukup
             tugaskan dp = 0 di sel terhalang. Karena 0 adalah ELEMEN
             IDENTITAS penjumlahan, sel itu menyumbang nol ke tetangganya dan
             seluruh jalur yang melewatinya otomatis mati.

📖 ATURAN SENTINEL YANG UNIVERSAL:
   sentinel = elemen identitas dari operator gabung.
     +   -> 0
     min -> +INF
     max -> -INF
   Memakai 0 untuk soal MINIMUM adalah kesalahan besar (jalur haram jadi
   "gratis"). Lihat Solution 5 untuk kasus max.

⚠️ PERIKSA SEL AWAL DAN TUJUAN LEBIH DULU.
   Kalau (0,0) adalah '#', jawabannya 0 -- tapi kode yang langsung menulis
   dp[1][1] = 1 akan melewatkan ini. Sampel 3 menguji tepat kasus itu.

⚠️ TUGASKAN 0 SECARA EKSPLISIT, jangan hanya "continue" tanpa penugasan.
   Pada soal multi-test atau array yang dipakai ulang, nilai lama bisa tersisa.

⚠️ URUTAN PEMERIKSAAN DI DALAM LOOP:
   cek halangan DULU, baru cek (i==1 && j==1). Kalau terbalik, sel awal yang
   terhalang tetap diberi nilai 1.

⚠️ MEMBACA INPUT. Grid dibaca PER BARIS sebagai string, bukan per karakter
   dengan cin >> c. Perhatikan format soal.

VERIFIKASI SAMPEL 1 (3x4, halangan di (0,3) dan (1,1)):
   grid:  . . . #
          . # . .
          . . . .
   dp (padding 1-indexed):
     baris1: 1 1 1 0
     baris2: 1 0 1 1
     baris3: 1 1 2 3
   dp[3][4] = 3  ✓

VERIFIKASI SAMPEL 2 (diagonal terhalang):
   . #      dp: 1 0
   # .          0 0
   dp[2][2] = 0  ✓

🔄 ALTERNATIVE APPROACHES:
- ROLLING ARRAY: memori O(C), loop j KIRI KE KANAN.
- HALANGAN SEDIKIT (k <= 3000) di grid RAKSASA: kombinatorika +
  inclusion-exclusion terurut, O(k^2). Itu soal AtCoder DP-Y.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    cin >> R >> C;
    vector<string> g(R);
    for (auto& s : g) cin >> s;

    if (g[0][0] == '#' || g[R-1][C-1] == '#') { cout << 0 << '\n'; return 0; }

    vector<vector<ll>> dp(R + 1, vector<ll>(C + 1, 0));
    dp[1][1] = 1;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            if (g[i-1][j-1] == '#') { dp[i][j] = 0; continue; }   // cek halangan DULU
            if (i == 1 && j == 1) continue;
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
        }

    cout << dp[R][C] << '\n';
    return 0;
}
