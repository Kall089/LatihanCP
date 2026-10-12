/*
============================================================
  Day 46 — Counting / Radix / Bucket Sort | CP Template
============================================================
  BATAS BAWAH: pengurutan berbasis PERBANDINGAN >= n log n.
  Counting sort tidak melanggarnya -- ia di LUAR model, karena
  memakai nilai sebagai ALAMAT MEMORI, bukan membandingkan.

  PILIH BERDASARKAN ANGKA, JANGAN REFLEKS:
    V <= 1e6 dan V <~ n log n   -> counting sort   O(n + V)
    n >= 1e6, waktu ketat        -> radix basis 256 (~2-3x std::sort)
    selain itu                   -> std::sort

    n = 1e6, V = 1e6  -> counting 2e6  vs sort 3e7   counting menang 15x
    n = 1e3, V = 1e6  -> counting 1e6  vs sort 1.5e4 SORT menang 60x

  STABILITAS = MENYAPU MUNDUR di langkah penempatan.
  Ini bukan detail: tanpa stabil, RADIX SORT HANCUR TOTAL.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. COUNTING SORT SEDERHANA ──────────────────────────
// Hanya untuk bilangan POLOS (tanpa data terkait), karena ia
// menulis ulang nilai alih-alih memindahkan objek.

void countingSortSederhana(vector<int>& a, int maks) {
    vector<int> cnt(maks + 1, 0);               // maks+1, bukan maks
    for (int x : a) cnt[x]++;
    int idx = 0;
    for (int v = 0; v <= maks; v++)
        while (cnt[v]--) a[idx++] = v;
}

// ─── 2. COUNTING SORT STABIL (yang sebenarnya dipakai) ───

vector<int> countingSortStabil(const vector<int>& a, int maks) {
    int n = a.size();
    vector<int> cnt(maks + 1, 0), hasil(n);

    for (int x : a) cnt[x]++;                               // 1. frekuensi
    for (int v = 1; v <= maks; v++) cnt[v] += cnt[v - 1];   // 2. prefix sum
    for (int i = n - 1; i >= 0; i--)                        // 3. MUNDUR
        hasil[--cnt[a[i]]] = a[i];                          //    -> STABIL

    return hasil;
}

// ─── 3. COUNTING SORT UNTUK DATA BERPASANGAN ─────────────
// Bentuk inilah yang menjadi bahan bakar radix sort dan
// konstruksi suffix array (Day 220).

struct Item { int kunci; int data; };

vector<Item> countingSortItem(const vector<Item>& a, int maks) {
    int n = a.size();
    vector<int> cnt(maks + 1, 0);
    vector<Item> hasil(n);
    for (auto& it : a) cnt[it.kunci]++;
    for (int v = 1; v <= maks; v++) cnt[v] += cnt[v - 1];
    for (int i = n - 1; i >= 0; i--) hasil[--cnt[a[i].kunci]] = a[i];
    return hasil;
}

// ─── 4. MENANGANI BILANGAN NEGATIF ───────────────────────
// Geser dengan offset. Indeks negatif = perilaku tak terdefinisi
// yang sering TIDAK crash -> bug senyap.

void countingSortNegatif(vector<int>& a) {
    if (a.empty()) return;
    int mn = *min_element(a.begin(), a.end());
    int mx = *max_element(a.begin(), a.end());
    vector<int> cnt(mx - mn + 1, 0);
    for (int x : a) cnt[x - mn]++;
    int idx = 0;
    for (int v = 0; v < (int)cnt.size(); v++)
        while (cnt[v]--) a[idx++] = v + mn;
}

// ─── 5. RADIX SORT LSD BASIS 256 ─────────────────────────
// 4 lewat untuk 32 bit. cnt hanya 1 KB -> muat di cache L1.

void radixSortU32(vector<uint32_t>& a) {
    int n = a.size();
    if (n <= 1) return;
    vector<uint32_t> tmp(n);

    for (int shift = 0; shift < 32; shift += 8) {
        int cnt[256] = {0};
        for (uint32_t x : a) cnt[(x >> shift) & 255]++;
        for (int v = 1; v < 256; v++) cnt[v] += cnt[v - 1];
        for (int i = n - 1; i >= 0; i--)            // MUNDUR -> stabil
            tmp[--cnt[(a[i] >> shift) & 255]] = a[i];
        a.swap(tmp);                                 // O(1), jangan menyalin
    }
}

// Versi untuk int BERTANDA: balik bit tanda supaya urutan unsigned
// sama dengan urutan signed, lalu balikkan lagi setelah selesai.
void radixSortInt(vector<int>& a) {
    int n = a.size();
    if (n <= 1) return;
    vector<uint32_t> b(n);
    for (int i = 0; i < n; i++)
        b[i] = (uint32_t)a[i] ^ 0x80000000u;
    radixSortU32(b);
    for (int i = 0; i < n; i++)
        a[i] = (int)(b[i] ^ 0x80000000u);
}

// ─── 6. RADIX SORT UNTUK STRING BERPANJANG SAMA ──────────

void radixSortString(vector<string>& a, int L) {
    int n = a.size();
    if (n <= 1) return;
    vector<string> tmp(n);
    for (int pos = L - 1; pos >= 0; pos--) {        // dari karakter TERAKHIR
        vector<int> cnt(256, 0);
        for (auto& s : a) cnt[(unsigned char)s[pos]]++;
        for (int v = 1; v < 256; v++) cnt[v] += cnt[v - 1];
        for (int i = n - 1; i >= 0; i--)
            tmp[--cnt[(unsigned char)a[i][pos]]] = a[i];
        a.swap(tmp);
    }
}

// ─── 7. BUCKET SORT (asumsi distribusi SERAGAM) ──────────
// O(n) rata-rata HANYA kalau seragam. Kalau semua jatuh ke satu
// ember, degenerasi jadi O(n log n) atau lebih buruk.

void bucketSort01(vector<double>& a) {          // nilai di [0, 1)
    int n = a.size();
    if (n <= 1) return;
    vector<vector<double>> ember(n);
    for (double x : a) {
        int idx = (int)(x * n);
        if (idx >= n) idx = n - 1;
        ember[idx].push_back(x);
    }
    for (auto& e : ember) sort(e.begin(), e.end());
    int idx = 0;
    for (auto& e : ember) for (double x : e) a[idx++] = x;
}

// ─── 8. UJI STABILITAS ───────────────────────────────────

bool cekStabil(const vector<Item>& hasil) {
    for (size_t i = 1; i < hasil.size(); i++)
        if (hasil[i].kunci == hasil[i - 1].kunci &&
            hasil[i].data < hasil[i - 1].data) return false;
    return true;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<int> b = a;
    radixSortInt(b);
    cout << "radix sort   :";
    for (int x : b) cout << ' ' << x;
    cout << '\n';

    vector<int> c = a;
    countingSortNegatif(c);
    cout << "counting sort:";
    for (int x : c) cout << ' ' << x;
    cout << '\n';

    // uji stabilitas counting sort pada data berpasangan
    vector<Item> it(n);
    for (int i = 0; i < n; i++) it[i] = {abs(a[i]) % 5, i};
    vector<Item> hs = countingSortItem(it, 4);
    cout << "stabil?      : " << (cekStabil(hs) ? "YA" : "TIDAK") << '\n';

    return 0;
}
