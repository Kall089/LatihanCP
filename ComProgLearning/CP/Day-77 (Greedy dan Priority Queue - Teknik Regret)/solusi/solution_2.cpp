/*
============================================================
✅ SOLUSI Exercise 2: Pekerjaan Bertenggat
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── PERBEDAAN DARI EXERCISE 1 ───────────────────────────────
Kerangkanya identik: urut tenggat menaik, ambil semua,
batalkan saat melanggar. Yang berbeda hanya DUA hal:

  Exercise 1 : batasan = TOTAL DURASI <= tenggat
               buang durasi TERBESAR   -> MAX-heap
  Exercise 2 : batasan = JUMLAH pekerjaan <= tenggat
               buang keuntungan TERKECIL -> MIN-heap

Alasannya: di sini setiap pekerjaan memakan sumber daya yang
SAMA (satu slot). Jadi membuang mana pun membebaskan slot yang
sama banyaknya, dan yang membedakan hanyalah nilainya.
"Terburuk" berarti hal yang berbeda pada dua soal ini.

Salah arah heap tidak menghasilkan error apa pun — hanya
jawaban yang salah. Kalau kamu ingin merasakan bedanya,
jalankan solusi ini dengan max-heap pada stress test dan lihat
berapa persen kasus yang gagal.

── KENAPA MEMERIKSA PREFIKS SUDAH CUKUP ────────────────────
Klaim: sehimpunan pekerjaan (masing-masing 1 satuan waktu,
tenggat d_i) bisa dijadwalkan seluruhnya BILA DAN HANYA BILA,
setelah diurutkan menurut tenggat menaik, berlaku
      k + 1 <= d_(k)   untuk setiap k
yaitu pekerjaan ke-(k+1) muat pada slot ke-(k+1).

Arah "hanya bila" jelas. Arah "bila": jadwalkan saja pekerjaan
ke-k pada slot ke-k; syarat di atas menjamin slot itu tidak
melewati tenggatnya.
Ini kasus khusus teorema Hall yang bisa diperiksa dengan satu
sapuan — dan itulah sebabnya kita cukup memeriksa
'pq.size() > d' pada setiap langkah.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai MAX-heap.
2. Membandingkan pq.size() (unsigned) dengan d (signed) tanpa
   cast. Kalau d bertipe ll dan pq.size() bertipe size_t,
   perbandingannya bisa mengejutkan. Kode di bawah meng-cast
   secara eksplisit.
3. Lupa long long: n = 2*10^5 dikali p = 10^9 -> 2*10^14.
4. Menyangka soal ini butuh DP. Tidak — regret sudah optimal.

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
    vector<pair<ll, ll>> j(n);                  // (tenggat, keuntungan)
    for (auto& [d, p] : j) cin >> d >> p;

    sort(j.begin(), j.end());                   // tenggat MENAIK

    priority_queue<ll, vector<ll>, greater<ll>> pq;   // MIN-heap keuntungan
    ll total = 0;
    for (auto& [d, p] : j) {
        pq.push(p);
        total += p;
        if ((ll)pq.size() > d) {                // slot tidak cukup
            total -= pq.top();                  // buang keuntungan TERKECIL
            pq.pop();
        }
    }

    cout << total << '\n';
    return 0;
}
