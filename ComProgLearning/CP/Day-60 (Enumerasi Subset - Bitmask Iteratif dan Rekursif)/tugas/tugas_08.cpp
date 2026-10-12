/*
============================================================
📋 TUGAS 08: Subset dengan Tepat K Elemen
============================================================
Source: Original
Difficulty: Medium
Topics: bitmask enumeration, __builtin_popcount, sorting

PROBLEM:
Diberikan array a[] dengan n elemen dan bilangan k.
Cetak semua subset yang memiliki tepat k elemen beserta
jumlah elemennya. Urutkan output berdasarkan sum secara ascending;
jika sum sama, urutkan berdasarkan nilai mask secara ascending.

INPUT FORMAT:
- Baris 1: dua integer n dan k
- Baris 2: n buah integer a[0..n-1]

OUTPUT FORMAT:
- Satu baris per subset dalam format: { e1 e2 ... } sum=S
  dengan elemen ditampilkan sesuai urutan indeks aslinya

CONSTRAINTS:
- 1 ≤ n ≤ 15
- 0 ≤ k ≤ n
- 1 ≤ a[i] ≤ 100

SAMPLE INPUT 1:
4 2
1 3 5 2

SAMPLE OUTPUT 1:
{ 1 2 } sum=3
{ 1 3 } sum=4
{ 3 2 } sum=5
{ 1 5 } sum=6
{ 5 2 } sum=7
{ 3 5 } sum=8

SAMPLE INPUT 2:
3 1
4 2 6

SAMPLE OUTPUT 2:
{ 2 } sum=2
{ 4 } sum=4
{ 6 } sum=6

NOTE: Gunakan __builtin_popcount(mask) == k untuk memfilter subset.
      Kumpulkan semua subset yang valid, sort berdasarkan (sum, mask),
      lalu cetak elemen-elemennya sesuai urutan indeks.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    // Collect all subsets with exactly k elements
    vector<pair<int,int>> valid; // (sum, mask)
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) != k) continue;
        int sum = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) sum += a[i];
        valid.push_back({sum, mask});
    }

    // Sort by sum ascending, then by mask ascending
    sort(valid.begin(), valid.end());

    for (auto [sum, mask] : valid) {
        cout << "{ ";
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) cout << a[i] << ' ';
        cout << "} sum=" << sum << '\n';
    }
    return 0;
}
