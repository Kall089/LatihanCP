/*
 * Day 19 — Two Pointers
 * File  : tugas_11.cpp
 * Topik : Trapping Rain Water
 * Tingkat: Hard
 * -----------------------------------------------
 * Diberikan array H berisi N bilangan bulat non-negatif yang merepresentasikan
 * ketinggian kolom-kolom. Hitung total air yang bisa ditampung setelah hujan.
 *
 * Air yang tertampung di posisi i:
 *   water[i] = max(0, min(maxLeft[i], maxRight[i]) - H[i])
 * Di mana:
 *   maxLeft[i]  = maksimum H[0..i]
 *   maxRight[i] = maksimum H[i..n-1]
 *
 * Pendekatan Naif O(n²) atau O(n) dengan array prefix:
 *   Hitung maxLeft[] dan maxRight[], lalu jumlahkan.
 *
 * Pendekatan Two Pointers O(n) O(1) space:
 *   - L = 0, R = n-1
 *   - maxLeft = 0, maxRight = 0
 *   - Jika H[L] <= H[R]:
 *       Jika H[L] >= maxLeft: update maxLeft = H[L]
 *       Else: tambahkan (maxLeft - H[L]) ke air
 *       L++
 *   - Jika H[L] > H[R]:
 *       Jika H[R] >= maxRight: update maxRight = H[R]
 *       Else: tambahkan (maxRight - H[R]) ke air
 *       R--
 *
 * Mengapa benar?
 *   Sisi dengan ketinggian lebih kecil menentukan air yang bisa ditampung.
 *   Kita memproses dari sisi yang lebih kecil, dengan jaminan sisi lain
 *   setidaknya setinggi sisi yang sedang diproses.
 *
 * Input format  : Baris 1: N
 *                 Baris 2: N bilangan bulat non-negatif
 * Output format : Satu bilangan: total air yang tertampung
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ H[i] ≤ 10^5
 *
 * Sample Input 1:      Sample Output 1:
 * 12                   6
 * 0 1 0 2 1 0 1 3 2 1 2 1
 *
 * Sample Input 2:      Sample Output 2:
 * 6                    9
 * 4 2 0 3 2 5
 *
 * Sample Input 3:      Sample Output 3:
 * 3                    0
 * 1 2 3
 *
 * Penjelasan Sample 1:
 *   H=[0,1,0,2,1,0,1,3,2,1,2,1]
 *   Air di setiap posisi: [0,0,1,0,1,2,1,0,0,1,0,0]
 *   Total: 1+1+2+1+1 = 6 ✓
 *
 * Penjelasan Sample 2:
 *   H=[4,2,0,3,2,5]
 *   maxLeft:  [4,4,4,4,4,5]
 *   maxRight: [5,5,5,5,5,5]
 *   water: [0, min(4,5)-2=2, min(4,5)-0=4, min(4,5)-3=1, min(4,5)-2=2, 0]
 *   Total: 2+4+1+2 = 9 ✓
 *
 * Hint:
 *   Coba implementasikan dengan prefix array dulu (O(n) space),
 *   lalu optimasi ke two pointers O(1) space.
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
