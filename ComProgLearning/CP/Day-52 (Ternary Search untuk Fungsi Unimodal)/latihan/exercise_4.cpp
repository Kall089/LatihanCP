/*
============================================================
🏋️ Exercise 4: Biaya Perjalanan Optimal
============================================================
Day: 52 | Difficulty: Medium
Topic: Ternary search integer
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu berada di lantai 0 sebuah gedung dan ingin mencapai lantai N.
Ada dua cara berpindah:
- Naik tangga satu lantai membutuhkan waktu A detik per lantai.
- Naik lift: kamu harus menunggu B detik terlebih dahulu, lalu lift membawa
  kamu naik dengan waktu C detik per lantai.
Kamu boleh naik tangga sampai lantai k terlebih dahulu (untuk k mana pun
dari 0 sampai N), lalu melanjutkan dengan lift sampai lantai N.
Cari waktu tempuh MINIMUM. Perhatikan bahwa waktu tunggu lift tetap harus
dibayar meskipun kamu hanya naik lift nol lantai — kecuali kamu memang tidak
memakai lift sama sekali (yaitu k = N).

📥 INPUT FORMAT:
- Satu baris berisi N, A, B, dan C

📤 OUTPUT FORMAT:
- Satu bilangan bulat: waktu minimum

📏 CONSTRAINTS:
- 1 <= N <= 10^12
- 1 <= A, B, C <= 10^9

📎 SAMPLE INPUT 1:
100 10 100 1

📎 SAMPLE OUTPUT 1:
200

Penjelasan: naik tangga seluruhnya butuh 100 * 10 = 1000 detik.
Langsung naik lift butuh 100 (menunggu) + 100 * 1 = 200 detik.
Jadi lift jauh lebih cepat.

📎 SAMPLE INPUT 2:
5 1 100 1

📎 SAMPLE OUTPUT 2:
5

Penjelasan: naik tangga seluruhnya butuh 5 * 1 = 5 detik, sedangkan lift
butuh 100 + 5 = 105 detik. Di sini tangga yang menang.

💡 HINT: Tuliskan biaya sebagai fungsi dari k (berapa lantai yang ditempuh
         dengan tangga). Fungsi itu berbentuk gabungan dua bagian linear,
         yang membuatnya CEMBUNG — dan karenanya unimodal.
         Karena N bisa mencapai 10^12, menyapu seluruh k mustahil.
         Kamu bisa memakai ternary search integer, TETAPI perhatikan bahwa
         fungsi ini punya DATARAN kalau A tepat sama dengan C — dan ternary
         search tidak dijamin benar pada dataran. Pikirkan cara mengatasinya.
         (Petunjuk tambahan: soal ini sebenarnya bisa diselesaikan tanpa
         pencarian sama sekali, hanya dengan membandingkan dua kandidat.
         Coba temukan kandidat mana saja itu.)

🎯 Learning Goals:
- [ ] Menyusun fungsi biaya dan membuktikan kecembungannya
- [ ] Menyadari bahaya dataran pada ternary search
- [ ] Melihat bahwa fungsi linear per bagian sering punya solusi langsung
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: biaya(k) = k*A + (k < N ? B + (N-k)*C : 0)

    // TODO: perhatikan overflow: N sampai 10^12 dikali A sampai 10^9

    return 0;
}
