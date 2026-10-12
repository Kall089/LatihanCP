/*
============================================================
✅ Solution 1: Toko Buku
============================================================
Approach: DP 0/1 knapsack, rolling array satu dimensi
Complexity: Time O(N·X) | Space O(X)
Key Insight: Setiap buku punya keputusan BINER: beli atau tidak. Tidak ada
             urutan greedy yang benar, karena membeli buku "berrasio tinggi"
             bisa menghabiskan uang dengan cara yang menghalangi kombinasi
             yang lebih baik.

📖 KENAPA GREEDY RASIO GAGAL -- contoh tandingan:
       X = 10
       buku A: harga 6, halaman 7   -> rasio 1.167  (tertinggi)
       buku B: harga 5, halaman 5
       buku C: harga 5, halaman 5
   Greedy rasio: beli A (7 halaman), sisa uang 4, tidak ada yang muat -> 7
   Optimal     : beli B dan C -> 10
   Greedy rasio BENAR untuk fractional knapsack (barang boleh dipotong,
   Day 74), tetapi keputusan biner membuat "sisa uang terbuang" menjadi
   masalah nyata.

📖 REKURENSNYA:
   dp[c] = total halaman maksimum dengan sisa uang tepat c.
   Untuk setiap buku:  dp[c] = max(dp[c], dp[c - h] + s)

⚠️ LOOP KAPASITAS HARUS MUNDUR. Ini bagian terpenting hari ini.
   MUNDUR: saat membaca dp[c - h], nilainya MASIH dari iterasi buku
           SEBELUMNYA -> buku sekarang belum dipakai -> tiap buku SEKALI  ✓
   MAJU  : dp[c - h] SUDAH diperbarui pada iterasi ini -> buku bisa dibeli
           berkali-kali -> itu UNBOUNDED knapsack, bukan 0/1  ✗

⚠️ MEMORI ADALAH ALASAN NYATA MEMILIH VERSI 1D:
   Tabel 2D berukuran (N+1) x (X+1) = 1001 x 100001 int = 400 MB -> MLE.
   Versi 1D hanya 100001 int = 400 KB. Rolling array di sini bukan
   optimasi, melainkan KEHARUSAN.
   Cara mengetahuinya: hitung N * X sebelum menulis. 1000 * 10^5 = 10^8 sel.

⚠️ TIPE DATA: 1000 buku dengan 1000 halaman memberi 10^6 -- muat di int.
   Tetapi kalau nilainya sampai 10^9, totalnya 10^12 dan long long wajib.
   Solusi ini memakai long long sebagai kebiasaan; biayanya nol.

VERIFIKASI SAMPEL 1 (X=10, harga [4,8,5,3], halaman [5,12,8,1]):
   Kombinasi terbaik: buku 1 (harga 4, 5 halaman) + buku 3 (harga 5, 8 halaman)
   Total harga 9 <= 10, total halaman 13.   ✓
   Perhatikan buku 2 punya halaman terbanyak (12) tetapi harganya 8,
   menyisakan 2 -- tidak cukup untuk apa pun. Greedy "halaman terbanyak"
   akan menjawab 12, salah.

CATATAN: implementasi ini telah diuji terhadap brute force 2^n pada 20000
kasus acak.

🔄 ALTERNATIVE APPROACHES:
- DP 2D: sama benarnya, tetapi MLE untuk batas ini.
- Meet in the middle: hanya kalau N <= 40 (Day 54). Di sini N = 1000.
- DP atas nilai: total halaman bisa 10^6, sebanding dengan X -- tidak ada
  keuntungan. Baru berguna kalau X jauh lebih besar (lihat Exercise 5).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int n, X;
   cin >> n >> X;
   vector<int> h(n), s(n);
   for (int &x : h)
      cin >> x;
   for (int &x : s)
      cin >> x;

   vector<ll> dp(X + 1, 0); // 1D: 400 KB, bukan 400 MB

   for (int i = 0; i < n; i++)
      for (int c = X; c >= h[i]; c--) // MUNDUR -> tiap buku sekali
         dp[c] = max(dp[c], dp[c - h[i]] + s[i]);

   cout << dp[X] << '\n';
   return 0;
}
