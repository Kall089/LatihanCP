/*
============================================================
  Day 45 — Quick Sort & Quickselect | CP Template
============================================================
  ATURAN PRAKTIS: JANGAN menulis quicksort di kontes. Pakai std::sort.
  Yang benar-benar berguna dari hari ini adalah nth_element -- dan banyak
  peserta tidak tahu fungsi ini ada.

  MERGE: bagi buta   -> kerja saat MENGGABUNG
  QUICK: kerja saat MEMBAGI -> gabung gratis

  DUA PERTAHANAN WAJIB kalau menulis sendiri:
    1. pivot ACAK (mt19937, JANGAN rand())
    2. rekursi ke sisi KECIL, iterasi ke sisi besar -> stack O(log n)

  QUICKSELECT O(n) rata-rata karena hanya menelusuri SATU sisi:
    n + n/2 + n/4 + ... = 2n
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// ─── 1. PARTISI LOMUTO ───────────────────────────────────
// Rentang INKLUSIF [lo, hi]. Mengembalikan posisi akhir pivot.
// Invariant: a[lo..i-1] <= pivot, a[i..j-1] > pivot.
// Kelemahan: array penuh kembaran membelah (n-1, 0) -> O(n^2).

int partisiLomuto(vector<int>& a, int lo, int hi) {
    int pivot = a[hi];
    int i = lo;
    for (int j = lo; j < hi; j++)
        if (a[j] <= pivot) swap(a[i++], a[j]);
    swap(a[i], a[hi]);
    return i;
}

// ─── 2. QUICKSORT (pivot acak + rekursi sisi kecil) ──────

void quickSort(vector<int>& a, int lo, int hi) {
    while (lo < hi) {
        int r = lo + (int)(rng() % (unsigned)(hi - lo + 1));
        swap(a[r], a[hi]);                     // pivot ACAK
        int p = partisiLomuto(a, lo, hi);

        // rekursi ke sisi KECIL -> kedalaman stack dijamin O(log n)
        if (p - lo < hi - p) { quickSort(a, lo, p - 1); lo = p + 1; }
        else                 { quickSort(a, p + 1, hi); hi = p - 1; }
    }
}

void urutkan(vector<int>& a) {
    if (!a.empty()) quickSort(a, 0, (int)a.size() - 1);
}

// ─── 3. QUICKSELECT ──────────────────────────────────────
// Elemen terkecil ke-k (0-based). MENGUBAH urutan a.
// Tanpa rekursi -> ruang O(1).

int quickSelect(vector<int>& a, int k) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo < hi) {
        int r = lo + (int)(rng() % (unsigned)(hi - lo + 1));
        swap(a[r], a[hi]);
        int p = partisiLomuto(a, lo, hi);
        if (p == k) return a[p];
        if (p < k) lo = p + 1;                 // buang SELURUH sisi kiri
        else       hi = p - 1;                 // buang SELURUH sisi kanan
    }
    return a[lo];
}

// ─── 4. PARTISI TIGA ARAH (Dutch national flag) ──────────
// Setelah selesai: a[lo..lt-1] < p, a[lt..gt] == p, a[gt+1..hi] > p.
// Array penuh kembaran selesai dalam O(n), bukan O(n^2).

void partisi3(vector<int>& a, int lo, int hi, int& lt, int& gt) {
    int pivot = a[lo + (int)(rng() % (unsigned)(hi - lo + 1))];
    lt = lo; gt = hi;
    int i = lo;
    while (i <= gt) {
        if      (a[i] < pivot) swap(a[lt++], a[i++]);
        else if (a[i] > pivot) swap(a[i], a[gt--]);   // i TIDAK maju
        else                   i++;
    }
}

void quickSort3(vector<int>& a, int lo, int hi) {
    if (lo >= hi) return;
    int lt, gt;
    partisi3(a, lo, hi, lt, gt);
    quickSort3(a, lo, lt - 1);
    quickSort3(a, gt + 1, hi);
}

// ─── 5. YANG SEBENARNYA DIPAKAI DI KONTES ────────────────

// Elemen terkecil ke-k (0-based). O(n). MENGUBAH array.
int keK(vector<int> a, int k) {                // by value: array asli aman
    nth_element(a.begin(), a.begin() + k, a.end());
    return a[k];
}

// k elemen terkecil, TERURUT. O(n log k).
vector<int> kTerkecilTerurut(vector<int> a, int k) {
    partial_sort(a.begin(), a.begin() + k, a.end());
    return vector<int>(a.begin(), a.begin() + k);
}

// k elemen TERBESAR, urutan bebas. O(n).
vector<int> kTerbesar(vector<int> a, int k) {
    int n = a.size();
    nth_element(a.begin(), a.begin() + (n - k), a.end());
    return vector<int>(a.begin() + (n - k), a.end());
}

// Median. Untuk n genap, rata-rata dua nilai tengah.
double median(vector<int> a) {
    int n = a.size();
    nth_element(a.begin(), a.begin() + n / 2, a.end());
    if (n % 2) return a[n / 2];
    int atas = a[n / 2];
    int bawah = *max_element(a.begin(), a.begin() + n / 2);
    return (atas + bawah) / 2.0;
}

// ─── 6. k TERBESAR DARI STREAM (heap ukuran k) ───────────
// O(n log k) waktu, O(k) RUANG -- tidak perlu menyimpan seluruh array.
// nth_element butuh seluruh array di memori; ini tidak.

vector<int> kTerbesarStream(const vector<int>& a, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;   // MIN-heap
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();                // buang terkecil
    }
    vector<int> hasil;
    while (!pq.empty()) { hasil.push_back(pq.top()); pq.pop(); }
    return hasil;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    cout << "elemen ke-" << k << " (0-based) : " << keK(a, k) << '\n';
    cout << "median               : " << median(a) << '\n';

    vector<int> b = a;
    urutkan(b);
    cout << "quicksort sendiri    :";
    for (int x : b) cout << ' ' << x;
    cout << '\n';

    vector<int> c = a;
    quickSort3(c, 0, n - 1);
    cout << "quicksort tiga arah  :";
    for (int x : c) cout << ' ' << x;
    cout << '\n';

    return 0;
}
