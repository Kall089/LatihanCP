/*
============================================================
  Exercise 5 (Challenge): Enumerate Subsets of a Given Mask
============================================================
Diberikan sebuah bitmask M dan array a[]. Iterasi semua
subset dari M (termasuk empty set) menggunakan teknik
  for (sub = M; sub > 0; sub = (sub-1) & M)

Untuk setiap subset dari M (termasuk empty set), cetak:
  sub_biner : { elemen-elemen } | sum = X

Kemudian cetak:
  - Jumlah total subset
  - Subset dengan sum maksimum (jika ada lebih dari satu, cetak yang mask-nya terkecil)
  - Subset dengan sum minimum (non-empty, mask terkecil jika ada lebih dari satu)

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 20
  - 0 ≤ M < (1 << n)  (M diberikan sebagai bitmask desimal)
  - -100 ≤ a[i] ≤ 100

📎 SAMPLE INPUT:
  4
  3 -1 4 -2
  5

  (n=4, a={3,-1,4,-2}, M=5=0b0101 artinya himpunan {0,2} yaitu elemen {3,4})

📎 SAMPLE OUTPUT:
  0000 : { } | sum = 0
  0001 : { 3 } | sum = 3
  0100 : { 4 } | sum = 4
  0101 : { 3 4 } | sum = 7
  Total subset (termasuk empty): 4
  Subset sum maks: { 3 4 } (sum=7)
  Subset sum min (non-empty): { 3 } (sum=3)

💡 HINT:
  - Untuk empty set: proses sub=0 manual setelah atau sebelum loop
  - Loop: for (int sub = M; sub > 0; sub = (sub-1) & M)
  - Jumlah subset dari M = 2^popcount(M)
  - Hati-hati: urutan cetak harus dari kecil ke besar (simpan dulu ke vector)

🎯 Learning Goals:
  Menguasai teknik iterasi subset-dari-mask yang merupakan inti
  dari banyak Bitmask DP lanjutan.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int M;
    cin >> M;

    // Kumpulkan semua (sub, sum) pair
    vector<pair<int,long long>> subsets;  // (mask, sum)

    // TODO: kumpulkan semua subset dari M (termasuk empty set sub=0)
    // gunakan loop: for (sub = M; sub > 0; sub = (sub-1) & M)
    // lalu proses sub=0 secara manual

    // Sort berdasarkan mask (ascending) untuk output terurut
    sort(subsets.begin(), subsets.end());

    // TODO: cetak tiap subset dalam format yang diminta

    // TODO: cetak jumlah total subset

    // TODO: cari dan cetak subset dengan sum maksimum

    // TODO: cari dan cetak subset non-empty dengan sum minimum

    return 0;
}
