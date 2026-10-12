/*
============================================================
✅ Solution 2: Arah Loop yang Menentukan
============================================================
Approach: Rekurens yang sama, dua arah loop berbeda
Complexity: Time O(N·W) | Space O(W)
Key Insight: 0/1 knapsack dan unbounded knapsack punya rekurens yang HURUF
             PER HURUF SAMA pada versi satu dimensi. Yang membedakan
             hanyalah ARAH penyapuan kapasitas -- dan itu bukan detail
             teknis, melainkan DEFINISI masalahnya yang tertanam dalam kode.

📖 KENAPA ARAH MENENTUKAN:
   Saat memperbarui dp[c] dengan membaca dp[c - w[i]], pertanyaannya adalah:
   apakah nilai yang dibaca itu SUDAH memuat barang ke-i?

   MUNDUR (c dari W turun ke w[i]):
       dp[c - w[i]] punya indeks LEBIH KECIL dari c, sehingga pada sapuan
       menurun ia BELUM disentuh di iterasi barang ini.
       -> nilainya masih dari barang 0..i-1 -> barang i dipakai SEKALI
       -> 0/1 knapsack

   MAJU (c dari w[i] naik ke W):
       dp[c - w[i]] punya indeks lebih kecil, sehingga pada sapuan menaik ia
       SUDAH diperbarui di iterasi ini.
       -> nilainya mungkin sudah memuat barang i -> barang i dipakai LAGI
       -> UNBOUNDED knapsack

📖 DEMONSTRASI PADA SAMPEL 2 (satu barang w=2 v=3, W=4):
   MUNDUR: c=4 -> dp[2]=0 masih -> dp[4]=3
           c=3 -> dp[1]=0       -> dp[3]=3
           c=2 -> dp[0]=0       -> dp[2]=3
           dp[4] = 3   (barang dipakai sekali)   ✓
   MAJU  : c=2 -> dp[0]=0 -> dp[2]=3
           c=3 -> dp[1]=0 -> dp[3]=3
           c=4 -> dp[2]=3 SUDAH -> dp[4]=6      (barang dipakai DUA kali)
   Jawaban sampel 2 memang "3 6" -- keduanya benar untuk aturannya
   masing-masing.

⚠️ INILAH BUG NOMOR SATU DI TOPIK INI. Kalau kamu menulis loop maju untuk
   soal 0/1, jawabanmu akan lebih besar dari seharusnya -- dan itu terlihat
   "masuk akal" sehingga sulit dicurigai. Uji dengan kasus satu barang dan
   kapasitas besar; kalau jawabannya kelipatan nilai barang, kamu memakai
   arah yang salah.

⚠️ TIPE DATA: nilai sampai 10^9 dengan W/w[i] bisa 10^5 pengulangan pada
   versi unbounded memberi 10^14. long long wajib untuk dp.

🔄 ALTERNATIVE APPROACHES:
- Versi 2D untuk 0/1: eksplisit merujuk dp[i-1], sehingga arah loop tidak
  penting. Lebih aman dari salah arah, tetapi boros memori.
- Untuk unbounded, versi 2D merujuk dp[i] pada baris yang sama.
  Membandingkan kedua versi 2D adalah cara terbaik memahami perbedaannya.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    cin >> n >> W;
    vector<int> w(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    vector<ll> dp01(W + 1, 0), dpUnb(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int c = W; c >= w[i]; c--)          // MUNDUR -> 0/1
            dp01[c] = max(dp01[c], dp01[c - w[i]] + v[i]);

        for (int c = w[i]; c <= W; c++)          // MAJU -> unbounded
            dpUnb[c] = max(dpUnb[c], dpUnb[c - w[i]] + v[i]);
    }

    cout << dp01[W] << ' ' << dpUnb[W] << '\n';
    return 0;
}
