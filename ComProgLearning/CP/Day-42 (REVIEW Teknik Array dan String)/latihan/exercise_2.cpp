/*
============================================================
🏋️ Exercise 2: Pasangan Hari Genap
============================================================
Day: 42 | Difficulty: Medium
Topic: ❓ DIRAHASIAKAN — tebak sendiri sebelum menulis kode
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah toko mencatat keuntungan harian selama N hari (boleh negatif, artinya
rugi). Manajer ingin tahu ada berapa periode berurutan (l..r) yang total
keuntungannya habis dibagi M.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: N bilangan bulat

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2·10^5
- 1 ≤ M ≤ 10^5
- -10^9 ≤ a[i] ≤ 10^9

📎 SAMPLE INPUT 1:
5 5
2 3 5 4 1

📎 SAMPLE OUTPUT 1:
6

📎 SAMPLE INPUT 2:
3 3
1 1 1

📎 SAMPLE OUTPUT 2:
1

📎 SAMPLE INPUT 3:
4 2
-1 3 -2 2

📎 SAMPLE OUTPUT 3:
6

📎 SAMPLE INPUT 4:
1 7
7

📎 SAMPLE OUTPUT 4:
1

💡 HINT: Kata kerjanya "ada berapa", bukan "berapa maksimum". Itu mengubah
         tekniknya sepenuhnya. Sample 3 punya bilangan negatif untuk sebuah
         alasan — di C++, (-1) % 2 bukan 1.

🎯 Learning Goals:
- [ ] Membedakan "menghitung banyaknya" dari "mencari maksimum"
- [ ] Menangani modulo pada bilangan negatif
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: TEKNIK SAYA: ______________________
    //       ALASAN     : ______________________

    // TODO: Implementasi

    return 0;
}
