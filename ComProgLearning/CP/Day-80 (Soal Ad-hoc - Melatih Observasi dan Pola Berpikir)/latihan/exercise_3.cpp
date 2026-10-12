/*
============================================================
🏋️ Exercise 3: Mundur dari Tujuan
============================================================
Day: 80 | Difficulty: Medium
Topic: Membalik arah operasi
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu mulai dengan pasangan bilangan (1, 1). Pada setiap langkah kamu boleh
mengganti pasangan (x, y) menjadi (x + y, y) atau menjadi (x, y + x).
Diberikan pasangan target (a, b), cari JUMLAH LANGKAH MINIMUM untuk
mencapainya, atau -1 kalau tidak mungkin.

📥 INPUT FORMAT:
- Satu baris berisi a dan b

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah langkah minimum, atau -1

📏 CONSTRAINTS:
- 1 <= a, b <= 10^18

📎 SAMPLE INPUT 1:
5 3

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
1 1

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
4 4

📎 SAMPLE OUTPUT 3:
-1

💡 HINT: Coba dulu berpikir maju: dari (1,1) ada dua pilihan, lalu dua lagi,
         dan seterusnya. Percabangannya berlipat dua setiap langkah, dan
         dengan target sampai 10^18 itu jelas mustahil ditelusuri.
         Sekarang balik arahnya. Kalau kamu berada di (a, b), pasangan
         SEBELUMNYA pasti apa? Tuliskan kedua operasi maju dan cari
         inversnya.
         Kamu akan menemukan sesuatu yang penting: dari belakang, hanya ada
         SATU kemungkinan pada tiap langkah, bukan dua. Tidak ada
         percabangan sama sekali.
         Setelah itu, perhatikan bahwa proses mundurnya berupa pengurangan
         berulang. Kalau a jauh lebih besar dari b, kamu akan mengurangi b
         berkali-kali — dan ada cara yang jauh lebih cepat untuk melakukan
         itu sekaligus. Kamu sudah mengenal algoritmanya.
         Hati-hati pada satu kasus tepi: kapan proses mundurnya MACET?
         Sampel 3 menguji itu.
         Kasus tepi kedua: kalau salah satu bilangan bernilai 1, berapa
         langkah tersisa? Rumus pembagian biasa bisa salah di situ —
         periksa dengan tangan.

🎯 Learning Goals:
- [ ] Mengenali kapan pembalikan arah menghilangkan percabangan
- [ ] Mempercepat pengurangan berulang dengan pembagian
- [ ] Menangani kasus macet dan kasus tepi bernilai 1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: balik arah operasinya

    // TODO: percepat pengurangan berulang

    // TODO: tangani kasus macet dan nilai 1

    return 0;
}
