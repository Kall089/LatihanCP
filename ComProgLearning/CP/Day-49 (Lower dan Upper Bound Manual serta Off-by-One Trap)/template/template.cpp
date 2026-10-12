/*
============================================================
  Day 49 — Lower / Upper Bound Manual | CP Template
============================================================
  HAFALKAN SATU KERANGKA, BUKAN EMPAT VARIAN.

    int lo = 0, hi = n;                  konvensi [lo, hi), hi = n
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;    hindari overflow
        if (p(mid)) hi = mid;            mid MUNGKIN jawabannya
        else        lo = mid + 1;        mid PASTI bukan
    }
    return lo;                           indeks PERTAMA yang p true (atau n)

    lower_bound -> p(i) = (a[i] >= x)
    upper_bound -> p(i) = (a[i] >  x)    bedanya SATU KARAKTER

  INVARIANT: indeks < lo semuanya FALSE, indeks >= hi semuanya TRUE

  DUA PEMERIKSAAN BATAS YANG PALING SERING DILUPAKAN:
    sebelum a[i]   -> cek i < n
    sebelum a[i-1] -> cek i != 0

  JEBAKAN set/map:
    s.lower_bound(x)                    O(log n)  BENAR
    std::lower_bound(s.begin(), ...)    O(n)      TLE senyap
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. KERANGKA UMUM ────────────────────────────────────
// Indeks PERTAMA pada [0, n) yang p(i) bernilai true.
// Predikat harus MONOTON: false...false true...true
// Mengembalikan n kalau tidak ada yang true.

template <typename P>
int cariPertamaTrue(int n, P p) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (p(mid)) hi = mid;
        else        lo = mid + 1;
    }
    return lo;
}

// Indeks TERAKHIR yang p(i) true, pola: true...true false...false
// Mengembalikan -1 kalau tidak ada.
// PERHATIKAN +1 pada mid: tanpa itu loopnya TAK BERUJUNG.
template <typename P>
int cariTerakhirTrue(int n, P p) {
    int lo = -1, hi = n - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;      // BULATKAN KE ATAS
        if (p(mid)) lo = mid;
        else        hi = mid - 1;
    }
    return lo;
}

// ─── 2. LOWER / UPPER BOUND MANUAL ───────────────────────

int lowerBound(const vector<int>& a, int x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;
        else             lo = mid + 1;
    }
    return lo;
}

int upperBound(const vector<int>& a, int x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] > x) hi = mid;              // satu karakter berbeda
        else            lo = mid + 1;
    }
    return lo;
}

// ─── 3. TURUNAN YANG LANGSUNG TERPAKAI ───────────────────

bool ada(const vector<int>& a, int x) {
    int i = lowerBound(a, x);
    return i < (int)a.size() && a[i] == x;     // cek batas DULU
}

int hitungSamaDengan(const vector<int>& a, int x) {
    return upperBound(a, x) - lowerBound(a, x);
}

// Banyaknya elemen pada rentang [L, R] inklusif.
int hitungRentang(const vector<int>& a, int L, int R) {
    if (L > R) return 0;
    return upperBound(a, R) - lowerBound(a, L);
}

// Nilai terbesar yang <= x. false kalau tidak ada.
bool terbesarKurangSama(const vector<int>& a, int x, int& hasil) {
    int i = upperBound(a, x);
    if (i == 0) return false;                  // semua elemen > x
    hasil = a[i - 1];
    return true;
}

// Nilai terkecil yang >= x. false kalau tidak ada.
bool terkecilLebihSama(const vector<int>& a, int x, int& hasil) {
    int i = lowerBound(a, x);
    if (i == (int)a.size()) return false;      // semua elemen < x
    hasil = a[i];
    return true;
}

// Nilai TERDEKAT dengan x. Array tidak boleh kosong.
int terdekat(const vector<int>& a, int x) {
    int i = lowerBound(a, x);
    if (i == 0) return a[0];                   // semua lebih besar
    if (i == (int)a.size()) return a.back();   // semua lebih kecil
    return (x - a[i - 1] <= a[i] - x) ? a[i - 1] : a[i];
}

// ─── 4. BINARY SEARCH PADA RENTANG NILAI (pratinjau Day 50) ──
// Ruang pencariannya NILAI, bukan indeks. Di sini
// lo + (hi - lo) / 2 bukan lagi kebiasaan baik, melainkan KEHARUSAN:
// dengan hi = 1e18, (lo + hi) MELUAP di long long.

template <typename P>
ll cariNilaiTerkecil(ll lo, ll hi, P bisa) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (bisa(mid)) hi = mid;
        else           lo = mid + 1;
    }
    return lo;
}

// ─── 5. CATATAN STL ──────────────────────────────────────
/*
    auto it = lower_bound(a.begin(), a.end(), x);
    int idx = it - a.begin();

    array MENURUN  : lower_bound(a.begin(), a.end(), x, greater<int>());
    equal_range    : auto [lb, ub] = equal_range(a.begin(), a.end(), x);

    set/map        : s.lower_bound(x)   <- FUNGSI ANGGOTA, O(log n)
                     JANGAN std::lower_bound(s.begin(), s.end(), x) -> O(n)
*/

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());                  // binary search BUTUH terurut

    int x;
    if (!(cin >> x)) return 0;

    cout << "lower_bound(" << x << ") = " << lowerBound(a, x) << '\n';
    cout << "upper_bound(" << x << ") = " << upperBound(a, x) << '\n';
    cout << "jumlah == " << x << "     = " << hitungSamaDengan(a, x) << '\n';
    cout << "ada?                = " << (ada(a, x) ? "YA" : "TIDAK") << '\n';
    cout << "terdekat            = " << terdekat(a, x) << '\n';

    int v;
    cout << "terbesar <= " << x << "    = ";
    if (terbesarKurangSama(a, x, v)) cout << v << '\n'; else cout << "tidak ada\n";
    cout << "terkecil >= " << x << "    = ";
    if (terkecilLebihSama(a, x, v)) cout << v << '\n'; else cout << "tidak ada\n";

    return 0;
}
