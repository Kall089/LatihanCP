/*
 * Day 11 — Recursion Dasar
 * File  : tugas_11.cpp
 * Topik : Pascal's Triangle Row n
 * Kesulitan: Hard
 * -----------------------------------------------
 * Cetak baris ke-n dari segitiga Pascal menggunakan rekursi.
 * C(n, k) = C(n-1, k-1) + C(n-1, k)
 * C(n, 0) = C(n, n) = 1  (base case)
 *
 * Gunakan memoization untuk efisiensi.
 *
 * Input format  : Satu bilangan n
 * Output format : n+1 bilangan: C(n,0) C(n,1) ... C(n,n) dipisah spasi
 * Constraints   : 0 ≤ n ≤ 30
 *
 * Sample Input 1:      Sample Output 1:
 * 4                    1 4 6 4 1
 *
 * Sample Input 2:      Sample Output 2:
 * 0                    1
 *
 * Sample Input 3:      Sample Output 3:
 * 5                    1 5 10 10 5 1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan C(n, k) rekursif dengan memoization
    // C(n, 0) = C(n, n) = 1
    // C(n, k) = C(n-1, k-1) + C(n-1, k)
    // Kemudian cetak C(n,0), C(n,1), ..., C(n,n)

    return 0;
}
