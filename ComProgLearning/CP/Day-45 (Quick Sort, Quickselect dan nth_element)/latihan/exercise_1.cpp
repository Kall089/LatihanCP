/*
============================================================
🏋️ Exercise 1: Elemen Terbesar ke-K
============================================================
Day: 45 | Difficulty: Easy
Topic: nth_element / quickselect
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan sebuah bilangan K.
Cari elemen TERBESAR ke-K di dalam array. Perhatikan bahwa elemen yang
nilainya sama tetap dihitung terpisah — misalnya pada array [3, 3, 1],
elemen terbesar ke-1 adalah 3 dan elemen terbesar ke-2 juga 3.
Karena N besar dan kamu hanya membutuhkan SATU nilai, mengurutkan seluruh
array adalah pekerjaan yang berlebihan. Cari cara yang lebih cepat.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= K <= N <= 10^6
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
6 2
3 2 1 5 6 4

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
3 2
3 3 1

📎 SAMPLE OUTPUT 2:
3

💡 HINT: Ada fungsi di STL yang menemukan elemen pada posisi tertentu
         dalam waktu LINIER, tanpa mengurutkan sisanya. Cari tahu namanya.
         Hati-hati dengan konversi indeks: "terbesar ke-K" berarti indeks
         ke berapa kalau array diurutkan MENAIK?

🎯 Learning Goals:
- [ ] Mengenal nth_element dan bedanya dengan sort
- [ ] Konversi antara "terbesar ke-K" dan indeks 0-based
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca input

    // TODO: cari posisi yang benar, lalu pakai nth_element

    return 0;
}
