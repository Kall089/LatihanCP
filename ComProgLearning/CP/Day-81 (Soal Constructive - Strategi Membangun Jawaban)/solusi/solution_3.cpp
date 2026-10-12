/*
============================================================
✅ SOLUSI Exercise 3: Tepat K Bergeser
============================================================
Difficulty: Medium | Kompleksitas: O(n)

── KEMUSTAHILAN: k = 1 ─────────────────────────────────────
Kalau kamu memindahkan elemen x dari posisinya, ia menempati
posisi milik elemen lain, katakanlah y. Maka y juga terusir
dari posisinya, sehingga y ikut bergeser.
Jadi jumlah posisi yang bergeser tidak pernah bisa tepat 1.

Formalnya: himpunan posisi yang bergeser membentuk gabungan
siklus, dan siklus terpendek yang bukan titik tetap berukuran
2. Jadi k = 1 mustahil, sedangkan k = 0 dan k >= 2 mungkin.

Verifikasi dengan brute force untuk n <= 7 memastikan tidak
ada nilai k lain yang mustahil.

── KONSTRUKSI: MULAI DARI IDENTITAS ────────────────────────
Strategi 3 dari teori: mulai dari sesuatu yang jelas benar,
lalu perbaiki.

Permutasi identitas memberi tepat 0 posisi bergeser. Sekarang
naikkan menjadi tepat k.

Kalau kita MEMBALIK blok k elemen pertama:
  - k GENAP : setiap elemen berpasangan dengan elemen lain,
              semuanya bergeser -> tepat k  ✓
  - k GANJIL: elemen TENGAH tetap di tempatnya, sehingga hanya
              k - 1 yang bergeser  ✗

── MENANGANI k GANJIL ──────────────────────────────────────
Setelah membalik blok berukuran k ganjil, elemen tengah
(indeks k/2) masih di tempatnya. Tukar ia dengan salah satu
elemen lain di dalam blok — misalnya elemen di indeks k-1.

Setelah pertukaran itu, elemen tengah pasti bergeser. Yang
perlu diperiksa: apakah elemen di indeks k-1 tetap bergeser?
Ya, karena ia sekarang memuat nilai yang tadinya di tengah,
dan nilai itu berbeda dari k (isi aslinya) selama k >= 3.

Untuk k = 1 kita sudah mengembalikan -1, jadi kasus k ganjil
terkecil yang diproses adalah k = 3, dan di situ konstruksinya
sah.

── CARA MENGUJI ────────────────────────────────────────────
Uji SELURUH pasangan (n, k) dengan n dari 1 sampai 60 dan k
dari 0 sampai n. Itu sekitar 1.800 kasus dan berjalan seketika.
Untuk tiap kasus, periksa: hasilnya permutasi sah, dan jumlah
posisi bergesernya tepat k.
Template hari ini melakukannya: 0 kegagalan.

Menguji seluruh KOMBINASI parameter (bukan sampel) adalah
kebiasaan yang menangkap kesalahan kasus tepi seperti k = 0,
k = n, dan k ganjil terkecil.

── JEBAKAN ─────────────────────────────────────────────────
1. Lupa k = 1 mustahil.
2. Membalik blok k ganjil tanpa menangani elemen tengah.
3. Lupa k = 0 (identitas, jangan lakukan apa-apa).
4. Menguji beberapa (n, k) pilihan.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    if (k == 1) { cout << -1 << '\n'; return 0; }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);                 // identitas: 0 bergeser

    // balik blok k pertama: k genap -> tepat k bergeser
    for (int i = 0; i < k / 2; i++) swap(p[i], p[k - 1 - i]);

    // k ganjil: elemen tengah masih di tempatnya, tukar dengan ujung blok
    if (k % 2 == 1 && k >= 3) swap(p[k / 2], p[k - 1]);

    for (int i = 0; i < n; i++) cout << p[i] << " \n"[i == n - 1];
    return 0;
}
