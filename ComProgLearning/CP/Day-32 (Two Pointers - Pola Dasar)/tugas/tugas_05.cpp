/*
 * Day 19 — Two Pointers
 * File  : tugas_05.cpp
 * Topik : Move All Zeros to End (In-Place)
 * Tingkat: Easy
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat. Geser semua elemen nol ke
 * akhir array, pertahankan urutan relatif elemen non-nol. Lakukan secara
 * in-place (modifikasi array A langsung).
 *
 * Contoh:
 *   A = [0, 1, 0, 3, 12]
 *   Setelah: [1, 3, 12, 0, 0]
 *   Urutan relatif 1, 3, 12 dipertahankan. ✓
 *
 * Pendekatan Two Pointers (Slow-Fast, Same Direction):
 *   - slow = posisi penulisan elemen non-nol
 *   - fast iterasi semua elemen
 *   - Jika A[fast] != 0 → tulis ke A[slow], slow++
 *   - Setelah loop: isi A[slow..n-1] dengan 0
 *
 * Input format  : Baris 1: N
 *                 Baris 2: N bilangan bulat
 * Output format : N bilangan setelah pemindahan nol
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    1 3 12 0 0
 * 0 1 0 3 12
 *
 * Sample Input 2:      Sample Output 2:
 * 4                    1 2 3 0
 * 0 1 2 3
 *
 * Sample Input 3:      Sample Output 3:
 * 3                    1 2 3
 * 1 2 3
 *
 * Sample Input 4:      Sample Output 4:
 * 3                    0 0 0
 * 0 0 0
 *
 * Penjelasan Sample 1:
 *   A=[0,1,0,3,12]
 *   slow=0
 *   fast=0: A[0]=0 → skip
 *   fast=1: A[1]=1 ≠ 0 → A[slow=0]=1, slow++
 *   fast=2: A[2]=0 → skip
 *   fast=3: A[3]=3 ≠ 0 → A[slow=1]=3, slow++
 *   fast=4: A[4]=12 ≠ 0 → A[slow=2]=12, slow++
 *   Isi A[3..4] dengan 0
 *   Result: [1, 3, 12, 0, 0] ✓
 *
 * Bonus: Dapatkah kamu selesaikan dengan jumlah operasi swap minimum?
 *        (Hint: swap A[slow] dan A[fast] alih-alih copy)
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

    for (int fast = 0; fast < n; fast++)
    {
        if (arr[fast] != 0)
        {
            swap(arr[slow], arr[fast]);
            slow++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}
