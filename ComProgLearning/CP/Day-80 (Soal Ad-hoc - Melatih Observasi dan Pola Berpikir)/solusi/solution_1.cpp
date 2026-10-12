/*
============================================================
✅ SOLUSI Exercise 1: Menyamakan dengan Biaya Terkecil
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── JAWABANNYA: MEDIAN, BUKAN RATA-RATA ─────────────────────
Sampel 1: {1, 2, 9, 2, 6}
  rata-rata = 4  -> biaya 3 + 2 + 5 + 2 + 2 = 14
  median    = 2  -> biaya 1 + 0 + 7 + 0 + 4 = 12   ✓
Selisihnya nyata, dan naluri "pakai rata-rata" adalah kesalahan
paling umum pada soal jenis ini.

── KENAPA MEDIAN (argumen pergeseran) ──────────────────────
Bayangkan target x bergeser ke kanan sejauh delta kecil.
  biaya BERTAMBAH delta untuk setiap a_i < x
  biaya BERKURANG delta untuk setiap a_i > x
Jadi bergeser ke kanan menguntungkan selama JUMLAH titik di
kanan lebih banyak daripada di kiri.

Titik seimbangnya adalah tempat jumlah titik di kiri sama
dengan di kanan — yaitu MEDIAN.

── KAPAN MEDIAN, KAPAN RATA-RATA ───────────────────────────
Yang menentukan adalah FUNGSI BIAYA:

  sum |a_i - x|      -> MEDIAN
  sum (a_i - x)^2    -> RATA-RATA
  max |a_i - x|      -> TITIK TENGAH (min + maks) / 2

Turunkan sendiri kalau lupa: untuk kuadrat, turunannya
2 * sum(x - a_i) = 0 memberi x = rata-rata.

── JAWABAN TIDAK SELALU UNIK ───────────────────────────────
Kalau n GENAP, SELURUH rentang antara dua nilai tengah
memberikan biaya yang sama persis. Itu konsekuensi langsung
dari argumen pergeseran: di dalam rentang itu, jumlah titik di
kiri dan kanan seimbang, sehingga menggeser tidak mengubah apa
pun.
Karena itu memakai a[n/2] atau a[(n-1)/2] sama-sama benar.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai rata-rata.
2. Lupa long long: 2*10^5 elemen dengan selisih 10^9
   -> total sampai 2*10^14.
3. Menghitung median tanpa mengurutkan.
4. Untuk n = 1, jawabannya 0. Kode di bawah menanganinya
   secara alami.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    // nth_element cukup: kita hanya butuh mediannya, bukan urutan penuh
    nth_element(a.begin(), a.begin() + n / 2, a.end());
    ll m = a[n / 2];

    ll total = 0;
    for (ll x : a) total += llabs(x - m);

    cout << total << '\n';
    return 0;
}
