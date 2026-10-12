/*
 * Day 19 — Two Pointers
 * File  : tugas_01.cpp
 * Topik : Count Pairs With Sum = K
 * Tingkat: Easy
 * -----------------------------------------------
 * Diberikan sorted array A berisi N bilangan bulat dan sebuah target K.
 * Hitung berapa banyak pasangan (i, j) dengan i < j sehingga A[i] + A[j] = K.
 *
 * Perhatian: Jika array mengandung duplikat, pasangan yang sama secara nilai
 * tetap dihitung jika indeksnya berbeda.
 *
 * Contoh:
 *   A = [1, 1, 2, 3, 4, 5], K = 5
 *   Pasangan yang valid:
 *     (A[0]=1, A[4]=4): 1+4=5 ✓
 *     (A[1]=1, A[4]=4): 1+4=5 ✓
 *     (A[2]=2, A[3]=3): 2+3=5 ✓  ← tunggu, ini indeks 2 dan 3, nilai 2+3=5
 *   Total: Hitung semua pasangan indeks (i,j) dengan A[i]+A[j]=K
 *
 * Input format  : Baris 1: N K
 *                 Baris 2: N bilangan bulat (sorted ascending)
 * Output format : Satu bilangan: jumlah pasangan
 * Constraints   : 2 ≤ N ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *                 -2×10^9 ≤ K ≤ 2×10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 5 6                  2
 * 1 2 3 4 5
 *
 * Sample Input 2:      Sample Output 2:
 * 6 5                  3
 * 1 1 2 3 4 5
 *
 * Sample Input 3:      Sample Output 3:
 * 4 10                 0
 * 1 2 3 4
 *
 * Penjelasan Sample 1:
 *   A=[1,2,3,4,5], K=6
 *   Pasangan: (1,5)=6, (2,4)=6 → 2 pasangan ✓
 *
 * Penjelasan Sample 2:
 *   A=[1,1,2,3,4,5], K=5
 *   Saat A[L]+A[R]=5: jika A[L]=A[R], hitung kombinasi C(count, 2)
 *   Jika A[L]!=A[R], hitung count_L * count_R
 *
 * Hint:
 *   - Gunakan two pointers L dan R
 *   - Saat A[L]+A[R] < K: L++
 *   - Saat A[L]+A[R] > K: R--
 *   - Saat A[L]+A[R] = K:
 *     - Jika A[L] != A[R]: hitung jumlah A[L] (countL) dan A[R] (countR)
 *       tambahkan countL * countR ke jawaban, L += countL, R -= countR
 *     - Jika A[L] == A[R]: semua elemen di antara L dan R sama
 *       jumlah elemen = R-L+1, tambahkan C(jumlah, 2), stop
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
