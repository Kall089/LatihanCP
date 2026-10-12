/*
============================================================
🏋️ Exercise 6: Pulau Setelah Setiap Penambahan
============================================================
Day: 134 | Difficulty: Hard (Contest-level)
Topic: DSU pada grid
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah peta berupa grid berukuran R baris dan C kolom yang mula-mula
seluruhnya berupa laut.
Terjadi T operasi. Operasi ke-t mengubah sel pada baris r dan kolom c
menjadi DARATAN. Sebuah sel yang sudah menjadi daratan bisa saja diubah
lagi (dan operasi itu tidak mengubah apa pun).
Sebuah PULAU adalah kumpulan sel daratan yang saling terhubung secara
horizontal atau vertikal (empat arah, bukan diagonal).
Setelah setiap operasi, cetak berapa banyak pulau yang ada saat itu.

📥 INPUT FORMAT:
- Baris pertama: R, C, dan T
- T baris berikutnya: masing-masing r dan c (1-based)

📤 OUTPUT FORMAT:
- T baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= R, C <= 500
- R * C <= 2 * 10^5
- 1 <= T <= 2 * 10^5

📎 SAMPLE INPUT 1:
3 3 4
1 1
1 2
2 2
3 3

📎 SAMPLE OUTPUT 1:
1
1
1
2

📎 SAMPLE OUTPUT — penjelasan:
Setelah operasi 1: satu daratan, satu pulau.
Setelah operasi 2: dua daratan bersebelahan, tetap satu pulau.
Setelah operasi 3: (2,2) bersebelahan dengan (1,2), tetap satu pulau.
Setelah operasi 4: (3,3) terpisah, jadi dua pulau.

💡 HINT: Menjalankan pencarian menyeluruh pada grid setelah setiap operasi
         akan terlalu lambat. Sebaliknya, jaga hitungan pulau secara
         inkremental.
         Saat sebuah sel baru menjadi daratan, hitungan pulau bertambah satu
         — lalu untuk setiap tetangganya yang SUDAH menjadi daratan dan
         belum berada di pulau yang sama, penggabungan mengurangi hitungan
         itu satu.
         Dua hal yang mudah salah: memeriksa tetangga yang berada di LUAR
         grid, dan menggabungkan dengan tetangga yang masih berupa laut.
         Perhatikan juga bahwa operasi pada sel yang SUDAH daratan tidak
         boleh mengubah hitungan sama sekali.
         Untuk memetakan koordinat dua dimensi menjadi indeks tunggal,
         pikirkan rumus yang menjamin setiap sel mendapat indeks berbeda.

🎯 Learning Goals:
- [ ] Memetakan grid menjadi indeks tunggal untuk DSU
- [ ] Menjaga hitungan komponen secara inkremental pada grid
- [ ] Menangani batas grid dan operasi berulang dengan benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: idx(r, c) untuk memetakan koordinat jadi indeks tunggal

    // TODO: saat sel baru jadi daratan: pulau++, lalu gabungkan dengan
    //       tetangga yang SUDAH daratan (pulau-- tiap penggabungan berhasil)

    // TODO: operasi pada sel yang sudah daratan tidak mengubah apa pun

    return 0;
}
