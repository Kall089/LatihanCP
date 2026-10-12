/*
============================================================
  Day 41 — Latihan Terpadu Teknik Array | CP Template
============================================================
  Kumpulan alat Day 29-40 dalam satu tempat, siap disalin.

  URUTAN BERPIKIR SEBELUM MENULIS KODE
    1. Lihat n dan Q  -> tentukan kompleksitas target
    2. Apa yang saya KUNCI?  (ujung kanan? pasangan baris? jawabannya?)
    3. Apa yang saya BUANG?  (kandidat mana yang pasti tidak berguna lagi?)
    4. Ada elemen negatif?   -> menyingkirkan sliding window
    5. Ada batas panjang?    -> menyingkirkan Kadane

  n <= 10^6 -> O(n)        n <= 10^5 -> O(n log n)
  n <= 5000 -> O(n^2)      n <= 20   -> O(2^n)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. PREFIX SUM 1D ────────────────────────────────────
// sum(l..r) 0-based inklusif = P[r+1] - P[l]
struct Prefix1D {
    vector<ll> P;
    Prefix1D(const vector<ll>& a) : P(a.size() + 1, 0) {
        for (size_t i = 0; i < a.size(); i++) P[i + 1] = P[i] + a[i];
    }
    ll sum(int l, int r) const { return P[r + 1] - P[l]; }
};

// ─── 2. PREFIX SUM 2D ────────────────────────────────────
// sum submatriks (r1,c1)..(r2,c2) inklusif, semuanya 0-based
struct Prefix2D {
    vector<vector<ll>> P;
    Prefix2D(const vector<vector<ll>>& m) {
        int R = m.size(), C = m[0].size();
        P.assign(R + 1, vector<ll>(C + 1, 0));
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                P[i+1][j+1] = m[i][j] + P[i][j+1] + P[i+1][j] - P[i][j];
    }
    ll sum(int r1, int c1, int r2, int c2) const {
        return P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1];
    }
};

// ─── 3. DIFFERENCE ARRAY ─────────────────────────────────
// semua update DULU, finalisasi SEKALI di akhir. d berukuran n+1.
struct Diff {
    vector<ll> d;
    Diff(int n) : d(n + 1, 0) {}
    void add(int l, int r, ll v) { d[l] += v; d[r + 1] -= v; }
    vector<ll> finish() {
        vector<ll> a(d.size() - 1);
        ll run = 0;
        for (size_t i = 0; i + 1 < d.size(); i++) { run += d[i]; a[i] = run; }
        return a;
    }
};

// ─── 4. KADANE ───────────────────────────────────────────
ll kadane(const vector<ll>& a) {                 // TIDAK boleh kosong
    ll best = LLONG_MIN, cur = 0;
    for (ll x : a) { cur = max(x, cur + x); best = max(best, cur); }
    return best;
}
ll kadaneBolehKosong(const vector<ll>& a) {      // jawaban minimal 0
    ll best = 0, cur = 0;
    for (ll x : a) { cur = max(0LL, cur + x); best = max(best, cur); }
    return best;
}

// ─── 5. TWO POINTERS ─────────────────────────────────────
// window terpendek dengan sum >= s. HANYA VALID kalau semua elemen >= 0.
int windowTerpendek(const vector<ll>& a, ll s) {
    int n = a.size(), l = 0, best = INT_MAX;
    ll sum = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum - a[l] >= s) sum -= a[l++];
        if (sum >= s) best = min(best, r - l + 1);
    }
    return best == INT_MAX ? -1 : best;
}

// ─── 6. MONOTONIC STACK ──────────────────────────────────
// pse[i] = indeks pertama di KIRI i dengan nilai < a[i], atau -1
vector<int> prevSmaller(const vector<ll>& a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        res[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return res;
}
// nge[i] = indeks pertama di KANAN i dengan nilai > a[i], atau n
vector<int> nextGreater(const vector<ll>& a) {
    int n = a.size();
    vector<int> res(n, n);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) { res[st.top()] = i; st.pop(); }
        st.push(i);
    }
    return res;
}
// luas persegi panjang terbesar di histogram (dipakai juga untuk grid)
ll luasHistogram(vector<int> h) {
    int m = h.size();
    h.push_back(0);                    // sentinel: stack pasti kosong di akhir
    stack<int> st;
    ll best = 0;
    for (int i = 0; i <= m; i++) {
        while (!st.empty() && h[st.top()] >= h[i]) {
            ll t = h[st.top()]; st.pop();
            ll w = st.empty() ? i : (i - st.top() - 1);
            best = max(best, t * w);
        }
        st.push(i);
    }
    return best;
}

// ─── 7. MONOTONIC DEQUE ──────────────────────────────────
// maksimum tiap jendela ukuran k. Deque menyimpan INDEKS.
vector<ll> maxJendela(const vector<ll>& a, int k) {
    deque<int> dq;
    vector<ll> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();   // kadaluarsa
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();   // tertutupi
        dq.push_back(i);
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

// ─── 8. COORDINATE COMPRESSION ───────────────────────────
// mengembalikan indeks terkompresi 0..m-1, dan daftar nilai aslinya
pair<vector<int>, vector<ll>> kompres(const vector<ll>& v) {
    vector<ll> s = v;
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    vector<int> idx(v.size());
    for (size_t i = 0; i < v.size(); i++)
        idx[i] = lower_bound(s.begin(), s.end(), v[i]) - s.begin();
    return {idx, s};
}

// ─── 9. PREFIX + HASH MAP ────────────────────────────────
// banyaknya subarray dengan jumlah tepat k
ll hitungSubarraySum(const vector<ll>& a, ll k) {
    map<ll, ll> cnt;               // map, bukan unordered_map (anti-hash)
    cnt[0] = 1;                    // prefix kosong
    ll pre = 0, res = 0;
    for (ll x : a) {
        pre += x;
        auto it = cnt.find(pre - k);
        if (it != cnt.end()) res += it->second;
        cnt[pre]++;
    }
    return res;
}
// banyaknya subarray yang jumlahnya habis dibagi m
ll hitungSubarrayHabisDibagi(const vector<ll>& a, ll m) {
    vector<ll> cnt(m, 0);
    cnt[0] = 1;
    ll pre = 0, res = 0;
    for (ll x : a) {
        pre = ((pre + x) % m + m) % m;    // jaga tetap non-negatif
        res += cnt[pre];
        cnt[pre]++;
    }
    return res;
}

// ─── 10. SWEEP LINE ──────────────────────────────────────
// overlap maksimum dari N interval TERTUTUP [l, r]
ll overlapMaksimum(const vector<pair<ll,ll>>& iv) {
    vector<pair<ll,int>> ev;
    for (auto& p : iv) { ev.push_back({p.first, +1}); ev.push_back({p.second + 1, -1}); }
    sort(ev.begin(), ev.end());
    ll cur = 0, best = 0;
    for (auto& e : ev) { cur += e.second; best = max(best, cur); }
    return best;
}

// ─── 11. STRESS TEST ─────────────────────────────────────
// Wajib untuk soal GABUNGAN: dua teknik = dua kali lipat permukaan bug.
// Pola pakai:
//   for (iter) { bangun input acak KECIL; bandingkan cepat vs brute; }
// Cetak counterexample terkecil, bukan yang pertama ditemukan.

int main() {
    FASTIO;

    // TODO: kerjakan di sini

    return 0;
}
