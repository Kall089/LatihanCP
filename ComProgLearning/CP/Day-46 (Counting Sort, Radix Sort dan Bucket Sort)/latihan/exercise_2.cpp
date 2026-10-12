/*
============================================================
🏋️ Exercise 2: Counting Sort yang Stabil
============================================================
Day: 46 | Difficulty: Easy
Topic: Prefix sum + penempatan mundur
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N barang, barang ke-i punya KODE berupa bilangan bulat antara
0 dan 1000, serta NAMA berupa satu huruf kecil.
Urutkan barang-barang itu berdasarkan kode secara menaik. Barang dengan
kode yang SAMA harus tetap dalam urutan seperti pada input.
Cetak nama-nama barang setelah diurutkan, sebagai satu string tanpa spasi.
Kamu harus menyelesaikannya dengan counting sort, bukan dengan sort bawaan.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: masing-masing kode dan satu huruf

📤 OUTPUT FORMAT:
- Satu baris berisi N huruf

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= kode <= 1000

📎 SAMPLE INPUT 1:
5
3 a
1 b
3 c
2 d
1 e

📎 SAMPLE OUTPUT 1:
bedac

📎 SAMPLE INPUT 2:
3
7 x
7 y
7 z

📎 SAMPLE OUTPUT 2:
xyz

💡 HINT: Counting sort versi "cetak berulang" seperti Exercise 1 tidak bisa
         dipakai di sini, karena setiap barang membawa data lain yang harus
         ikut berpindah.
         Ubah array frekuensi menjadi prefix sum, lalu tempatkan setiap
         barang ke posisi finalnya. Arah penyapuan pada langkah penempatan
         menentukan apakah hasilnya stabil atau tidak — coba kedua arah
         pada sampel 1 dan lihat bedanya.

🎯 Learning Goals:
- [ ] Menulis counting sort tiga langkah yang benar
- [ ] Memahami kenapa penyapuan MUNDUR menghasilkan stabilitas
- [ ] Menangani elemen yang membawa data terkait
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung frekuensi kode

    // TODO: ubah menjadi prefix sum

    // TODO: tempatkan, perhatikan ARAH penyapuan

    return 0;
}
