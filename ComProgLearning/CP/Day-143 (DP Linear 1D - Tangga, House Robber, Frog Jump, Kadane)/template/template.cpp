/*
============================================================
TEMPLATE Day 143 — DP Linear 1D
============================================================
Empat pola inti + variannya. Semua 0-INDEXED kecuali disebutkan.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

// ------------------------------------------------------------------
// 1. CLIMBING STAIRS — banyak cara, langkah 1 atau 2
// ------------------------------------------------------------------
ll tangga(int n) {
    ll a = 1, b = 1;                 // dp[0]=1, dp[1]=1
    for (int i = 2; i <= n; i++) { ll c = (a + b) % MOD; a = b; b = c; }
    return n == 0 ? 1 : b;
}

// 1b. Langkah 1..k, dengan anak tangga rusak (rusak[i] == true -> dp[i] = 0)
ll tanggaK(int n, int k, const vector<char>& rusak) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (rusak[i]) { dp[i] = 0; continue; }        // TUGASKAN 0, jangan skip
        for (int j = 1; j <= k && j <= i; j++)
            dp[i] = (dp[i] + dp[i - j]) % MOD;
    }
    return dp[n];
}

// 1c. Biaya minimum menaiki tangga (LC 746): biaya dibayar saat MENGINJAK
ll tanggaMinCost(const vector<ll>& cost) {
    int n = cost.size();
    ll a = 0, b = 0;                 // boleh mulai dari indeks 0 atau 1
    for (int i = 2; i <= n; i++) { ll c = min(b + cost[i-1], a + cost[i-2]); a = b; b = c; }
    return b;
}

// ------------------------------------------------------------------
// 2. HOUSE ROBBER — dilarang mengambil dua yang bersebelahan
// ------------------------------------------------------------------
ll robber(const vector<ll>& a) {
    ll p2 = 0, p1 = 0;
    for (ll x : a) {
        ll c = max(p1, p2 + x);
        p2 = p1;                     // URUTAN INI PENTING
        p1 = c;
    }
    return p1;
}

// 2b. Versi MELINGKAR: jalankan linear dua kali
ll robberCircular(const vector<ll>& a) {
    int n = a.size();
    if (n == 1) return a[0];         // WAJIB ditangani terpisah
    vector<ll> tanpaAkhir(a.begin(), a.end() - 1);
    vector<ll> tanpaAwal (a.begin() + 1, a.end());
    return max(robber(tanpaAkhir), robber(tanpaAwal));
}

// 2c. Rekonstruksi: rumah mana saja yang dirampok
vector<int> robberPilihan(const vector<ll>& a) {
    int n = a.size();
    vector<ll> dp(n + 1, 0);         // dp[i] = jawaban untuk a[0..i-1]
    for (int i = 1; i <= n; i++)
        dp[i] = max(dp[i-1], (i >= 2 ? dp[i-2] : 0) + a[i-1]);
    vector<int> pilih;
    for (int i = n; i > 0; ) {
        if (dp[i] == dp[i-1]) { i--; }                       // tidak dirampok
        else { pilih.push_back(i - 1); i -= 2; }             // dirampok
    }
    reverse(pilih.begin(), pilih.end());
    return pilih;
}

// ------------------------------------------------------------------
// 3. FROG JUMP — biaya minimum, lompatan 1..k
// ------------------------------------------------------------------
ll frog(const vector<ll>& h, int k) {
    int n = h.size();
    const ll INF = LLONG_MAX / 4;
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= k && j <= i; j++)
            dp[i] = min(dp[i], dp[i-j] + llabs(h[i] - h[i-j]));
    return dp[n-1];
}

// ------------------------------------------------------------------
// 4. KADANE — subarray TIDAK KOSONG dengan jumlah maksimum
// ------------------------------------------------------------------
ll kadane(const vector<ll>& a) {
    ll cur = a[0], best = a[0];      // BUKAN 0 -- array bisa semua negatif
    for (size_t i = 1; i < a.size(); i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}

// 4b. Kadane + indeks [bs, be]
ll kadaneIdx(const vector<ll>& a, int& bs, int& be) {
    ll cur = a[0], best = a[0];
    int s = 0; bs = be = 0;
    for (int i = 1; i < (int)a.size(); i++) {
        if (a[i] > cur + a[i]) { cur = a[i]; s = i; }   // MULAI ULANG
        else                     cur = cur + a[i];
        if (cur > best) { best = cur; bs = s; be = i; } // REKOR BARU
    }
    return best;
}

// 4c. Kadane MELINGKAR
ll kadaneCircular(const vector<ll>& a) {
    ll total = 0, mx = a[0], mn = a[0], cmx = a[0], cmn = a[0];
    for (ll x : a) total += x;
    for (size_t i = 1; i < a.size(); i++) {
        cmx = max(a[i], cmx + a[i]); mx = max(mx, cmx);
        cmn = min(a[i], cmn + a[i]); mn = min(mn, cmn);
    }
    if (mx < 0) return mx;           // semua negatif: total-mn = 0 (kosong), TIDAK SAH
    return max(mx, total - mn);
}

// 4d. Kadane PRODUK: simpan max DAN min (negatif membalik peran)
ll kadaneProduct(const vector<ll>& a) {
    ll mx = a[0], mn = a[0], best = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        ll x = a[i];
        ll nmx = max({x, mx * x, mn * x});
        ll nmn = min({x, mx * x, mn * x});
        mx = nmx; mn = nmn;          // hitung DULU, tugaskan kemudian
        best = max(best, mx);
    }
    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // Salin bagian yang dibutuhkan ke solusimu.
    return 0;
}
