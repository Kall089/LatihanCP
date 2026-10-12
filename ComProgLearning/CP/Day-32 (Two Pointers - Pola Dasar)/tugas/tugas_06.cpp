/*
 * Day 19 — Two Pointers
 * File  : tugas_06.cpp
 * Topik : Longest Subarray With Sum <= K
 * Tingkat: Medium
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat NON-NEGATIF dan bilangan K.
 * Temukan panjang subarray (kontinu) terpanjang dengan jumlah elemen ≤ K.
 *
 * Pendekatan Sliding Window (Two Pointers Same Direction):
 *   - L = 0, R = 0: ujung kiri dan kanan window
 *   - Expand: R++ (tambahkan A[R] ke sum)
 *   - Shrink: jika sum > K, kurangi A[L] dan L++
 *   - Update jawaban: ans = max(ans, R - L + 1) ketika sum ≤ K
 *
 * Mengapa benar? Setiap elemen masuk dan keluar window tepat satu kali → O(n).
 *
 * Input format  : Baris 1: N K
 *                 Baris 2: N bilangan bulat non-negatif
 * Output format : Satu bilangan: panjang subarray terpanjang dengan sum ≤ K
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ A[i] ≤ 10^9
 *                 0 ≤ K ≤ 10^18
 *
 * Sample Input 1:      Sample Output 1:
 * 5 6                  3
 * 1 3 2 5 1
 *
 * Sample Input 2:      Sample Output 2:
 * 4 15                 4
 * 1 2 3 4
 *
 * Sample Input 3:      Sample Output 3:
 * 3 0                  1
 * 1 2 3
 *
 * Sample Input 4:      Sample Output 4:
 * 5 100               5
 * 1 2 3 4 5
 *
 * Penjelasan Sample 1:
 *   A=[1,3,2,5,1], K=6
 *   Window [1,3,2]=6 ≤ 6 → panjang 3
 *   Window [3,2,5]=10 > 6
 *   Window [2,5]=7 > 6
 *   Window [5,1]=6 ≤ 6 → panjang 2
 *   Jawaban: 3 ✓
 *
 * Penjelasan Sample 3:
 *   A=[1,2,3], K=0
 *   Tidak ada subarray dengan sum=0 kecuali... hmm, semua elemen positif.
 *   Window terpanjang dengan sum≤0 tidak ada? Tapi A[i] ≥ 0 dan K ≥ 0.
 *   Jika A berisi 0, window bisa kosong... tapi panjang minimum = 1.
 *   Sebenarnya jika K=0 dan semua elemen positif, tidak ada subarray valid.
 *   Output: 0 (tidak ada subarray)
 *   (Note: constraint A[i] ≥ 0 memastikan sliding window bekerja)
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
