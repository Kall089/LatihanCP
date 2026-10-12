/*
============================================================
  Day 74 — Fractional Knapsack & Greedy Rasio | Template
============================================================
  SATU KATA YANG MENENTUKAN SEGALANYA: "BOLEH DIPOTONG?"

    boleh dipotong (fractional)  -> GREEDY rasio, O(n log n)
    harus utuh     (0/1)         -> DP knapsack, O(n * W)
    boleh berkali-kali (unbounded)-> DP, loop MAJU
    jumlah terbatas per jenis     -> DP + dekomposisi biner

  Kalau kamu greedy pada soal 0/1, kamu akan WA.
  Kalau kamu DP pada soal fractional dengan berat pecahan,
  kamu bahkan tidak bisa menyusun tabelnya.

  CONTOH TANDINGAN WAJIB HAFAL (0/1, W = 10):
      barang (berat, nilai) = (6,7) (5,5) (5,5)
      rasio  : 1.167  1.0  1.0
      greedy : ambil (6,7) -> sisa 4, tidak muat apa pun -> 7
      optimal: (5,5) + (5,5) -> 10
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. FRACTIONAL KNAPSACK ───────────────────────────────
// Barang boleh dipotong. Urutkan menurut rasio nilai/berat
// MENURUN, ambil sebanyak mungkin, potong yang terakhir.
//
// Perbandingan rasio ditulis sebagai PERKALIAN SILANG agar
// eksak: v1/w1 > v2/w2  <=>  v1*w2 > v2*w1  (w positif).

double fractionalKnapsack(vector<ll> w, vector<ll> v, ll W) {
    int n = w.size();
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return (__int128)v[a] * w[b] > (__int128)v[b] * w[a];   // rasio menurun
    });

    double total = 0;
    ll sisa = W;
    for (int i : ord) {
        if (sisa == 0) break;
        if (w[i] <= sisa) {                 // ambil utuh
            total += v[i];
            sisa  -= w[i];
        } else {                            // potong
            total += (double)v[i] * sisa / w[i];
            sisa = 0;
        }
    }
    return total;
}

// Versi rasional eksak: kembalikan hasil sebagai pecahan p/q.
// Berguna kalau soal meminta jawaban eksak, bukan desimal.
pair<ll, ll> fractionalEksak(vector<ll> w, vector<ll> v, ll W) {
    int n = w.size();
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return (__int128)v[a] * w[b] > (__int128)v[b] * w[a];
    });

    ll p = 0, q = 1, sisa = W;
    for (int i : ord) {
        if (sisa == 0) break;
        if (w[i] <= sisa) { p += v[i] * q; sisa -= w[i]; }
        else {
            // p/q + v[i]*sisa/w[i]
            p = p * w[i] + (ll)v[i] * sisa * q;
            q = q * w[i];
            ll g = __gcd(p, q); if (g) { p /= g; q /= g; }
            sisa = 0;
        }
    }
    ll g = __gcd(p, q); if (g) { p /= g; q /= g; }
    return {p, q};
}

// ─── 2. 0/1 KNAPSACK (PEMBANDING) ─────────────────────────
// Bukan greedy. Loop kapasitas MUNDUR agar tiap barang sekali.

ll knapsack01(const vector<ll>& w, const vector<ll>& v, ll W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (ll c = W; c >= w[i]; c--)      // MUNDUR
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

// ─── 3. UNBOUNDED KNAPSACK ────────────────────────────────
// Barang boleh dipakai berkali-kali. Loop kapasitas MAJU.

ll knapsackUnbounded(const vector<ll>& w, const vector<ll>& v, ll W) {
    vector<ll> dp(W + 1, 0);
    for (ll c = 1; c <= W; c++)             // MAJU
        for (size_t i = 0; i < w.size(); i++)
            if (w[i] <= c) dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

// ─── 4. GREEDY RASIO PADA 0/1 (SENGAJA SALAH) ─────────────
// Disediakan HANYA untuk stress test: jalankan bersama
// knapsack01 dan lihat sendiri seberapa sering ia gagal.

ll greedyRasio01(vector<ll> w, vector<ll> v, ll W) {
    int n = w.size();
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return (__int128)v[a] * w[b] > (__int128)v[b] * w[a];
    });
    ll sisa = W, total = 0;
    for (int i : ord) if (w[i] <= sisa) { total += v[i]; sisa -= w[i]; }
    return total;
}

// ─── 5. POLA RASIO LAIN YANG BENAR ────────────────────────

// (a) Maksimalkan RATA-RATA dari k elemen terpilih:
//     bukan soal rasio biasa -> binary search on answer.
//     Ambil k elemen dengan (a[i] - x) terbesar; layak bila
//     jumlahnya >= 0.  (Day 50/51)

// (b) Maksimalkan sum(a)/sum(b)  (fractional programming):
//     cari x terbesar sehingga max sum(a[i] - x*b[i]) >= 0.
//     Fungsinya monoton turun terhadap x -> binary search.
double maksimalRasioSubset(vector<double> a, vector<double> b, int k) {
    int n = a.size();
    double lo = 0, hi = 1e9;
    for (int it = 0; it < 100; it++) {      // 100 iterasi = presisi cukup
        double x = (lo + hi) / 2;
        vector<double> d(n);
        for (int i = 0; i < n; i++) d[i] = a[i] - x * b[i];
        sort(d.rbegin(), d.rend());
        double s = 0;
        for (int i = 0; i < k; i++) s += d[i];
        if (s >= 0) lo = x; else hi = x;
    }
    return lo;
}

// (c) Tukar dua barang untuk memaksimalkan: bandingkan
//     v1*w2 vs v2*w1, bukan v1/w1 vs v2/w2. Hindari pembagian.

// ─── 6. JEBAKAN ───────────────────────────────────────────
//
//  a) Memakai greedy rasio pada soal 0/1.  -> WA
//  b) Membandingkan rasio dengan double saat v, w besar.
//     v/w dengan v, w sampai 10^9: double punya 53 bit
//     mantissa, dua rasio yang sangat dekat bisa tertukar.
//     Pakai perkalian silang.
//  c) w[i] = 0 pada perkalian silang: v1*0 > v2*w1 selalu
//     false, sehingga barang gratis bisa tenggelam.
//     Tangani w = 0 secara terpisah (ambil semuanya dulu).
//  d) Lupa bahwa jawaban fractional biasanya PECAHAN.
//     Perhatikan format keluaran yang diminta soal.
//  e) Kapasitas W besar (10^18) membuat DP mustahil — itu
//     sinyal bahwa soalnya memang fractional atau punya
//     struktur khusus.

// ─── MAIN: demo + stress test ─────────────────────────────

int main() {
    FASTIO;

    vector<ll> w = {6, 5, 5}, v = {7, 5, 5};
    ll W = 10;
    cout << fixed << setprecision(6);
    cout << "fractional   : " << fractionalKnapsack(w, v, W) << " (harusnya 11.000000 = 7 + 4/5 * 5)\n";
    cout << "0/1 optimal  : " << knapsack01(w, v, W)         << " (harusnya 10)\n";
    cout << "greedy 0/1   : " << greedyRasio01(w, v, W)      << " (harusnya 7 -- SALAH)\n";

    // Seberapa sering greedy rasio gagal pada 0/1?
    mt19937 rng(74);
    int gagal = 0, total = 20000;
    for (int t = 0; t < total; t++) {
        int n = 1 + rng() % 8;
        vector<ll> ww(n), vv(n);
        for (int i = 0; i < n; i++) { ww[i] = 1 + rng() % 12; vv[i] = 1 + rng() % 20; }
        ll cap = 1 + rng() % 25;
        if (greedyRasio01(ww, vv, cap) != knapsack01(ww, vv, cap)) gagal++;
    }
    cout << "greedy 0/1 gagal pada " << gagal << " dari " << total
         << " kasus (" << (100.0 * gagal / total) << "%)\n";

    // Verifikasi fractional >= 0/1 selalu benar
    bool ok = true;
    for (int t = 0; t < 20000 && ok; t++) {
        int n = 1 + rng() % 8;
        vector<ll> ww(n), vv(n);
        for (int i = 0; i < n; i++) { ww[i] = 1 + rng() % 12; vv[i] = 1 + rng() % 20; }
        ll cap = 1 + rng() % 25;
        if (fractionalKnapsack(ww, vv, cap) < knapsack01(ww, vv, cap) - 1e-9) ok = false;
    }
    cout << "fractional >= 0/1 : " << (ok ? "20000 kasus OK" : "GAGAL") << '\n';

    return 0;
}
