/*
============================================================
✅ Solution 5: Katak Melompat (Frog Jump)
============================================================
Approach: DP 1D, minimum atas jendela K ke belakang
Complexity: Time O(N*K) | Space O(N)
Key Insight: dp[i] = biaya minimum untuk SAMPAI di batu i. Untuk sampai di i,
             lompatan terakhir datang dari salah satu batu i-1 .. i-K. Coba
             semuanya, ambil yang termurah.

📖 REKURENS:
   dp[i] = min over j = 1..K of  dp[i-j] + |h[i] - h[i-j]|      (i-j >= 0)
   dp[0] = 0

⚠️ KENAPA GREEDY GAGAL.
   Memilih batu dengan ketinggian PALING MIRIP terlihat masuk akal, tetapi
   lompatan yang mahal sekarang bisa membuka posisi yang jauh lebih murah
   nanti. Sampel 2 adalah contohnya: dari batu 0, greedy melihat batu 1
   (selisih 20) dan batu 2 (selisih 30) lalu memilih batu 1 -- yang kebetulan
   benar. Tetapi susun ulang ketinggiannya sedikit dan greedy langsung salah.
   DP mempertimbangkan SEMUA kombinasi tanpa perlu argumen tambahan.

⚠️ dp[0] = 0, sisanya INF. Batu yang belum terjangkau tidak boleh dipakai
   merelaksasi -- dengan INF = LLONG_MAX/4, penjumlahan tetap aman dan nilainya
   otomatis kalah di min. (Kalau memakai LLONG_MAX, dp[i-j] + selisih akan
   OVERFLOW.)

⚠️ BATAS j <= i. Jangan mengakses indeks negatif. Ini bug paling sering di
   soal ini.

⚠️ llabs / abs. Untuk long long pakai llabs atau std::abs dari <cstdlib>
   dengan tipe yang benar -- abs(int) pada long long memotong nilainya.

VERIFIKASI SAMPEL 1 (K=1, h=[10,30,40,20]):
   Dengan K=1 tidak ada pilihan sama sekali -- katak wajib melewati setiap batu.
   dp[1]=|10-30|=20 ; dp[2]=20+|30-40|=30 ; dp[3]=30+|40-20|=50   ✓

VERIFIKASI SAMPEL 2 (K=2, h=[10,30,40,20]):
   dp[1]=20
   dp[2]=min(dp[1]+10, dp[0]+30)=min(30,30)=30
   dp[3]=min(dp[2]+20, dp[1]+10)=min(50,30)=30   ✓

VERIFIKASI SAMPEL 3 (K=4, h=[10,100,100,100,20]):
   dp[4] bisa langsung dari dp[0]: 0 + |10-20| = 10  ✓

🔄 ALTERNATIVE APPROACHES:
- K besar (10^5): O(N*K) TLE. Kalau biayanya bisa dipisah menjadi bentuk
  dp[j] + f(j) + g(i), pakai MONOTONIC DEQUE (Day 37) untuk minimum jendela
  geser -> O(N). Untuk |h[i]-h[j]| murni, dekomposisinya rumit dan soal
  biasanya tidak memintanya.
- Memori O(K) saja: cukup simpan K nilai dp terakhir secara melingkar.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<ll> h(n);
    for (auto& x : h) cin >> x;

    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= k && j <= i; j++)          // j <= i: jangan negatif
            dp[i] = min(dp[i], dp[i - j] + llabs(h[i] - h[i - j]));

    cout << dp[n - 1] << '\n';
    return 0;
}
