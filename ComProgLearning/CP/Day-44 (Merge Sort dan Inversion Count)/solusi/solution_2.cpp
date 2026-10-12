/*
============================================================
✅ Solution 2: Merge Sort dari Nol
============================================================
Approach: Divide and conquer dengan konvensi setengah terbuka
Complexity: Time O(n log n) SELALU | Space O(n)
Key Insight: Berbeda dari quicksort, pembagian merge sort SELALU seimbang
             karena titik tengahnya dihitung, bukan bergantung pada data.
             Tidak ada kasus terburuk O(n^2). Harganya: memori tambahan O(n).

📖 PENJELASAN PENDEKATAN:
1. Basis: r - l <= 1 berarti 0 atau 1 elemen -- sudah terurut.
2. Bagi di mid, rekursi ke [l, mid) dan [mid, r).
3. Merge kedua bagian ke tmp, lalu salin kembali ke a.

KENAPA O(n log n): kedalaman rekursi log2(n) karena selalu membagi dua,
dan setiap level menyalin setiap elemen tepat sekali -> O(n) per level.

⚠️ ALOKASIKAN tmp SEKALI DI LUAR REKURSI.
   Membuat vector<int> baru di setiap pemanggilan berarti O(n log n)
   alokasi memori, yang bisa membuat kodemu 5 kali lebih lambat daripada
   versi yang benar. Ini kesalahan kinerja paling umum pada merge sort.

⚠️ mid = l + (r - l) / 2, BUKAN (l + r) / 2.
   Untuk indeks array biasa keduanya sama, tetapi kebiasaan ini akan
   menyelamatkanmu saat melakukan binary search pada rentang nilai besar
   (Day 50), di mana l + r bisa overflow.

⚠️ JANGAN LUPA MENYALIN tmp KEMBALI KE a. Kalau dilewatkan, pemanggilan
   rekursif di level atasnya akan membaca data lama dan hasilnya kacau
   dengan cara yang sulit dilacak.

KONVENSI SETENGAH TERBUKA [l, r) dipilih karena:
   - basisnya sederhana: r - l <= 1
   - pembagiannya bersih: [l, mid) dan [mid, r), tanpa +1 atau -1
   - panjangnya langsung r - l
   Konvensi [l, r] inklusif juga benar, tetapi menuntut lebih banyak
   penyesuaian +1/-1 yang menjadi sumber bug.

🔄 ALTERNATIVE APPROACHES:
- std::sort: lebih cepat (~2x) dan lebih pendek. Di kontes, ini pilihannya.
- std::stable_sort: kalau butuh stabil.
- Merge sort iteratif (bottom-up): menghindari rekursi, berguna kalau
  kedalaman stack menjadi masalah.
- Menulis merge sort sendiri hanya masuk akal kalau kamu butuh HASIL
  SAMPINGANNYA -- yaitu inversi (Exercise 3).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void mergeSort(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return;                    // 0 atau 1 elemen
    int mid = l + (r - l) / 2;                 // hindari overflow

    mergeSort(a, tmp, l, mid);
    mergeSort(a, tmp, mid, r);

    int i = l, j = mid, k = l;
    while (i < mid && j < r)
        tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i < mid) tmp[k++] = a[i++];
    while (j < r)   tmp[k++] = a[j++];

    for (int t = l; t < r; t++) a[t] = tmp[t]; // JANGAN dilupakan
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<int> tmp(n);                        // SEKALI, di luar rekursi
    mergeSort(a, tmp, 0, n);

    string out;
    for (int i = 0; i < n; i++) {
        out += to_string(a[i]);
        out += (i + 1 == n) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
