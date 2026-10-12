/*
 * Day 19 — Two Pointers
 * File  : tugas_09.cpp
 * Topik : Four Sum — Temukan Quadruple dengan Sum = K
 * Tingkat: Medium
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat dan target K. Temukan SEMUA
 * quadruple unik (a, b, c, d) dengan a ≤ b ≤ c ≤ d dan a+b+c+d = K.
 * Output jumlah quadruple, diikuti masing-masing quadruple (satu per baris).
 *
 * Pendekatan: Generalisasi Three Sum → Four Sum
 *   1. Sort array
 *   2. Outer loop i (fix A[i])
 *   3. Second loop j (fix A[j], j > i)
 *   4. Two pointers L=j+1, R=n-1 untuk mencari A[L]+A[R] = K-A[i]-A[j]
 *   5. Skip duplikat di semua level
 *
 * Complexity: O(n³) time
 *
 * Input format  : Baris 1: N K
 *                 Baris 2: N bilangan bulat
 * Output format : Baris 1: jumlah quadruple
 *                 Baris 2...: masing-masing quadruple (nilai terurut, spasi)
 * Constraints   : 4 ≤ N ≤ 1000
 *                 -10^6 ≤ A[i] ≤ 10^6
 *                 -4×10^6 ≤ K ≤ 4×10^6
 *
 * Sample Input 1:      Sample Output 1:
 * 6 0                  2
 * -3 -2 -1 0 1 2       -3 -2 1 4 ← salah, perlu cek
 * (recalc: A=[-3,-2,-1,0,1,2], K=0:
 *  quadruple sum=0:
 *  (-3,-2,1,4)? 4 tidak ada.
 *  (-3,-2,2,3)? 3 tidak ada.
 *  (-3,-1,2,2)? duplikat.
 *  (-3,0,1,2)=-3+0+1+2=0 ✓
 *  (-2,-1,1,2)=-2-1+1+2=0 ✓
 *  (-3,-2,2,3)? tidak ada.
 *  Total: 2)
 *
 * Sample Input 1:      Sample Output 1:
 * 6 0                  2
 * -3 -2 -1 0 1 2       -3 0 1 2
 *                      -2 -1 1 2
 *
 * Sample Input 2:      Sample Output 2:
 * 4 10                 1
 * 1 2 3 4              1 2 3 4
 *
 * Sample Input 3:      Sample Output 3:
 * 5 0                  0
 * 1 2 3 4 5
 *
 * Hint:
 *   - Outer loop: for i = 0 to n-4
 *     - if (i>0 && A[i]==A[i-1]) continue  // skip duplikat i
 *     - Inner loop: for j = i+1 to n-3
 *       - if (j>i+1 && A[j]==A[j-1]) continue  // skip duplikat j
 *       - target = K - A[i] - A[j]
 *       - L=j+1, R=n-1: two pointer untuk A[L]+A[R] == target
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Tulis solusimu di sini

    return 0;
}
