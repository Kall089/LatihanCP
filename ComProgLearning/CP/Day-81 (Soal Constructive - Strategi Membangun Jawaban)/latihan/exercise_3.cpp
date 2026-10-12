/*
============================================================
🏋️ Exercise 3: Tepat K Bergeser
============================================================
Day: 81 | Difficulty: Medium
Topic: Konstruksi baku lalu perbaiki
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan n dan k. Susun sebuah permutasi p dari bilangan 1 sampai n
sehingga TEPAT k posisi memenuhi p[i] tidak sama dengan i, dan n dikurangi k
posisi sisanya memenuhi p[i] sama dengan i.
Kalau ada beberapa jawaban, cetak mana saja.
Kalau tidak ada, cetak -1.

📥 INPUT FORMAT:
- Satu baris berisi n dan k

📤 OUTPUT FORMAT:
- n bilangan dipisah spasi, atau -1

📏 CONSTRAINTS:
- 1 <= n <= 2 * 10^5
- 0 <= k <= n

📎 SAMPLE INPUT 1:
5 3

📎 SAMPLE OUTPUT 1:
3 1 2 4 5

📎 SAMPLE INPUT 2:
5 1

📎 SAMPLE OUTPUT 2:
-1

📎 SAMPLE INPUT 3:
5 0

📎 SAMPLE OUTPUT 3:
1 2 3 4 5

💡 HINT: Kasus mustahilnya tidak sepele. Pikirkan: kalau kamu memindahkan
         sebuah elemen dari posisinya, ke mana ia pergi, dan apa yang
         terjadi pada elemen yang tadinya menempati tujuan itu?
         Dari situ kamu bisa menyimpulkan bahwa satu nilai k tertentu tidak
         mungkin. Buktikan dengan brute force untuk n kecil.
         Untuk konstruksinya, pakai Strategi 3: mulai dari sesuatu yang
         jelas benar, lalu perbaiki. Permutasi identitas memberi tepat nol
         posisi bergeser. Sekarang bagaimana caramu menaikkan angka itu
         menjadi tepat k?
         Petunjuk: kalau kamu MEMBALIK sebuah blok berukuran m, berapa
         posisi yang bergeser? Hati-hati kalau m ganjil — ada satu elemen
         yang tetap di tempatnya.
         Untuk menangani k ganjil, kamu butuh satu penyesuaian tambahan.
         Pikirkan operasi kecil apa yang menggeser tepat tiga elemen.
         Uji konstruksimu untuk SELURUH pasangan (n, k) dengan n sampai 60
         dan k dari 0 sampai n. Itu 1800-an kasus dan berjalan seketika.

🎯 Learning Goals:
- [ ] Memulai dari konstruksi baku lalu memperbaikinya
- [ ] Menemukan kasus mustahil yang tidak sepele
- [ ] Menguji seluruh kombinasi parameter, bukan sampel
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kasus mustahil

    // TODO: mulai dari identitas, lalu geser tepat k posisi

    return 0;
}
