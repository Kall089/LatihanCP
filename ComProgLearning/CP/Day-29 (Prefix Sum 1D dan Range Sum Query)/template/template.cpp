/*
============================================================
  Day 29 — Prefix Sum 1D | CP Template
============================================================
  KONVENSI YANG DIPAKAI (jangan dicampur dengan yang lain)
    pre berukuran n+1, pre[0] = 0
    pre[i+1] = pre[i] + a[i]
    jumlah a[l..r] = pre[r+1] - pre[l]      l, r 0-based inklusif

  KENAPA n+1
    pre[0] = 0 menghapus percabangan "if (l == 0)".
    Percabangan itu sumber bug terbesar di topik ini.

  TIPE DATA
    long long SELALU. 10^5 elemen x 10^9 = 10^14, int jebol di 2.1e9.

  TIDAK BISA PREFIX
    min, max, gcd  -> tidak punya invers, pakai Sparse Table (Day 169)
  ADA UPDATE
    -> Fenwick Tree (Day 170), bukan prefix sum
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. PREFIX SUM DASAR ─────────────────────────────────

vector<ll> bangunPrefix(const vector<ll>& a) {
    int n = a.size();
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
    return pre;
}

// jumlah a[l..r], 0-based inklusif
inline ll rangeSum(const vector<ll>& pre, int l, int r) {
    return pre[r + 1] - pre[l];
}

// ─── 2. PREFIX XOR ───────────────────────────────────────

vector<ll> bangunPrefixXor(const vector<ll>& a) {
    int n = a.size();
    vector<ll> px(n + 1, 0);
    for (int i = 0; i < n; i++) px[i + 1] = px[i] ^ a[i];
    return px;
}

inline ll rangeXor(const vector<ll>& px, int l, int r) {
    return px[r + 1] ^ px[l];
}

// ─── 3. PREFIX COUNT ─────────────────────────────────────
// Ubah pertanyaan jadi array 0/1 lalu jumlahkan. Sering lebih
// berguna daripada prefix sum biasa.

template <typename F>
vector<int> bangunPrefixCount(const vector<ll>& a, F kondisi) {
    int n = a.size();
    vector<int> c(n + 1, 0);
    for (int i = 0; i < n; i++) c[i + 1] = c[i] + (kondisi(a[i]) ? 1 : 0);
    return c;
}

// ─── 4. SUBARRAY DENGAN JUMLAH = K ───────────────────────
// Bekerja untuk bilangan NEGATIF (sliding window tidak).

ll hitungSubarraySamaDengan(const vector<ll>& a, ll K) {
    map<ll, ll> freq;                    // map, bukan unordered_map: aman dari hack
    freq[0] = 1;                         // prefix kosong -- JANGAN LUPA
    ll cur = 0, hasil = 0;
    for (ll v : a) {
        cur += v;
        auto it = freq.find(cur - K);
        if (it != freq.end()) hasil += it->second;
        freq[cur]++;
    }
    return hasil;
}

// ─── 5. SUBARRAY YANG HABIS DIBAGI K ─────────────────────

ll hitungHabisDibagi(const vector<ll>& a, ll K) {
    vector<ll> cnt(K, 0);
    cnt[0] = 1;
    ll cur = 0, hasil = 0;
    for (ll v : a) {
        cur = ((cur + v) % K + K) % K;   // normalisasi sisa NEGATIF
        hasil += cnt[cur];
        cnt[cur]++;
    }
    return hasil;
}

// ─── 6. TURUNAN UMUM ─────────────────────────────────────

// Indeks keseimbangan: jumlah kiri == jumlah kanan. -1 kalau tidak ada.
int indeksSeimbang(const vector<ll>& a) {
    vector<ll> pre = bangunPrefix(a);
    ll total = pre.back();
    for (int i = 0; i < (int)a.size(); i++)
        if (pre[i] == total - pre[i + 1]) return i;
    return -1;
}

// Jumlah maksimum segmen dengan panjang TEPAT k.
ll maxSegmenPanjangK(const vector<ll>& a, int k) {
    int n = a.size();
    if (k > n) return LLONG_MIN;
    vector<ll> pre = bangunPrefix(a);
    ll best = LLONG_MIN;
    for (int i = 0; i + k <= n; i++) best = max(best, pre[i + k] - pre[i]);
    return best;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (ll& v : a) cin >> v;

    vector<ll> pre = bangunPrefix(a);

    cout << "total            : " << pre[n] << '\n';
    cout << "jumlah a[0..n-1] : " << rangeSum(pre, 0, n - 1) << '\n';
    cout << "indeks seimbang  : " << indeksSeimbang(a) << '\n';
    cout << "subarray sum = 0 : " << hitungSubarraySamaDengan(a, 0) << '\n';

    return 0;
}
