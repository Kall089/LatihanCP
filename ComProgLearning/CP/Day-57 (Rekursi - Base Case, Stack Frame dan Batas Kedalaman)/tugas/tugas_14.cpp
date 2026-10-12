/*
 * Day 11 — Recursion Dasar
 * File  : tugas_14.cpp
 * Topik : Merge Sort Rekursif
 * Kesulitan: Hard
 * -----------------------------------------------
 * Implementasikan Merge Sort menggunakan rekursi.
 * Kompleksitas target: O(n log n).
 *
 * Langkah:
 *   1. Bagi array menjadi dua setengah
 *   2. Sort rekursif kiri dan kanan
 *   3. Merge dua setengah yang sudah sorted
 *
 * Input format  : Baris 1: n
 *                 Baris 2: n bilangan bulat
 * Output format : Array setelah sort, dipisah spasi
 * Constraints   : 1 ≤ n ≤ 10^5, -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    1 2 3 4 9
 * 3 1 9 2 4
 *
 * Sample Input 2:      Sample Output 2:
 * 1                    7
 * 7
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan mergeSort(A, l, r) rekursif
    // dan merge(A, l, mid, r) untuk menggabungkan dua bagian sorted
    //
    // void merge(vector<int>& A, int l, int mid, int r) {
    //     vector<int> tmp;
    //     int i=l, j=mid+1;
    //     while (i<=mid && j<=r) ...
    // }
    //
    // void mergeSort(vector<int>& A, int l, int r) {
    //     if (l >= r) return;
    //     int mid = (l+r)/2;
    //     mergeSort(A, l, mid);
    //     mergeSort(A, mid+1, r);
    //     merge(A, l, mid, r);
    // }

    return 0;
}
