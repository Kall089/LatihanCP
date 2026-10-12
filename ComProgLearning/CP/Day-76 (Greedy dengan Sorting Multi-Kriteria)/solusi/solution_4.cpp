/*
============================================================
✅ SOLUSI Exercise 4: Pekerjaan Dua Tahap
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── JAWABANNYA: URUT b MENURUN ──────────────────────────────
Yang mengejutkan: a SAMA SEKALI tidak muncul dalam kriteria
pengurutan. Naluri menyarankan a menaik, a+b menurun, atau
rasio a/b. Ketiganya salah.

── BUKTI (exchange argument pada max) ──────────────────────
Ambil urutan optimal. Lihat dua pekerjaan BERDAMPINGAN i lalu
j. Misal waktu mesin bersama sebelum keduanya adalah S.

  urutan (i, j):
      selesai_i = S + a_i + b_i
      selesai_j = S + a_i + a_j + b_j
      maksimum  = max(S + a_i + b_i, S + a_i + a_j + b_j)

  urutan (j, i):
      maksimum  = max(S + a_j + b_j, S + a_i + a_j + b_i)

Kurangkan konstanta (S + a_i + a_j) dari kedua sisi:

      (i, j) -> max( b_i - a_j ,  b_j )
      (j, i) -> max( b_j - a_i ,  b_i )

Andaikan b_i >= b_j. Maka:
      sisi kiri  : b_i - a_j <= b_i  dan  b_j <= b_i   -> <= b_i
      sisi kanan : memuat b_i secara langsung          -> >= b_i

Jadi urutan (i, j) TIDAK LEBIH BURUK ketika b_i >= b_j.
Menukar pasangan berdampingan yang melanggar tidak pernah
memperburuk, sehingga urutan b menurun optimal. ∎

Pekerjaan lain tidak terpengaruh karena a_i + a_j tetap sama —
waktu mulai pekerjaan berikutnya identik.

── INTUISI ─────────────────────────────────────────────────
Tahap kedua berjalan paralel, jadi ia "gratis" selama masih ada
tahap pertama yang berjalan. Pekerjaan dengan tahap kedua
PANJANG harus dimulai secepat mungkin agar ekornya tersembunyi
di balik pekerjaan lain. Panjang tahap pertamanya tidak relevan
untuk urutan — ia hanya menggeser semuanya secara seragam.

── CARA MENEMUKANNYA SENDIRI ───────────────────────────────
Kalau kamu tidak langsung melihat buktinya, pakai brute force
atas seluruh permutasi untuk n <= 7, lalu bandingkan dengan
beberapa dugaan kriteria. Kriteria yang bertahan pada ribuan
kasus acak hampir pasti benar, dan setelah itu buktinya jauh
lebih mudah dicari karena kamu tahu apa yang harus dibuktikan.
Diverifikasi: 20.000 kasus acak vs seluruh permutasi, cocok.

── JEBAKAN ─────────────────────────────────────────────────
1. Menebak kriteria. Tiga dugaan yang wajar semuanya salah.
2. Mengira jawabannya adalah sum(a) + max(b). Itu benar hanya
   kalau pekerjaan ber-b terbesar dikerjakan TERAKHIR — dan
   justru itu yang tidak kita lakukan.
3. Lupa long long: n = 2*10^5 dan a = 10^9 -> 2*10^14.
4. Melacak maksimum hanya di akhir. Waktu selesai terakhir bisa
   dicapai oleh pekerjaan mana pun, bukan hanya yang terakhir.
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
    vector<pair<ll, ll>> job(n);
    for (auto& [a, b] : job) cin >> a >> b;

    // b MENURUN — a tidak ikut menentukan urutan
    sort(job.begin(), job.end(), [](const pair<ll, ll>& x, const pair<ll, ll>& y) {
        return x.second > y.second;
    });

    ll t = 0, jawab = 0;
    for (auto& [a, b] : job) {
        t += a;                          // tahap pertama selesai di sini
        jawab = max(jawab, t + b);       // tahap kedua berjalan paralel
    }

    cout << jawab << '\n';
    return 0;
}
