/*
 * Day 19 — Two Pointers
 * File  : tugas_04.cpp
 * Topik : Squares of a Sorted Array
 * Tingkat: Easy
 * -----------------------------------------------
 * Diberikan sorted array A berisi N bilangan bulat (bisa negatif dan positif).
 * Output array berisi kuadrat masing-masing elemen, dalam urutan menaik.
 *
 * Tantangan: jika A berisi bilangan negatif, kuadratnya bisa lebih besar
 * dari kuadrat elemen positif. Contoh: A=[-4,-1,0,3,10]
 * Kuadrat: [16, 1, 0, 9, 100] → sorted: [0, 1, 9, 16, 100]
 *
 * Pendekatan Two Pointers (O(n)):
 *   - L = 0, R = N-1
 *   - Bandingkan abs(A[L]) dengan abs(A[R])
 *   - Elemen dengan nilai absolut lebih besar masuk ke hasil dari belakang
 *   - Advance pointer yang dipilih
 *
 * Alternatif naif: kuadratkan semua, lalu sort → O(n log n)
 * Target: solusi O(n) dengan two pointers.
 *
 * Input format  : Baris 1: N
 *                 Baris 2: N bilangan bulat (sorted ascending, bisa negatif)
 * Output format : N bilangan: kuadrat elemen sorted ascending
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 -10^4 ≤ A[i] ≤ 10^4
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    0 1 9 16 100
 * -4 -1 0 3 10
 *
 * Sample Input 2:      Sample Output 2:
 * 4                    1 4 9 16
 * -2 -1 1 2
 *
 * Sample Input 3:      Sample Output 3:
 * 3                    1 4 9
 * 1 2 3
 *
 * Penjelasan Sample 1:
 *   A=[-4,-1,0,3,10], kuadrat=[16,1,0,9,100]
 *   L=0(val=-4,sq=16), R=4(val=10,sq=100): 16<100 → R masuk ke result[4]=100, R--
 *   L=0(sq=16), R=3(val=3,sq=9): 16>9 → L masuk ke result[3]=16, L++
 *   ... dst
 *
 * Hint:
 *   - Buat array hasil berukuran N
 *   - Isi dari belakang (indeks N-1 ke 0)
 *   - Gunakan L dan R untuk memilih kuadrat terbesar berikutnya
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

    int left = 0, right = n - 1;

    vector<int> hasil(n);

    int idx = n - 1;

    while (right >= left)
    {
        if (abs(arr[left]) > abs(arr[right]))
        {
            hasil[idx] = pow(arr[left], 2);
            left++;
        }
        else
        {
            hasil[idx] = pow(arr[right], 2);
            right--;
        }
        idx--;
    }

    for (int i = 0; i < n; i++)
    {
        cout << hasil[i] << " ";
    }
}