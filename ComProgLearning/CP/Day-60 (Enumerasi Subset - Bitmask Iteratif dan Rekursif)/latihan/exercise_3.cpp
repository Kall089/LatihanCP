/*
============================================================
  Exercise 3: Print Semua Subset dari n Elemen
============================================================
Diberikan array a[] dengan n elemen. Print semua subset
(termasuk subset kosong) dalam urutan bitmask dari kecil ke besar.

Untuk setiap subset, cetak:
  mask (biner, n digit) : { elemen-elemen }

Kemudian di akhir cetak total jumlah subset.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 20
  - -1000 ≤ a[i] ≤ 1000
  - Untuk n ≤ 4: cetak semua subset
  - Untuk n > 4: cetak hanya 5 subset pertama dan 5 terakhir,
    dengan "..." di tengah

📎 SAMPLE INPUT:
  3
  10 20 30

📎 SAMPLE OUTPUT:
  000 : { }
  001 : { 10 }
  010 : { 20 }
  011 : { 10 20 }
  100 : { 30 }
  101 : { 10 30 }
  110 : { 20 30 }
  111 : { 10 20 30 }
  Total subset: 8

💡 HINT:
  - Loop mask dari 0 sampai (1<<n)-1
  - Untuk cetak biner n-digit: gunakan bitset<n> atau loop dari bit n-1 ke 0
  - Elemen ke-i ada di subset jika (mask >> i) & 1 == 1
  - Total subset selalu 2^n

🎯 Learning Goals:
  Memahami dan mengimplementasikan iterasi semua subset menggunakan bitmask.
*/

#include <bits/stdc++.h>
using namespace std;

// Helper: cetak bitmask sebagai binary dengan n digit
string toBinary(int mask, int n) {
    string s = "";
    for (int i = n - 1; i >= 0; i--) {
        // TODO: tambahkan '1' jika bit ke-i aktif, '0' jika tidak
    }
    return s;
}

void printSubset(int mask, int n, vector<int>& a) {
    // TODO: cetak format "biner : { elemen-elemen }"
    // Contoh: "011 : { 10 20 }"
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int total = 1 << n;

    if (n <= 4) {
        // TODO: print semua subset dari mask=0 sampai mask=(1<<n)-1
    } else {
        // TODO: print 5 pertama
        for (int mask = 0; mask < 5; mask++) {
            printSubset(mask, n, a);
        }
        cout << "...\n";
        // TODO: print 5 terakhir
        for (int mask = total - 5; mask < total; mask++) {
            printSubset(mask, n, a);
        }
    }

    // TODO: cetak "Total subset: X"

    return 0;
}
