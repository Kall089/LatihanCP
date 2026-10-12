/*
============================================================
  Day 71 — Prinsip Greedy | CP Template
============================================================
  Yang penting dari hari ini BUKAN kode, melainkan CARA MENGUJI
  dan MEMBUKTIKAN dugaan greedy. Template ini berisi alat untuk itu.

  URUTAN KERJA DI KONTES
    1. tebak kriteria greedy                     (30 detik)
    2. cari contoh tandingan dengan n = 2, 3     (2 menit)
    3. stress test terhadap brute force          (5 menit)
    4. tulis greedy, submit
    5. buktikan dengan exchange argument HANYA kalau ragu

  MENEMUKAN KOMPARATOR
    "kalau hanya ada DUA elemen, mana yang harus lebih dulu?"
    Jawabannya langsung menjadi komparator.

  SINYAL GREEDY SALAH
    n <= 20/40                    -> brute force / MITM / DP bitmask
    kapasitas + benda tak terpotong -> DP knapsack (Day 145)
    "berapa CARA"                 -> DP / kombinatorik
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. KERANGKA UMUM GREEDY ─────────────────────────────
/*
    sort(a.begin(), a.end(), kriteria);
    Hasil h = kosong;
    for (auto& x : a)
        if (bolehDiambil(x, h)) ambil(x, h);

    Hampir seluruh soal greedy berbentuk ini. Pekerjaan sesungguhnya
    adalah menemukan `kriteria` yang benar -- bukan menulis kodenya.
*/

// ─── 2. PENJADWALAN: MINIMUMKAN TOTAL WAKTU SELESAI ──────
// Kriteria: TERPENDEK DULU (shortest processing time).
// Bukti exchange: menukar pasangan berdampingan yang terbalik
// mengurangi total sebesar (t[i] - t[j]) > 0, dan tidak memengaruhi
// pekerjaan lain karena total waktu keduanya tidak berubah.

ll totalWaktuSelesai(vector<ll> t) {
    sort(t.begin(), t.end());                 // terpendek dulu
    ll sekarang = 0, total = 0;
    for (ll x : t) {
        sekarang += x;
        total += sekarang;
    }
    return total;
}

// ─── 3. KOMPARATOR GABUNGAN (susun string terbesar) ──────
// Contoh terbaik dari "bandingkan dua elemen untuk menemukan kriteria".
// "urut menurun sebagai bilangan" SALAH: [3, 30] -> 303, bukan 330.

string susunTerbesar(vector<string> a) {
    sort(a.begin(), a.end(), [](const string& x, const string& y) {
        return x + y > y + x;                 // mana yang gabungannya lebih besar
    });
    string s;
    for (auto& x : a) s += x;
    // hilangkan nol di depan: "00" harus menjadi "0"
    int i = 0;
    while (i + 1 < (int)s.size() && s[i] == '0') i++;
    return s.substr(i);
}

// ─── 4. GREEDY + HEAP (kerangka Huffman, Day 75) ─────────
// "Gabungkan dua tumpukan berulang" -> ambil dua TERKECIL tiap langkah.

ll biayaGabungan(vector<ll> a) {
    priority_queue<ll, vector<ll>, greater<ll>> pq(a.begin(), a.end());
    ll total = 0;
    while (pq.size() > 1) {
        ll x = pq.top(); pq.pop();
        ll y = pq.top(); pq.pop();
        total += x + y;
        pq.push(x + y);
    }
    return total;
}

// ─── 5. ALAT UJI: BRUTE FORCE ATAS SELURUH PERMUTASI ─────
// Untuk n <= 8, mencoba seluruh permutasi instan. Ini pembanding
// terbaik untuk menguji dugaan greedy yang berbentuk "urutan optimal".

template <typename F>
ll bruteMinPermutasi(vector<ll> a, F hitung) {
    sort(a.begin(), a.end());
    ll best = LLONG_MAX;
    do {
        best = min(best, hitung(a));
    } while (next_permutation(a.begin(), a.end()));
    return best;
}

// ─── 6. ALAT UJI: BRUTE FORCE ATAS SELURUH SUBSET ────────
// Untuk dugaan greedy yang berbentuk "pilih subhimpunan terbaik".

template <typename F>
ll bruteMaxSubset(int n, F nilai) {
    ll best = LLONG_MIN;
    for (int mask = 0; mask < (1 << n); mask++) best = max(best, nilai(mask));
    return best;
}

// ─── 7. CONTOH TANDINGAN KLASIK (hafalkan) ───────────────
/*
    KNAPSACK RASIO (greedy SALAH untuk 0/1):
        W = 10 ; (berat 6, nilai 7), (5, 5), (5, 5)
        greedy rasio -> 7 ; optimal -> 10

    KOIN GREEDY (salah untuk himpunan sembarang):
        koin {1, 3, 4}, bayar 6
        greedy 4+1+1 = 3 koin ; optimal 3+3 = 2 koin

    INTERVAL TERPENDEK DULU (salah):
        [1,10], [9,12], [11,20]
        greedy -> 1 interval ; optimal [1,10] + [11,20] -> 2

    INTERVAL MULAI PALING AWAL (salah):
        [1,100], [2,3], [4,5]
        greedy -> 1 interval ; optimal -> 2
*/

// ─── 8. CATATAN STRICT WEAK ORDERING ─────────────────────
/*
    Komparator untuk std::sort HARUS memenuhi strict weak ordering:
      - cmp(x, x) selalu FALSE
      - kalau cmp(x, y) maka TIDAK cmp(y, x)
      - transitif
    Melanggarnya bisa membuat sort() CRASH, bukan sekadar salah urut.

    Komparator "x + y > y + x" pada string memenuhinya (bisa dibuktikan),
    tetapi tidak semua komparator "intuitif" aman. Kalau ragu, uji dengan
    array berisi banyak elemen kembar.
*/

// ─── MAIN: demonstrasi + stress test ─────────────────────

int main() {
    FASTIO;

    // Demonstrasi: total waktu selesai
    vector<ll> t = {3, 1, 2};
    cout << "total waktu selesai [3,1,2] : " << totalWaktuSelesai(t) << " (harusnya 10)\n";

    // Demonstrasi: susun string terbesar
    vector<string> s = {"3", "30", "34", "5", "9"};
    cout << "susun terbesar              : " << susunTerbesar(s) << " (harusnya 9534330)\n";

    // Stress test: greedy SPT vs brute force seluruh permutasi
    mt19937 rng(20240813);
    bool ok = true;
    for (int iter = 0; iter < 3000 && ok; iter++) {
        int n = 1 + rng() % 7;
        vector<ll> a(n);
        for (ll& x : a) x = 1 + rng() % 20;

        ll g = totalWaktuSelesai(a);
        ll b = bruteMinPermutasi(a, [](const vector<ll>& v) {
            ll sek = 0, tot = 0;
            for (ll x : v) { sek += x; tot += sek; }
            return tot;
        });
        if (g != b) {
            cout << "CONTOH TANDINGAN:";
            for (ll x : a) cout << ' ' << x;
            cout << "  greedy " << g << " optimal " << b << '\n';
            ok = false;
        }
    }
    cout << "stress SPT                  : " << (ok ? "3000 kasus OK" : "GAGAL") << '\n';

    return 0;
}
