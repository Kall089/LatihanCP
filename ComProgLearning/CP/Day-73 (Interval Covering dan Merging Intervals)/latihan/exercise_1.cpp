/*
============================================================
🏋️ Exercise 1: Menggabungkan Rentang
============================================================
Day: 73 | Difficulty: Easy
Topic: Merge intervals
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N rentang [l, r]. Gabungkan semua rentang yang beririsan atau
bersentuhan menjadi rentang-rentang yang saling terpisah.
Cetak hasilnya terurut menaik menurut ujung kirinya.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: l dan r

📤 OUTPUT FORMAT:
- Baris pertama: banyaknya rentang hasil
- Baris berikutnya: masing-masing satu rentang, l dan r dipisah spasi

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= l <= r <= 10^9

📎 SAMPLE INPUT 1:
4
1 3
2 6
8 10
15 18

📎 SAMPLE OUTPUT 1:
3
1 6
8 10
15 18

📎 SAMPLE INPUT 2:
2
1 10
2 3

📎 SAMPLE OUTPUT 2:
1
1 10

💡 HINT: Day 72 mengajarkan "interval selalu urut menurut ujung kanan".
         Untuk soal ini aturan itu TIDAK berlaku. Coba dulu kedua cara
         mengurutkan pada sampel 1 dan lihat mana yang membuat algoritmanya
         masuk akal.
         Setelah diurutkan dengan benar, kamu hanya perlu membandingkan
         rentang baru dengan SATU rentang saja. Rentang yang mana, dan
         kenapa cukup satu?
         Sampel 2 sangat penting. Ia memuat rentang yang TERMUAT PENUH di
         dalam rentang sebelumnya. Kesalahan paling umum pada soal ini
         hanya muncul pada kasus seperti ini — kalau kodemu memberi output
         "1 3" untuk sampel 2, kamu baru saja menemukan bugnya sendiri.

🎯 Learning Goals:
- [ ] Menyadari bahwa kriteria pengurutan bergantung pada pertanyaan
- [ ] Memahami invarian yang membuat pemeriksaan satu rentang cukup
- [ ] Menangani rentang yang termuat penuh
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan menurut kriteria yang tepat

    // TODO: sapu; perhatikan baik-baik cara memperbarui ujung kanan

    return 0;
}
