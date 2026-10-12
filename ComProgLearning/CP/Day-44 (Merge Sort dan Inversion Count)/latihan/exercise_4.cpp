/*
============================================================
🏋️ Exercise 4: Pertukaran Berdampingan Minimum
============================================================
Day: 44 | Difficulty: Medium
Topic: Inversi sebagai jawaban soal yang berbeda
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah barisan N kereta berjajar di rel, masing-masing punya nomor yang
berbeda-beda. Kamu hanya boleh melakukan satu jenis operasi: MENUKAR DUA
KERETA YANG BERDAMPINGAN.
Cari jumlah operasi MINIMUM yang dibutuhkan untuk membuat barisan kereta
terurut menaik berdasarkan nomornya.

📥 INPUT FORMAT:
- Baris pertama: T (banyaknya kasus uji)
- Setiap kasus: baris berisi N, lalu baris berisi N bilangan

📤 OUTPUT FORMAT:
- T baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= T <= 10
- 1 <= N <= 10^5
- Nilai bisa sampai 10^9 dan tidak dijamin berupa permutasi

📎 SAMPLE INPUT 1:
2
5
3 1 2 5 4
3
1 2 3

📎 SAMPLE OUTPUT 1:
3
0

💡 HINT: Soal ini terlihat berbeda dari Exercise 3, tetapi jawabannya
         adalah besaran yang sama persis. Pikirkan: satu pertukaran
         berdampingan mengubah status BERAPA pasangan?
         Kalau kamu bisa menjawab itu, kamu bisa membuktikan bahwa
         jawabannya tidak mungkin lebih kecil dari suatu angka tertentu —
         dan bahwa angka itu selalu tercapai.

🎯 Learning Goals:
- [ ] Mengenali inversi di balik deskripsi soal yang berbeda
- [ ] Bisa berargumen kenapa itu MINIMUM, bukan sekadar mungkin
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: untuk tiap kasus, hitung inversi

    return 0;
}
