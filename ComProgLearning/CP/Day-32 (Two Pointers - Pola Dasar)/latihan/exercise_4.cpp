/*
 * Day 19 — Two Pointers
 * File  : exercise_4.cpp
 * Topik : Three Sum Closest
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat dan sebuah target T. Temukan
 * tiga elemen A[i], A[j], A[k] (i < j < k) sehingga A[i]+A[j]+A[k] paling
 * dekat dengan T. Output jumlah ketiga elemen tersebut.
 *
 * Jika ada beberapa triplet dengan jarak yang sama ke T, output yang mana saja.
 *
 * Strategi:
 *   1. Sort array
 *   2. Untuk setiap i: gunakan two pointers L=i+1, R=N-1
 *   3. Hitung sum = A[i]+A[L]+A[R]
 *   4. Update jawaban jika |sum-T| < |ans-T|
 *   5. Jika sum < T → L++; jika sum > T → R--; jika sama → break
 *
 * Input format  : Baris 1: N T (1 ≤ N ≤ 3000, -10^5 ≤ T ≤ 10^5)
 *                 Baris 2: N bilangan bulat
 * Output format : Satu bilangan: sum triplet terdekat ke T
 * Constraints   : 3 ≤ N ≤ 3000
 *                 -10^4 ≤ A[i] ≤ 10^4
 *                 -10^5 ≤ T ≤ 10^5
 *
 * Sample Input 1:      Sample Output 1:
 * 4 1                  2
 * -1 2 1 -4
 *
 * Sample Input 2:      Sample Output 2:
 * 3 100                6
 * 1 2 3
 *
 * Sample Input 3:      Sample Output 3:
 * 5 0                  0
 * -2 -1 0 1 2
 *
 * Penjelasan Sample 1:
 *   Sorted: [-4,-1,1,2]. Triplet terdekat ke 1:
 *   (-1+1+2)=2 → |2-1|=1
 *   (-4+1+2)=-1 → |-1-1|=2
 *   Closest: 2
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, T;
    cin >> n >> T;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    // TODO: implementasikan three sum closest
    // sort(A.begin(), A.end());
    // int ans = A[0] + A[1] + A[2];  // inisialisasi dengan triplet pertama
    //
    // for (int i = 0; i < n - 2; i++) {
    //     int L = i + 1, R = n - 1;
    //     while (L < R) {
    //         int s = A[i] + A[L] + A[R];
    //         if (abs(s - T) < abs(ans - T)) ans = s;
    //         if (s < T) L++;
    //         else if (s > T) R--;
    //         else break;  // s == T, perfect match
    //     }
    // }
    // cout << ans << "\n";

    return 0;
}
