/*
============================================================
📋 TUGAS 03: Best Time to Buy and Sell Stock
============================================================
Source: LeetCode 121
Difficulty: Easy
Topics: kadane pada array selisih

PROBLEM:
Diberikan harga saham selama N hari. Beli tepat sekali, lalu jual tepat
sekali pada hari SETELAH hari beli. Cari keuntungan maksimum. Kalau
semua kemungkinan transaksi merugi, cetak 0 (tidak bertransaksi).

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N harga

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5
- 0 <= p[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
6
7 1 5 3 6 4
output:
5
penjelasan: beli di hari 2 (harga 1), jual di hari 5 (harga 6).
Lewat array selisih d = [-6,4,-2,3,-2], jawabannya adalah Kadane
BOLEH-KOSONG pada d: [4,-2,3] = 5.

SAMPLE 2 - harga terus turun
input:
5
7 6 4 3 1
output:
0
penjelasan: semua selisih negatif. Karena boleh tidak bertransaksi,
jawabannya 0. Di sinilah versi "boleh kosong" wajib dipakai.

SAMPLE 3 - N = 1
input:
1
5
output:
0
penjelasan: tidak ada hari untuk menjual. Jangan sampai kodemu
mengakses p[1] dan crash.

SAMPLE 4 - untung terbesar bukan dari titik terendah yang terlihat
input:
6
2 4 1 7 5 11
output:
10
penjelasan: beli di hari 3 (harga 1), jual di hari 6 (harga 11).
Kalau kamu berhenti di kenaikan pertama (2 -> 4) kamu cuma dapat 2.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- jawaban minimal 0 (versi BOLEH KOSONG)
- aman untuk N = 1
- harga sampai 10^9, selisihnya muat di int tapi pakai long long saja
============================================================
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

    int best = INT_MIN, currMax = 0;

    for (int i = 1; i < n; i++)
    {
        int diff = arr[i] - arr[i - 1];

        currMax = max(0, currMax + diff);
        best = max(best, currMax);
    }

    cout << best;
}