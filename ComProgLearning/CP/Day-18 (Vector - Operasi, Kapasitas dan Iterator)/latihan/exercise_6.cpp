/*
============================================================
🏋️ Exercise 6: Student Records (Multi-Criteria Sort + Tuple)
============================================================
Day: 3 | Difficulty: Hard
Topic: Tuple, Vector, Custom Sort, String
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah universitas menyimpan data mahasiswa berupa:
- Nama (string)
- IPK (floating point, 2 desimal)
- Angkatan (integer tahun)

Urutkan mahasiswa dengan aturan:
1. IPK TERTINGGI dulu (descending)
2. Jika IPK sama, angkatan TERLAMA dulu (ascending)
3. Jika IPK dan angkatan sama, nama secara LEXICOGRAPHIC (ascending)

Output nama-nama mahasiswa setelah diurutkan, satu per baris.

📥 INPUT FORMAT:
- Baris pertama: integer N (jumlah mahasiswa)
- N baris berikutnya: nama (string tanpa spasi), IPK (double), angkatan (int)

📤 OUTPUT FORMAT:
- N baris: nama mahasiswa setelah diurutkan

📏 CONSTRAINTS:
- 1 ≤ N ≤ 100,000
- 1 ≤ |nama| ≤ 20
- 0.00 ≤ IPK ≤ 4.00
- 2000 ≤ angkatan ≤ 2025

📎 SAMPLE INPUT 1:
5
Alice 3.80 2021
Bob 3.90 2020
Charlie 3.80 2020
Dave 3.90 2021
Eve 3.80 2021

📎 SAMPLE OUTPUT 1:
Bob
Dave
Charlie
Alice
Eve

📎 SAMPLE INPUT 2:
3
Zoe 4.00 2022
Amy 4.00 2022
Mia 4.00 2022

📎 SAMPLE OUTPUT 2:
Amy
Mia
Zoe

💡 HINT: Gunakan vector<tuple<...>> atau struct.
         Untuk sort descending IPK, bisa negate atau custom comparator.
         Hati-hati floating point comparison!

🎯 Learning Goals:
- [ ] Baca data campuran (string, double, int) ke tuple/struct
- [ ] Implementasi multi-criteria sort
- [ ] Handle floating point dalam sorting
- [ ] Gunakan custom comparator atau trick negate
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N

    // TODO: Baca data mahasiswa ke container yang sesuai
    //       (vector<tuple<...>> atau vector<struct>)

    // TODO: Sort dengan aturan:
    //       1. IPK descending
    //       2. Angkatan ascending
    //       3. Nama ascending (lexicographic)

    // TODO: Output nama-nama setelah sort

    return 0;
}
