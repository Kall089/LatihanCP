/*
============================================================
  Day 54 — Meet in the Middle | CP Template
============================================================
  TANDA PENGENAL: n <= 40 (kadang 35 atau 45) + "pilih subhimpunan".
  Batas itu tidak muncul kebetulan -- penyusun soal memilihnya persis
  agar 2^(n/2) lolos dan 2^n tidak.

    2^40 = 1e12   MUSTAHIL
    2^20 + 2^20 = 2e6   SEKETIKA
  Kita menukar PERKALIAN menjadi PENJUMLAHAN.

  KERANGKA
    1. bagi jadi dua paruh (k = n/2)
    2. bangkitkan SELURUH subset masing-masing
    3. urutkan salah satu paruh
    4. PREFIX MAKSIMUM   <- WAJIB kalau ada bobot DAN nilai terpisah
    5. untuk tiap subset paruh lain, binary search

  PERIKSA DULU SEBELUM MENULIS:
    bobot kecil (W <= 1e6)? -> DP knapsack O(n W) lebih sederhana (Day 145)
    n <= 20?                -> brute force 2^n langsung
    n > 45?                 -> 2^22 x 45 terlalu berat, cari cara lain

  BUG NOMOR SATU: lupa prefix maksimum. Ia HANYA muncul saat bobot dan
  nilai terpisah, sehingga sering lolos dari soal-soal awal.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. BANGKITKAN SELURUH SUBSET ────────────────────────
// O(2^k), bukan O(2^k * k): bangun dari subset yang satu bit lebih kecil.

vector<ll> semuaSubset(const vector<ll>& a) {
    int k = a.size();
    vector<ll> hasil(1 << k, 0);
    for (int mask = 1; mask < (1 << k); mask++) {
        int b = __builtin_ctz(mask);              // bit terendah yang menyala
        hasil[mask] = hasil[mask ^ (1 << b)] + a[b];
    }
    return hasil;
}

// ─── 2. POLA 1: HITUNG SUBSET BERJUMLAH TEPAT X ──────────
// Setiap subset penuh terhitung TEPAT SEKALI karena pembagian
// kiri/kanan sudah tetap -- tidak ada perhitungan ganda.
// Subset KOSONG ikut terhitung; koreksi kalau soal melarangnya.

ll hitungSubsetJumlah(const vector<ll>& a, ll X) {
    int n = a.size(), k = n / 2;
    vector<ll> sk = semuaSubset(vector<ll>(a.begin(), a.begin() + k));
    vector<ll> sn = semuaSubset(vector<ll>(a.begin() + k, a.end()));

    sort(sk.begin(), sk.end());

    ll total = 0;
    for (ll s : sn) {
        ll butuh = X - s;
        total += upper_bound(sk.begin(), sk.end(), butuh)
               - lower_bound(sk.begin(), sk.end(), butuh);
    }
    return total;
}

// ─── 3. POLA 2: MAKSIMALKAN TANPA MELEBIHI BATAS ─────────

ll maksTanpaMelebihi(const vector<ll>& a, ll batas) {
    int n = a.size(), k = n / 2;
    vector<ll> sk = semuaSubset(vector<ll>(a.begin(), a.begin() + k));
    vector<ll> sn = semuaSubset(vector<ll>(a.begin() + k, a.end()));

    sort(sk.begin(), sk.end());
    for (size_t i = 1; i < sk.size(); i++)        // prefix maksimum
        sk[i] = max(sk[i], sk[i - 1]);

    ll best = 0;
    for (ll s : sn) {
        if (s > batas) continue;
        ll sisa = batas - s;
        int idx = int(upper_bound(sk.begin(), sk.end(), sisa) - sk.begin()) - 1;
        if (idx >= 0) best = max(best, s + sk[idx]);
    }
    return best;
}

// ─── 4. POLA 3: KNAPSACK 0/1 (bobot dan nilai TERPISAH) ──
// DI SINILAH prefix maksimum benar-benar WAJIB: subset dengan bobot
// lebih kecil bisa punya nilai lebih besar, sehingga "posisi terakhir
// yang muat" belum tentu yang terbaik.

struct Barang { ll bobot, nilai; };

vector<pair<ll, ll>> bangkitPasangan(const vector<Barang>& b, int mulai, int akhir) {
    int m = akhir - mulai;
    vector<pair<ll, ll>> v(1 << m);
    for (int mask = 1; mask < (1 << m); mask++) {
        int i = __builtin_ctz(mask);
        auto prev = v[mask ^ (1 << i)];
        v[mask] = {prev.first + b[mulai + i].bobot, prev.second + b[mulai + i].nilai};
    }
    return v;
}

ll knapsackMitm(const vector<Barang>& b, ll kapasitas) {
    int n = b.size(), k = n / 2;
    auto A = bangkitPasangan(b, 0, k);
    auto B = bangkitPasangan(b, k, n);

    sort(A.begin(), A.end());                     // urut berdasarkan BOBOT
    for (size_t i = 1; i < A.size(); i++)         // prefix maksimum atas NILAI
        A[i].second = max(A[i].second, A[i - 1].second);

    ll best = 0;
    for (auto& pr : B) {
        if (pr.first > kapasitas) continue;
        ll sisa = kapasitas - pr.first;
        int idx = int(upper_bound(A.begin(), A.end(),
                      make_pair(sisa, LLONG_MAX)) - A.begin()) - 1;
        if (idx >= 0) best = max(best, pr.second + A[idx].second);
    }
    return best;
}

// ─── 5. POLA 4: JUMLAH SUBSET TERDEKAT DENGAN TARGET ─────
// Perlu memeriksa DUA kandidat di sekitar lower_bound.

ll terdekatDenganTarget(const vector<ll>& a, ll target) {
    int n = a.size(), k = n / 2;
    vector<ll> sk = semuaSubset(vector<ll>(a.begin(), a.begin() + k));
    vector<ll> sn = semuaSubset(vector<ll>(a.begin() + k, a.end()));

    sort(sk.begin(), sk.end());

    ll best = LLONG_MAX, bestVal = 0;
    for (ll s : sn) {
        ll butuh = target - s;
        int i = int(lower_bound(sk.begin(), sk.end(), butuh) - sk.begin());
        for (int d = -1; d <= 0; d++) {           // dua kandidat di sekitarnya
            int j = i + d;
            if (j < 0 || j >= (int)sk.size()) continue;
            ll tot = s + sk[j];
            if (llabs(tot - target) < best) { best = llabs(tot - target); bestVal = tot; }
        }
    }
    return bestVal;
}

// ─── 6. VARIAN TANPA BITMASK: 4-SUM ──────────────────────
// Semangat yang sama: n^4 menjadi n^2 + n^2.

ll empatSum(const vector<ll>& A, const vector<ll>& B,
            const vector<ll>& C, const vector<ll>& D) {
    map<ll, ll> peta;                              // map, bukan unordered: aman dari hack
    for (ll x : A) for (ll y : B) peta[x + y]++;

    ll total = 0;
    for (ll z : C) for (ll w : D) {
        auto it = peta.find(-(z + w));
        if (it != peta.end()) total += it->second;
    }
    return total;
}

// ─── 7. BRUTE FORCE (untuk stress test -- WAJIB dipakai) ──

ll hitungNaif(const vector<ll>& a, ll X) {
    int n = a.size();
    ll c = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll s = 0;
        for (int i = 0; i < n; i++) if (mask >> i & 1) s += a[i];
        if (s == X) c++;
    }
    return c;
}

ll maksNaif(const vector<ll>& a, ll batas) {
    int n = a.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll s = 0;
        for (int i = 0; i < n; i++) if (mask >> i & 1) s += a[i];
        if (s <= batas) best = max(best, s);
    }
    return best;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    ll X;
    if (!(cin >> n >> X)) return 0;
    vector<ll> a(n);
    for (ll& v : a) cin >> v;

    cout << "subset jumlah = " << X << " : " << hitungSubsetJumlah(a, X) << '\n';
    cout << "  cek naif             : " << hitungNaif(a, X) << '\n';
    cout << "maks tanpa lebih " << X << "  : " << maksTanpaMelebihi(a, X) << '\n';
    cout << "  cek naif             : " << maksNaif(a, X) << '\n';
    cout << "terdekat dengan " << X << "   : " << terdekatDenganTarget(a, X) << '\n';

    return 0;
}
