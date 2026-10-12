/*
============================================================
✅ SOLUSI Exercise 3: Pengaruh Rentang Generator
============================================================
Difficulty: Medium | Kompleksitas: O(B) waktu, O(1) memori

── KAPAN KODE SALAH ITU TERLIHAT SALAH ─────────────────────
Kode salah mengambil dua elemen terbesar tanpa memeriksa
apakah nilainya berbeda. Ia berbeda dari jawaban benar tepat
ketika DUA ELEMEN TERBESAR BERNILAI SAMA — yaitu ketika nilai
maksimum array muncul MINIMAL DUA KALI.

Merumuskan syarat ini dengan tepat adalah setengah dari soal.

── MENGHITUNG PELUANGNYA ───────────────────────────────────
Kelompokkan seluruh array menurut nilai maksimumnya.

  banyak array dengan seluruh elemen <= m          = m^N
  banyak array dengan maksimum TEPAT m             = m^N - (m-1)^N
  di antaranya, yang maksimumnya muncul SEKALI     = N * (m-1)^(N-1)
      (pilih posisi mana yang bernilai m: N cara;
       sisanya bebas asal < m: (m-1)^(N-1) cara)

  jadi yang maksimumnya muncul >= 2 kali:
      (m^N - (m-1)^N) - N * (m-1)^(N-1)

Jumlahkan atas m dari 1 sampai B, lalu bagi B^N.

── MENGHINDARI BILANGAN RAKSASA ────────────────────────────
B^N dengan B = 10^6 dan N = 60 adalah bilangan berukuran ratusan
digit. Menghitung pembilang dan pembagi secara terpisah lalu
membaginya MUSTAHIL dengan tipe data biasa.

Solusinya: bekerja dengan RASIO sejak awal. Bagi setiap suku
dengan B^N secara langsung:

      (m/B)^N - ((m-1)/B)^N - N * ((m-1)/B)^(N-1) / B

Setiap suku sekarang berupa bilangan antara 0 dan 1, dan
pow() menanganinya tanpa masalah.

Trik "bagi dulu, jangan hitung lalu bagi" ini sangat sering
berguna pada soal peluang.

── HASILNYA ────────────────────────────────────────────────
  N = 2, B = 3        -> 33,333333 %
  N = 2, B = 1000000  -> 0,000100 %

BUG YANG SAMA. GENERATOR BERBEDA. KESIMPULAN BERLAWANAN.

Dengan rentang 1..3, sepertiga masukan acak akan menangkap
bugnya — kamu pasti menemukannya. Dengan rentang 1..10^6, kamu
butuh sekitar sejuta kasus untuk punya peluang wajar
menemukannya; dengan 20.000 kasus kamu akan menyimpulkan
kodemu benar dan submit, lalu WA.

── PELAJARAN UTAMA HARI INI ────────────────────────────────
Generator yang bagus DIRANCANG untuk memecahkan kodemu, bukan
"acak saja". Pilih rentang berdasarkan apa yang ingin kamu
pecahkan:

  tie-break, nilai berulang -> rentang SANGAT KECIL (0..3)
  interval bertabrakan      -> koordinat kecil (0..15)
  overflow                  -> nilai MAKSIMUM (10^18)
  presisi pecahan           -> dua nilai hampir sama
  kasus tepi                -> n = 1, n = 2, semua sama

── JEBAKAN ─────────────────────────────────────────────────
1. Menghitung m^N sebagai bilangan bulat. Meluap total.
2. Memakai float alih-alih double. Presisinya tidak cukup.
3. Lupa kasus m = 1: (m-1)^(N-1) = 0^(N-1) = 0 untuk N >= 2,
   sehingga sukunya nol. pow(0, k) dengan k > 0 aman.
4. Salah merumuskan syaratnya, misalnya "ada dua elemen sama"
   alih-alih "dua elemen TERBESAR sama".
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll N, B;
    if (!(cin >> N >> B)) return 0;

    // Bekerja dengan RASIO sejak awal agar tidak meluap.
    long double total = 0;
    for (ll m = 1; m <= B; m++) {
        long double r  = (long double)m / B;
        long double rm = (long double)(m - 1) / B;

        long double maksTepatM  = powl(r, (long double)N) - powl(rm, (long double)N);
        long double munculSekali = (long double)N * powl(rm, (long double)(N - 1)) / B;

        total += maksTepatM - munculSekali;
    }

    cout << fixed << setprecision(6) << (double)(total * 100.0L) << '\n';
    return 0;
}
