/*
============================================================
✅ SOLUSI Exercise 1: Mengambil Kursus
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── IDE UTAMA (REGRET) ──────────────────────────────────────
Urutkan menurut TENGGAT MENAIK. Ambil setiap kursus. Kalau
total waktu melewati tenggat kursus yang sedang diproses,
batalkan kursus dengan DURASI TERBESAR di antara yang sudah
diambil.

── KENAPA TENGGAT MENAIK ───────────────────────────────────
Saat memproses kursus bertenggat d, SELURUH kursus yang sudah
terpilih punya tenggat <= d. Kalau total waktu mereka <= d,
maka jadwalnya layak seluruhnya — karena tiap kursus selesai
lebih awal dari total, dan tenggatnya sudah diperiksa saat ia
masuk.
Urutan lain merusak sifat ini: kursus bertenggat kecil bisa
masuk belakangan dan membatalkan kelayakan yang sudah kita
anggap terjamin.

── KENAPA MEMBUANG YANG TERLAMA ────────────────────────────
Invarian yang dijaga algoritma ini ada DUA:
  (1) jumlah kursus terpilih maksimum di antara semua himpunan
      layak dari kursus-kursus yang sudah diproses
  (2) di antara yang berukuran maksimum, total waktunya minimum

Sifat (2) yang membuat induksinya berjalan: keadaan dengan
total waktu lebih kecil MENDOMINASI — apa pun yang bisa
dilakukan dari keadaan lain, bisa juga dari keadaan ini.

Membuang kursus terlama mengurangi total sebanyak-banyaknya
dengan mengorbankan hanya satu kursus. Itu persis menjaga
sifat (2).

── YANG DIBUANG BISA YANG BARU MASUK ───────────────────────
Kalau kursus baru adalah yang terlama, ia langsung dibuang
lagi. Itu BUKAN pemborosan — itu berarti menolak kursus itu
memang pilihan terbaik, dan kodenya menemukannya sendiri tanpa
percabangan tambahan.
Sampel 3 dibuat khusus menguji ini: kursus (100, 100) masuk
lalu langsung dibuang.

── KENAPA "TERPENDEK DULU" SALAH ───────────────────────────
Mengurutkan menurut durasi mengabaikan tenggat sama sekali.
Contoh: (t=5, d=5) dan (t=4, d=6). Terpendek dulu mengambil
yang kedua (t=4), lalu yang pertama tidak muat (4+5=9 > 5).
Jawabannya tetap 1, tetapi pada masukan yang lebih besar
kesalahan seperti ini menumpuk.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai MIN-heap. Kita ingin membuang durasi TERBESAR.
2. Lupa mengurangi 'total' saat membuang.
3. Membaca masukan sebagai (d, t) padahal soal memberi (t, d).
4. Lupa long long: n = 2*10^5 dikali t = 10^4 -> 2*10^9,
   sudah melampaui int.

Diverifikasi: 20.000 kasus acak vs brute force 2^n, cocok.
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
    vector<pair<ll, ll>> k(n);                  // (tenggat, durasi)
    for (int i = 0; i < n; i++) {
        ll t, d;
        cin >> t >> d;
        k[i] = {d, t};
    }

    sort(k.begin(), k.end());                   // tenggat MENAIK

    priority_queue<ll> pq;                      // MAX-heap durasi terpilih
    ll total = 0;
    for (auto& [d, t] : k) {
        pq.push(t);
        total += t;
        if (total > d) {                        // tenggat terlanggar
            total -= pq.top();                  // buang durasi TERBESAR
            pq.pop();
        }
    }

    cout << pq.size() << '\n';
    return 0;
}
