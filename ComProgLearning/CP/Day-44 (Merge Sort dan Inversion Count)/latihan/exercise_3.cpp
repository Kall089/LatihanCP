/*
============================================================
🏋️ Exercise 3: Hitung Inversi
============================================================
Day: 44 | Difficulty: Medium
Topic: Inversion count di dalam merge
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Hitung banyaknya INVERSI, yaitu
banyaknya pasangan indeks (i, j) dengan i < j dan a[i] > a[j].
Sebagai contoh, array [2, 1, 3] punya satu inversi yaitu pasangan (2, 1).
Perhatikan bahwa elemen yang nilainya SAMA tidak dihitung sebagai inversi.
Karena N bisa mencapai 10^5, pendekatan O(N^2) akan TLE.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya inversi

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- -10^9 <= a[i] <= 10^9
- Jawaban bisa mencapai ~5 * 10^9

📎 SAMPLE INPUT 1:
6
5 2 4 6 1 3

📎 SAMPLE OUTPUT 1:
9

📎 SAMPLE INPUT 2:
5
1 2 3 4 5

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
4
4 3 2 1

📎 SAMPLE OUTPUT 3:
6

💡 HINT: Inversi yang seluruhnya berada di bagian kiri dan yang seluruhnya
         di bagian kanan sudah dihitung oleh rekursi. Yang tersisa hanyalah
         inversi yang MELINTASI batas — dan itu bisa dihitung saat merge.
         Saat kamu mengambil sebuah elemen dari bagian KANAN, berapa banyak
         elemen di bagian kiri yang lebih besar darinya? Ingat bahwa bagian
         kiri sudah terurut.
         Jawabannya BUKAN satu.

🎯 Learning Goals:
- [ ] Memahami kenapa penghitungannya mid - i dan bukan 1
- [ ] Menyadari bahwa inversi lintas batas adalah satu-satunya yang tersisa
- [ ] Ingat long long
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: fungsi rekursif yang mengembalikan jumlah inversi

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: panggil, cetak

    return 0;
}
