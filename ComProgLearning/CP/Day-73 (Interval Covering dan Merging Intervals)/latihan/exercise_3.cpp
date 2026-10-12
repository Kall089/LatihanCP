/*
============================================================
🏋️ Exercise 3: Menyiram Taman
============================================================
Day: 73 | Difficulty: Medium
Topic: Interval covering
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah taman berbentuk garis lurus dari posisi 0 sampai posisi T.
Ada N alat penyiram; alat ke-i mampu menyiram seluruh rentang [l[i], r[i]].
Kamu ingin menyalakan alat SESEDIKIT MUNGKIN sehingga SELURUH taman dari 0
sampai T tersiram tanpa ada bagian yang terlewat.
Cetak jumlah alat minimum, atau -1 kalau tidak mungkin.

📥 INPUT FORMAT:
- Baris pertama: N dan T
- N baris berikutnya: l[i] dan r[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah alat minimum, atau -1

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= T <= 10^9
- 0 <= l[i] <= r[i] <= 10^9

📎 SAMPLE INPUT 1:
4 12
0 3
2 6
5 9
8 12

📎 SAMPLE OUTPUT 1:
4

📎 SAMPLE INPUT 2:
3 10
0 5
4 10
0 2

📎 SAMPLE OUTPUT 2:
2

📎 SAMPLE INPUT 3:
2 10
0 3
5 10

📎 SAMPLE OUTPUT 3:
-1

💡 HINT: Ini pola BARU, bukan varian Exercise 1 dan bukan varian Day 72.
         Bayangkan sebuah penanda 'sampai' yang menyatakan seberapa jauh
         taman sudah tersiram. Awalnya 0.
         Alat mana saja yang boleh kamu pertimbangkan sekarang? Jawabannya:
         semua alat yang jangkauan kirinya tidak melewati 'sampai' — kalau
         l lebih besar dari 'sampai', memakainya akan menyisakan lubang.
         Di antara alat-alat yang boleh, mana yang kamu pilih? Ada godaan
         mengambil yang pertama ditemukan. Uji ide itu pada sampel 2
         sebelum mempercayainya.
         Sampel 3 mengingatkanmu bahwa jawabannya bisa tidak ada. Pastikan
         kodemu berhenti alih-alih berputar selamanya.
         Terakhir: kalau kamu me-reset penunjuk pencarian di setiap putaran,
         kompleksitasnya menjadi N kuadrat. Pikirkan kenapa penunjuk itu
         sebenarnya tidak perlu mundur.

🎯 Learning Goals:
- [ ] Menguasai greedy jangkauan terjauh
- [ ] Menangani kasus tidak mungkin dengan benar
- [ ] Menyadari bahwa penunjuk yang monoton membuat algoritmanya linear
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan

    // TODO: dorong 'sampai' sejauh mungkin pada tiap langkah

    // TODO: deteksi kasus tidak mungkin

    return 0;
}
