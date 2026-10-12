/*
 * Day 19 — Two Pointers
 * File  : tugas_08.cpp
 * Topik : Sort Colors (Dutch National Flag Problem)
 * Tingkat: Medium
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan yang hanya berisi nilai 0, 1, dan 2.
 * Sort array secara in-place tanpa menggunakan fungsi sort bawaan.
 * Semua 0 harus berada di awal, diikuti semua 1, lalu semua 2.
 *
 * Ini adalah implementasi Dutch National Flag Algorithm (E.W. Dijkstra):
 *   Gunakan 3 pointer: low, mid, high
 *   Invariant:
 *     A[0..low-1]    = semua 0
 *     A[low..mid-1]  = semua 1
 *     A[mid..high]   = belum diproses
 *     A[high+1..n-1] = semua 2
 *
 *   Loop: while (mid <= high)
 *     - A[mid] == 0: swap(A[low], A[mid]), low++, mid++
 *     - A[mid] == 1: mid++
 *     - A[mid] == 2: swap(A[mid], A[high]), high--
 *       (JANGAN mid++ saat swap dengan high!)
 *
 * Input format  : Baris 1: N
 *                 Baris 2: N bilangan (hanya 0, 1, 2)
 * Output format : N bilangan setelah diurutkan
 * Constraints   : 1 ≤ N ≤ 300.000
 *                 A[i] ∈ {0, 1, 2}
 *
 * Sample Input 1:      Sample Output 1:
 * 6                    0 0 1 1 2 2
 * 2 0 2 1 1 0
 *
 * Sample Input 2:      Sample Output 2:
 * 5                    0 0 1 2 2
 * 0 1 2 2 0
 *
 * Sample Input 3:      Sample Output 3:
 * 3                    0 1 2
 * 2 1 0
 *
 * Penjelasan Sample 1:
 *   A=[2,0,2,1,1,0], low=0, mid=0, high=5
 *   A[mid=0]=2 → swap(A[0],A[5]), high-- → A=[0,0,2,1,1,2], high=4
 *   A[mid=0]=0 → swap(A[0],A[0]), low++, mid++ → low=1, mid=1
 *   A[mid=1]=0 → swap(A[1],A[1]), low++, mid++ → low=2, mid=2
 *   A[mid=2]=2 → swap(A[2],A[4]), high-- → A=[0,0,1,1,2,2], high=3
 *   A[mid=2]=1 → mid++
 *   A[mid=3]=1 → mid++
 *   mid=4 > high=3, stop.
 *   Result: [0,0,1,1,2,2] ✓
 *
 * Bonus: Solusi O(n) one-pass dengan O(1) space.
 *        Bandingkan dengan counting sort O(n): hitung jumlah 0,1,2 lalu isi.
 *        Dutch Flag lebih elegan karena benar-benar satu pass!
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Tulis solusimu di sini

    return 0;
}
