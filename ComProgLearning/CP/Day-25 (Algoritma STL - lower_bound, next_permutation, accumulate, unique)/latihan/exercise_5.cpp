/*
 * Day 6 — STL Algorithms
 * File  : exercise_5.cpp
 * Topik : STL Algorithm Toolbox — find, count, reverse, rotate
 * -----------------------------------------------
 * Terapkan berbagai STL algorithm: cari posisi elemen, hitung kemunculan,
 * reverse array, rotate array.
 *
 * Input format  : Baris 1: n
 *                 Baris 2: n bilangan
 *                 Baris 3: x (cari), k (rotasi kiri)
 * Output format : Baris 1: posisi x pertama (atau -1)
 *                 Baris 2: jumlah kemunculan x
 *                 Baris 3: array setelah reverse
 *                 Baris 4: array setelah rotate k ke kiri (dari array original)
 * Constraints   : 1 ≤ n ≤ 10^5, 0 ≤ k < n
 *
 * Sample Input 1:      Sample Output 1:
 * 6                    1
 * 1 3 2 3 4 3          3
 * 3 2                  3 4 3 2 3 1
 *                      2 3 4 3 1 3
 *
 * Sample Input 2:      Sample Output 2:
 * 5                    -1
 * 5 4 3 2 1            0
 * 6 3                  1 2 3 4 5
 *                      2 1 5 4 3
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    int x, k; cin >> x >> k;

    // TODO 1: Cari posisi pertama elemen x
    // auto it = find(A.begin(), A.end(), x);
    // int pos = (it == A.end()) ? -1 : (int)(it - A.begin());

    // TODO 2: Hitung jumlah kemunculan x
    // int cnt = (int)count(A.begin(), A.end(), x);

    // TODO 3: Reverse (buat copy rev = A, lalu reverse)
    // vector<int> rev = A;
    // reverse(rev.begin(), rev.end());

    // TODO 4: Rotate k ke kiri (buat copy rot = A, lalu rotate)
    // vector<int> rot = A;
    // rotate(rot.begin(), rot.begin() + k, rot.end());

    cout << -1 << "\n"; // pos
    cout << 0  << "\n"; // count
    // cetak rev
    // cetak rot
    return 0;
}
