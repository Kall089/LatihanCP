/*
============================================================
🏋️ Exercise 6: Membalik Tanda
============================================================
Day: 80 | Difficulty: Hard (Contest-level)
Topic: Menggabungkan invarian, paritas, dan konstruksi
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat (boleh negatif). Kamu harus
melakukan TEPAT K operasi. Satu operasi memilih sebuah elemen dan mengubah
tandanya (dari x menjadi -x).
Sebuah elemen boleh dipilih berkali-kali.
Cari JUMLAH SELURUH ELEMEN yang paling besar setelah tepat K operasi.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= K <= 10^9
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
3 1
4 2 3

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
3 2
4 2 3

📎 SAMPLE OUTPUT 2:
9

📎 SAMPLE INPUT 3:
4 3
-1 -2 -3 4

📎 SAMPLE OUTPUT 3:
10

💡 HINT: Perhatikan kata TEPAT K. Kamu tidak boleh berhenti lebih awal, dan
         itulah seluruh kesulitan soal ini.
         Mulailah dengan bagian yang mudah: selama masih ada bilangan
         NEGATIF dan masih ada operasi tersisa, apa yang jelas menguntungkan
         untuk dilakukan? Dan negatif yang mana yang kamu pilih dulu?
         Setelah tahap itu selesai, ada dua kemungkinan. Salah satunya
         mudah. Yang satunya adalah inti soal ini: operasi masih tersisa
         padahal semua bilangan sudah tidak negatif.
         Di situ, pikirkan tentang PARITAS sisa operasimu. Kalau sisanya
         genap, apa yang bisa kamu lakukan tanpa merugikan sama sekali?
         Kalau ganjil, kamu terpaksa membalik satu bilangan non-negatif.
         Bilangan mana yang paling murah untuk dikorbankan?
         Sampel 1 dan 2 memakai data yang sama dengan K berbeda satu, dan
         jawabannya berbeda jauh. Hitung keduanya dengan tangan untuk
         melihat kenapa.
         Sampel 3 menguji apakah kamu memilih negatif dalam urutan yang
         benar.
         Waspadai nilai nol: kalau ada nol di dalam array, apakah paritas
         masih menjadi masalah?

🎯 Learning Goals:
- [ ] Memisahkan tahap yang jelas menguntungkan dari tahap sisa
- [ ] Memakai paritas untuk menangani operasi berlebih
- [ ] Menemukan elemen yang paling murah dikorbankan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tahap yang jelas menguntungkan

    // TODO: tangani sisa operasi lewat paritas

    return 0;
}
