/*
============================================================
🏋️ Exercise 4: Radix Sort
============================================================
Day: 46 | Difficulty: Medium
Topic: Radix sort LSD
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat NON-NEGATIF yang nilainya bisa
mencapai 10^9. Urutkan array itu menaik.
Perhatikan bahwa counting sort langsung tidak bisa dipakai: array frekuensi
sebesar 10^9 membutuhkan 4 GB memori. Kamu harus memecah setiap bilangan
menjadi beberapa bagian dan mengurutkannya bertahap.
Untuk latihan ini, tuliskan sendiri prosedurnya (jangan memakai sort bawaan).

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan terurut menaik

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- 0 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
8
170 45 75 90 802 24 2 66

📎 SAMPLE OUTPUT 1:
2 24 45 66 75 90 170 802

📎 SAMPLE INPUT 2:
3
1000000000 1 999999999

📎 SAMPLE OUTPUT 2:
1 999999999 1000000000

💡 HINT: Urutkan berdasarkan bagian yang PALING TIDAK signifikan lebih dulu,
         lalu naik bertahap ke bagian yang lebih signifikan.
         Ada satu sifat yang harus dimiliki prosedur pengurutan di setiap
         tahap, dan tanpa sifat itu seluruh hasilnya menjadi sampah. Coba
         jalankan dengan tangan pada array [21, 12, 11] memakai basis 10
         untuk menemukan sifat apa yang dimaksud.
         Untuk basis, pertimbangkan 256 (satu byte): pengambilan digitnya
         cukup dengan operasi geser dan AND, dan array hitungnya kecil
         sehingga muat di cache.

🎯 Learning Goals:
- [ ] Menulis radix sort LSD yang benar
- [ ] Menemukan sendiri kenapa stabilitas menjadi syarat mutlak
- [ ] Memilih basis dan menghitung berapa lewat yang dibutuhkan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: beberapa lewat, masing-masing counting sort STABIL pada satu digit

    // TODO: tukar array kerja dan array sementara, jangan menyalin

    return 0;
}
