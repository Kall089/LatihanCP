/*
============================================================
📋 TUGAS 02: Subarray dengan Jumlah Minimum
============================================================
Source: Original
Difficulty: Easy
Topics: kadane arah sebaliknya, pakai ulang alat yang ada

PROBLEM:
Diberikan array N bilangan bulat (boleh negatif). Cari jumlah subarray
TIDAK KOSONG yang paling KECIL.

Soal ini kelihatan seperti soal baru, padahal bukan. Sebelum menulis
Kadane versi minimum dari nol, pikirkan dulu: apa yang terjadi kalau
seluruh array kamu kalikan -1?

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
6
3 -4 2 -3 -1 7
output:
-6
penjelasan: subarray [-4,2,-3,-1] = -6. Menambahkan 3 di depan atau 7
di belakang justru menaikkan jumlahnya.

SAMPLE 2 - semua positif
input:
4
2 5 1 3
output:
1
penjelasan: kalau semua elemen positif, subarray terbaik pasti panjang 1,
yaitu elemen terkecil. Cermin dari fakta "semua negatif -> ambil elemen
terbesar" di tugas 01.

SAMPLE 3 - N = 1
input:
1
-7
output:
-7

SAMPLE 4 - semua negatif
input:
5
-2 -3 -4 -1 -2
output:
-12
penjelasan: kebalikan dari sample 2 - semua negatif berarti ambil
SELURUH array.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- kalau kamu menegasikan array, jangan lupa menegasikan HASILNYA juga
- -(-10^9) tetap muat di long long, tapi jangan pakai int
- inisialisasi: LLONG_MAX untuk min, bukan 0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    long long worst = INT_MAX;
    long long currMin = 0;

    for (int i = 0; i < n; i++)
    {
        currMin = min(arr[i], currMin + arr[i]);
        worst = min(worst, currMin);
    }

    cout << worst;
}