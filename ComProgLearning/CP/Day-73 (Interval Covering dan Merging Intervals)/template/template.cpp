/*
============================================================
  Day 73 — Interval Covering & Merging | Template
============================================================
  DUA POLA YANG SANGAT BERBEDA

  MERGING  — gabungkan interval yang beririsan
      urut menurut AWAL (l)
      O(n log n), hasilnya daftar interval terpisah

  COVERING — tutupi target [S, T] dengan interval sesedikit mungkin
      urut menurut AWAL (l)
      dari posisi 'sampai', ambil yang JANGKAUANNYA TERJAUH
      O(n log n), bisa IMPOSSIBLE

  Perhatikan: KEDUANYA urut menurut l.
  Bandingkan Day 72 (activity selection) yang urut menurut r.
  Kriteria pengurutan ditentukan oleh PERTANYAAN, bukan oleh
  bentuk datanya.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, ll> pll;

// ─── 1. MERGE INTERVALS ───────────────────────────────────
// Gabungkan semua interval yang beririsan.
// gabungSentuh = true  -> [1,3] dan [3,5] digabung menjadi [1,5]
// gabungSentuh = false -> keduanya tetap terpisah (model setengah terbuka)

vector<pll> gabungInterval(vector<pll> a, bool gabungSentuh = true) {
    if (a.empty()) return {};
    sort(a.begin(), a.end());              // urut menurut l, lalu r

    vector<pll> res;
    res.push_back(a[0]);
    for (size_t i = 1; i < a.size(); i++) {
        ll l = a[i].first, r = a[i].second;
        bool nyambung = gabungSentuh ? (l <= res.back().second)
                                     : (l <  res.back().second);
        if (nyambung) res.back().second = max(res.back().second, r);
        else          res.push_back({l, r});
    }
    return res;
}

// Total panjang yang tertutupi (setelah digabung).
ll totalPanjang(const vector<pll>& a) {
    ll s = 0;
    for (auto& [l, r] : gabungInterval(a)) s += r - l;
    return s;
}

// ─── 2. INTERVAL COVERING ─────────────────────────────────
// Tutupi [S, T] dengan interval sesedikit mungkin.
// Mengembalikan -1 kalau tidak mungkin.
//
// INTI ALGORITMA:
//   'sampai' = sejauh mana [S, T] sudah tertutupi
//   di antara semua interval dengan l <= sampai,
//   ambil yang r-nya TERBESAR
//
// Interval dianggap menutupi rentang tertutup; syarat menyambung
// adalah l <= sampai (bersentuhan sudah cukup untuk menutupi
// garis kontinu).

int minimalPenutup(vector<pll> a, ll S, ll T) {
    sort(a.begin(), a.end());
    ll sampai = S;
    int hit = 0;
    size_t i = 0;
    while (sampai < T) {
        ll terjauh = sampai;
        // ambil semua interval yang bisa dimulai dari 'sampai'
        while (i < a.size() && a[i].first <= sampai) {
            terjauh = max(terjauh, a[i].second);
            i++;
        }
        if (terjauh == sampai) return -1;   // macet: ada lubang
        sampai = terjauh;
        hit++;
    }
    return hit;
}

// Versi yang juga mengembalikan interval mana saja yang dipakai.
vector<pll> pilihPenutup(vector<pll> a, ll S, ll T) {
    sort(a.begin(), a.end());
    ll sampai = S;
    vector<pll> res;
    size_t i = 0;
    while (sampai < T) {
        ll terjauh = sampai;
        pll pilih = {0, 0};
        while (i < a.size() && a[i].first <= sampai) {
            if (a[i].second > terjauh) { terjauh = a[i].second; pilih = a[i]; }
            i++;
        }
        if (terjauh == sampai) return {};    // tidak mungkin
        res.push_back(pilih);
        sampai = terjauh;
    }
    return res;
}

// ─── 3. INTERVAL POINT COVERING (dual activity selection) ─
// Titik minimum sehingga setiap interval memuat minimal satu titik.
// Jawabannya = jumlah interval saling lepas maksimum.
// Urut menurut r, tembak di r.

int minimalTitik(vector<pll> a) {
    sort(a.begin(), a.end(), [](const pll& x, const pll& y) {
        return x.second < y.second;
    });
    int hit = 0;
    ll titik = LLONG_MIN;
    for (auto& [l, r] : a) {
        if (l > titik) { hit++; titik = r; }   // tembak di ujung kanan
    }
    return hit;
}

// ─── 4. INSERT INTERVAL ───────────────────────────────────
// Sisipkan interval baru ke daftar yang SUDAH terurut dan terpisah.
// O(n) tanpa pengurutan ulang.

vector<pll> sisipkan(const vector<pll>& a, pll baru) {
    vector<pll> res;
    size_t i = 0, n = a.size();
    while (i < n && a[i].second < baru.first) res.push_back(a[i++]);
    while (i < n && a[i].first <= baru.second) {
        baru.first  = min(baru.first,  a[i].first);
        baru.second = max(baru.second, a[i].second);
        i++;
    }
    res.push_back(baru);
    while (i < n) res.push_back(a[i++]);
    return res;
}

// ─── 5. LUBANG (GAP) DI ANTARA INTERVAL ───────────────────
// Bagian dari [S, T] yang TIDAK tertutupi.

vector<pll> cariLubang(vector<pll> a, ll S, ll T) {
    vector<pll> g, m = gabungInterval(a);
    ll cur = S;
    for (auto& [l, r] : m) {
        if (r <= S) continue;
        if (l >= T) break;
        if (l > cur) g.push_back({cur, min(l, T)});
        cur = max(cur, r);
        if (cur >= T) break;
    }
    if (cur < T) g.push_back({cur, T});
    return g;
}

// ─── 6. BRUTE FORCE UNTUK STRESS TEST ─────────────────────

int bruteCovering(const vector<pll>& a, ll S, ll T) {
    int n = a.size(), best = INT_MAX;
    for (int m = 0; m < (1 << n); m++) {
        vector<pll> s;
        for (int i = 0; i < n; i++) if (m >> i & 1) s.push_back(a[i]);
        // periksa apakah gabungan s menutupi [S, T] tanpa lubang
        auto g = gabungInterval(s);
        bool ok = false;
        for (auto& [l, r] : g) if (l <= S && r >= T) { ok = true; break; }
        if (ok) best = min(best, __builtin_popcount(m));
    }
    return best == INT_MAX ? -1 : best;
}

// ─── 7. JEBAKAN ───────────────────────────────────────────
//
//  a) MERGING urut menurut l. Kalau kamu urut menurut r,
//     penggabungannya salah.
//     COVERING juga urut menurut l.
//     ACTIVITY SELECTION (Day 72) urut menurut r.
//     Jangan mencampuradukkan ketiganya.
//
//  b) Pada merging, res.back().second = a[i].second SALAH.
//     Harus max(...). Contoh: [1,10] lalu [2,3] -> tetap [1,10].
//
//  c) Pada covering, mengambil interval pertama yang muat
//     (bukan yang terjauh) SALAH.
//
//  d) Covering bisa IMPOSSIBLE. Jangan lupa menanganinya.
//
//  e) Bilangan bulat vs kontinu. Kalau menutupi {1..T} sebagai
//     himpunan bilangan bulat, [1,3] dan [4,6] SUDAH menyambung.
//     Kalau garis kontinu, keduanya menyisakan lubang (3,4).
//     Perlakuan yang lazim: pada versi bilangan bulat, ubah
//     [l, r] menjadi [l, r+1] lalu pakai kode kontinu.

// ─── MAIN: demo + stress test ─────────────────────────────

int main() {
    FASTIO;

    vector<pll> demo = {{1,3},{2,6},{8,10},{15,18}};
    cout << "merge : ";
    for (auto& [l, r] : gabungInterval(demo)) cout << "[" << l << "," << r << "] ";
    cout << "(harusnya [1,6] [8,10] [15,18])\n";

    vector<pll> cov = {{0,3},{2,6},{5,9},{8,12}};
    cout << "cover [0,12] : " << minimalPenutup(cov, 0, 12) << " (harusnya 4)\n";
    cout << "cover [0,20] : " << minimalPenutup(cov, 0, 20) << " (harusnya -1)\n";

    vector<pll> tk = {{1,4},{2,5},{7,9}};
    cout << "titik minimum: " << minimalTitik(tk) << " (harusnya 2)\n";

    mt19937 rng(73);
    bool ok = true;
    for (int t = 0; t < 4000 && ok; t++) {
        int n = 1 + rng() % 9;
        vector<pll> a(n);
        for (int i = 0; i < n; i++) {
            ll x = rng() % 12, y = x + 1 + rng() % 6;
            a[i] = {x, y};
        }
        ll S = 0, T = 1 + rng() % 12;
        if (minimalPenutup(a, S, T) != bruteCovering(a, S, T)) ok = false;
    }
    cout << "stress cover : " << (ok ? "4000 kasus OK" : "GAGAL") << '\n';

    return 0;
}
