/*
============================================================
✅ SOLUSI Exercise 6: Barisan dengan Selisih yang Ditentukan
============================================================
Difficulty: Hard | Kompleksitas: O(n)

── MENYELESAIKAN DUA UJUNG EKSTREM DULU ────────────────────
Strategi umum untuk soal constructive berparameter: selesaikan
kasus parameter TERKECIL dan TERBESAR lebih dulu, lalu cari
cara menggabungkannya untuk nilai di antaranya.

  k = 1        : 1 2 3 ... n
                 seluruh selisih bernilai 1, jadi tepat satu
                 nilai berbeda.
  k maksimum   : pola melompat (zig-zag) dari kedua ujung.

── BATAS ATAS UNTUK k ──────────────────────────────────────
Ada n-1 pasangan tetangga, jadi paling banyak n-1 selisih
berbeda. Selain itu selisih selalu antara 1 dan n-1, sehingga
paling banyak n-1 nilai yang mungkin.
Jadi k <= n - 1. Kalau k >= n, jawabannya -1.

Kasus khusus n = 1: tidak ada tetangga sama sekali, jadi
himpunan selisihnya KOSONG dan k harus 0. Karena batasan soal
memberi k >= 1, n = 1 selalu -1.

Sampel 3 (n = 2, k = 2) menguji batas ini: n-1 = 1, jadi k = 2
mustahil.

── POLA MELOMPAT UNTUK k MAKSIMUM ──────────────────────────
Mulai dari 1, lalu bolak-balik ke ujung yang berlawanan:
    1, n, 2, n-1, 3, n-2, ...
Selisih berturut-turut:
    n-1, n-2, n-3, ..., 2, 1
Seluruhnya berbeda — tepat n-1 nilai. Itu maksimum.

Untuk n = 5: 1 5 2 4 3, selisihnya 4 3 2 1 -> 4 nilai berbeda.
Cocok dengan sampel 1.

── MENGGABUNGKAN UNTUK k DI ANTARANYA ──────────────────────
Ide: pakai pola melompat hanya untuk BAGIAN AWAL, secukupnya
untuk menghasilkan k-1 selisih berbeda, lalu lanjutkan dengan
pola berurutan yang seluruh selisihnya bernilai 1.

Lebih tepatnya: jalankan pola melompat untuk k suku pertama.
Itu menghasilkan k-1 selisih yang seluruhnya berbeda, yaitu
    n-1, n-2, ..., n-k+1
Setelah k suku, bilangan yang TERSISA membentuk rentang
kontigu. Cetak sisanya secara berurutan (menaik atau menurun,
bergantung di mana pola melompat berhenti).

── TITIK SAMBUNG: BAGIAN YANG PALING RAWAN ─────────────────
Selisih antara suku ke-k dan suku ke-(k+1) HARUS bernilai 1,
agar tidak memperkenalkan nilai baru.

Kalau pola melompat berhenti setelah mengambil dari ujung
KIRI, suku terakhirnya adalah bilangan terkecil yang tersisa
dikurangi satu, dan kita lanjutkan MENAIK dari sisa terkecil.
Kalau berhenti setelah mengambil dari ujung KANAN, suku
terakhirnya tepat di atas sisa terbesar, dan kita lanjutkan
MENURUN dari sisa terbesar.

Dalam kedua kasus selisih sambungnya tepat 1. Kode di bawah
melacak batas kiri dan kanan yang tersisa, sehingga
penanganannya menjadi otomatis.

── PEMERIKSA ───────────────────────────────────────────────
Validasi tiga hal: hasilnya permutasi 1..n yang sah, dan
jumlah nilai selisih berbeda tepat k.
Jalankan untuk SELURUH pasangan (n, k) dengan n sampai 50 dan
k dari 1 sampai n.

── JEBAKAN ─────────────────────────────────────────────────
1. Lupa batas k <= n-1.
2. Lupa n = 1.
3. Titik sambung memperkenalkan selisih baru.
4. Melanjutkan ke arah yang salah setelah pola melompat.
5. Menguji beberapa (n, k) saja.
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

    if (k > n - 1) { cout << -1 << '\n'; return 0; }   // termasuk n = 1

    vector<int> p;
    p.reserve(n);

    int lo = 1, hi = n;
    // pola melompat untuk k suku pertama -> menghasilkan k-1 selisih berbeda
    for (int t = 0; t < k; t++) {
        if (t % 2 == 0) p.push_back(lo++);
        else            p.push_back(hi--);
    }

    // sisanya kontigu: lanjutkan ke arah yang membuat selisih sambung = 1
    if (k % 2 == 0) {
        // berhenti setelah mengambil dari kanan -> lanjut MENURUN dari hi
        for (int x = hi; x >= lo; x--) p.push_back(x);
    } else {
        // berhenti setelah mengambil dari kiri -> lanjut MENAIK dari lo
        for (int x = lo; x <= hi; x++) p.push_back(x);
    }

    for (int i = 0; i < n; i++) cout << p[i] << " \n"[i == n - 1];
    return 0;
}
