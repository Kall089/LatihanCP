/*
============================================================
🏋️ Exercise 1: Nilai Paling Sering Muncul
============================================================
Day: 40 | Difficulty: Easy
Topic: Array frekuensi dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat antara 1 dan 10^6. Cari nilai yang
paling sering muncul, lalu cetak nilai itu beserta banyaknya kemunculan.
Jika ada beberapa nilai dengan banyak kemunculan yang sama, cetak nilai
yang PALING KECIL di antara mereka.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Dua bilangan dipisah spasi: nilai dan banyaknya kemunculan

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- 1 <= a[i] <= 10^6

📎 SAMPLE INPUT 1:
7
3 1 4 1 5 1 4

📎 SAMPLE OUTPUT 1:
1 3

📎 SAMPLE INPUT 2:
4
2 2 5 5

📎 SAMPLE OUTPUT 2:
2 2

💡 HINT: Karena nilainya paling besar 10^6, kamu bisa memakai array biasa
         alih-alih map — dan bedanya bisa mencapai 100 kali lipat untuk
         N sebesar ini.
         Deklarasikan array itu sebagai variabel GLOBAL: ia otomatis nol,
         dan array sebesar itu di dalam fungsi bisa membuat stack meledak.
         Untuk aturan seri, perhatikan urutan penyapuanmu.

🎯 Learning Goals:
- [ ] Memilih array alih-alih map ketika domainnya kecil
- [ ] Menyadari kenapa array besar harus global
- [ ] Menangani aturan tie-breaking lewat arah sapuan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int cnt[100000];

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int nilai = 0, best = 0;
    for (int i = 0; i < n; i++)
    {
        if (cnt[i] > best)
        {
            best = cnt[i];
            nilai = i;
        }
    }

    cout << nilai << " " << best;
}