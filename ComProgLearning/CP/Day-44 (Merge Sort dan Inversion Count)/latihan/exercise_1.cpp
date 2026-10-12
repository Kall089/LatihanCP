/*
============================================================
🏋️ Exercise 1: Gabungkan Dua Array Terurut
============================================================
Day: 44 | Difficulty: Easy
Topic: Langkah merge
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan dua array yang MASING-MASING sudah terurut menaik: array A berisi
N elemen dan array B berisi M elemen. Gabungkan keduanya menjadi satu array
terurut menaik yang berisi seluruh N+M elemen.
Elemen yang nilainya sama boleh muncul beberapa kali dan semuanya harus
ikut tercetak. Kamu tidak boleh memakai fungsi pengurutan apa pun —
manfaatkan bahwa kedua array sudah terurut.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: N bilangan array A
- Baris ketiga: M bilangan array B

📤 OUTPUT FORMAT:
- Satu baris berisi N+M bilangan terurut menaik

📏 CONSTRAINTS:
- 1 <= N, M <= 2 * 10^5
- -10^9 <= nilai <= 10^9

📎 SAMPLE INPUT 1:
3 3
2 4 5
1 3 6

📎 SAMPLE OUTPUT 1:
1 2 3 4 5 6

📎 SAMPLE INPUT 2:
2 3
1 1
1 1 1

📎 SAMPLE OUTPUT 2:
1 1 1 1 1

💡 HINT: Gunakan dua penunjuk, satu untuk masing-masing array. Ambil yang
         lebih kecil dan majukan penunjuknya. Jangan lupa menyalin SISA
         array yang belum habis setelah salah satunya kehabisan.
         Kalau nanti kamu memakai ini untuk data berpasangan, perhatikan
         apa yang harus diambil saat nilainya SERI.

🎯 Learning Goals:
- [ ] Menulis langkah merge dengan benar, termasuk penanganan sisa
- [ ] Menyadari peran perbandingan saat nilai seri
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca kedua array

    // TODO: dua penunjuk, ambil yang lebih kecil

    // TODO: salin sisa yang belum habis

    return 0;
}
