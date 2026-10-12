/*
============================================================
🏋️ Exercise 2: Frekuensi Nilai Besar
============================================================
Day: 38 | Difficulty: Easy
Topic: Kompresi sebagai jembatan ke array frekuensi
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dengan nilai hingga 10^9, dan Q
pertanyaan. Setiap pertanyaan berisi satu bilangan x, dan kamu harus
menjawab berapa kali x muncul di dalam array.
Perhatikan bahwa membuat array frekuensi berukuran 10^9 mustahil, tetapi
paling banyak hanya ada N nilai berbeda yang benar-benar muncul.
Nilai yang ditanyakan boleh saja TIDAK ADA di dalam array — dalam hal itu
jawabannya 0.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: masing-masing satu bilangan x

📤 OUTPUT FORMAT:
- Q baris berisi bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- -10^9 <= a[i], x <= 10^9

📎 SAMPLE INPUT 1:
5 3
4 4 9 1 9
4
9
100

📎 SAMPLE OUTPUT 1:
2
2
0

💡 HINT: Setelah kompresi, buat array hitungan berukuran "banyak nilai
         berbeda". Untuk menjawab pertanyaan, cari posisi x — tetapi
         hati-hati: kalau x tidak ada di kamus, pencarian biner akan
         mengembalikan posisi TEMPAT x SEHARUSNYA disisipkan, bukan
         posisi x. Kamu harus memeriksanya.

🎯 Learning Goals:
- [ ] Menggabungkan kompresi dengan array frekuensi
- [ ] Menangani query yang nilainya tidak ada di kamus
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kompres array, bangun array frekuensi

    // TODO: untuk tiap query, cari posisi lalu VERIFIKASI nilainya cocok

    return 0;
}
