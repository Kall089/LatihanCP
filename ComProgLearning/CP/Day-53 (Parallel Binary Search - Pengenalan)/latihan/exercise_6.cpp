/*
============================================================
🏋️ Exercise 6: Kapan Jalur Aman Terbentuk
============================================================
Day: 53 | Difficulty: Hard (Contest-level)
Topic: Parallel binary search + DSU pada grid
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah pulau direpresentasikan sebagai grid berukuran R baris dan C kolom.
Mula-mula seluruh sel terendam air.
Selama T hari, setiap hari tepat satu sel muncul ke permukaan menjadi
daratan (sel yang sama tidak pernah muncul dua kali).
Ada Q pertanyaan. Pertanyaan ke-i berisi dua sel, dan kamu harus menjawab
pada HARI KEBERAPA kedua sel itu pertama kali dapat dihubungkan dengan
berjalan hanya melalui DARATAN, bergerak ke empat arah (atas, bawah, kiri,
kanan). Cetak -1 kalau tidak pernah bisa.
Dijamin kedua sel pada setiap pertanyaan pasti muncul sebagai daratan pada
suatu hari.

📥 INPUT FORMAT:
- Baris pertama: R, C, T, dan Q
- T baris berikutnya: baris dan kolom sel yang muncul pada hari itu
- Q baris berikutnya: r1, c1, r2, c2

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= R, C <= 500, dan R*C <= 2 * 10^5
- 1 <= T <= R*C
- 1 <= Q <= 2 * 10^5

📎 SAMPLE INPUT 1:
2 2 4 2
1 1
1 2
2 2
2 1
1 1 1 2
1 1 2 1

📎 SAMPLE OUTPUT 1:
2
4

💡 HINT: Gabungan dari Exercise 4 (DSU) dan penanganan grid.
         Ada satu detail penting: kedua sel yang ditanyakan harus SUDAH
         menjadi daratan sebelum mereka bisa terhubung. Jadi jawabannya
         tidak mungkin lebih awal dari hari kemunculan sel yang paling
         belakangan di antara keduanya.
         Saat menerapkan hari ke-t, jadikan sel itu daratan lalu gabungkan
         dengan tetangga yang SUDAH menjadi daratan. Perhatikan bahwa
         menggabungkan dengan sel yang belum muncul adalah bug yang mudah
         terjadi.
         Untuk memetakan sel (r, c) menjadi indeks tunggal, gunakan
         (r-1)*C + (c-1). Hati-hati dengan batas grid saat memeriksa
         tetangga.

🎯 Learning Goals:
- [ ] Menggabungkan DSU, grid, dan parallel binary search
- [ ] Menangani syarat tambahan (kedua sel harus sudah muncul)
- [ ] Memetakan koordinat dua dimensi menjadi indeks tunggal
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: catat hari kemunculan tiap sel

    // TODO: kerangka parallel binary search dengan DSU

    // TODO: saat sel muncul, gabungkan HANYA dengan tetangga yang sudah muncul

    return 0;
}
