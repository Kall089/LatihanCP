/*
============================================================
✅ Solution 5: Maksimum Permen dengan Halangan
============================================================
Approach: DP grid dengan operator max dan sentinel -INF
Complexity: Time O(R*C) | Space O(R*C)
Key Insight: Sentinel harus ELEMEN IDENTITAS dari operator gabung. Untuk max
             itu -INF. Memakai 0 adalah kesalahan yang halus tapi fatal:
             sel tembok akan terlihat seperti sel sah bernilai 0, dan jalur
             yang menembus tembok jadi dianggap valid.

📖 REKURENS:
   tembok        : dp[i][j] = -INF
   selain itu    : best = max(dp[i-1][j], dp[i][j-1])
                   kalau best == -INF -> dp[i][j] = -INF   (TAK TERJANGKAU)
                   kalau tidak        -> dp[i][j] = a[i][j] + best
   dp[0][0] = a[0][0] kalau bukan tembok

⚠️ SENTINEL HARUS DILEWATI, BUKAN SEKADAR DIINISIALISASI.
   Kalau kamu menulis dp[i][j] = a[i][j] + max(...) tanpa memeriksa, maka
   (-INF) + a[i][j] menghasilkan angka yang JAUH LEBIH BESAR dari -INF, dan
   nilai sampah itu MENANG di max berikutnya lalu menular ke seluruh grid.
   Gejalanya: jawaban berupa angka negatif raksasa. Ini kesalahan yang sama
   persis dengan Day 120 bagian 4.2 -- pola yang layak dihafal.

⚠️ TAK TERJANGKAU vs TERHALANG adalah dua hal berbeda yang kebetulan memakai
   sentinel yang sama. Sel bebas yang semua jalannya terblokir juga -INF.
   Keduanya sama-sama tidak boleh dipakai merelaksasi.

⚠️ NILAI 0 SAH. Sel boleh berisi 0 permen. Karena itu kamu TIDAK bisa memakai
   "dp == 0" sebagai penanda tidak terjangkau.

⚠️ CEK SEL AWAL. Kalau (0,0) adalah tembok, jawabannya -1.

VERIFIKASI SAMPEL 1:
   grid:  1  2  3
         -1 -1  4
          7  8  5
   dp:    1  3  6
         -I -I 10
         -I -I 15
   Baris 2 kolom 0 dan 1 adalah tembok. Sel (2,0) dan (2,1) BEBAS tapi tidak
   terjangkau (atasnya tembok, kirinya tidak ada / tembok) -> -INF.
   dp[2][2] = 5 + max(dp[1][2]=10, dp[2][1]=-INF) = 15  ✓

VERIFIKASI SAMPEL 2: kedua jalur tertutup tembok -> dp[1][1] = -INF -> -1  ✓

VERIFIKASI SAMPEL 3: max(1+2+4, 1+3+4) = 8  ✓

🔄 ALTERNATIVE APPROACHES:
- Memakai pasangan (bisa_dijangkau, nilai) alih-alih sentinel numerik. Lebih
  panjang tapi menghilangkan seluruh kelas bug overflow sentinel. Layak
  dipertimbangkan kalau nilainya bisa sangat besar.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 4;

int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int R, C;
   cin >> R >> C;
   vector<vector<ll>> a(R, vector<ll>(C));
   for (auto &row : a)
      for (auto &x : row)
         cin >> x;

   vector<vector<ll>> dp(R, vector<ll>(C, NEG));
   if (a[0][0] != -1)
      dp[0][0] = a[0][0];

   for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++)
      {
         if (a[i][j] == -1)
         {
            dp[i][j] = NEG;
            continue;
         } // TEMBOK
         if (i == 0 && j == 0)
            continue;
         ll best = NEG;
         if (i > 0)
            best = max(best, dp[i - 1][j]);
         if (j > 0)
            best = max(best, dp[i][j - 1]);
         if (best == NEG)
            dp[i][j] = NEG; // LEWATI sentinel
         else
            dp[i][j] = a[i][j] + best;
      }

   cout << (dp[R - 1][C - 1] == NEG ? -1 : dp[R - 1][C - 1]) << '\n';
   return 0;
}
