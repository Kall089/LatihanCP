/*
============================================================
🏋️ Exercise 1: Bandingkan Dua Substring
============================================================
Day: 33 | Difficulty: Easy
Topic: Prefix hash + perbandingan O(1)
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah string S dan Q pertanyaan. Setiap pertanyaan berisi empat
bilangan a, b, c, d yang berarti: apakah potongan S[a..b] sama persis dengan
potongan S[c..d]?
Indeks dimulai dari 1 dan kedua ujungnya termasuk.

Menjawab setiap pertanyaan dengan membandingkan huruf satu per satu terlalu
lambat kalau potongannya panjang dan pertanyaannya banyak. Pakai prefix hash
supaya tiap pertanyaan dijawab dalam O(1).

📥 INPUT FORMAT:
- Baris pertama: string S
- Baris kedua: bilangan Q
- Q baris berikutnya: empat bilangan a, b, c, d

📤 OUTPUT FORMAT:
- Q baris: "SAMA" atau "BEDA" untuk tiap pertanyaan.

📏 CONSTRAINTS:
- 1 <= |S| <= 2 x 10^5
- 1 <= Q <= 2 x 10^5
- 1 <= a <= b <= |S|, 1 <= c <= d <= |S|
- S hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
abcabc
3
1 3 4 6
1 2 2 3
2 2 5 5

📎 SAMPLE OUTPUT 1:
SAMA
BEDA
SAMA

📎 SAMPLE INPUT 2:
aaaa
2
1 2 3 4
1 3 2 4

📎 SAMPLE OUTPUT 2:
SAMA
SAMA

💡 HINT:
- Bangun prefix hash sekali di awal: h[i+1] = h[i] + kode(s[i]) * p[i].
- Kalau panjang kedua potongan berbeda, langsung BEDA tanpa menghitung apa pun.
- Untuk membandingkan, samakan bobotnya dengan mengalikan silang:
  get(a,b) * p[c] == get(c,d) * p[a].
- Jangan memakai pembagian modular; perkalian silang jauh lebih aman.

🎯 Learning Goals:
- [ ] Membangun prefix hash dengan benar
- [ ] Membandingkan substring dalam O(1)
- [ ] Menyamakan bobot tanpa modular inverse
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
}