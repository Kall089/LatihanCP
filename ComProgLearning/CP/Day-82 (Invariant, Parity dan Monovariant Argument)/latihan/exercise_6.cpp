/*
============================================================
🏋️ Exercise 6: Lampu dan Saklar
============================================================
Day: 82 | Difficulty: Hard (Contest-level)
Topic: Invarian pada operasi baris dan kolom
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada papan lampu berukuran N kali M; setiap sel berisi lampu yang menyala (1)
atau padam (0).
Satu operasi memilih SATU BARIS atau SATU KOLOM, lalu membalik keadaan
SELURUH lampu di baris atau kolom itu.
Diberikan keadaan awal dan keadaan target, tentukan apakah target bisa
dicapai. Cetak "YA" atau "TIDAK".

📥 INPUT FORMAT:
- Baris pertama: N dan M
- N baris berikutnya: keadaan awal, masing-masing string sepanjang M
- N baris berikutnya: keadaan target, masing-masing string sepanjang M

📤 OUTPUT FORMAT:
- "YA" atau "TIDAK"

📏 CONSTRAINTS:
- 1 <= N, M <= 1000

📎 SAMPLE INPUT 1:
2 2
00
00
11
11

📎 SAMPLE OUTPUT 1:
YA

📎 SAMPLE INPUT 2:
2 2
00
00
10
00

📎 SAMPLE OUTPUT 2:
TIDAK

📎 SAMPLE INPUT 3:
2 3
000
000
110
110

📎 SAMPLE OUTPUT 3:
YA

💡 HINT: Mulailah dengan menyederhanakan. Alih-alih memikirkan keadaan awal
         dan target secara terpisah, lihat SELISIH keduanya: sel mana saja
         yang harus dibalik. Sekarang pertanyaannya menjadi "bisakah pola
         selisih ini dihasilkan oleh operasi baris dan kolom?"
         Selanjutnya, perhatikan bahwa membalik baris yang sama DUA KALI
         sama saja dengan tidak melakukan apa-apa. Jadi yang penting
         hanyalah, untuk tiap baris dan tiap kolom, apakah ia dibalik dengan
         jumlah GANJIL atau GENAP.
         Sebut r[i] bernilai 1 kalau baris i dibalik ganjil kali, dan c[j]
         serupa untuk kolom. Tuliskan rumus untuk keadaan akhir sel (i, j)
         dalam r[i] dan c[j].
         Dari rumus itu, kamu bisa menurunkan hubungan yang HARUS berlaku di
         antara empat sel mana pun yang membentuk persegi panjang. Tuliskan
         hubungan itu — ia adalah invariannya.
         Cara paling praktis memakainya: tetapkan salah satu nilai (misalnya
         r[0] sama dengan 0), lalu seluruh nilai lain menjadi tertentu.
         Setelah itu periksa apakah seluruh sel konsisten.
         Sampel 2 gagal karena membalik satu sel saja mustahil: setiap
         operasi membalik seluruh baris atau seluruh kolom.
         Kasus tepi: N atau M sama dengan 1.

🎯 Learning Goals:
- [ ] Menyederhanakan soal menjadi selisih awal dan target
- [ ] Menyadari bahwa hanya paritas jumlah operasi yang penting
- [ ] Menurunkan invarian berbentuk hubungan antar empat sel
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung selisih awal dan target

    // TODO: tetapkan r[0], turunkan sisanya, periksa konsistensi

    return 0;
}
