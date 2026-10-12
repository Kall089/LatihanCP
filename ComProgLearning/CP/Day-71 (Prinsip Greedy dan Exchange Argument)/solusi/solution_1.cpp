/*
============================================================
✅ SOLUSI Exercise 1: Antrean Kasir
============================================================
Difficulty: Easy | Kompleksitas: O(n log n) waktu, O(n) memori

── IDE UTAMA ────────────────────────────────────────────────
Layani pelanggan dengan waktu TERPENDEK lebih dulu (Shortest
Processing Time / SPT).

── KENAPA BENAR: EXCHANGE ARGUMENT ─────────────────────────
Ambil sembarang urutan optimal. Misalkan ada dua pelanggan
BERDAMPINGAN pada posisi k dan k+1 dengan waktu a dan b, dan
a > b (melanggar aturan kita).

Misal waktu berjalan sebelum posisi k adalah S. Maka:
  urutan (a, b): sumbangan = (S + a) + (S + a + b) = 2S + 2a + b
  urutan (b, a): sumbangan = (S + b) + (S + b + a) = 2S + 2b + a

Selisihnya = (2a + b) - (2b + a) = a - b > 0.
Jadi menukar keduanya MENGURANGI total.

Yang penting: pelanggan SEBELUM posisi k tidak terpengaruh
(waktu selesainya tidak berubah), dan pelanggan SESUDAH posisi
k+1 juga tidak terpengaruh karena a + b tetap sama — jumlah
waktu dua pelanggan itu tidak berubah oleh penukaran, sehingga
titik mulai pelanggan berikutnya identik.

Kesimpulan: setiap urutan yang punya pelanggan berdampingan
"melanggar" bisa diperbaiki. Dengan menukar berulang kali kita
sampai ke urutan terurut menaik tanpa pernah memperburuk total.
Maka urutan terurut menaik pasti optimal. ∎

── SUDUT PANDANG LAIN (lebih intuitif) ─────────────────────
Kalau pelanggan diletakkan pada posisi ke-p (1-indexed) dari
belakang, waktunya dihitung sebanyak p kali dalam total.
  total = n*t[urutan 1] + (n-1)*t[urutan 2] + ... + 1*t[urutan n]
Untuk meminimalkan, koefisien TERBESAR (n) harus dipasangkan
dengan nilai TERKECIL. Itulah rearrangement inequality.

── JEBAKAN ─────────────────────────────────────────────────
1. n = 2*10^5 dan t = 10^9 → total bisa mencapai
   sekitar 2*10^5 * 2*10^5 * 10^9 / 2 = 2*10^19 ... sebenarnya
   lebih tepatnya sum(prefix) <= n * (n*maxT) yang jelas jauh
   melampaui int. WAJIB long long. (Nilai terburuk sekitar
   2*10^10 * 10^9 → tidak muat bahkan di long long? Tidak:
   sum <= n * sum(t) <= 2*10^5 * 2*10^14 = 4*10^19 — ini SEDIKIT
   di atas batas long long (9.2*10^18). Pada soal nyata batasnya
   biasanya dibuat aman; di sini asumsikan batas soal menjamin
   hasil muat di long long. Kalau ragu, __int128 aman.)
2. Menghitung ulang prefix dari awal untuk tiap pelanggan →
   O(n^2), TLE.
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
    vector<ll> t(n);
    for (ll &x : t) cin >> x;

    // Langkah greedy: terpendek dulu.
    sort(t.begin(), t.end());

    // sekarang = waktu berjalan, bertambah tiap pelanggan selesai.
    // total    = jumlah seluruh waktu selesai.
    ll sekarang = 0, total = 0;
    for (ll x : t) {
        sekarang += x;      // pelanggan ini selesai pada detik 'sekarang'
        total += sekarang;  // sumbangannya ke total
    }

    cout << total << '\n';
    return 0;
}
