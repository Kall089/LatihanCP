/*
============================================================
🏋️ Exercise 4: Menunggu Hari Lebih Panas
============================================================
Day: 42 | Difficulty: Medium
Topic: ❓ DIRAHASIAKAN — tebak sendiri sebelum menulis kode
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan suhu harian selama N hari. Untuk SETIAP hari i, tentukan berapa
hari lagi sampai muncul hari yang suhunya LEBIH TINGGI dari hari i.
Kalau tidak pernah ada hari yang lebih panas sesudahnya, jawabannya 0.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- N bilangan dipisah spasi

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2·10^5
- 1 ≤ suhu ≤ 10^9

📎 SAMPLE INPUT 1:
8
73 74 75 71 69 72 76 73

📎 SAMPLE OUTPUT 1:
1 1 4 2 1 1 0 0

📎 SAMPLE INPUT 2:
4
30 40 50 60

📎 SAMPLE OUTPUT 2:
1 1 1 0

📎 SAMPLE INPUT 3:
3
50 40 30

📎 SAMPLE OUTPUT 3:
0 0 0

📎 SAMPLE INPUT 4:
3
5 5 5

📎 SAMPLE OUTPUT 4:
0 0 0

💡 HINT: Frasa "untuk SETIAP i, cari yang terdekat" cuma menunjuk ke satu
         teknik di seluruh blok Day 29-41. Sample 4 menguji apakah kamu
         memakai "lebih tinggi" atau keliru memakai "lebih tinggi atau sama".

🎯 Learning Goals:
- [ ] Mengenali pola "untuk tiap i, tetangga terdekat"
- [ ] Memahami perbedaan < dan <= saat ada nilai kembar
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
