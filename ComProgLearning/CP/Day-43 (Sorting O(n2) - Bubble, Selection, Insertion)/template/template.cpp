/*
============================================================
  Day 43 — Sorting O(n^2) | CP Template
============================================================
  DI KONTES, PAKAI std::sort. Tiga algoritma ini dipelajari karena:
    1. soal sering menanyakan PROSESNYA (berapa swap, keadaan setelah k langkah)
    2. swap bubble = banyaknya INVERSI  <- identitas yang sering terpakai
    3. insertion sort benar-benar dipakai di dalam std::sort untuk potongan kecil
    4. melatih cara berpikir INVARIANT

             invariant                    stabil  swap    terbaik
  BUBBLE     k terbesar sudah di kanan     YA     O(n^2)  O(n) dgn flag
  SELECTION  k terkecil sudah di kiri      TIDAK  n-1     O(n^2)
  INSERTION  k pertama terurut relatif     YA     O(n^2)  O(n)

  BATAS PRAKTIS
    n <= 5000  -> O(n^2) aman
    n > 10^4   -> WAJIB O(n log n)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. BUBBLE SORT (dengan flag -> terbaik O(n)) ────────

void bubbleSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i + 1 < n; i++) {
        bool adaTukar = false;
        for (int j = 0; j + 1 < n - i; j++)     // j+1 < n-i, bukan j < n-i
            if (a[j] > a[j + 1]) {              // '>' bukan '>=' -> STABIL
                swap(a[j], a[j + 1]);
                adaTukar = true;
            }
        if (!adaTukar) break;                   // sudah terurut
    }
}

// Jumlah swap bubble sort = banyaknya INVERSI.
// Parameter BY VALUE supaya array asli tidak berubah.
// Untuk n > 5000, pakai merge sort (Day 44) atau BIT (Day 170).
ll hitungSwapBubble(vector<int> a) {
    int n = a.size();
    ll swapCount = 0;
    for (int i = 0; i + 1 < n; i++)
        for (int j = 0; j + 1 < n - i; j++)
            if (a[j] > a[j + 1]) { swap(a[j], a[j + 1]); swapCount++; }
    return swapCount;
}

// ─── 2. SELECTION SORT (swap paling sedikit: n-1) ────────

void selectionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i + 1 < n; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;   // '<' -> ambil kemunculan PERTAMA
        if (minIdx != i) swap(a[i], a[minIdx]); // hindari swap sia-sia
    }
}

// TIDAK STABIL. Contoh: [2a, 2b, 1] -> [1, 2b, 2a], urutan 2a/2b terbalik.
ll hitungSwapSelection(vector<int> a) {
    int n = a.size();
    ll c = 0;
    for (int i = 0; i + 1 < n; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) if (a[j] < a[minIdx]) minIdx = j;
        if (minIdx != i) { swap(a[i], a[minIdx]); c++; }
    }
    return c;
}

// ─── 3. INSERTION SORT (GESER, bukan swap) ───────────────
// Kerja total = O(n + banyaknya inversi). Sangat cepat pada data
// hampir terurut: kalau tiap elemen <= k posisi dari tempatnya -> O(nk).

void insertionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int kunci = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > kunci) {        // '>' -> berhenti saat sama -> STABIL
            a[j + 1] = a[j];                    // GESER: satu penulisan, bukan tiga
            j--;
        }
        a[j + 1] = kunci;
    }
}

// Jumlah PERGESERAN = banyaknya inversi (sama dengan swap bubble).
ll hitungGeserInsertion(vector<int> a) {
    int n = a.size();
    ll c = 0;
    for (int i = 1; i < n; i++) {
        int kunci = a[i], j = i - 1;
        while (j >= 0 && a[j] > kunci) { a[j + 1] = a[j]; j--; c++; }
        a[j + 1] = kunci;
    }
    return c;
}

// ─── 4. INSERTION SORT + BINARY SEARCH ───────────────────
// Perbandingan turun jadi O(n log n), TAPI pergeseran tetap O(n^2).
// Hanya berguna kalau operasi PERBANDINGAN mahal (string panjang, dsb).

void binaryInsertionSort(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        int kunci = a[i];
        // upper_bound -> menyisipkan SETELAH yang sama -> tetap stabil
        int pos = int(upper_bound(a.begin(), a.begin() + i, kunci) - a.begin());
        for (int j = i; j > pos; j--) a[j] = a[j - 1];
        a[pos] = kunci;
    }
}

// ─── 5. COCKTAIL SHAKER (bubble dua arah) ────────────────
// Mengatasi masalah "kura-kura": elemen kecil di ujung kanan yang
// bergerak sangat lambat pada bubble biasa. Tetap O(n^2).

void cocktailSort(vector<int>& a) {
    int kiri = 0, kanan = (int)a.size() - 1;
    while (kiri < kanan) {
        bool adaTukar = false;
        for (int j = kiri; j < kanan; j++)
            if (a[j] > a[j + 1]) { swap(a[j], a[j + 1]); adaTukar = true; }
        kanan--;
        for (int j = kanan; j > kiri; j--)
            if (a[j - 1] > a[j]) { swap(a[j - 1], a[j]); adaTukar = true; }
        kiri++;
        if (!adaTukar) break;
    }
}

// ─── 6. UJI STABILITAS ───────────────────────────────────

struct Item { int kunci; int urutanAsli; };

bool stabil(const vector<Item>& hasil) {
    for (size_t i = 1; i < hasil.size(); i++)
        if (hasil[i].kunci == hasil[i - 1].kunci &&
            hasil[i].urutanAsli < hasil[i - 1].urutanAsli) return false;
    return true;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    cout << "swap bubble    : " << hitungSwapBubble(a) << '\n';
    cout << "swap selection : " << hitungSwapSelection(a) << '\n';
    cout << "geser insertion: " << hitungGeserInsertion(a) << '\n';

    vector<int> b = a;
    insertionSort(b);
    cout << "hasil urut     :";
    for (int x : b) cout << ' ' << x;
    cout << '\n';

    return 0;
}
