/*
============================================================
🏋️ Exercise 2: Puncak Gunung
============================================================
Day: 52 | Difficulty: Easy
Topic: Binary search pada selisih (domain integer)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan yang membentuk "gunung": nilainya naik
secara ketat sampai suatu titik puncak, lalu turun secara ketat sampai
akhir. Dijamin tidak ada dua elemen bersebelahan yang nilainya sama, dan
puncaknya tidak berada di ujung array.
Cari INDEKS puncaknya (0-based).
Kompleksitas yang diharapkan O(log N) — jadi menyapu seluruh array tidak
diterima.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: indeks puncak

📏 CONSTRAINTS:
- 3 <= N <= 10^6
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
7
1 4 7 9 8 5 2

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
3
1 5 2

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Meski soal ini terlihat seperti kasus ternary search, ada
         pendekatan yang LEBIH BAIK untuk domain integer.
         Perhatikan selisih antar elemen bersebelahan: a[i+1] - a[i].
         Di daerah menanjak selisihnya positif, di daerah menurun negatif.
         Bagaimana pola positif-lalu-negatif itu bisa kamu manfaatkan?
         Kalau kamu menyadarinya, kamu bisa memakai kerangka yang sudah kamu
         kuasai dari Day 49 — lebih sedikit iterasi dan tanpa kasus tepi
         yang merepotkan.

🎯 Learning Goals:
- [ ] Melihat bahwa unimodal dapat diubah menjadi monoton lewat selisih
- [ ] Memakai kerangka first-true (Day 49) pada masalah yang tampak berbeda
- [ ] Menyadari kenapa ini lebih baik daripada ternary search integer
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: predikatnya "masih menanjak di mid", yaitu a[mid] < a[mid+1]

    // TODO: kerangka first-true dari Day 49

    return 0;
}
