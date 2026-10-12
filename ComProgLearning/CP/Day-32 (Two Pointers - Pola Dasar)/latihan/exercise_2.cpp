/*
 * Day 19 — Two Pointers
 * File  : exercise_2.cpp
 * Topik : Remove Duplicates In-Place (Slow-Fast Pointers)
 * -----------------------------------------------
 * Diberikan sorted array A berisi N bilangan bulat. Hapus semua elemen
 * duplikat secara in-place sehingga setiap elemen unik hanya muncul sekali.
 * Ubah array A secara langsung (in-place), lalu output:
 *   - Baris 1: panjang array baru
 *   - Baris 2: elemen-elemen array baru (dipisah spasi)
 *
 * Gunakan slow-fast two pointers:
 *   - slow  = posisi penulisan (elemen unik terakhir)
 *   - fast  = membaca semua elemen
 *   - Jika A[fast] != A[slow] → tulis A[fast] ke A[++slow]
 *
 * Input format  : Baris 1: N (1 ≤ N ≤ 200.000)
 *                 Baris 2: N bilangan bulat terurut menaik
 * Output format : Baris 1: panjang array unik
 *                 Baris 2: elemen array unik
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *                 Array sudah terurut menaik
 *
 * Sample Input 1:      Sample Output 1:
 * 7                    4
 * 1 1 2 3 3 3 4        1 2 3 4
 *
 * Sample Input 2:      Sample Output 2:
 * 5                    3
 * 1 2 2 3 3            1 2 3
 *
 * Sample Input 3:      Sample Output 3:
 * 1                    1
 * 5                    5
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int slow = 0;

    for (int fast = 1; fast < n; fast++)
    {
        if (arr[fast] != arr[slow])
        {
            slow++;
            arr[slow] = arr[fast];
        }
    }

    for (int i = 0; i < slow + 1; i++)
    {
        cout << arr[i];
    }
}