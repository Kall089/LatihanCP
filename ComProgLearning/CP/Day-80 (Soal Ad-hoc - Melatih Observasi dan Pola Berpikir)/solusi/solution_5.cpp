/*
============================================================
✅ SOLUSI Exercise 5: Menemukan Rumus dari Barisan
============================================================
Difficulty: Hard | Kompleksitas: O(n) waktu, O(1) memori

── PROSES PENEMUAN (yang seharusnya kamu jalani) ───────────
Jangan menurunkan rumusnya dari nol. Lakukan ini:

(1) brute force seluruh permutasi untuk n = 1..8:
        0  1  2  9  44  265  1854  14833

(2) cetak selisih dan rasio:
        selisih 1 : 1  1  7  35  221  1589  12979
        selisih 2 : 0  6  28 186 1368 11390
        rasio     : 2.000 4.500 4.889 6.023 6.996 8.001

(3) baca polanya:
    - selisih pertama tidak tetap -> bukan linear
    - selisih kedua tidak tetap   -> bukan kuadrat
    - rasio tidak tetap           -> bukan eksponensial
    - RASIO MENDEKATI n           -> curigai FAKTORIAL

(4) dugaan: D(n) = n * D(n-1) + sesuatu kecil.
        4 * 2 = 8,  D(4) = 9   -> selisih +1
        5 * 9 = 45, D(5) = 44  -> selisih -1
        6 * 44 = 264, D(6) = 265 -> selisih +1
    Polanya berselang-seling: (-1)^n.

(5) rumus: D(n) = n * D(n-1) + (-1)^n,  dengan D(0) = 1

(6) VERIFIKASI untuk n lebih besar dari yang dipakai menebak.
    Template hari ini memeriksanya untuk n = 1..8: cocok.

── KENAPA LANGKAH (6) WAJIB ────────────────────────────────
Kalau kamu menebak dari 5 suku lalu langsung submit, kamu
sedang berjudi. Tiga suku pertama bisa cocok dengan ratusan
rumus berbeda. Verifikasi untuk n yang LEBIH BESAR adalah
pemisah antara tebakan dan kesimpulan.

── ARITMETIKA MODULAR DENGAN SUKU NEGATIF ──────────────────
Rumusnya memuat (-1)^n, sehingga bisa mengurangi. Dalam
aritmetika modular, hasil pengurangan bisa negatif dan operator
% di C++ mempertahankan tandanya.

Kebiasaan yang menyelamatkan:
        d = (n * d + tambahan + MOD) % MOD;
Menambahkan MOD sebelum mengambil sisa membuat hasilnya selalu
non-negatif tanpa perlu percabangan.

── BATASAN n SAMPAI 10^7 ───────────────────────────────────
Itu berarti kita butuh rekurensi satu sapuan, bukan rumus
dengan penjumlahan bersarang. Rekurensi di atas O(n) dengan
memori O(1) — cukup menyimpan satu nilai sebelumnya.

Ada juga rumus tertutup D(n) = n! * sum (-1)^k / k!, tetapi ia
membutuhkan invers modular dan justru lebih lambat serta lebih
rawan bug.

── KASUS TEPI ──────────────────────────────────────────────
    D(1) = 0   (satu bilangan pasti di posisinya sendiri)
    D(2) = 1
Rekurensi menanganinya secara alami dari D(0) = 1:
    D(1) = 1*1 + (-1) = 0   ✓
    D(2) = 2*0 + (+1) = 1   ✓
Selalu periksa n = 1 dan n = 2 secara terpisah — rumus yang
benar untuk n besar sering gagal di situ.

── JEBAKAN ─────────────────────────────────────────────────
1. Menebak dari terlalu sedikit suku.
2. Tidak memverifikasi untuk n lebih besar.
3. Lupa menangani nilai negatif dalam modulo.
4. Memakai rumus tertutup yang butuh invers modular padahal
   rekurensi jauh lebih sederhana.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    if (!(cin >> n)) return 0;

    ll d = 1;                                   // D(0) = 1
    for (ll i = 1; i <= n; i++) {
        ll tambahan = (i % 2 == 0) ? 1 : MOD - 1;   // (-1)^i, dinyatakan positif
        d = (i % MOD * d + tambahan) % MOD;
    }

    cout << d << '\n';
    return 0;
}
