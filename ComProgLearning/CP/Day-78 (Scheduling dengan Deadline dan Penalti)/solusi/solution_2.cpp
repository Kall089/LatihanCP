/*
============================================================
✅ SOLUSI Exercise 2: Sesedikit Mungkin Terlambat
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── FUNGSI TUJUAN YANG BERBEDA ──────────────────────────────
Exercise 1 meminimalkan keterlambatan MAKSIMUM.
Exercise 2 meminimalkan JUMLAH yang terlambat.
Keduanya diawali "urut tenggat menaik", tetapi hanya satu yang
selesai di situ.

Periksa sampel 1: pekerjaan (5,5), (5,9), (3,12).
  EDF apa adanya : t = 5 (ok), 10 > 9 (terlambat),
                   13 > 12 (terlambat)  -> 2 terlambat
  jawaban benar  : 1
EDF menyebarkan keterlambatan; ia tidak berusaha meminimalkan
JUMLAH pekerjaan yang terlambat.

── ALGORITMA MOORE-HODGSON ─────────────────────────────────
Kerangka regret Day 77:
  urut tenggat menaik
  ambil setiap pekerjaan
  kalau total waktu melewati tenggat, buang durasi TERBESAR

Jawabannya n dikurangi jumlah yang tersisa di dalam heap.

── KE MANA PEKERJAAN YANG DIBUANG PERGI ────────────────────
Ini yang paling sering membingungkan. Pekerjaan yang dibuang
dari heap TETAP DIKERJAKAN — hanya saja dijadwalkan SETELAH
seluruh pekerjaan tepat waktu.

Karena ia sudah pasti terlambat, kapan tepatnya ia dikerjakan
tidak memengaruhi fungsi tujuan. Jadi isi heap adalah himpunan
pekerjaan TEPAT WAKTU, bukan himpunan yang dikerjakan.

── KENAPA MEMBUANG YANG TERLAMA ────────────────────────────
Invarian dua-sifat Day 77: di antara semua himpunan tepat-waktu
berukuran maksimum, algoritma ini menjaga yang TOTAL DURASINYA
MINIMUM. Membuang durasi terbesar menjaga sifat itu, karena
membebaskan waktu sebanyak-banyaknya dengan mengorbankan hanya
satu pekerjaan.

── KENAPA URUT TENGGAT MENAIK ──────────────────────────────
Klaim pendukung: kalau sehimpunan pekerjaan bisa diselesaikan
tepat waktu semua, maka mengerjakannya menurut tenggat menaik
juga berhasil (exchange argument Exercise 1).
Karena itu kita boleh membatasi diri pada jadwal terurut
tenggat, dan pemeriksaan "total > tenggat sekarang" menjadi
syarat yang tepat.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai EDF apa adanya lalu menghitung yang terlambat.
2. Memakai MIN-heap. Kita membuang durasi TERBESAR.
3. Lupa mengurangi total saat membuang.
4. Menyangka pekerjaan yang dibuang tidak dikerjakan.

Diverifikasi: 4.000 kasus acak vs seluruh permutasi, cocok.
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
    vector<pair<ll, ll>> j(n);                  // (tenggat, durasi)
    for (int i = 0; i < n; i++) {
        ll t, d;
        cin >> t >> d;
        j[i] = {d, t};
    }

    sort(j.begin(), j.end());                   // tenggat MENAIK

    priority_queue<ll> pq;                      // MAX-heap durasi tepat waktu
    ll t = 0;
    for (auto& [d, dur] : j) {
        pq.push(dur);
        t += dur;
        if (t > d) {                            // tenggat terlanggar
            t -= pq.top();                      // buang durasi TERBESAR
            pq.pop();
        }
    }

    cout << n - (int)pq.size() << '\n';
    return 0;
}
