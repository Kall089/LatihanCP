/*
============================================================
🏋️ Exercise 2: Partisi Genap-Ganjil
============================================================
Day: 45 | Difficulty: Easy
Topic: Partisi Lomuto / std::partition
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat, susun ulang isinya sehingga
SEMUA bilangan genap berada di depan SEMUA bilangan ganjil.
Urutan di antara bilangan genap boleh sembarang, begitu pula di antara
bilangan ganjil. Kamu harus melakukannya IN-PLACE (tanpa array tambahan)
dan dalam satu kali sapuan O(N).
Cetak array hasilnya, lalu cetak berapa bilangan genap yang ada.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Baris pertama: N bilangan hasil penyusunan
- Baris kedua: banyaknya bilangan genap

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
6
1 2 3 4 5 6

📎 SAMPLE OUTPUT 1:
2 4 6 1 3 5
3

Catatan: baris pertama hanya SALAH SATU susunan yang benar — susunan lain
yang memenuhi syarat juga diterima. Baris kedua harus tepat 3.

💡 HINT: Ini adalah langkah PARTISI dari quicksort, hanya saja predikatnya
         bukan "lebih kecil dari pivot" melainkan "genap".
         Jaga satu penunjuk sebagai batas: semua yang di sebelah kirinya
         sudah dipastikan genap.
         Hati-hati: (-3) % 2 bernilai -1 di C++, bukan 1.

🎯 Learning Goals:
- [ ] Memahami partisi sebagai pola umum, bukan hanya bagian quicksort
- [ ] Menjaga invariant dengan satu penunjuk batas
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: satu penunjuk batas, satu penunjuk penjelajah

    // TODO: tukar saat menemukan yang memenuhi predikat

    return 0;
}
