/*
============================================================
  Day 44 — Merge Sort & Inversion Count | CP Template
============================================================
  DI KONTES, PAKAI std::sort untuk mengurutkan.
  Tulis merge sort HANYA kalau kamu butuh hasil sampingannya --
  dan hasil sampingan yang paling sering dibutuhkan adalah INVERSI.

  KONVENSI: setengah terbuka [l, r). Jauh lebih sedikit off-by-one.

  MERGE stabil karena '<=' (ambil dari KIRI saat seri).

  INVERSI = satu baris tambahan:
      else { tmp[k++] = a[j++]; inv += mid - i; }
  KENAPA mid - i: bagian kiri SUDAH TERURUT, jadi a[j] lebih kecil
  dari SELURUH sisa kiri sekaligus. Ini yang membuatnya O(n log n).

  inv WAJIB long long: n = 1e5 -> maksimal 5e9 inversi.
  tmp dialokasikan SEKALI di luar rekursi (alokasi di dalam = 5x lebih lambat).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. MERGE SORT BAKU ──────────────────────────────────

void mergeSort(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return;
    int mid = l + (r - l) / 2;              // hindari overflow (l+r)/2

    mergeSort(a, tmp, l, mid);
    mergeSort(a, tmp, mid, r);

    int i = l, j = mid, k = l;
    while (i < mid && j < r)
        tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];   // '<=' -> STABIL
    while (i < mid) tmp[k++] = a[i++];
    while (j < r)   tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];
}

void urutkan(vector<int>& a) {
    vector<int> tmp(a.size());
    mergeSort(a, tmp, 0, (int)a.size());
}

// ─── 2. INVERSION COUNT ──────────────────────────────────
// Mengurutkan a SEKALIGUS mengembalikan banyaknya inversi.
// Kalau array asli harus dijaga, kirim salinannya.

ll invCount(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;

    ll inv = invCount(a, tmp, l, mid) + invCount(a, tmp, mid, r);

    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) {                 // '<=' -> kembar BUKAN inversi
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            inv += mid - i;                 // SELURUH sisa kiri sekaligus
        }
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r)   tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];

    return inv;
}

ll hitungInversi(vector<int> a) {           // BY VALUE: array asli aman
    vector<int> tmp(a.size());
    return invCount(a, tmp, 0, (int)a.size());
}

// ─── 3. VARIAN: PASANGAN a[i] > 2*a[j] ───────────────────
// DUA FASE terpisah, karena kondisinya berbeda dari kondisi merge.

ll pentingRec(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;
    ll res = pentingRec(a, tmp, l, mid) + pentingRec(a, tmp, mid, r);

    // FASE 1: hitung dengan two pointers (j hanya maju -> O(n) per level)
    int j = mid;
    for (int i = l; i < mid; i++) {
        while (j < r && (ll)a[i] > 2LL * a[j]) j++;
        res += j - mid;
    }

    // FASE 2: merge biasa
    int i2 = l, j2 = mid, k = l;
    while (i2 < mid && j2 < r) tmp[k++] = (a[i2] <= a[j2]) ? a[i2++] : a[j2++];
    while (i2 < mid) tmp[k++] = a[i2++];
    while (j2 < r)   tmp[k++] = a[j2++];
    for (int t = l; t < r; t++) a[t] = tmp[t];

    return res;
}

ll hitungPasanganPenting(vector<int> a) {
    vector<int> tmp(a.size());
    return pentingRec(a, tmp, 0, (int)a.size());
}

// ─── 4. MERGE DUA ARRAY TERURUT ──────────────────────────

vector<int> mergeDua(const vector<int>& x, const vector<int>& y) {
    vector<int> hasil;
    hasil.reserve(x.size() + y.size());
    size_t i = 0, j = 0;
    while (i < x.size() && j < y.size())
        hasil.push_back(x[i] <= y[j] ? x[i++] : y[j++]);
    while (i < x.size()) hasil.push_back(x[i++]);
    while (j < y.size()) hasil.push_back(y[j++]);
    return hasil;
}

// ─── 5. MERGE K ARRAY TERURUT (heap) ─────────────────────
// O(N log k), mengalahkan "gabung satu per satu" yang O(Nk).

vector<int> mergeK(const vector<vector<int>>& arr) {
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
    for (int i = 0; i < (int)arr.size(); i++)
        if (!arr[i].empty()) pq.push({arr[i][0], i, 0});

    vector<int> hasil;
    while (!pq.empty()) {
        auto t = pq.top(); pq.pop();
        hasil.push_back(t[0]);
        int ai = t[1], idx = t[2];
        if (idx + 1 < (int)arr[ai].size())
            pq.push({arr[ai][idx + 1], ai, idx + 1});
    }
    return hasil;
}

// ─── 6. MERGE SORT ITERATIF (bottom-up, tanpa rekursi) ───

void mergeSortIteratif(vector<int>& a) {
    int n = a.size();
    if (n <= 1) return;
    vector<int> tmp(n);
    for (int lebar = 1; lebar < n; lebar *= 2)
        for (int l = 0; l < n; l += 2 * lebar) {
            int mid = min(l + lebar, n), r = min(l + 2 * lebar, n);
            if (mid >= r) continue;
            int i = l, j = mid, k = l;
            while (i < mid && j < r) tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
            while (i < mid) tmp[k++] = a[i++];
            while (j < r)   tmp[k++] = a[j++];
            for (int t = l; t < r; t++) a[t] = tmp[t];
        }
}

// ─── 7. BRUTE FORCE (untuk stress test -- WAJIB dipakai) ──

ll inversiNaif(const vector<int>& a) {
    ll c = 0;
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = i + 1; j < a.size(); j++)
            if (a[i] > a[j]) c++;
    return c;
}

ll pentingNaif(const vector<int>& a) {
    ll c = 0;
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = i + 1; j < a.size(); j++)
            if ((ll)a[i] > 2LL * a[j]) c++;
    return c;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    cout << "inversi         : " << hitungInversi(a) << '\n';
    cout << "  cek naif      : " << inversiNaif(a) << '\n';
    cout << "a[i] > 2*a[j]   : " << hitungPasanganPenting(a) << '\n';
    cout << "  cek naif      : " << pentingNaif(a) << '\n';

    vector<int> b = a;
    urutkan(b);
    cout << "hasil urut      :";
    for (int x : b) cout << ' ' << x;
    cout << '\n';

    return 0;
}
