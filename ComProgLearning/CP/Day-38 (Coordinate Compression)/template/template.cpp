/*
============================================================
  Day 38 — Coordinate Compression | CP Template
============================================================
  KAPAN PAKAI
    nilai sampai 1e9 TAPI n cuma 1e5, dan kamu butuh array yang
    DIINDEKS OLEH NILAI (frekuensi, BIT, segment tree, bucket).

  IDIOM BAKU
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());   <- erase WAJIB
    idx = lower_bound(v.begin(), v.end(), x) - v.begin();

    unique() TIDAK menghapus apa pun sendirian -- ia hanya memindahkan
    elemen unik ke depan. Tanpa erase, size() tidak berubah dan isi di
    belakang TIDAK TERDEFINISI.

  YANG DIPERTAHANKAN : urutan relatif, kesamaan
  YANG HILANG        : jarak / selisih  -> simpan nilai asli, pakai v[i]

  JEBAKAN TERBESAR
    kumpulkan SEMUA nilai (termasuk dari QUERY) SEBELUM bangun().
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. STRUCT KOMPRESI (jenis A: buang duplikat) ────────

struct Kompres {
    vector<ll> v;

    void tambah(ll x) { v.push_back(x); }

    template <typename It>
    void tambahSemua(It b, It e) { v.insert(v.end(), b, e); }

    void bangun() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    // nilai -> peringkat (0-based). Nilai HARUS sudah ada di kamus.
    int idx(ll x) const {
        return int(lower_bound(v.begin(), v.end(), x) - v.begin());
    }

    // peringkat -> nilai asli
    ll nilai(int i) const { return v[i]; }

    int size() const { return (int)v.size(); }

    // Apakah x benar-benar ada di kamus (untuk berjaga-jaga).
    bool ada(ll x) const {
        int i = idx(x);
        return i < (int)v.size() && v[i] == x;
    }
};

// ─── 2. FUNGSI RINGKAS (kalau malas pakai struct) ────────

vector<int> kompres(vector<ll>& a) {
    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<int> hasil(a.size());
    for (size_t i = 0; i < a.size(); i++)
        hasil[i] = int(lower_bound(v.begin(), v.end(), a[i]) - v.begin());
    return hasil;
}

// ─── 3. KOMPRESI JENIS B: PERINGKAT PENUH ────────────────
// Setiap posisi mendapat peringkat UNIK; seri dipecah oleh indeks.
// Hasilnya selalu permutasi 0..n-1.

vector<int> peringkatPenuh(const vector<ll>& a) {
    int n = a.size();
    vector<int> urut(n);
    iota(urut.begin(), urut.end(), 0);
    sort(urut.begin(), urut.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;                          // pemecah seri
    });
    vector<int> rk(n);
    for (int k = 0; k < n; k++) rk[urut[k]] = k;
    return rk;
}

// ─── 4. KOMPRESI UNTUK INTERVAL ──────────────────────────
// WAJIB memasukkan r+1, kalau tidak celah antar interval HILANG.
// Interval [l, r] menjadi setengah terbuka [idx(l), idx(r+1)).

Kompres kompresInterval(const vector<pair<ll, ll>>& iv) {
    Kompres k;
    for (auto& pr : iv) {
        k.tambah(pr.first);
        k.tambah(pr.second + 1);               // <- ini yang menjaga celah
    }
    k.bangun();
    return k;
}

// ─── 5. SWEEP LINE: TOTAL PANJANG YANG TERTUTUP ──────────
// Catatan: masalah ini TIDAK butuh kompresi -- cukup sort.
// Ditaruh di sini sebagai pengingat: jangan pakai kompresi kalau
// kamu tidak butuh array yang diindeks nilai.

ll totalTertutup(vector<pair<ll, ll>> iv) {
    if (iv.empty()) return 0;
    sort(iv.begin(), iv.end());
    ll total = 0, akhir = LLONG_MIN;
    for (auto& pr : iv) {
        ll mulai = (akhir == LLONG_MIN) ? pr.first : max(pr.first, akhir + 1);
        if (pr.second >= mulai) total += pr.second - mulai + 1;
        akhir = max(akhir, pr.second);
    }
    return total;
}

// ─── 6. SWEEP: TUMPANG TINDIH MAKSIMUM ───────────────────
// Berapa interval terbanyak yang menutupi satu titik yang sama.

int tumpangTindihMaks(const vector<pair<ll, ll>>& iv) {
    vector<pair<ll, int>> ev;
    for (auto& pr : iv) {
        ev.push_back({pr.first, +1});
        ev.push_back({pr.second + 1, -1});     // keluar SETELAH r
    }
    sort(ev.begin(), ev.end());
    int cur = 0, best = 0;
    for (auto& e : ev) { cur += e.second; best = max(best, cur); }
    return best;
}

// ─── 7. KOMPRESI DUA DIMENSI ─────────────────────────────

struct Kompres2D {
    Kompres kx, ky;
    void tambah(ll x, ll y) { kx.tambah(x); ky.tambah(y); }
    void bangun() { kx.bangun(); ky.bangun(); }
    pair<int, int> idx(ll x, ll y) const { return {kx.idx(x), ky.idx(y)}; }
};

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (ll& v : a) cin >> v;

    Kompres k;
    k.tambahSemua(a.begin(), a.end());
    k.bangun();

    cout << "nilai berbeda : " << k.size() << '\n';
    cout << "hasil kompres :";
    for (ll x : a) cout << ' ' << k.idx(x);
    cout << '\n';
    cout << "peringkat penuh:";
    for (int r : peringkatPenuh(a)) cout << ' ' << r;
    cout << '\n';

    return 0;
}
