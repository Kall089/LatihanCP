/*
 * Day 20 — Sliding Window
 * File  : exercise_1.cpp
 * Topik : Maximum Sum Subarray Size K (Fixed-Size Window)
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat dan integer K.
 * Cari jumlah MAKSIMUM dari semua subarray kontinu yang berukuran tepat K.
 *
 * Gunakan teknik FIXED-SIZE SLIDING WINDOW:
 *   - Hitung sum window pertama [0..K-1]
 *   - Untuk setiap i dari K sampai N-1:
 *       sum += A[i] - A[i-K]   (tambah baru, kurangi lama)
 *       update jawaban
 *
 * Input format  : Baris 1: N dan K (1 ≤ K ≤ N ≤ 200.000)
 *                 Baris 2: N bilangan bulat
 * Output format : satu integer — sum maksimum
 * Constraints   : 1 ≤ K ≤ N ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *                 (Pakai long long untuk sum!)
 *
 * Sample Input 1:        Sample Output 1:
 * 6 3                    9
 * 2 1 5 1 3 2
 *
 * Sample Input 2:        Sample Output 2:
 * 5 2                    11
 * 4 7 1 8 3
 *
 * Sample Input 3:        Sample Output 3:
 * 4 4                    10
 * 1 2 3 4
 *
 * NOTE Sample 1: window [5,1,3] → sum = 9 (maksimum).
 * NOTE Sample 2: window [4,7] → 11, window [7,1]→8, window [1,8]→9, window [8,3]→11. Max=11.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n);

    long long sum = 0;
    long long ans;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < k; i++)
    {
        sum += a[i];
    }
    ans = sum;

    for (int i = k; i < n; i++)
    {
        sum += a[i] - a[i - k];
        ans = max(ans, sum);
    }

    cout << ans;
}
