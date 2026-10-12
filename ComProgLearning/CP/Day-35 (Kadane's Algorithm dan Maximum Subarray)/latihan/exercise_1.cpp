/*
============================================================
🏋️ Exercise 1: Jumlah Subarray Maksimum
============================================================
Day: 35 | Difficulty: Easy
Topic: Kadane dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat (boleh negatif). Cari subarray
(potongan berurutan) TIDAK KOSONG yang jumlah elemennya paling besar,
lalu cetak jumlah itu.
Perhatikan baik-baik kata "tidak kosong": kalau seluruh elemen bernilai
negatif, jawabannya adalah elemen terbesar (yang paling mendekati nol),
BUKAN nol.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
9
-2 1 -3 4 -1 2 1 -5 4

📎 SAMPLE OUTPUT 1:
6

📎 SAMPLE INPUT 2:
3
-5 -2 -9

📎 SAMPLE OUTPUT 2:
-2

💡 HINT: Untuk setiap posisi, kamu hanya punya dua pilihan: melanjutkan
         subarray sebelumnya, atau memulai yang baru dari sini. Kapan
         melanjutkan itu merugikan?
         Perhatikan juga inisialisasi jawabanmu — sampel 2 ada di sini
         khusus untuk menguji itu.

🎯 Learning Goals:
- [ ] Menurunkan rekurens Kadane sendiri
- [ ] Menginisialisasi best dengan benar untuk kasus semua negatif
- [ ] Refleks memakai long long
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    long long best = LLONG_MIN;
    long long worst = LLONG_MAX;
    long long currMin = 0;
    long long curr = 0;

    for (int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;

        curr = max(x, curr + x);
        best = max(best, curr);

        currMin = min(x, currMin + x);
        worst = min(worst, currMin);
    }

    cout << best << " " << worst;
}