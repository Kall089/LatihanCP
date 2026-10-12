/*
 * Day 19 — Two Pointers
 * File  : exercise_6.cpp
 * Topik : Merge Two Sorted Arrays
 * -----------------------------------------------
 * Diberikan dua sorted array A (berisi N elemen) dan B (berisi M elemen),
 * gabungkan keduanya menjadi satu sorted array yang berisi N+M elemen.
 * Output array hasil merge.
 *
 * Gunakan dua pointer independen:
 *   - i = pointer untuk A (mulai dari 0)
 *   - j = pointer untuk B (mulai dari 0)
 *   - Selalu ambil elemen yang lebih kecil, advance pointer-nya
 *   - Setelah salah satu habis, tambahkan sisa elemen array yang lain
 *
 * Input format  : Baris 1: N M (jumlah elemen A dan B)
 *                 Baris 2: N bilangan bulat (array A terurut menaik)
 *                 Baris 3: M bilangan bulat (array B terurut menaik)
 * Output format : N+M bilangan terurut menaik, dipisah spasi
 * Constraints   : 1 ≤ N, M ≤ 100.000
 *                 -10^9 ≤ A[i], B[j] ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 3 3                  1 2 3 4 5 6
 * 1 3 5
 * 2 4 6
 *
 * Sample Input 2:      Sample Output 2:
 * 4 2                  1 2 3 5 7 9
 * 1 3 7 9
 * 2 5
 *
 * Sample Input 3:      Sample Output 3:
 * 3 0                  1 2 3
 * 1 2 3
 *
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(m);
    for (auto& x : A) cin >> x;
    for (auto& x : B) cin >> x;

    vector<int> res;

    // TODO: implementasikan merge dengan two pointers
    // int i = 0, j = 0;
    // while (i < n && j < m) {
    //     if (A[i] <= B[j]) res.push_back(A[i++]);
    //     else               res.push_back(B[j++]);
    // }
    // while (i < n) res.push_back(A[i++]);
    // while (j < m) res.push_back(B[j++]);
    //
    // for (int k = 0; k < (int)res.size(); k++)
    //     cout << res[k] << " \n"[k == (int)res.size() - 1];

    return 0;
}
