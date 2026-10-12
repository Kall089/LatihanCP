/*
============================================================
✅ Solution 1: LIS Versi O(n^2)
============================================================
Approach: DP "berakhir tepat di i"
Complexity: Time O(N^2) | Space O(N)
Key Insight: Definisi "LIS sampai i" BUNTU -- kita tidak tahu nilai ekornya,
             jadi tidak bisa memutuskan apakah a[i] boleh disambung. Definisi
             yang bekerja adalah "LIS yang BERAKHIR TEPAT di i", karena
             ekornya jadi diketahui: a[i] itu sendiri.

📖 REKURENS:
   dp[i] = 1 + max{ dp[j] : j < i dan a[j] < a[i] }    (1 kalau tidak ada j)
   jawaban = max atas SELURUH dp[i]

⚠️ JAWABANNYA max(dp), BUKAN dp[n-1].
   Elemen terakhir belum tentu bagian dari LIS. Sampel 2 (array menurun)
   menguji ini: dp[n-1] = 1 kebetulan benar, tapi coba [1,2,3,0] -- dp[3] = 1
   sementara jawabannya 3.

⚠️ NILAI BOLEH NEGATIF. Jangan memakai 0 sebagai nilai netral atau sentinel.
   Sampel 3 memuat nilai negatif dan kembar sekaligus.

⚠️ KEMBAR TIDAK BOLEH DISAMBUNG pada versi KETAT: syaratnya a[j] < a[i],
   bukan <=. Untuk versi tidak menurun, gantilah menjadi <=.

⚠️ GREEDY GAGAL. "Ambil terus selama naik" pada [1,100,2,3,4] memberi 2,
   padahal jawabannya 4. Mengambil 100 lebih awal menutup masa depan -- tanda
   khas bahwa soal ini butuh DP.

VERIFIKASI SAMPEL 1 ([10,9,2,5,3,7,101,18]):
   dp = [1,1,1,2,2,3,4,4]
   max = 4  ✓   (mis. 2 5 7 101, atau 2 3 7 18)

VERIFIKASI SAMPEL 3 ([-3,-3,0,-1,2,2]):
   dp = [1,1,2,2,3,3]  -> 3  ✓
   Perhatikan dp[1] = 1: -3 tidak bisa menyambung -3 karena syaratnya KETAT.

🔄 ALTERNATIVE APPROACHES:
- O(n log n) dengan tails (Solution 2). Wajib kalau N > ~5000.
- Versi O(n^2) ini JUSTRU lebih berguna kalau kamu butuh modifikasi: LIS
  berbobot (ganti +1 dengan +w[i]), penghitungan, atau rekonstruksi sederhana.
- Sebagai jalur terpanjang di DAG (Day 120): edge i->j bila i<j dan a[i]<a[j].
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);

    cout << *max_element(dp.begin(), dp.end()) << '\n';   // max(dp)
    return 0;
}
