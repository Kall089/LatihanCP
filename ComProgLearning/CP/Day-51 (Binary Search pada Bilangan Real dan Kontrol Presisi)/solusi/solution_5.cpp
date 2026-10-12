/*
============================================================
✅ Solution 5: Rasio Terbaik
============================================================
Approach: Fractional programming (Dinkelbach / parametric search)
Complexity: Time O(100 * N) | Space O(N)
Key Insight: Transformasi yang sama dengan Exercise 3, tetapi diterapkan
             pada RASIO alih-alih rata-rata. Rata-rata sebenarnya hanya
             kasus khusus rasio dengan seluruh penyebut bernilai 1.

📖 TURUNAN TRANSFORMASINYA:
       (jumlah p terpilih) / (jumlah q terpilih) >= x
   <=> jumlah p - x * jumlah q >= 0            [kalikan kedua sisi dengan jumlah q]
   <=> jumlah dari (p[i] - x * q[i]) >= 0

   Predikatnya: ambil K nilai (p[i] - x*q[i]) TERBESAR, cek apakah jumlahnya
   tidak negatif.

⚠️ LANGKAH KEDUA HANYA SAH KARENA SELURUH q[i] POSITIF.
   Mengalikan sebuah pertidaksamaan dengan bilangan NEGATIF akan MEMBALIK
   tandanya. Kalau soal mengizinkan q[i] <= 0, transformasi ini runtuh dan
   kamu butuh pendekatan lain. Selalu periksa syarat ini sebelum memakainya
   -- ia mudah terlewat karena tidak muncul di rumus akhirnya.

⚠️ MONOTONISITAS: semakin besar x, semakin kecil setiap (p[i] - x*q[i])
   (sekali lagi karena q[i] > 0), sehingga semakin sulit jumlahnya tetap
   non-negatif. Predikatnya menurun, dan kita mencari x TERBESAR yang layak.

⚠️ PEMBULATAN AKHIR ADALAH JEBAKAN NYATA.
   Jawaban eksaknya mungkin 2.5, tetapi binary search bisa menghasilkan
   2.4999999999. Mengalikan 100 lalu memakai (int) akan memotong menjadi
   249, bukan 250.
   Solusinya: pakai pembulatan ke terdekat, bukan pemotongan:
       (ll)(x * 100 + 0.5)
   atau lebih baik lagi, llround(x * 100).
   Ini kesalahan yang sangat sering terjadi pada soal yang meminta jawaban
   bilangan bulat dari perhitungan real.

⚠️ BATAS ATAS: rasio maksimum yang mungkin adalah max(p[i]) / min(q[i]),
   yang dengan batasan soal bisa mencapai 10^6. Memakai hi = 10^6 + 1 aman.
   Memakai hi terlalu kecil akan memotong jawaban.

VERIFIKASI SAMPEL 1 (p = [1,2,3], q = [1,1,1], K = 2):
   Karena seluruh q = 1, ini persis soal rata-rata: pilih 3 dan 2,
   rasionya (3+2)/(1+1) = 2.5 -> 250   ✓
VERIFIKASI SAMPEL 2 (p = [7,1], q = [2,1], K = 1):
   Pilih benda pertama: 7/2 = 3.5 -> 350   ✓

🔄 ALTERNATIVE APPROACHES:
- Metode Dinkelbach: alih-alih binary search, iterasi
  x_{t+1} = (jumlah p terpilih) / (jumlah q terpilih) berdasarkan pilihan
  optimal pada x_t. Konvergen dalam sedikit iterasi (biasanya < 10), jauh
  lebih cepat daripada 100 iterasi binary search. Sedikit lebih rumit
  tetapi patut diketahui.
- Kalau K = N (harus memilih semuanya), jawabannya langsung sum(p)/sum(q)
  tanpa pencarian apa pun.
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
    vector<double> p(n), q(n);
    for (int i = 0; i < n; i++) cin >> p[i] >> q[i];

    vector<double> b(n);
    auto bisa = [&](double x) {
        for (int i = 0; i < n; i++) b[i] = p[i] - x * q[i];   // syarat: q[i] > 0
        nth_element(b.begin(), b.begin() + K, b.end(), greater<double>());
        double s = 0;
        for (int i = 0; i < K; i++) s += b[i];
        return s >= 0;
    };

    double lo = 0, hi = 1e6 + 1;
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (bisa(mid)) lo = mid;
        else           hi = mid;
    }

    cout << llround(lo * 100) << '\n';        // BULATKAN, jangan potong
    return 0;
}
