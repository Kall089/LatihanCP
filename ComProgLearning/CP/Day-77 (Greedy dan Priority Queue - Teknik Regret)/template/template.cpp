/*
============================================================
  Day 77 — Greedy + PQ: Teknik Regret | Template
============================================================
  IDE INTI

    Ambil DULU semua yang terlihat menguntungkan.
    Kalau melanggar batasan, BATALKAN pilihan TERBURUK
    yang sudah diambil.

  Kenapa ini bekerja: membatalkan pilihan terburuk selalu
  menghasilkan keadaan yang MENDOMINASI keadaan mana pun yang
  bisa dicapai dengan menolak sejak awal. Jadi kita tidak
  pernah kehilangan solusi optimal.

  KAPAN MEMAKAINYA
    - keputusan diproses berurutan (waktu, posisi, deadline)
    - ada batasan yang bisa terlanggar (kapasitas, waktu, uang)
    - membatalkan satu pilihan mengembalikan sumber daya
      dalam jumlah yang bisa dihitung

  BEDA DENGAN DAY 75
    Day 75 : heap menyimpan KANDIDAT yang belum dipilih
    Day 77 : heap menyimpan yang SUDAH dipilih, siap dibatalkan
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. POLA DASAR: DEADLINE + DURASI ─────────────────────
// n kursus, kursus i butuh waktu t[i] dan harus SELESAI
// sebelum d[i]. Maksimalkan jumlah kursus yang diambil.
//
// Urut deadline MENAIK. Ambil semua. Kalau total waktu
// melewati deadline sekarang, batalkan kursus TERLAMA.

int maksKursus(vector<pair<ll, ll>> k) {     // (deadline, durasi)
    sort(k.begin(), k.end());                 // deadline menaik
    priority_queue<ll> pq;                    // MAX-heap durasi terpilih
    ll total = 0;
    for (auto& [d, t] : k) {
        pq.push(t);
        total += t;
        if (total > d) {                      // melanggar deadline
            total -= pq.top();                // batalkan yang TERLAMA
            pq.pop();
        }
    }
    return (int)pq.size();
}

// ─── 2. POLA: DEADLINE + KEUNTUNGAN, DURASI SERAGAM ───────
// n pekerjaan, tiap pekerjaan butuh 1 satuan waktu, punya
// deadline d[i] dan keuntungan p[i]. Maksimalkan keuntungan.
//
// Urut deadline MENAIK. Ambil semua. Kalau jumlah terpilih
// melebihi deadline sekarang, batalkan yang KEUNTUNGANNYA
// TERKECIL.

ll maksKeuntungan(vector<pair<ll, ll>> j) {  // (deadline, keuntungan)
    sort(j.begin(), j.end());
    priority_queue<ll, vector<ll>, greater<ll>> pq;   // MIN-heap keuntungan
    ll total = 0;
    for (auto& [d, p] : j) {
        pq.push(p);
        total += p;
        if ((ll)pq.size() > d) {              // slot tidak cukup
            total -= pq.top();                // batalkan yang TERKECIL
            pq.pop();
        }
    }
    return total;
}

// ─── 3. POLA: ISI ULANG DI SEPANJANG PERJALANAN ───────────
// Perjalanan sejauh D. Ada n pom bensin di posisi p[i] dengan
// b[i] liter. Tangki awal berisi 'awal' liter, 1 liter per
// satuan jarak, kapasitas tak terbatas.
// Cari jumlah pemberhentian MINIMUM.
//
// Idenya terbalik: JANGAN isi saat melewati pom. Simpan saja
// sebagai "kupon". Saat bahan bakar habis, baru pakai kupon
// TERBESAR yang sudah terlewat.

int minIsiUlang(vector<pair<ll, ll>> pom, ll D, ll awal) {
    sort(pom.begin(), pom.end());
    priority_queue<ll> pq;                    // MAX-heap kupon
    ll bahan = awal, posisi = 0;
    int hit = 0;
    size_t i = 0;
    while (posisi < D) {
        // kumpulkan kupon dari semua pom yang bisa dicapai
        while (i < pom.size() && pom[i].first <= posisi + bahan) {
            pq.push(pom[i].second);
            i++;
        }
        posisi += bahan;
        bahan = 0;
        if (posisi >= D) break;
        if (pq.empty()) return -1;            // macet
        bahan = pq.top(); pq.pop();           // pakai kupon TERBESAR
        hit++;
    }
    return hit;
}

// ─── 4. POLA: MODAL BERTUMBUH (IPO) ───────────────────────
// Modal awal C, boleh menjalankan K proyek. Proyek i butuh
// modal m[i] dan memberi keuntungan p[i].
// Dua struktur: array terurut (belum terjangkau) + max-heap
// (sudah terjangkau).

ll maksModal(vector<pair<ll, ll>> proyek, int K, ll C) {  // (modal, untung)
    sort(proyek.begin(), proyek.end());
    priority_queue<ll> pq;
    size_t i = 0;
    for (int t = 0; t < K; t++) {
        while (i < proyek.size() && proyek[i].first <= C) {
            pq.push(proyek[i].second);        // jadi terjangkau
            i++;
        }
        if (pq.empty()) break;                // tidak ada yang bisa dijalankan
        C += pq.top(); pq.pop();              // ambil untung TERBESAR
    }
    return C;
}

// ─── 5. BRUTE FORCE UNTUK STRESS TEST ─────────────────────

int bruteKursus(const vector<pair<ll, ll>>& k) {
    int n = k.size(), best = 0;
    for (int m = 0; m < (1 << n); m++) {
        vector<pair<ll, ll>> s;
        for (int i = 0; i < n; i++) if (m >> i & 1) s.push_back(k[i]);
        sort(s.begin(), s.end());             // deadline menaik
        ll t = 0; bool ok = true;
        for (auto& [d, dur] : s) { t += dur; if (t > d) { ok = false; break; } }
        if (ok) best = max(best, (int)s.size());
    }
    return best;
}

ll bruteKeuntungan(const vector<pair<ll, ll>>& j) {
    int n = j.size(); ll best = 0;
    for (int m = 0; m < (1 << n); m++) {
        vector<pair<ll, ll>> s;
        for (int i = 0; i < n; i++) if (m >> i & 1) s.push_back(j[i]);
        sort(s.begin(), s.end());
        bool ok = true; ll tot = 0;
        for (size_t k = 0; k < s.size(); k++) {
            if ((ll)(k + 1) > s[k].first) { ok = false; break; }
            tot += s[k].second;
        }
        if (ok) best = max(best, tot);
    }
    return best;
}

// ─── 6. JEBAKAN ───────────────────────────────────────────
//
//  a) Arah heap. Pola 1 membatalkan durasi TERBESAR (max-heap),
//     pola 2 membatalkan keuntungan TERKECIL (min-heap).
//     Keduanya "membatalkan yang terburuk" — tetapi "terburuk"
//     berarti hal yang berbeda.
//
//  b) Mengurutkan menurut hal yang salah. Regret bekerja karena
//     kita memproses dalam urutan yang membuat batasan makin
//     KETAT (deadline menaik). Urutan lain merusak buktinya.
//
//  c) Menolak sejak awal alih-alih mengambil lalu membatalkan.
//     Menolak lebih awal kehilangan informasi.
//
//  d) Lupa mengurangi total saat membatalkan.
//
//  e) Pola 3: mengisi bensin saat melewati pom. Yang benar
//     adalah MENUNDA keputusan sampai benar-benar butuh.

// ─── MAIN: demo + stress test ─────────────────────────────

int main() {
    FASTIO;

    vector<pair<ll, ll>> kursus = {{5,2},{6,2},{7,1},{9,3},{100,100}};
    cout << "maks kursus     : " << maksKursus(kursus) << " (harusnya 4)\n";

    vector<pair<ll, ll>> kerja = {{4,20},{1,10},{1,40},{1,30}};
    cout << "maks keuntungan : " << maksKeuntungan(kerja) << " (harusnya 60)\n";

    vector<pair<ll, ll>> pom = {{10,60},{20,30},{30,30},{60,40}};
    cout << "min isi ulang   : " << minIsiUlang(pom, 100, 10) << " (harusnya 2)\n";

    vector<pair<ll, ll>> pr = {{0,1},{1,2},{1,3}};
    cout << "maks modal      : " << maksModal(pr, 2, 0) << " (harusnya 4)\n";

    mt19937 rng(77);
    bool ok1 = true, ok2 = true;
    for (int t = 0; t < 20000 && ok1; t++) {
        int n = 1 + rng() % 8;
        vector<pair<ll, ll>> k(n);
        for (int i = 0; i < n; i++) k[i] = {(ll)(1 + rng() % 12), (ll)(1 + rng() % 6)};
        if (maksKursus(k) != bruteKursus(k)) ok1 = false;
    }
    for (int t = 0; t < 20000 && ok2; t++) {
        int n = 1 + rng() % 8;
        vector<pair<ll, ll>> j(n);
        for (int i = 0; i < n; i++) j[i] = {(ll)(1 + rng() % 6), (ll)(1 + rng() % 20)};
        if (maksKeuntungan(j) != bruteKeuntungan(j)) ok2 = false;
    }
    cout << "stress kursus     : " << (ok1 ? "20000 kasus OK" : "GAGAL") << '\n';
    cout << "stress keuntungan : " << (ok2 ? "20000 kasus OK" : "GAGAL") << '\n';

    return 0;
}
