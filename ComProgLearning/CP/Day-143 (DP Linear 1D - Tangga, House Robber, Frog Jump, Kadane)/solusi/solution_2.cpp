/*
============================================================
✅ Solution 2: Tangga Rusak dengan Langkah 1..K
============================================================
Approach: DP 1D, jumlah atas jendela K
Complexity: Time O(N*K) | Space O(N)
Key Insight: Larangan tidak mengubah rekurensnya; ia hanya memaksa dp[i] = 0
             untuk anak tangga yang haram diinjak. Nilai 0 adalah elemen
             netral penjumlahan, jadi ia otomatis "menghapus" seluruh jalur
             yang melewatinya.

📖 REKURENS:
   dp[i] = dp[i-1] + dp[i-2] + ... + dp[i-K]     (untuk i-j >= 0)
   dp[0] = 1
   dp[i] = 0 kalau anak tangga i rusak

⚠️ TUGASKAN 0, JANGAN "continue" TANPA MENUGASKAN.
   Kalau kamu menulis  if (rusak[i]) continue;  pada array yang tidak
   diinisialisasi ulang, nilai lama bisa tersisa. Tulis
       if (rusak[i]) { dp[i] = 0; continue; }
   secara eksplisit. Kebiasaan ini menyelamatkanmu di soal multi-test.

⚠️ TUJUAN BOLEH RUSAK. Sampel 3 menguji ini: anak tangga N sendiri rusak,
   jadi jawabannya 0. Jangan buru-buru menganggap tujuan selalu sah.

⚠️ MODULO SETIAP PENJUMLAHAN, bukan hanya di akhir.

VERIFIKASI SAMPEL 1 (N=5, K=2, rusak={3}):
   dp[0]=1
   dp[1]=dp[0]=1
   dp[2]=dp[1]+dp[0]=2
   dp[3]=0            (rusak)
   dp[4]=dp[3]+dp[2]=0+2=2
   dp[5]=dp[4]+dp[3]=2+0=2   ✓

VERIFIKASI SAMPEL 2 (N=4, K=3, tidak ada yang rusak):
   1, 1, 2, 4, 7  ->  7  ✓

🔄 ALTERNATIVE APPROACHES:
- Untuk K besar (sampai 10^5), O(N*K) TLE. Pakai PREFIX SUM BERGULIR:
  dp[i] = S(i-1) - S(i-K-1) dengan S prefix sum dari dp -> O(N).
  Hati-hati dengan modulo negatif: tambahkan MOD sebelum mengambil sisa.
- CSES 1633 "Dice Combinations" adalah soal ini dengan K = 6 tanpa yang rusak.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int n, k, r;
   cin >> n >> k >> r;
   vector<char> rusak(n + 1, 0);
   for (int i = 0; i < r; i++)
   {
      int x;
      cin >> x;
      if (x <= n)
         rusak[x] = 1;
   }

   vector<ll> dp(n + 1, 0);
   dp[0] = 1;
   for (int i = 1; i <= n; i++)
   {
      if (rusak[i])
      {
         dp[i] = 0;
         continue;
      } // TUGASKAN eksplisit
      for (int j = 1; j <= k && j <= i; j++)
         dp[i] = (dp[i] + dp[i - j]) % MOD;
   }
   cout << dp[n] << '\n';
   return 0;
}
