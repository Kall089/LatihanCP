/*
============================================================
🏋️ Exercise 6: Menyeberangi Padang Pasir
============================================================
Day: 52 | Difficulty: Hard (Contest-level)
Topic: Ternary search pada titik pergantian moda
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu berada di titik A = (0, 0) dan ingin mencapai titik B = (bx, by)
dengan by > 0.
Daerah dengan koordinat y <= 0 adalah jalan aspal di mana kamu bisa bergerak
dengan kecepatan v1 satuan per detik. Daerah dengan y > 0 adalah padang
pasir di mana kecepatanmu hanya v2 satuan per detik (dijamin v2 <= v1).
Titik B berada di padang pasir. Kamu harus bergerak lurus di aspal sampai
suatu titik (p, 0) di garis pembatas, lalu bergerak lurus dari sana ke B.
Cari WAKTU TEMPUH MINIMUM. Cetak dengan 9 desimal.

📥 INPUT FORMAT:
- Satu baris berisi bx, by, v1, dan v2

📤 OUTPUT FORMAT:
- Satu bilangan real dengan 9 desimal

📏 CONSTRAINTS:
- -10^4 <= bx <= 10^4
- 1 <= by <= 10^4
- 1 <= v2 <= v1 <= 10^4

📎 SAMPLE INPUT 1:
0 10 1 1

📎 SAMPLE OUTPUT 1:
10.000000000

📎 SAMPLE INPUT 2:
10 10 2 1

📎 SAMPLE OUTPUT 2:
13.660254038

💡 HINT: Waktu tempuh sebagai fungsi dari p (titik penyeberangan) adalah
         jumlah dua akar kuadrat. Fungsi seperti itu CEMBUNG, sehingga
         unimodal — ternary search berlaku.
         Yang harus kamu putuskan sendiri adalah RENTANG PENCARIAN untuk p.
         Pikirkan: apakah masuk akal menyeberang di titik yang lebih jauh
         dari bx? Apakah masuk akal menyeberang di titik dengan tanda yang
         berlawanan dari bx? Tetapi berhati-hatilah — memasang rentang yang
         terlalu sempit akan memotong jawaban, sedangkan yang terlalu lebar
         hanya menambah satu-dua iterasi. Pilih yang aman.
         Perhatikan sampel 1: karena v1 sama dengan v2, tidak ada
         keuntungan menyeberang di tempat lain selain langsung menuju B,
         sehingga jawabannya persis jarak lurus. Pakai kasus itu untuk
         memverifikasi implementasimu sebelum mencoba sampel 2.

🎯 Learning Goals:
- [ ] Menyusun fungsi waktu tempuh dari geometri
- [ ] Menentukan rentang pencarian yang aman
- [ ] Menerapkan ternary search pada soal fisik/geometris
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: waktu(p) = |p| / v1 + jarak((p,0), B) / v2

    // TODO: tentukan rentang pencarian p yang cukup lebar

    return 0;
}
