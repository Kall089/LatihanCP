/*
============================================================
  Day 51 — Binary Search Real & Presisi | CP Template
============================================================
  ATURAN PERTAMA: kalau jawabannya bisa dinyatakan sebagai BILANGAN BULAT
  (mungkin setelah penskalaan), kerjakan sebagai integer. Seluruh materi
  ini adalah rencana cadangan, bukan pilihan utama.

  KERANGKA BAKU (pakai apa adanya):
    double lo = ..., hi = ...;
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (bisa(mid)) hi = mid;
        else           lo = mid;          <- lo = mid, BUKAN mid + 1
    }
    printf("%.9f\n", lo);

  ITERASI TETAP > EPSILON
    while (hi - lo > eps) bisa TAK BERUJUNG kalau nilainya besar:
    pada besaran 1e18, jarak antar double berdekatan sudah > 1e-9.

  BERAPA ITERASI: rentang / 2^k <= presisi
    1e9 -> 1e-6 butuh k >= 50 ; 1e18 -> 1e-9 butuh k >= 90
    100 iterasi mengecilkan rentang faktor 2^100 ~ 1e30. Selalu cukup.

  TRIK PALING PENTING: a[i] - x
    rata-rata >= x  <=>  sum(a[i] - x) >= 0
    rasio P/Q >= x  <=>  sum(p[i] - x*q[i]) >= 0
    Mengubah masalah TIDAK monoton menjadi monoton.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const double EPS = 1e-9;

// ─── 1. KERANGKA UMUM ────────────────────────────────────
// Nilai TERKECIL x pada [lo, hi] yang bisa(x) bernilai true.
// Predikat harus MONOTON: false...false true...true

template <typename P>
double cariMinimalReal(double lo, double hi, P bisa, int iter = 100) {
    for (int i = 0; i < iter; i++) {
        double mid = (lo + hi) / 2;        // untuk double ini aman (tidak meluap)
        if (bisa(mid)) hi = mid;
        else           lo = mid;           // BUKAN mid + 1
    }
    return lo;
}

// Nilai TERBESAR x yang bisa(x) true. Predikat: true...true false...false
template <typename P>
double cariMaksimalReal(double lo, double hi, P bisa, int iter = 100) {
    for (int i = 0; i < iter; i++) {
        double mid = (lo + hi) / 2;
        if (bisa(mid)) lo = mid;
        else           hi = mid;
    }
    return lo;
}

// ─── 2. PERBANDINGAN AMAN ────────────────────────────────
// JANGAN PERNAH menulis a == b untuk double.
// 0.1 + 0.2 == 0.3 bernilai FALSE.

bool eq(double a, double b)  { return fabs(a - b) < EPS; }
bool lt(double a, double b)  { return a < b - EPS; }
bool le(double a, double b)  { return a < b + EPS; }
bool gt(double a, double b)  { return a > b + EPS; }
bool ge(double a, double b)  { return a > b - EPS; }

// Untuk NILAI BESAR, epsilon absolut terlalu ketat -- pakai relatif.
bool eqRel(double a, double b, double rel = 1e-9) {
    return fabs(a - b) <= rel * max(1.0, max(fabs(a), fabs(b)));
}

// ─── 3. AKAR KUADRAT (contoh paling sederhana) ───────────

double akar(double v) {
    double lo = 0, hi = max(1.0, v);
    for (int i = 0; i < 100; i++) {
        double mid = (lo + hi) / 2;
        if (mid * mid >= v) hi = mid;
        else                lo = mid;
    }
    return lo;
}

// ─── 4. RATA-RATA MAKSIMUM DARI TEPAT k ELEMEN ───────────
// Trik a[i] - x: rata-rata >= x  <=>  sum(a[i] - x) >= 0

double rataMaksimalKElemen(const vector<double>& a, int k) {
    double lo = *min_element(a.begin(), a.end());
    double hi = *max_element(a.begin(), a.end());

    auto bisa = [&](double x) {
        vector<double> b(a.size());
        for (size_t i = 0; i < a.size(); i++) b[i] = a[i] - x;
        sort(b.rbegin(), b.rend());              // k terbesar
        double s = 0;
        for (int i = 0; i < k; i++) s += b[i];
        return s >= 0;
    };

    return cariMaksimalReal(lo, hi, bisa);
}

// ─── 5. RATA-RATA SEGMEN MAKSIMUM, PANJANG MINIMAL L ─────
// Gabungan tiga teknik: trik a[i]-x, prefix sum, minimum berjalan.

double rataSegmenMaksimal(const vector<double>& a, int L) {
    int n = a.size();
    double lo = *min_element(a.begin(), a.end());
    double hi = *max_element(a.begin(), a.end());

    auto bisa = [&](double x) {
        vector<double> pre(n + 1, 0);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + (a[i] - x);
        double minPre = 0;
        for (int i = L; i <= n; i++) {
            minPre = min(minPre, pre[i - L]);
            if (pre[i] - minPre >= 0) return true;
        }
        return false;
    };

    return cariMaksimalReal(lo, hi, bisa);
}

// ─── 6. FRACTIONAL PROGRAMMING (rasio maksimum) ──────────
// Pilih tepat k pasangan (p, q) yang memaksimalkan sum(p)/sum(q).
// rasio >= x  <=>  sum(p[i] - x*q[i]) >= 0

double rasioMaksimal(const vector<double>& p, const vector<double>& q, int k) {
    int n = p.size();
    auto bisa = [&](double x) {
        vector<double> b(n);
        for (int i = 0; i < n; i++) b[i] = p[i] - x * q[i];
        sort(b.rbegin(), b.rend());
        double s = 0;
        for (int i = 0; i < k; i++) s += b[i];
        return s >= 0;
    };
    return cariMaksimalReal(0, 1e9, bisa);
}

// ─── 7. CATATAN PENCETAKAN ───────────────────────────────
/*
    printf("%.9f\n", x);                        paling ringkas
    cout << fixed << setprecision(9) << x;      'fixed' WAJIB

    TANPA fixed, setprecision(9) berarti 9 digit SIGNIFIKAN:
        setprecision(9)          pada 1234567.891234 -> 1234567.89
        fixed << setprecision(9) pada 1234567.891234 -> 1234567.891234000

    Cetak LEBIH BANYAK desimal daripada yang diminta soal.
    Pakai double, JANGAN float (float hanya ~7 digit signifikan).
*/

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<double> a(n);
    for (double& x : a) cin >> x;

    printf("akar(2)              = %.9f\n", akar(2.0));
    printf("rata-rata maks %d el = %.9f\n", k, rataMaksimalKElemen(a, k));
    printf("rata segmen min %d   = %.9f\n", k, rataSegmenMaksimal(a, k));

    return 0;
}
