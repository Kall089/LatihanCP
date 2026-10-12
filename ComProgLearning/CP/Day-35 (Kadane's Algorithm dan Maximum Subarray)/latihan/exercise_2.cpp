/*
============================================================
🏋️ Exercise 2: Subarray Maksimum Beserta Posisinya
============================================================
Day: 35 | Difficulty: Easy
Topic: Kadane + pelacakan indeks
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Cari subarray tidak kosong dengan
jumlah maksimum, lalu cetak tiga bilangan: jumlahnya, indeks awal, dan
indeks akhir (1-based, inklusif).
Jika ada beberapa subarray dengan jumlah maksimum yang sama, cetak yang
indeks awalnya PALING KECIL. Jika masih seri, cetak yang indeks akhirnya
paling kecil.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Tiga bilangan dipisah spasi: jumlah, awal, akhir

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
9
-2 1 -3 4 -1 2 1 -5 4

📎 SAMPLE OUTPUT 1:
6 4 7

📎 SAMPLE INPUT 2:
3
-5 -2 -9

📎 SAMPLE OUTPUT 2:
-2 2 2

💡 HINT: Simpan satu variabel tambahan: indeks awal subarray yang sedang
         kamu bangun. Variabel itu hanya berubah pada satu momen — momen
         ketika kamu memutuskan untuk MEMULAI BARU.
         Untuk aturan tie-breaking, perhatikan apakah kamu memakai
         perbandingan > atau >= saat memperbarui jawaban terbaik.

🎯 Learning Goals:
- [ ] Melacak indeks tanpa merusak kesederhanaan Kadane
- [ ] Menangani aturan tie-breaking lewat pilihan operator perbandingan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    int bl, br;
    int curr = arr[1];
    int curL;
    int best = INT_MIN;

    for (int i = 1; i <= n; i++)
    {
        if (curr < 0)
        {
            curr = arr[i];
            curL = i;
        }
        else
        {
            curr += arr[i];
        }

        if (best < curr)
        {
            best = curr;
            bl = curL;
            br = i;
        }
    }

    cout << best << " " << bl << " " << br;
}