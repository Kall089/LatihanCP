/*
============================================================
🏋️ Exercise 3: Counting Sort dengan Nilai Negatif
============================================================
Day: 46 | Difficulty: Medium
Topic: Offset
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat yang nilainya berada di antara
-10^6 dan 10^6 (boleh negatif). Urutkan array itu menaik menggunakan
counting sort.
Perhatikan bahwa indeks array tidak boleh negatif, sehingga kamu perlu
satu penyesuaian sebelum bisa memakai nilai sebagai indeks.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan terurut menaik

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- -10^6 <= a[i] <= 10^6

📎 SAMPLE INPUT 1:
5
3 -1 4 -1 5

📎 SAMPLE OUTPUT 1:
-1 -1 3 4 5

📎 SAMPLE INPUT 2:
3
-5 -5 -5

📎 SAMPLE OUTPUT 2:
-5 -5 -5

💡 HINT: Geser seluruh nilai sehingga yang terkecil menjadi nol, lakukan
         counting sort, lalu geser kembali.
         Ada dua pilihan untuk pergeserannya: memakai batas dari soal
         (-10^6), atau memakai nilai minimum yang benar-benar ada di array.
         Pilihan kedua lebih hemat memori — pikirkan seberapa besar bedanya
         untuk sampel 2.
         Peringatan: mengakses indeks negatif di C++ sering TIDAK
         menyebabkan crash, sehingga bugnya bisa lolos dari pengujianmu.

🎯 Learning Goals:
- [ ] Memakai offset untuk memetakan nilai negatif ke indeks yang sah
- [ ] Menyadari bahaya indeks negatif yang tidak crash
- [ ] Memilih ukuran array berdasarkan data, bukan hanya batas soal
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: cari nilai minimum dan maksimum yang benar-benar ada

    // TODO: counting sort pada nilai yang sudah digeser

    // TODO: geser kembali saat mencetak

    return 0;
}
