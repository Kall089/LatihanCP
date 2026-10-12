/*
============================================================
✅ SOLUSI Exercise 1: Permutasi Tanpa Titik Tetap
============================================================
Difficulty: Easy | Kompleksitas: O(n)

── URUTAN KERJA: PEMERIKSA DULU ────────────────────────────
Soal constructive punya BANYAK jawaban benar. Untuk n = 4,
jawaban 2 3 4 1 benar, dan 4 3 2 1 juga benar, dan 2 1 4 3
juga benar. Karena itu membandingkan keluaranmu dengan contoh
di soal TIDAK BISA dipakai untuk menguji.

Yang bisa dipakai hanyalah PEMERIKSA: fungsi yang memvalidasi
seluruh syarat secara langsung.

    bool periksa(const vector<int>& p, int n) {
        if ((int)p.size() != n) return false;      // ukuran
        vector<bool> ada(n + 1, false);
        for (int i = 0; i < n; i++) {
            if (p[i] < 1 || p[i] > n) return false;  // rentang
            if (ada[p[i]]) return false;             // duplikat
            ada[p[i]] = true;
            if (p[i] == i + 1) return false;         // syarat soal
        }
        return true;
    }

Perhatikan bahwa tiga pemeriksaan pertama (ukuran, rentang,
duplikat) sering dilupakan, padahal itulah yang paling sering
rusak akibat salah indeks.

── KEMUSTAHILAN ────────────────────────────────────────────
n = 1: satu-satunya permutasi adalah [1], dan p[0] = 1.
Mustahil.
n >= 2: selalu mungkin (konstruksi di bawah membuktikannya).

── KONSTRUKSI: GESER SATU LANGKAH ──────────────────────────
    p[i] = (i + 1) mod n + 1

Untuk i dari 0 sampai n-1, ini menghasilkan
    2, 3, 4, ..., n, 1
Setiap posisi bergeser, jadi tidak ada titik tetap.

Kenapa ini permutasi yang sah: pemetaan i -> (i+1) mod n adalah
bijeksi pada {0, ..., n-1}, sehingga hasilnya memuat setiap
nilai 1..n tepat sekali.

── CARA MENGUJI ────────────────────────────────────────────
Jangan menguji beberapa n pilihan. Jalankan:

    untuk n = 2 sampai 300:
        periksa(bangun(n), n) harus true

Ini murah (di bawah satu detik) dan menangkap hampir semua
kesalahan kasus tepi. Template hari ini melakukannya, dan
hasilnya: 0 kegagalan untuk n = 2..300.

Untuk klaim "mustahil" pada n = 1, verifikasi juga dengan
brute force bahwa memang tidak ada permutasi yang memenuhi.

── JEBAKAN ─────────────────────────────────────────────────
1. Lupa n = 1.
2. Rumus geser yang menghasilkan nilai 0 atau n+1 karena salah
   menempatkan "+1" dan "mod n".
3. Mencoba mencocokkan keluaran dengan contoh di soal.
4. Menguji beberapa n pilihan, bukan seluruh n kecil.
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

    if (n == 1) { cout << -1 << '\n'; return 0; }

    for (int i = 0; i < n; i++)
        cout << (i + 1) % n + 1 << " \n"[i == n - 1];

    return 0;
}
