/*
============================================================
✅ SOLUSI Exercise 4: Enam Klaim
============================================================
Difficulty: Medium | Kompleksitas: O(2^n * n) atau O(n! * n), n <= 8

── TIGA DARI ENAM KLAIM ITU SALAH ──────────────────────────
  1. interval, ambil r terkecil          -> BENAR   (Day 72)
  2. interval, ambil TERPENDEK dulu      -> SALAH
  3. jumlah waktu selesai, terpendek dulu-> BENAR   (Day 71, SPT)
  4. knapsack 0/1, rasio tertinggi       -> SALAH   (Day 74)
  5. gabung tumpukan, urut lalu berurutan-> SALAH   (Day 75)
  6. keterlambatan maksimum, tenggat awal-> BENAR   (Day 78, EDF)

Kalau tebakanmu sebelum menulis kode berbeda dari daftar ini,
selisihnya adalah ukuran seberapa jauh intuisimu masih bisa
diperbaiki. Itu informasi yang berharga, bukan kegagalan.

── CONTOH TANDINGAN UNTUK YANG SALAH ───────────────────────
  Klaim 2 : [1,10] [9,12] [11,20]
            terpendek dulu ambil [9,12] saja  -> 1
            optimal [1,10] dan [11,20]        -> 2
  Klaim 4 : W = 10, (berat,nilai) = (6,7) (5,5) (5,5)
            greedy 7, optimal 10
  Klaim 5 : {1,1,1,1,1,1}
            sekuensial 20, Huffman 16

── MEMILIH BENTUK BRUTE FORCE ──────────────────────────────
Batasan n <= 8 memberi kebebasan penuh. Yang penting memilih
bentuk yang SESUAI jenis soalnya:

  MEMILIH sebagian (klaim 1, 2, 4)  -> seluruh 2^n himpunan bagian
  MENYUSUN urutan (klaim 3, 6)      -> seluruh n! permutasi
  MENGGABUNGKAN berulang (klaim 5)  -> rekursi atas semua pasangan

Memakai bentuk yang salah menghasilkan brute force yang juga
salah — dan brute force yang salah lebih berbahaya daripada
tidak punya brute force sama sekali, karena ia memberi rasa
aman palsu.

── KENAPA MENULIS ENAM BRUTE FORCE ITU BERHARGA ────────────
Terasa membosankan, dan itu memang intinya. Brute force yang
membosankan dan jelas benar lebih berharga daripada satu solusi
pintar yang mungkin salah.

Aturan penting: JANGAN mengoptimalkan brute force. Setiap
optimasi adalah kesempatan untuk salah. Kalau terlalu lambat,
kecilkan n — bukan optimalkan kodenya.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai bentuk brute force yang tidak sesuai.
2. "Memperbaiki" strategi yang sedang diuji.
3. Lupa bahwa klaim 5 butuh rekursi, bukan permutasi: urutan
   penggabungan bukan permutasi elemen.
4. Interval setengah terbuka vs tertutup (Day 72). Kode di
   bawah memakai [l, r).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ── klaim 1 & 2: interval saling lepas [l, r) ──
int bruteInterval(const vector<pair<ll, ll>>& v) {
    int n = v.size(), best = 0;
    for (int m = 0; m < (1 << n); m++) {
        vector<pair<ll, ll>> s;
        for (int i = 0; i < n; i++) if (m >> i & 1) s.push_back(v[i]);
        sort(s.begin(), s.end());
        bool ok = true;
        for (size_t i = 1; i < s.size(); i++)
            if (s[i].first < s[i - 1].second) { ok = false; break; }
        if (ok) best = max(best, (int)s.size());
    }
    return best;
}

int greedyUjungKecil(vector<pair<ll, ll>> v) {
    sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.second < b.second; });
    ll akhir = LLONG_MIN; int hit = 0;
    for (auto& [l, r] : v) if (l >= akhir) { hit++; akhir = r; }
    return hit;
}

int greedyTerpendek(vector<pair<ll, ll>> v) {
    sort(v.begin(), v.end(), [](auto& a, auto& b) {
        return a.second - a.first < b.second - b.first;
    });
    vector<pair<ll, ll>> pilih;
    for (auto& iv : v) {
        bool bentrok = false;
        for (auto& p : pilih)
            if (iv.first < p.second && p.first < iv.second) { bentrok = true; break; }
        if (!bentrok) pilih.push_back(iv);
    }
    return (int)pilih.size();
}

// ── klaim 3: jumlah waktu selesai ──
ll bruteFlow(vector<ll> t) {
    sort(t.begin(), t.end());
    ll best = LLONG_MAX;
    do {
        ll c = 0, s = 0;
        for (ll x : t) { c += x; s += c; }
        best = min(best, s);
    } while (next_permutation(t.begin(), t.end()));
    return best;
}
ll greedySPT(vector<ll> t) {
    sort(t.begin(), t.end());
    ll c = 0, s = 0;
    for (ll x : t) { c += x; s += c; }
    return s;
}

// ── klaim 4: knapsack 0/1 ──
ll bruteKnap(const vector<pair<ll, ll>>& b, ll W) {
    vector<ll> dp(W + 1, 0);
    for (auto& [w, v] : b)
        for (ll c = W; c >= w; c--) dp[c] = max(dp[c], dp[c - w] + v);
    return dp[W];
}
ll greedyKnap(const vector<pair<ll, ll>>& b, ll W) {
    vector<int> ord(b.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        __int128 k = (__int128)b[x].second * b[y].first;
        __int128 n = (__int128)b[y].second * b[x].first;
        if (k != n) return k > n;
        return x < y;                            // tie-break indeks (Day 76)
    });
    ll sisa = W, tot = 0;
    for (int i : ord) if (b[i].first <= sisa) { tot += b[i].second; sisa -= b[i].first; }
    return tot;
}

// ── klaim 5: menggabungkan tumpukan ──
ll bruteGabung(vector<ll> a) {
    if (a.size() <= 1) return 0;
    ll best = LLONG_MAX;
    int n = a.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            vector<ll> b;
            for (int k = 0; k < n; k++) if (k != i && k != j) b.push_back(a[k]);
            b.push_back(a[i] + a[j]);
            best = min(best, a[i] + a[j] + bruteGabung(b));
        }
    return best;
}
ll greedySekuensial(vector<ll> a) {
    if (a.size() <= 1) return 0;
    sort(a.begin(), a.end());
    ll cur = a[0], tot = 0;
    for (size_t i = 1; i < a.size(); i++) { cur += a[i]; tot += cur; }
    return tot;
}

// ── klaim 6: keterlambatan maksimum ──
ll bruteLmax(vector<pair<ll, ll>> j) {       // (durasi, tenggat)
    sort(j.begin(), j.end());
    ll best = LLONG_MAX;
    do {
        ll t = 0, w = LLONG_MIN;
        for (auto& [dur, d] : j) { t += dur; w = max(w, t - d); }
        best = min(best, w);
    } while (next_permutation(j.begin(), j.end()));
    return best;
}
ll greedyEDF(vector<pair<ll, ll>> j) {
    sort(j.begin(), j.end(), [](auto& a, auto& b) { return a.second < b.second; });
    ll t = 0, w = LLONG_MIN;
    for (auto& [dur, d] : j) { t += dur; w = max(w, t - d); }
    return w;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K, n;
    if (!(cin >> K >> n)) return 0;

    ll g = 0, o = 0;
    if (K == 1 || K == 2) {
        vector<pair<ll, ll>> v(n);
        for (auto& [l, r] : v) cin >> l >> r;
        o = bruteInterval(v);
        g = (K == 1) ? greedyUjungKecil(v) : greedyTerpendek(v);
    } else if (K == 3) {
        vector<ll> t(n);
        for (ll& x : t) cin >> x;
        o = bruteFlow(t);
        g = greedySPT(t);
    } else if (K == 4) {
        ll W;
        cin >> W;
        vector<pair<ll, ll>> b(n);
        for (auto& [w, v] : b) cin >> w >> v;
        o = bruteKnap(b, W);
        g = greedyKnap(b, W);
    } else if (K == 5) {
        vector<ll> a(n);
        for (ll& x : a) cin >> x;
        o = bruteGabung(a);
        g = greedySekuensial(a);
    } else {
        vector<pair<ll, ll>> j(n);
        for (auto& [t, d] : j) cin >> t >> d;
        o = bruteLmax(j);
        g = greedyEDF(j);
    }

    if (g == o) cout << "BENAR\n";
    else cout << g << ' ' << o << '\n';
    return 0;
}
