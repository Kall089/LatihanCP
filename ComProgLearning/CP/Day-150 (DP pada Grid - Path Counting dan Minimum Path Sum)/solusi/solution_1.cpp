/*
============================================================
✅ Solution 1: Menghitung Jalur
============================================================
Approach: DP grid, versi padding
Complexity: Time O(R*C) | Space O(R*C)
Key Insight: Setiap jalur ke (i,j) dibedakan oleh LANGKAH TERAKHIRNYA -- dari
             atas atau dari kiri. Kedua himpunan itu saling lepas, jadi
             jumlahnya boleh ditambahkan tanpa risiko terhitung dua kali.

📖 KENAPA GRID INI BOLEH DI-DP:
   Definisikan f(i,j) = i + j. Setiap gerakan yang diizinkan menaikkan f tepat
   satu. Kalau ada siklus, kita kembali ke sel yang sama dengan f yang sudah
   bertambah -- mustahil. Jadi grafnya DAG (Day 120), dan urutan topologisnya
   GRATIS: baris demi baris, kiri ke kanan.

📖 PADDING MENGHILANGKAN if TEPI:
   Pakai indeks 1..R dan 1..C. Baris 0 dan kolom 0 berisi 0, yaitu elemen
   identitas penjumlahan, sehingga dp[i-1][j] dan dp[i][j-1] selalu aman
   diakses tanpa penjagaan.

⚠️ dp[1][1] HARUS DI-SET MANUAL DAN DILEWATI DI DALAM LOOP.
   Kalau tidak dilewati, dp[1][1] = dp[0][1] + dp[1][0] = 0 akan menimpanya,
   dan seluruh tabel menjadi nol. Ini bug paling umum pada versi padding.

⚠️ MODULO. R = C = 1000 memberi C(1998, 999) -- angka dengan ratusan digit.
   Sampel 3 (100 x 100) sudah jauh melewati batas long long, jadi ia menguji
   apakah kamu memodulo di setiap penjumlahan.

VERIFIKASI SAMPEL 1 (R=3, C=7):
   Baris 1: semua 1 (hanya bisa lurus ke kanan)
   Baris 2: 1 2 3 4 5 6 7
   Baris 3: 1 3 6 10 15 21 28
   dp[3][7] = 28  ✓
   Cocok dengan rumus kombinatorik C(3+7-2, 3-1) = C(8,2) = 28.

VERIFIKASI SAMPEL 2 (R=1, C=5): hanya satu jalur lurus -> 1  ✓

🔄 ALTERNATIVE APPROACHES:
- KOMBINATORIKA: C(R+C-2, R-1) dengan faktorial + invers modular, O(R+C).
  WAJIB kalau R, C sampai 10^6 sehingga tabel O(R*C) tidak muat.
- ROLLING ARRAY: memori O(C). Lihat Solution 2 dan template bagian 6.
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

    vector<vector<ll>> dp(R + 1, vector<ll>(C + 1, 0));
    dp[1][1] = 1;                                   // set MANUAL
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            if (i == 1 && j == 1) continue;         // JANGAN ditimpa
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
        }

    cout << dp[R][C] << '\n';
    return 0;
}
