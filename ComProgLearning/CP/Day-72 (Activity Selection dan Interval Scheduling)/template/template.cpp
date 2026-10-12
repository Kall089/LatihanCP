/*
============================================================
  Day 72 — Activity Selection & Interval Scheduling | Template
============================================================
  ATURAN EMAS

    Maksimalkan JUMLAH interval saling lepas
        -> urutkan menurut UJUNG (r) menaik, ambil serakah
    Maksimalkan TOTAL BOBOT interval saling lepas
        -> BUKAN greedy. Itu DP + binary search.
    Minimalkan jumlah "ruang"/mesin untuk semua interval
        -> sapuan event, atau heap berisi ujung
    Interval yang berpotongan pada satu titik
        -> putuskan dulu: tertutup [l,r] atau setengah terbuka [l,r)

  SATU KALIMAT YANG MENYELAMATKAN
    Selesai paling awal = menyisakan sisa waktu TERBANYAK
    untuk semua interval berikutnya.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Interval {
    ll l, r;
    int idx;
};

// ─── 1. ACTIVITY SELECTION: jumlah maksimum saling lepas ──
// Interval dianggap TERTUTUP [l, r]. Dua interval boleh dipakai
// bersama hanya jika r_sebelumnya < l_sekarang (STRICT).
// Kalau soal memperbolehkan bersentuhan di ujung, ganti '<' -> '<='.

// bolehSentuh = true  -> interval [l, r) : akhir == awal berikutnya DIPERBOLEHKAN
// bolehSentuh = false -> interval [l, r] tertutup : harus benar-benar terpisah
// SALAH memilih salah satunya adalah penyebab WA nomor satu pada soal interval.
int maksSalingLepas(vector<Interval> a, bool bolehSentuh = false) {
    sort(a.begin(), a.end(), [](const Interval& x, const Interval& y) {
        return x.r < y.r;
    });
    int hit = 0;
    ll akhir = LLONG_MIN;
    for (const auto& it : a) {
        bool muat = bolehSentuh ? (it.l >= akhir) : (it.l > akhir);
        if (muat) { hit++; akhir = it.r; }
    }
    return hit;
}

// Versi yang juga mengembalikan interval mana saja yang dipilih.
vector<int> pilihSalingLepas(vector<Interval> a) {
    sort(a.begin(), a.end(), [](const Interval& x, const Interval& y) {
        return x.r < y.r;
    });
    vector<int> res;
    ll akhir = LLONG_MIN;
    for (const auto& it : a) {
        if (it.l > akhir) { res.push_back(it.idx); akhir = it.r; }
    }
    return res;
}

// ─── 2. JUMLAH MINIMUM YANG HARUS DIBUANG ─────────────────
// Agar sisanya saling lepas. Selalu n - maksSalingLepas.

int minimalDibuang(const vector<Interval>& a) {
    return (int)a.size() - maksSalingLepas(a);
}

// ─── 3. JUMLAH MESIN / RUANGAN MINIMUM ────────────────────
// Ini BUKAN activity selection. Semua interval harus dijadwalkan;
// yang dicari adalah tumpang tindih maksimum pada satu titik waktu.
// Teknik sapuan event: +1 saat mulai, -1 saat selesai.
// Urutan penting: pada waktu yang sama, proses SELESAI dulu kalau
// bersentuhan di ujung diperbolehkan.

int minimalRuangan(const vector<Interval>& a) {
    vector<pair<ll, int>> ev;
    for (const auto& it : a) {
        ev.push_back({it.l, +1});
        ev.push_back({it.r, -1});     // gunakan {it.r + 1, -1} bila [l,r] bilangan bulat tertutup
    }
    sort(ev.begin(), ev.end());       // (-1 < +1) -> selesai diproses lebih dulu
    int cur = 0, best = 0;
    for (auto& e : ev) { cur += e.second; best = max(best, cur); }
    return best;
}

// Versi heap: menyimpan waktu selesai ruangan yang sedang terpakai.
int minimalRuanganHeap(vector<Interval> a) {
    sort(a.begin(), a.end(), [](const Interval& x, const Interval& y) {
        return x.l < y.l;
    });
    priority_queue<ll, vector<ll>, greater<ll>> pq;   // waktu selesai paling awal di atas
    for (const auto& it : a) {
        if (!pq.empty() && pq.top() <= it.l) pq.pop();  // ruangan itu sudah bebas
        pq.push(it.r);
    }
    return (int)pq.size();
}

// ─── 4. WEIGHTED INTERVAL SCHEDULING (BUKAN GREEDY) ───────
// Maksimalkan TOTAL BOBOT. Greedy "ujung terkecil" GAGAL di sini:
//   [1,10] bobot 100  vs  [1,2] bobot 1 dan [3,4] bobot 1
//   greedy ambil dua interval kecil (total 2), optimal 100.
// Solusinya DP: urutkan menurut r, lalu
//   dp[i] = max(dp[i-1], w[i] + dp[p(i)])
// dengan p(i) = interval terakhir yang r-nya < l[i] (cari dengan binary search).

ll bobotMaksimum(vector<Interval> a, vector<ll> w) {
    int n = a.size();
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) { return a[x].r < a[y].r; });

    vector<ll> R(n), L(n), W(n);
    for (int i = 0; i < n; i++) {
        R[i] = a[ord[i]].r; L[i] = a[ord[i]].l; W[i] = w[ord[i]];
    }

    vector<ll> dp(n + 1, 0);
    for (int i = 0; i < n; i++) {
        // p = banyaknya interval (dalam urutan r) yang r-nya < L[i]
        int p = (int)(lower_bound(R.begin(), R.begin() + i, L[i]) - R.begin());
        dp[i + 1] = max(dp[i], W[i] + dp[p]);
    }
    return dp[n];
}

// ─── 5. BRUTE FORCE UNTUK STRESS TEST (n <= 20) ───────────

int bruteSalingLepas(const vector<Interval>& a) {
    int n = a.size(), best = 0;
    for (int m = 0; m < (1 << n); m++) {
        vector<Interval> s;
        for (int i = 0; i < n; i++) if (m >> i & 1) s.push_back(a[i]);
        sort(s.begin(), s.end(), [](const Interval& x, const Interval& y) {
            return x.l < y.l;
        });
        bool ok = true;
        for (int i = 1; i < (int)s.size(); i++)
            if (s[i].l <= s[i - 1].r) { ok = false; break; }
        if (ok) best = max(best, (int)s.size());
    }
    return best;
}

// ─── 6. JEBAKAN YANG SERING MEMAKAN KORBAN ────────────────
//
//  a) Mengurutkan menurut AWAL (l) -> SALAH.
//     [1,100] [2,3] [4,5] : greedy-l ambil 1, optimal 2.
//
//  b) Mengurutkan menurut PANJANG -> SALAH.
//     [1,10] [9,12] [11,20] : greedy ambil [9,12] saja (1), optimal 2.
//
//  c) Bingung tertutup vs setengah terbuka.
//     "rapat sampai jam 5" dan "rapat mulai jam 5" biasanya TIDAK bentrok.
//     Kalau begitu, syaratnya r <= l, bukan r < l.
//
//  d) Menyangka soal berbobot bisa greedy. Cek: kalau ada bobot,
//     hampir pasti DP.

// ─── MAIN: demo + stress test ─────────────────────────────

int main() {
    FASTIO;

    vector<Interval> demo = {{3,5,0}, {4,9,1}, {5,8,2}};
    cout << "saling lepas [l,r]  : " << maksSalingLepas(demo, false) << " (harusnya 1)\n";
    cout << "saling lepas [l,r)  : " << maksSalingLepas(demo, true)  << " (harusnya 2)\n";
    cout << "ruangan minimum     : " << minimalRuanganHeap(demo) << " (harusnya 2)\n";
    cout << "bobot maks (1,1,1)  : " << bobotMaksimum(demo, {1,1,1}) << " (harusnya 1, versi tertutup)\n";

    mt19937 rng(72);
    bool ok = true;
    for (int t = 0; t < 3000 && ok; t++) {
        int n = 1 + rng() % 9;
        vector<Interval> a(n);
        for (int i = 0; i < n; i++) {
            ll x = rng() % 20, y = rng() % 20;
            if (x > y) swap(x, y);
            a[i] = {x, y, i};
        }
        if (maksSalingLepas(a) != bruteSalingLepas(a)) ok = false;
    }
    cout << "stress greedy vs bf : " << (ok ? "3000 kasus OK" : "GAGAL") << '\n';

    return 0;
}
