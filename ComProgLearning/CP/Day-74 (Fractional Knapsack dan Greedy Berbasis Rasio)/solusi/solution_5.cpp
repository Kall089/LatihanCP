/*
============================================================
✅ SOLUSI Exercise 5: Rasio Terbaik
============================================================
Difficulty: Hard | Kompleksitas: O(100 * n log n)

── KENAPA GREEDY RASIO GAGAL ───────────────────────────────
Naluri: urutkan menurut a[i]/b[i] dan ambil K teratas.
Sampel 1: mesin (1,1) (2,1) (3,4), rasio 1, 2, 0.75, K = 2.
  K teratas menurut rasio : (2,1) dan (1,1)
    -> (2+1)/(1+1) = 1.5   kebetulan benar di sini
Tetapi kebetulan itu tidak bertahan. Rasio sebuah GABUNGAN
bukan gabungan sederhana dari rasio individual: menambahkan
mesin berasio rendah tetapi ber-b sangat kecil bisa menaikkan
rasio total, dan sebaliknya.
Buat sendiri contoh tandingannya dengan generator acak dan
brute force C(n,K) — itu latihan yang sangat berharga.

── MENGUBAH OPTIMASI MENJADI KELAYAKAN ─────────────────────
Alih-alih mencari nilai maksimum secara langsung, tanyakan:
  "apakah ada pilihan K mesin dengan rasio >= x?"

  sum(a) / sum(b) >= x
  <=> sum(a) >= x * sum(b)          (b positif, jadi aman)
  <=> sum(a) - x * sum(b) >= 0
  <=> sum( a[i] - x * b[i] ) >= 0

Sisi kanan bisa dimaksimalkan LANGSUNG: hitung
d[i] = a[i] - x*b[i], ambil K terbesar, jumlahkan.
Kalau jumlahnya >= 0, rasio x bisa dicapai.

Perhatikan keindahannya: pembagian hilang sama sekali, dan
soal "pilih K dengan rasio terbaik" berubah menjadi "pilih K
terbesar dari sebuah array" — yang trivial.

Teknik ini dikenal sebagai fractional programming atau metode
Dinkelbach. Bentuk a[i] - x*b[i] adalah generalisasi dari trik
a[i] - x pada soal "maksimalkan rata-rata" di Day 51.

── KENAPA PREDIKATNYA MONOTON ──────────────────────────────
Semakin besar x, setiap d[i] = a[i] - x*b[i] semakin kecil
(karena b[i] > 0), sehingga jumlah K terbesar juga semakin
kecil. Predikat "layak" berubah dari true menjadi false tepat
satu kali. Itulah syarat binary search.

── PRESISI ─────────────────────────────────────────────────
Pakai jumlah ITERASI TETAP (100), bukan while (hi - lo > eps).
Alasannya (Day 51):
  - 100 iterasi mengecilkan interval dengan faktor 2^100,
    jauh melampaui presisi double — hasilnya pasti konvergen
  - while dengan epsilon bisa berputar selamanya kalau
    (lo+hi)/2 sudah tidak bisa membedakan lo dan hi
Batas atas hi: rasio maksimum tidak melebihi max(a)/min(b),
di sini paling besar 10^4/1 = 10^4. Memakai 1e9 juga aman,
hanya membuang beberapa iterasi.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai greedy rasio langsung.
2. Memakai while dengan epsilon.
3. Mengambil K TERKECIL alih-alih K terbesar dari d.
4. Lupa bahwa nth_element lebih cepat dari sort penuh di sini
   (O(n) vs O(n log n) per iterasi) — dipakai di kode bawah.
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
    vector<double> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    // layak(x) : adakah K mesin dengan sum(a) - x*sum(b) >= 0 ?
    vector<double> d(n);
    auto layak = [&](double x) {
        for (int i = 0; i < n; i++) d[i] = a[i] - x * b[i];
        // ambil K terbesar: taruh K terbesar di depan
        nth_element(d.begin(), d.begin() + K, d.end(), greater<double>());
        double s = 0;
        for (int i = 0; i < K; i++) s += d[i];
        return s >= 0;
    };

    double lo = 0, hi = 1e9;
    for (int it = 0; it < 100; it++) {            // iterasi TETAP
        double mid = (lo + hi) / 2;
        if (layak(mid)) lo = mid;
        else            hi = mid;
    }

    cout << fixed << setprecision(6) << lo << '\n';
    return 0;
}
