/*
============================================================
✅ SOLUSI Exercise 6: Menyewa K Pekerja
============================================================
Difficulty: Hard | Kompleksitas: O(n log n) waktu, O(n) memori

── MENURUNKAN RUMUS BIAYA LEBIH DULU ───────────────────────
Andaikan kelompok S sudah dipilih. Aturan (1) berkata ada satu
bilangan r sehingga tiap anggota dibayar r * q[i].
Aturan (2) berkata r * q[i] >= w[i] untuk setiap anggota, yaitu

        r >= w[i] / q[i]        untuk semua i di S

Karena r harus memenuhi SELURUH anggota, nilai terkecil yang
sah adalah

        r = max( w[i] / q[i] )  atas i di S

dan totalnya

        biaya(S) = r * sum( q[i] )
                 = max(rasio dalam S) * (jumlah kualitas S)

Sekarang biayanya hanya bergantung pada DUA besaran. Itulah
kunci seluruh soal — dan itu ditemukan sebelum satu baris kode
pun ditulis.

── STRATEGI: TIAP PEKERJA SEBAGAI PENENTU RASIO ────────────
Urutkan pekerja menurut rasio w/q MENAIK. Proses satu per satu,
menganggap pekerja sekarang sebagai PENENTU rasio (yaitu
pemilik rasio terbesar di dalam kelompok).

Kalau pekerja ke-i adalah penentu, semua anggota lain harus
punya rasio yang tidak lebih besar — yaitu berasal dari
pekerja 0..i-1 yang sudah terlewat.

Rumus biaya memberitahu kita apa yang harus dipilih: karena r
sudah tetap (rasio pekerja i), kita ingin JUMLAH KUALITAS
sekecil mungkin. Jadi ambil K-1 kualitas TERKECIL dari yang
sudah terlewat, ditambah kualitas pekerja i sendiri.

── KENAPA MAX-HEAP, BUKAN MIN-HEAP ─────────────────────────
Ini titik yang paling membingungkan. Kita ingin menyimpan K
kualitas TERKECIL. Untuk memelihara himpunan itu saat elemen
baru masuk, kita perlu membuang anggota TERBESAR di dalamnya —
dan yang memberikan maksimum dengan cepat adalah MAX-HEAP.

Pola umum:
    ingin K TERKECIL  -> MAX-heap berukuran K, buang puncak
    ingin K TERBESAR  -> MIN-heap berukuran K, buang puncak
Banyak orang salah di sini karena naluri mengatakan sebaliknya.

── KENAPA CUKUP MEMERIKSA n KELOMPOK ───────────────────────
Setiap kelompok optimal punya tepat satu anggota dengan rasio
terbesar. Kelompok itu pasti terhitung ketika kita memproses
anggota tersebut sebagai penentu, dan pada saat itu kita sudah
memilih K-1 kualitas terkecil yang tersedia — yaitu pilihan
terbaik untuk penentu tersebut.
Jadi menjelajahi n kemungkinan penentu sudah mencakup seluruh
kelompok optimal.

── PRESISI ─────────────────────────────────────────────────
Saat MENGURUTKAN, bandingkan rasio dengan perkalian silang
(Day 74):
    w_a/q_a < w_b/q_b   <=>   w_a * q_b < w_b * q_a
Perhitungan akhirnya boleh memakai bilangan real karena hanya
dilakukan sekali per kandidat dan tidak dipakai untuk
mengurutkan.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai min-heap untuk menjaga K terkecil.
2. Mengurutkan rasio dengan pembagian double.
3. Lupa memasukkan kualitas pekerja penentu itu sendiri ke
   dalam kelompok.
4. Menghitung biaya sebelum ukuran heap mencapai K.
5. Menyangka "ambil K pekerja dengan rasio terkecil" itu
   benar. Uji dengan brute force C(n,K) pada n kecil —
   dugaan itu gagal.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    if (!(cin >> n >> K)) return 0;
    vector<ll> q(n), w(n);
    for (int i = 0; i < n; i++) cin >> q[i] >> w[i];

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    // urut menurut rasio w/q MENAIK, dibandingkan tanpa pembagian
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return w[a] * q[b] < w[b] * q[a];
    });

    priority_queue<ll> pq;              // MAX-heap: menjaga K kualitas TERKECIL
    ll sumQ = 0;
    double best = numeric_limits<double>::infinity();

    for (int i : ord) {
        pq.push(q[i]);
        sumQ += q[i];
        if ((int)pq.size() > K) {       // buang kualitas TERBESAR
            sumQ -= pq.top();
            pq.pop();
        }
        if ((int)pq.size() == K) {
            double r = (double)w[i] / q[i];        // pekerja i penentu rasio
            best = min(best, r * (double)sumQ);
        }
    }

    cout << fixed << setprecision(6) << best << '\n';
    return 0;
}
