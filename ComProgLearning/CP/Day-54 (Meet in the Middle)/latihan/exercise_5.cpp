/*
============================================================
🏋️ Exercise 5: Jumlah Subset Terdekat dengan Target
============================================================
Day: 54 | Difficulty: Hard
Topic: Meet in the middle + dua kandidat
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat (boleh negatif) dan sebuah target T.
Pilih sebuah subhimpunan (boleh kosong) sehingga SELISIH ABSOLUT antara
jumlah subhimpunan itu dan T menjadi SEKECIL MUNGKIN.
Cetak selisih absolut minimum tersebut.

📥 INPUT FORMAT:
- Baris pertama: N dan T
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: selisih absolut minimum

📏 CONSTRAINTS:
- 1 <= N <= 40
- -10^9 <= a[i] <= 10^9
- -10^12 <= T <= 10^12

📎 SAMPLE INPUT 1:
4 7
1 2 3 4

📎 SAMPLE OUTPUT 1:
0

📎 SAMPLE INPUT 2:
3 10
1 2 3

📎 SAMPLE OUTPUT 2:
4

📎 SAMPLE INPUT 3:
2 0
-5 5

📎 SAMPLE OUTPUT 3:
0

💡 HINT: Berbeda dari Exercise 2 dan 3, di sini kamu tidak mencari nilai
         yang tepat sama maupun yang terbesar di bawah batas — kamu mencari
         yang PALING DEKAT, dan itu bisa berada di atas MAUPUN di bawah.
         Setelah lower_bound memberimu posisi, kandidat terbaik ada di
         posisi itu atau tepat SEBELUMNYA. Periksa keduanya, dan jangan
         lupa memeriksa batas sebelum mengakses (pola yang sama dengan
         Day 49).
         Perhatikan bahwa nilainya boleh NEGATIF, sehingga menambahkan
         elemen tidak selalu memperbesar jumlah. Apakah itu mengganggu
         pendekatanmu? Pikirkan baik-baik — jawabannya tidak.

🎯 Learning Goals:
- [ ] Varian "terdekat" yang membutuhkan dua kandidat
- [ ] Memeriksa batas array sebelum mengakses
- [ ] Menyadari bahwa MITM tidak terganggu oleh nilai negatif
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: dua paruh, urutkan salah satunya

    // TODO: untuk tiap jumlah paruh lain, periksa DUA kandidat

    return 0;
}
