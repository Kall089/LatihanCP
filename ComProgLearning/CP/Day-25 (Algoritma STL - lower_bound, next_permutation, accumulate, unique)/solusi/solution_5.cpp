/*
 * Day 6 — STL Algorithms
 * File  : solution_5.cpp
 * Topik : STL Algorithm Toolbox — find, count, reverse, rotate
 * -----------------------------------------------
 * Terapkan berbagai STL algorithm: cari posisi elemen, hitung kemunculan, reverse subarray, rotate array.
 *
 * Input format  : Baris 1: n
Baris 2: n bilangan
Baris 3: x (cari x), k (rotasi k ke kiri)
 * Output format : Baris 1: posisi x pertama (atau -1)
Baris 2: jumlah kemunculan x
Baris 3: array setelah reverse
Baris 4: array setelah rotate k ke kiri
 * Constraints   : 1 ≤ n ≤ 10^5, 0 ≤ k < n
 *
 * Sample Input 1:
 * 6
 * 1 3 2 3 4 3
 * 3 2
 *
 * Sample Output 1:
 * 1
 * 3
 * 3 4 3 2 3 1
 * 2 3 4 3 1 3
 *
 * Sample Input 2:
 * 5
 * 5 4 3 2 1
 * 6 3
 *
 * Sample Output 2:
 * -1
 * 0
 * 1 2 3 4 5
 * 2 1 5 4 3
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

    // find
    auto it = find(A.begin(), A.end(), x);
    int pos = (it == A.end()) ? -1 : (int)(it - A.begin());
    cout << pos << "\n";

    // count
    cout << count(A.begin(), A.end(), x) << "\n";

    // reverse (copy)
    vector<int> rev = A;
    reverse(rev.begin(), rev.end());
    for (int i = 0; i < n; i++) cout << rev[i] << "\n"[i==n-1];

    // rotate k kiri
    vector<int> rot = A;
    rotate(rot.begin(), rot.begin() + k, rot.end());
    for (int i = 0; i < n; i++) cout << rot[i] << "\n"[i==n-1];

    return 0;
}
