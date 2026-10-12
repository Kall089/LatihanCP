/*
============================================================
  Day 52 — Ternary Search | CP Template
============================================================
  MONOTON  -> binary search
  UNIMODAL -> ternary search   (naik lalu turun, SATU puncak)

  URUTAN PERTIMBANGAN SEBELUM MEMAKAI TERNARY:
    1. Adakah solusi EKSAK?  sum|a[i]-x| -> median
                             sum(a[i]-x)^2 -> rata-rata
                             ax^2+bx+c -> -b/(2a)
    2. Bisakah jadi BINARY SEARCH PADA SELISIH? (untuk domain integer)
    3. Baru ternary search.

  BAHAYA UTAMA: kalau fungsinya TIDAK unimodal, ternary search GAGAL
  DIAM-DIAM -- memberi jawaban yang terlihat masuk akal tetapi salah.
  UJI DULU dengan f(x) = (x-3)^2 yang jawabannya kamu tahu.

  BIAYA: f dievaluasi DUA KALI per iterasi, dan tiap langkah hanya
  membuang 1/3 (bukan 1/2), sehingga butuh LEBIH BANYAK iterasi
  daripada binary search. Bisa 4x lebih lambat.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. TERNARY SEARCH REAL: MINIMUM ─────────────────────
// Mengembalikan titik x yang meminimumkan f pada [lo, hi].

template <typename F>
double cariMinimum(double lo, double hi, F f, int iter = 200) {
    for (int i = 0; i < iter; i++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2;        // minimum ada di kiri m2
        else               lo = m1;        // minimum ada di kanan m1
    }
    return (lo + hi) / 2;
}

// MAKSIMUM: cari minimum dari -f. Lebih aman daripada membalik tanda
// secara manual, karena tanda yang tertukar adalah bug paling umum di sini.
template <typename F>
double cariMaksimum(double lo, double hi, F f, int iter = 200) {
    return cariMinimum(lo, hi, [&](double x) { return -f(x); }, iter);
}

// ─── 2. TERNARY SEARCH INTEGER ───────────────────────────
// Menyisakan beberapa kandidat lalu memeriksanya manual, karena pada
// domain diskrit m1 dan m2 bisa berdekatan sehingga f(m1) == f(m2)
// tanpa memberi informasi arah -- dan loopnya bisa macet.

template <typename F>
int cariMinimumInt(int lo, int hi, F f) {
    while (hi - lo > 2) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2 - 1;
        else               lo = m1 + 1;
    }
    int best = lo;
    for (int i = lo + 1; i <= hi; i++)
        if (f(i) < f(best)) best = i;
    return best;
}

// ─── 3. BINARY SEARCH PADA SELISIH (DISARANKAN untuk integer) ──
// f unimodal (naik lalu turun) -> selisih f(i+1)-f(i) MONOTON menurun.
// Kerangkanya sama persis dengan Day 49, lebih sedikit iterasi,
// dan tidak ada kasus tepi yang merepotkan.

template <typename F>
int cariPuncak(int lo, int hi, F f) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid) < f(mid + 1)) lo = mid + 1;   // masih menanjak
        else                     hi = mid;        // sudah menurun
    }
    return lo;
}

// Versi untuk lembah (turun lalu naik): cari titik terendah.
template <typename F>
int cariLembah(int lo, int hi, F f) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid) > f(mid + 1)) lo = mid + 1;   // masih menurun
        else                     hi = mid;
    }
    return lo;
}

// ─── 4. SOLUSI EKSAK (jangan pakai ternary kalau mengenalinya) ──

// f(x) = sum |a[i] - x| minimum di MEDIAN
double minJumlahJarak(vector<double> a) {
    int n = a.size();
    nth_element(a.begin(), a.begin() + n / 2, a.end());
    double med = a[n / 2];
    double s = 0;
    for (double v : a) s += fabs(v - med);
    return s;
}

// f(x) = sum (a[i] - x)^2 minimum di RATA-RATA
double minJumlahKuadrat(const vector<double>& a) {
    double mean = accumulate(a.begin(), a.end(), 0.0) / a.size();
    double s = 0;
    for (double v : a) s += (v - mean) * (v - mean);
    return s;
}

// ─── 5. TERNARY BERSARANG (dua dimensi) ──────────────────
// Biayanya iterLuar * 2 * iterDalam * 2 evaluasi -- HITUNG DULU
// sebelum memakainya. Dengan 200x200 itu 160000 evaluasi g.

template <typename G>
double cariMinimum2D(double xlo, double xhi, double ylo, double yhi, G g,
                     int iterLuar = 100, int iterDalam = 100) {
    auto fx = [&](double x) {
        return cariMinimum(ylo, yhi, [&](double y) { return g(x, y); }, iterDalam);
    };
    // fx mengembalikan y terbaik; kita butuh NILAI-nya
    auto nilai = [&](double x) { return g(x, fx(x)); };
    double xb = cariMinimum(xlo, xhi, nilai, iterLuar);
    return g(xb, fx(xb));
}

// ─── 6. UJI UNIMODALITAS (pakai sebelum percaya hasilnya) ──
// Lima menit menguji jauh lebih murah daripada satu jam men-debug
// algoritma yang memang tidak berlaku.

template <typename F>
bool ujiUnimodal(double lo, double hi, F f, int n = 1000) {
    vector<double> v(n);
    for (int i = 0; i < n; i++) v[i] = f(lo + (hi - lo) * i / (n - 1));
    int ganti = 0;
    for (int i = 2; i < n; i++)
        if ((v[i] > v[i - 1]) != (v[i - 1] > v[i - 2])) ganti++;
    return ganti <= 1;                     // pergantian arah hanya SEKALI
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    // Uji kebenaran dengan fungsi yang jawabannya kita tahu.
    auto f = [](double x) { return (x - 3) * (x - 3); };

    printf("min (x-3)^2 pada [0,10] = %.9f  (harusnya 3)\n",
           cariMinimum(0, 10, f));
    printf("max -(x-3)^2 pada [0,10] = %.9f  (harusnya 3)\n",
           cariMaksimum(0, 10, [&](double x) { return -f(x); }));
    printf("unimodal? %s\n", ujiUnimodal(0, 10, f) ? "YA" : "TIDAK");

    // Versi integer pada array unimodal
    vector<ll> arr = {1, 4, 7, 9, 8, 5, 2};
    auto g = [&](int i) { return arr[i]; };
    printf("puncak indeks (binary selisih) = %d  (harusnya 3)\n",
           cariPuncak(0, (int)arr.size() - 1, g));
    printf("puncak indeks (ternary int)    = %d  (harusnya 3)\n",
           cariMinimumInt(0, (int)arr.size() - 1, [&](int i) { return -arr[i]; }));

    return 0;
}
