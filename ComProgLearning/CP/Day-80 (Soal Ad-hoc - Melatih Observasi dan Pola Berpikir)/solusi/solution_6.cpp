/*
============================================================
✅ SOLUSI Exercise 6: Membalik Tanda
============================================================
Difficulty: Hard | Kompleksitas: O(n log n)

── DUA TAHAP ───────────────────────────────────────────────
TAHAP 1 — yang jelas menguntungkan.
Selama masih ada bilangan NEGATIF dan masih ada operasi,
balik negatif dengan NILAI MUTLAK TERBESAR lebih dulu.
Membalik -x menjadi +x menambah jumlah sebesar 2x, jadi kita
ingin x sebesar mungkin.

Urutkan menaik, lalu sapu dari kiri: negatif dengan nilai
mutlak terbesar berada paling kiri.

TAHAP 2 — sisa operasi setelah tidak ada negatif.
Di sinilah inti soal. Kata "TEPAT K" berarti kita tidak boleh
berhenti; sisa operasi harus dihabiskan.

── PARITAS MENYELESAIKAN TAHAP 2 ───────────────────────────
Kalau sisa operasi GENAP: balik satu elemen yang sama bolak-
balik. Dua pembalikan mengembalikannya seperti semula, jadi
biayanya NOL. Tidak ada kerugian.

Kalau sisa operasi GANJIL: kita terpaksa membalik satu elemen
non-negatif dan membiarkannya negatif. Kerugiannya 2 dikali
nilai elemen itu, jadi pilih elemen dengan NILAI TERKECIL.

Perhatikan bahwa elemen terkecil itu dicari SETELAH tahap 1,
yaitu pada array yang sudah dibalik sebagian. Mencarinya pada
array asli adalah kesalahan yang mudah dibuat.

── PERAN NILAI NOL ─────────────────────────────────────────
Kalau setelah tahap 1 ada elemen bernilai NOL, paritas berhenti
menjadi masalah: membalik nol tidak mengubah apa pun, jadi sisa
operasi ganjil pun tidak merugikan.
Kode di bawah menanganinya secara alami: nilai minimumnya
adalah 0, sehingga pengurangannya 2 * 0 = 0.

── VERIFIKASI SAMPEL ───────────────────────────────────────
Sampel 1: {4,2,3}, K=1. Tidak ada negatif.
  sisa 1 (ganjil) -> balik yang terkecil (2)
  jumlah 4 + 3 - 2 = 5  ✓
Sampel 2: {4,2,3}, K=2. Tidak ada negatif.
  sisa 2 (genap) -> tanpa kerugian
  jumlah 9  ✓
Dua sampel dengan data sama dan K berbeda satu, jawabannya
berbeda 4. Itu menunjukkan bahwa paritas benar-benar penting.

Sampel 3: {-1,-2,-3,4}, K=3.
  urut: -3, -2, -1, 4
  balik -3 -> 3 (K=2), balik -2 -> 2 (K=1), balik -1 -> 1 (K=0)
  jumlah 3 + 2 + 1 + 4 = 10  ✓
  sisa 0, tidak ada kerugian.

── JEBAKAN ─────────────────────────────────────────────────
1. Berhenti sebelum K habis. Soal meminta TEPAT K.
2. Membalik negatif dengan nilai mutlak TERKECIL dulu.
3. Mencari elemen minimum pada array ASLI, bukan setelah
   tahap 1.
4. Lupa bahwa nol membuat paritas tidak relevan.
5. Lupa long long: 2*10^5 elemen dengan nilai 10^9.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll K;
    if (!(cin >> n >> K)) return 0;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    sort(a.begin(), a.end());                   // negatif terbesar di kiri

    // TAHAP 1: balik negatif, mulai dari nilai mutlak terbesar
    for (int i = 0; i < n && K > 0 && a[i] < 0; i++) {
        a[i] = -a[i];
        K--;
    }

    ll total = 0, terkecil = LLONG_MAX;
    for (ll x : a) { total += x; terkecil = min(terkecil, x); }

    // TAHAP 2: sisa operasi ganjil -> korbankan elemen terkecil
    if (K % 2 == 1) total -= 2 * terkecil;

    cout << total << '\n';
    return 0;
}
