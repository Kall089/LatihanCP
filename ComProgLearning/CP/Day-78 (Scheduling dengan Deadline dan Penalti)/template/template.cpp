/*
============================================================
  Day 78 — Scheduling: Deadline & Penalti | Template
============================================================
  TIGA FUNGSI TUJUAN YANG BERBEDA JAUH

    1. MINIMALKAN KETERLAMBATAN MAKSIMUM (max lateness)
       -> urut DEADLINE menaik (EDF: Earliest Deadline First)
       -> greedy, O(n log n), TERBUKTI optimal

    2. MINIMALKAN JUMLAH YANG TERLAMBAT (number of late jobs)
       -> algoritma Moore-Hodgson: EDF + buang durasi terbesar
       -> greedy + heap (Day 77), O(n log n)

    3. MINIMALKAN TOTAL PENALTI BERBOBOT (weighted tardiness)
       -> NP-HARD secara umum
       -> kasus khusus durasi seragam: greedy/regret
       -> kasus kecil: DP bitmask atau DP di atas waktu

  KESALAHAN PALING MAHAL DI HARI INI:
    memakai algoritma nomor 1 atau 2 untuk soal nomor 3.
    Bacalah fungsi tujuannya dengan sangat teliti.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Job { ll t, d, w; int idx; };   // durasi, deadline, bobot

// ─── 1. EDF: MINIMALKAN KETERLAMBATAN MAKSIMUM ────────────
// lateness_i = C_i - d_i  (boleh negatif kalau selesai lebih awal)
// Urut deadline MENAIK. Seluruh pekerjaan dikerjakan.

ll maxLateness(vector<Job> j) {
    sort(j.begin(), j.end(), [](const Job& a, const Job& b) { return a.d < b.d; });
    ll t = 0, worst = LLONG_MIN;
    for (auto& x : j) { t += x.t; worst = max(worst, t - x.d); }
    return worst;
}

// Varian yang lazim: TARDINESS maksimum = max(0, lateness).
ll maxTardiness(vector<Job> j) { return max(0LL, maxLateness(j)); }

// ─── 2. MOORE-HODGSON: MINIMALKAN JUMLAH TERLAMBAT ────────
// Kembalikan jumlah pekerjaan yang TEPAT WAKTU (maksimum).
// Persis pola regret Day 77.

int maksTepatWaktu(vector<Job> j) {
    sort(j.begin(), j.end(), [](const Job& a, const Job& b) { return a.d < b.d; });
    priority_queue<ll> pq;                  // MAX-heap durasi terpilih
    ll t = 0;
    for (auto& x : j) {
        pq.push(x.t);
        t += x.t;
        if (t > x.d) { t -= pq.top(); pq.pop(); }
    }
    return (int)pq.size();
}

// ─── 3. DURASI SERAGAM + BOBOT: REGRET ────────────────────
// Tiap pekerjaan 1 satuan waktu, terlambat -> kehilangan w[i].
// Minimalkan total bobot yang hilang = total - maksimum terselamatkan.

ll minPenaltiSeragam(vector<Job> j) {
    ll total = 0;
    for (auto& x : j) total += x.w;
    sort(j.begin(), j.end(), [](const Job& a, const Job& b) { return a.d < b.d; });
    priority_queue<ll, vector<ll>, greater<ll>> pq;   // MIN-heap bobot
    ll selamat = 0;
    for (auto& x : j) {
        pq.push(x.w);
        selamat += x.w;
        if ((ll)pq.size() > x.d) { selamat -= pq.top(); pq.pop(); }
    }
    return total - selamat;
}

// ─── 4. DP UNTUK WEIGHTED TARDINESS (n kecil ATAU T kecil) ─
// dp[w] = bobot maksimum yang bisa DISELAMATKAN kalau total
//         waktu terpakai tepat w. Urut deadline menaik.
// Kompleksitas O(n * T), T = min(sum t, max d).

ll minPenaltiDP(vector<Job> j) {
    ll total = 0, sumT = 0, maxD = 0;
    for (auto& x : j) { total += x.w; sumT += x.t; maxD = max(maxD, x.d); }
    sort(j.begin(), j.end(), [](const Job& a, const Job& b) { return a.d < b.d; });

    ll T = min(sumT, maxD);
    vector<ll> dp(T + 1, -1);
    dp[0] = 0;
    for (auto& x : j) {
        ll batas = min(x.d, T);
        for (ll w = batas; w >= x.t; w--)          // MUNDUR
            if (dp[w - x.t] >= 0) dp[w] = max(dp[w], dp[w - x.t] + x.w);
    }
    ll best = 0;
    for (ll w = 0; w <= T; w++) best = max(best, dp[w]);
    return total - best;
}

// ─── 5. BRUTE FORCE (SEMUA PERMUTASI) ─────────────────────

ll bruteMaxLateness(vector<Job> j) {
    sort(j.begin(), j.end(), [](const Job& a, const Job& b) { return a.idx < b.idx; });
    ll best = LLONG_MAX;
    vector<int> p(j.size());
    iota(p.begin(), p.end(), 0);
    do {
        ll t = 0, worst = LLONG_MIN;
        for (int i : p) { t += j[i].t; worst = max(worst, t - j[i].d); }
        best = min(best, worst);
    } while (next_permutation(p.begin(), p.end()));
    return best;
}

ll bruteMinPenalti(vector<Job> j) {
    int n = j.size();
    ll best = LLONG_MAX;
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    do {
        ll t = 0, pen = 0;
        for (int i : p) { t += j[i].t; if (t > j[i].d) pen += j[i].w; }
        best = min(best, pen);
    } while (next_permutation(p.begin(), p.end()));
    return best;
}

// ─── 6. JEBAKAN ───────────────────────────────────────────
//
//  a) Memakai EDF untuk soal "minimalkan JUMLAH terlambat".
//     EDF meminimalkan keterlambatan MAKSIMUM, bukan jumlahnya.
//
//  b) Memakai Moore-Hodgson untuk soal berbobot.
//     Moore-Hodgson memaksimalkan JUMLAH, bukan bobot.
//
//  c) Menyangka weighted tardiness bisa greedy. NP-hard.
//     Batasan kecil (n <= 20 atau sum t <= 10^5) adalah tanda DP.
//
//  d) Lateness vs tardiness. Lateness boleh negatif;
//     tardiness = max(0, lateness). Fungsi tujuannya berbeda.
//
//  e) Lupa bahwa waktu mulai bisa BUKAN nol, atau ada waktu
//     rilis r[i]. Dengan waktu rilis, EDF preemptive masih
//     optimal tetapi non-preemptive menjadi NP-hard.

// ─── MAIN: demo + stress test ─────────────────────────────

int main() {
    FASTIO;

    vector<Job> j = {{3,6,10,0},{2,8,20,1},{1,9,30,2}};
    cout << "max lateness  : " << maxLateness(j)   << " (harusnya -3)\n";
    cout << "maks tepat wkt: " << maksTepatWaktu(j) << " (harusnya 3)\n";
    cout << "min penalti DP: " << minPenaltiDP(j)   << " (harusnya 0)\n";

    vector<Job> k = {{3,3,5,0},{3,4,10,1},{3,5,1,2}};
    cout << "penalti DP    : " << minPenaltiDP(k)   << '\n';
    cout << "penalti brute : " << bruteMinPenalti(k) << '\n';

    mt19937 rng(78);
    bool o1 = true, o2 = true, o3 = true;
    for (int t = 0; t < 4000 && o1; t++) {
        int n = 1 + rng() % 7;
        vector<Job> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {(ll)(1 + rng() % 5), (ll)(1 + rng() % 15), (ll)(1 + rng() % 20), i};
        if (maxLateness(a) != bruteMaxLateness(a)) o1 = false;
    }
    for (int t = 0; t < 4000 && o2; t++) {
        int n = 1 + rng() % 7;
        vector<Job> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {(ll)(1 + rng() % 5), (ll)(1 + rng() % 15), 1, i};
        // dengan bobot seragam, min penalti = n - maks tepat waktu
        if ((ll)(n - maksTepatWaktu(a)) != bruteMinPenalti(a)) o2 = false;
    }
    for (int t = 0; t < 4000 && o3; t++) {
        int n = 1 + rng() % 7;
        vector<Job> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {(ll)(1 + rng() % 5), (ll)(1 + rng() % 15), (ll)(1 + rng() % 20), i};
        if (minPenaltiDP(a) != bruteMinPenalti(a)) o3 = false;
    }
    cout << "stress EDF        : " << (o1 ? "4000 kasus OK" : "GAGAL") << '\n';
    cout << "stress Moore      : " << (o2 ? "4000 kasus OK" : "GAGAL") << '\n';
    cout << "stress DP berbobot: " << (o3 ? "4000 kasus OK" : "GAGAL") << '\n';

    return 0;
}
