/*
 * Day 19 — Two Pointers
 * File  : exercise_1.cpp
 * Topik : Two Sum Sorted Array
 * -----------------------------------------------
 * Diberikan sebuah sorted array A (terurut menaik) berisi N bilangan bulat
 * dan sebuah target T. Temukan sepasang indeks (i, j) dengan i < j sehingga
 * A[i] + A[j] = T. Jika ada, output pasangan indeks (1-based). Jika tidak
 * ada, output "IMPOSSIBLE".
 *
 * Gunakan pendekatan two pointers (opposite direction):
 *   - L = 0 (ujung kiri), R = N-1 (ujung kanan)
 *   - Jika A[L]+A[R] == T → output L+1 dan R+1
 *   - Jika A[L]+A[R] < T  → L++ (butuh nilai lebih besar)
 *   - Jika A[L]+A[R] > T  → R-- (butuh nilai lebih kecil)
 *
 * Input format  : Baris 1: N (1 ≤ N ≤ 200.000)
 *                 Baris 2: N bilangan bulat terurut menaik
 *                 Baris 3: T
 * Output format : "i j" (1-indexed, spasi) atau "IMPOSSIBLE"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *                 -2×10^18 ≤ T ≤ 2×10^18
 *
 * Sample Input 1:      Sample Output 1:
 * 6                    1 6
 * 1 3 4 6 8 9
 * 10
 *
 * Sample Input 2:      Sample Output 2:
 * 6                    1 4
 * 1 3 4 6 8 9
 * 7
 *
 * Sample Input 3:      Sample Output 3:
 * 4                    IMPOSSIBLE
 * 1 2 3 4
 * 10
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int target;
    cin >> target;

    int left = 0, right = n - 1;

    while (right < left)
    {
        int jumlah = arr[left] + arr[right];

        if (jumlah > target)
        {
            right--;
        }
        else
        {
            left++;
        }
    }

    cout << left + 1 << " " << right + 1;

    return 0;
}
