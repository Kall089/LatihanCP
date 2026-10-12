/*
============================================================
✅ Solution 3: Rata-rata Maksimum dari K Elemen
============================================================
Approach: Binary search + transformasi a[i] - x
Complexity: Time O(100 * N log N) | Space O(N)
Key Insight: "Rata-rata" tidak monoton terhadap apa pun, sehingga binary
             search tidak bisa langsung diterapkan. Transformasi a[i] - x
             MEMULIHKAN monotonisitas dengan mengubah pertanyaan tentang
             RATA-RATA menjadi pertanyaan tentang JUMLAH.

📖 TURUNAN TRANSFORMASINYA:
       rata-rata terpilih >= x
   <=> (jumlah terpilih) / K >= x
   <=> jumlah terpilih - K*x >= 0
   <=> jumlah dari (a[i] - x) untuk elemen terpilih >= 0

   Setelah transformasi, pertanyaannya menjadi: "adakah K elemen yang jumlah
   (a[i] - x)-nya tidak negatif?" Jawabannya jelas: ambil K nilai (a[i] - x)
   TERBESAR. Kalau jumlah mereka pun negatif, tidak ada pilihan lain yang
   bisa positif.

   Dan predikat itu MONOTON: semakin besar x, semakin kecil setiap (a[i]-x),
   sehingga semakin sulit jumlahnya tetap non-negatif.

⚠️ TRANSFORMASI INI ADALAH POLA TERPENTING DARI SELURUH TOPIK HARI INI.
   Ia muncul di: rata-rata maksimum, rata-rata segmen (Exercise 4), rasio
   maksimum (Exercise 5), maximum density subgraph, dan seluruh keluarga
   FRACTIONAL PROGRAMMING. Pastikan kamu bisa MENURUNKANNYA, bukan sekadar
   menghafal bentuk akhirnya -- karena bentuk akhirnya berbeda untuk setiap
   soal, tetapi turunannya selalu sama.

⚠️ ARAH: predikatnya true untuk x KECIL, false untuk x besar. Jadi kita
   mencari x TERBESAR yang masih layak:
       if (bisa(mid)) lo = mid; else hi = mid;

⚠️ BATAS: lo = min(a), hi = max(a). Rata-rata dari subhimpunan apa pun pasti
   berada di antara elemen terkecil dan terbesar, jadi rentang ini pasti
   memuat jawabannya dan tidak lebih lebar dari perlu.

CATATAN JUJUR: soal ini sebenarnya punya solusi langsung -- urutkan menurun,
ambil K teratas, hitung rata-ratanya. O(N log N) tanpa binary search sama
sekali. Ia ada di sini SEBAGAI LATIHAN, karena Exercise 4 dan 5 memakai
transformasi yang sama tetapi TIDAK punya solusi langsung. Kalau kamu
menemui soal ini di kontes, pakai solusi langsungnya.

VERIFIKASI SAMPEL 1 (a = [1,3,5,2], K = 2):
   x = 4.0 : (a[i]-x) = -3, -1, 1, -2; dua terbesar 1 dan -1; jumlah 0 >= 0  layak
   x = 4.1 : -3.1, -1.1, 0.9, -2.1; dua terbesar 0.9 dan -1.1; jumlah -0.2   tidak
   jawabannya 4.0, yaitu rata-rata dari 5 dan 3.   ✓

🔄 ALTERNATIVE APPROACHES:
- Solusi langsung: sort menurun, rata-rata K teratas. O(N log N), eksak,
  tanpa masalah presisi. Pilihan yang benar untuk soal ini.
- nth_element (Day 45): O(N), lebih cepat lagi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    if (!(cin >> n >> K)) return 0;
    vector<double> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    double lo = *min_element(a.begin(), a.end());
    double hi = *max_element(a.begin(), a.end());

    vector<double> b(n);
    auto bisa = [&](double x) {
        for (int i = 0; i < n; i++) b[i] = a[i] - x;   // transformasi
        nth_element(b.begin(), b.begin() + K, b.end(), greater<double>());
        double s = 0;
        for (int i = 0; i < K; i++) s += b[i];         // K terbesar
        return s >= 0;
    };

    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (bisa(mid)) lo = mid;                       // layak -> coba lebih besar
        else           hi = mid;
    }

    printf("%.6f\n", lo);
    return 0;
}
