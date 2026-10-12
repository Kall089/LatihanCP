/*
 * Day 19 — Two Pointers
 * File  : tugas_02.cpp
 * Topik : Common Element in Two Sorted Arrays
 * Tingkat: Easy
 * -----------------------------------------------
 * Diberikan dua sorted array A (N elemen) dan B (M elemen).
 * Cek apakah ada setidaknya satu elemen yang muncul di keduanya.
 * Output "YES" jika ada elemen yang sama, "NO" jika tidak.
 *
 * Gunakan teknik merge pointer (mirip merge sort):
 *   - i = pointer untuk A, j = pointer untuk B
 *   - Jika A[i] == B[j] → FOUND
 *   - Jika A[i] < B[j] → i++ (A[i] terlalu kecil untuk match B[j])
 *   - Jika A[i] > B[j] → j++ (B[j] terlalu kecil untuk match A[i])
 *
 * Input format  : Baris 1: N M
 *                 Baris 2: N bilangan bulat (sorted ascending)
 *                 Baris 3: M bilangan bulat (sorted ascending)
 * Output format : "YES" atau "NO"
 * Constraints   : 1 ≤ N, M ≤ 200.000
 *                 -10^9 ≤ A[i], B[j] ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 4 4                  YES
 * 1 3 5 7
 * 2 3 6 8
 *
 * Sample Input 2:      Sample Output 2:
 * 3 3                  NO
 * 1 3 5
 * 2 4 6
 *
 * Sample Input 3:      Sample Output 3:
 * 5 3                  YES
 * 1 2 3 4 5
 * 3 6 9
 *
 * Penjelasan Sample 1:
 *   A=[1,3,5,7] dan B=[2,3,6,8]: nilai 3 ada di keduanya → YES ✓
 *
 * Penjelasan Sample 2:
 *   A=[1,3,5] dan B=[2,4,6]: tidak ada nilai yang sama → NO ✓
 *
 * Bonus: Jika ingin output semua elemen yang sama,
 *        lanjutkan pointer keduanya setelah match ditemukan.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    vector<int> b(m);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }

    int i = 0, j = 0;

    while (i < n && j < m)
    {
        if (a[i] == b[j])
        {
            cout << "found";
            return 0;
        }
        else if (a[i] < b[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }

    cout << "NO" << endl;
}