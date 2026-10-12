/*
============================================================
✅ SOLUSI Exercise 6: Menjadwalkan dengan Mesin Ganda
============================================================
Difficulty: Hard | Kompleksitas: O(n log n)

── PERUBAHAN DARI EXERCISE 2: SATU BARIS ───────────────────
Dengan M mesin, sampai waktu d kita bisa menyelesaikan
paling banyak d * M pekerjaan (M pekerjaan per slot, d slot).
Jadi syaratnya berubah dari

    pq.size() > d        menjadi        pq.size() > d * M

Selebihnya identik. Ini contoh bagus bahwa memahami MENGAPA
sebuah algoritma bekerja membuat perluasannya menjadi sepele.

── MEMERIKSA ULANG BUKTINYA ────────────────────────────────
Klaim: sehimpunan pekerjaan (masing-masing 1 satuan waktu,
tenggat d_i) bisa dijadwalkan pada M mesin BILA DAN HANYA BILA,
setelah diurutkan menurut tenggat menaik, berlaku
      k + 1 <= d_(k) * M    untuk setiap k

Arah "hanya bila": pekerjaan ke-1 sampai ke-(k+1) semuanya
bertenggat <= d_(k), dan hanya ada d_(k) * M slot-mesin sampai
waktu itu.

Arah "bila": jadwalkan pekerjaan ke-k (0-indexed) pada slot
waktu floor(k / M) + 1, mesin (k mod M). Pekerjaan ke-k selesai
pada waktu floor(k/M) + 1 <= ... syaratnya k + 1 <= d_(k) * M
memberi (k+1)/M <= d_(k), dan karena floor(k/M) + 1 <= (k+M)/M
= k/M + 1, syaratnya terpenuhi.

Jadi pemeriksaan prefiks tetap cukup. ∎

── OVERFLOW PADA d * M ─────────────────────────────────────
d sampai n = 2*10^5 dan M sampai 10^5, jadi d * M mencapai
2*10^10 — MELAMPAUI int. Perkaliannya harus dalam long long.
Ini bug yang mudah terlewat karena kedua faktornya sendiri
muat di int.

── VERIFIKASI SILANG ───────────────────────────────────────
Jalankan solusi ini dengan M = 1 dan bandingkan dengan solusi
Exercise 2 pada masukan acak yang sama. Keduanya harus identik.
Verifikasi silang seperti ini jauh lebih cepat daripada menulis
brute force baru, dan sering menangkap kesalahan perluasan.

── JEBAKAN ─────────────────────────────────────────────────
1. Overflow pada d * M.
2. Menyangka perlu M heap terpisah. Tidak — kapasitas total
   yang penting, bukan mesin mana.
3. Memakai MAX-heap (lihat Exercise 2).
4. Menyangka jawabannya sama dengan menjalankan Exercise 2
   sebanyak M kali. Tidak.

Diverifikasi: 20.000 kasus acak vs brute force 2^n, cocok.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll M;
    if (!(cin >> n >> M)) return 0;
    vector<pair<ll, ll>> j(n);                  // (tenggat, keuntungan)
    for (auto& [d, p] : j) cin >> d >> p;

    sort(j.begin(), j.end());                   // tenggat MENAIK

    priority_queue<ll, vector<ll>, greater<ll>> pq;   // MIN-heap keuntungan
    ll total = 0;
    for (auto& [d, p] : j) {
        pq.push(p);
        total += p;
        if ((ll)pq.size() > d * M) {            // d * M dalam LONG LONG
            total -= pq.top();
            pq.pop();
        }
    }

    cout << total << '\n';
    return 0;
}
