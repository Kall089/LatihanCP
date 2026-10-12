/*
 * Day 19 — Two Pointers
 * File  : tugas_03.cpp
 * Topik : Pair With Sum = 0 (Zero Sum Pair)
 * Tingkat: Easy
 * -----------------------------------------------
 * Diberikan sorted array A berisi N bilangan bulat (bisa negatif).
 * Cek apakah ada pasangan (i, j) dengan i < j sehingga A[i] + A[j] = 0.
 * Jika ada, output "YES" dan indeks pasangan pertama yang ditemukan (1-based).
 * Jika tidak ada, output "NO".
 *
 * Ini adalah kasus khusus dari Two Sum dengan target = 0.
 *
 * Input format  : Baris 1: N
 *                 Baris 2: N bilangan bulat (sorted ascending)
 * Output format : "YES\ni j" (1-based) atau "NO"
 * Constraints   : 2 ≤ N ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 6                    YES
 * -3 -1 0 2 3 5        1 5
 *
 * Sample Input 2:      Sample Output 2:
 * 4                    NO
 * 1 2 3 4
 *
 * Sample Input 3:      Sample Output 3:
 * 5                    YES
 * -5 -3 -1 1 5         1 5
 *
 * Sample Input 4:      Sample Output 4:
 * 4                    YES
 * -2 -1 0 2            1 4
 *
 * Penjelasan Sample 1:
 *   A=[-3,-1,0,2,3,5]: A[0]=-3, A[4]=3 → -3+3=0 → YES, "1 5" ✓
 *
 * Penjelasan Sample 4:
 *   A=[-2,-1,0,2]: A[0]=-2, A[3]=2 → -2+2=0 → YES, "1 4" ✓
 *
 * Hint:
 *   Sama persis dengan Two Sum Sorted, hanya target T = 0.
 *   Perhatikan elemen 0: A[i]+A[j]=0 bisa berupa A[i]=0 dan A[j]=0,
 *   atau A[i]=-x dan A[j]=x untuk x positif.
 */

#include <bits/stdc++.h>
using namespace std;

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

    int left = 0, right = n - 1;

    while (right > left)
    {
        int jumlah = arr[left] + arr[right];

        if (jumlah == 0)
        {
            cout << "YES" << endl;
            cout << left + 1 << " " << right + 1;
            return 0;
        }
        else if (jumlah > 0)
        {
            right--;
        }
        else
        {
            left++;
        }
    }

    cout << "NO";

    return 0;
}
