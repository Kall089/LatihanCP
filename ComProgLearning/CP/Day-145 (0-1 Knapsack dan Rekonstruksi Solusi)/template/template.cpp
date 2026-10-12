/*
============================================================
  Day 145 — 0/1 Knapsack | CP Template
============================================================
  LANGKAH PERTAMA SELALU: HITUNG n * W.
    n*W  <= 1e8  -> DP atas KAPASITAS (versi 1D)
    n*SV <= 1e8  -> DP atas NILAI (kalau W besar tapi nilai kecil)
    n <= 40      -> meet in the middle (Day 54)
  Banyak orang menulis DP dulu lalu baru sadar W = 1e18.

  INTI 0/1:
    for (i = 0..n-1)
        for (c = W; c >= w[i]; c--)          <- MUNDUR!
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);

    MUNDUR: dp[c-w[i]] masih dari barang SEBELUMNYA -> tiap barang SEKALI
    MAJU  : dp[c-w[i]] sudah diperbarui -> barang boleh BERKALI-KALI
    Satu karakter memisahkan 0/1 dari UNBOUNDED.

  GREEDY RASIO SALAH untuk 0/1. Ia benar hanya untuk FRACTIONAL (Day 74).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. KNAPSACK 0/1 VERSI 1D (default) ──────────────────

ll knapsack01(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int c = W; c >= w[i]; c--)          // MUNDUR
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

// ─── 2. VERSI 2D (dipakai kalau butuh REKONSTRUKSI) ──────

vector<vector<ll>> knapsackTabel(const vector<int>& w, const vector<ll>& v, int W) {
    int n = w.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i - 1][c];                             // tidak ambil
            if (c >= w[i - 1])
                dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i - 1]] + v[i - 1]);
        }
    return dp;
}

// Telusuri MUNDUR: nilai berubah dari baris atas -> barang itu diambil.
vector<int> rekonstruksi(const vector<int>& w, int W, const vector<vector<ll>>& dp) {
    vector<int> dipilih;
    int c = W;
    for (int i = (int)w.size(); i >= 1; i--)
        if (dp[i][c] != dp[i - 1][c]) {          // nilainya berubah -> diambil
            dipilih.push_back(i - 1);            // kembalikan ke 0-based
            c -= w[i - 1];
        }
    reverse(dipilih.begin(), dipilih.end());
    return dipilih;
}

// ─── 3. UNBOUNDED (barang boleh berkali-kali) ────────────
// Perbedaannya HANYA arah loop.

ll knapsackUnbounded(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int c = w[i]; c <= W; c++)          // MAJU
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

// ─── 4. BOUNDED (barang ke-i tersedia k[i] buah) ─────────
// Dekomposisi BINER: pecah k jadi 1, 2, 4, ..., sisa.
// O(W * sum k) menjadi O(W * sum log k). Untuk k = 1e6: 20 barang, bukan sejuta.

ll knapsackBounded(const vector<int>& w, const vector<ll>& v,
                   const vector<int>& k, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++) {
        int sisa = k[i];
        for (int p = 1; sisa > 0; p *= 2) {
            int ambil = min(p, sisa);
            sisa -= ambil;
            ll bobot = (ll)ambil * w[i], nilai = (ll)ambil * v[i];
            if (bobot > W) break;
            for (int c = W; c >= bobot; c--)     // MUNDUR (tiap paket sekali)
                dp[c] = max(dp[c], dp[c - bobot] + nilai);
        }
    }
    return dp[W];
}

// ─── 5. SUBSET SUM ───────────────────────────────────────
// Knapsack 0/1 dengan nilai = berat. bisa[0] = 1 (subhimpunan kosong).

vector<char> subsetSum(const vector<int>& a, int S) {
    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;                                 // JANGAN lupa
    for (int x : a)
        for (int c = S; c >= x; c--)             // MUNDUR
            if (bisa[c - x]) bisa[c] = 1;
    return bisa;
}

// Versi BITSET: 64x lebih cepat, dan kodenya justru lebih pendek.
template <size_t MAXS>
bitset<MAXS> subsetSumBitset(const vector<int>& a) {
    bitset<MAXS> bs;
    bs[0] = 1;
    for (int x : a) bs |= bs << x;
    return bs;
}

// ─── 6. MENGHITUNG CARA (bukan memaksimalkan) ────────────
// Struktur rekurens SAMA; hanya operator penggabungnya berubah: max -> +

ll hitungCara(const vector<int>& a, int S, ll MOD = 1000000007LL) {
    vector<ll> cara(S + 1, 0);
    cara[0] = 1;
    for (int x : a)
        for (int c = S; c >= x; c--)
            cara[c] = (cara[c] + cara[c - x]) % MOD;
    return cara[S];
}

// ─── 7. DP ATAS NILAI (kalau W sangat besar) ─────────────
// Membalik peran: dp[val] = berat MINIMUM untuk mencapai nilai val.
// Berguna saat W = 1e18 tetapi sum(v) <= 1e4.

ll knapsackAtasNilai(const vector<int>& w, const vector<ll>& v, ll W) {
    ll totalV = accumulate(v.begin(), v.end(), 0LL);
    const ll INF = LLONG_MAX / 4;
    vector<ll> dp(totalV + 1, INF);
    dp[0] = 0;

    for (size_t i = 0; i < w.size(); i++)
        for (ll val = totalV; val >= v[i]; val--)
            if (dp[val - v[i]] != INF)
                dp[val] = min(dp[val], dp[val - v[i]] + w[i]);

    for (ll val = totalV; val >= 0; val--)
        if (dp[val] <= W) return val;
    return 0;
}

// ─── 8. BRUTE FORCE (untuk stress test -- WAJIB dipakai) ──

ll knapsackNaif(const vector<int>& w, const vector<ll>& v, int W) {
    int n = w.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll bw = 0, bv = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) { bw += w[i]; bv += v[i]; }
        if (bw <= W) best = max(best, bv);
    }
    return best;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n, W;
    if (!(cin >> n >> W)) return 0;
    vector<int> w(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    cout << "0/1 knapsack   : " << knapsack01(w, v, W) << '\n';
    cout << "  cek naif     : " << knapsackNaif(w, v, W) << '\n';
    cout << "unbounded      : " << knapsackUnbounded(w, v, W) << '\n';
    cout << "atas nilai     : " << knapsackAtasNilai(w, v, W) << '\n';

    auto dp = knapsackTabel(w, v, W);
    auto pilih = rekonstruksi(w, W, dp);
    cout << "barang dipilih :";
    for (int i : pilih) cout << ' ' << i;
    cout << '\n';

    return 0;
}
