/*
============================================================
✅ SOLUSI Exercise 2: Tetangga Tidak Berurutan
============================================================
Difficulty: Easy | Kompleksitas: O(n)

── KEMUSTAHILAN ────────────────────────────────────────────
Periksa dengan brute force untuk n kecil:
    n = 1 : [1]                      -> mungkin (tidak ada tetangga)
    n = 2 : [1,2] dan [2,1]          -> keduanya berselisih 1, MUSTAHIL
    n = 3 : keenam permutasi diperiksa -> MUSTAHIL
    n = 4 : [2,4,1,3]                -> mungkin
Jadi hanya n = 2 dan n = 3 yang mustahil.

Menemukan seluruh kasus mustahil dengan brute force jauh lebih
andal daripada menebaknya.

── KONSTRUKSI: DUA BLOK ────────────────────────────────────
Ide: kelompokkan bilangan menjadi GENAP dan GANJIL. Di dalam
tiap kelompok, bilangan berurutan berselisih 2 — aman.

Tersisa satu tempat yang harus diperiksa: TITIK SAMBUNG antara
kedua blok.

── TITIK SAMBUNG MENENTUKAN SEGALANYA ──────────────────────
Ada DUA cara menyusun kedua blok, dan hanya SATU yang benar.

  (a) GANJIL dulu, lalu GENAP:
        n = 5 : 1 3 5 2 4      ✓
        n = 6 : 1 3 5 2 4 6    ✓
        n = 7 : 1 3 5 7 2 4 6  ✓
        n = 4 : 1 3 2 4        ✗  |3 - 2| = 1
      Gagal HANYA di n = 4.

  (b) GENAP dulu, lalu GANJIL:
        n = 4 : 2 4 1 3        ✓
        n = 5 : 2 4 1 3 5      ✓
        n = 6 : 2 4 6 1 3 5    ✓

Kenapa (b) aman: sambungnya adalah bilangan genap TERBESAR
(minimal 4 untuk n >= 4) dan angka 1. Selisihnya minimal 3.
Kenapa (a) rapuh: sambungnya adalah ganjil terbesar dan angka
2. Untuk n = 4 itu 3 dan 2, berselisih tepat 1.

── PELAJARAN METODOLOGIS ───────────────────────────────────
Kalau kamu menguji versi (a) hanya pada n = 5, 6, 7, kamu akan
menyimpulkan ia benar dan submit — lalu WA pada n = 4.

Karena itu: jalankan pemeriksamu untuk SELURUH n dari 1 sampai
200, bukan beberapa n pilihan. Ini persis pelajaran Day 79
tentang generator, diterapkan pada soal constructive.

Bug ini benar-benar saya temukan saat menulis template hari
ini — versi pertama memakai (a) dan pemeriksa melaporkan tepat
satu kegagalan.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai urutan blok yang salah.
2. Tidak memeriksa titik sambung secara eksplisit.
3. Menguji beberapa n saja.
4. Lupa n = 1 (yang justru MUNGKIN, bukan mustahil).
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

    if (n == 2 || n == 3) { cout << -1 << '\n'; return 0; }

    // GENAP dulu, lalu GANJIL. Titik sambungnya (genap terbesar, 1)
    // berselisih minimal 3 untuk n >= 4.
    bool pertama = true;
    for (int i = 2; i <= n; i += 2) { cout << (pertama ? "" : " ") << i; pertama = false; }
    for (int i = 1; i <= n; i += 2) { cout << (pertama ? "" : " ") << i; pertama = false; }
    cout << '\n';

    return 0;
}
