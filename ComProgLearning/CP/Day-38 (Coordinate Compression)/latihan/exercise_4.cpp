/*
============================================================
🏋️ Exercise 4: Total Panjang Tertutup
============================================================
Day: 38 | Difficulty: Medium
Topic: Sweep line pada interval koordinat besar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N interval bilangan bulat [l, r] (inklusif di kedua ujung).
Interval boleh saling tumpang tindih. Hitung BERAPA BANYAK bilangan bulat
berbeda yang tertutup oleh setidaknya satu interval.
Sebagai contoh, [1,3] dan [2,5] bersama-sama menutupi bilangan
1, 2, 3, 4, 5 — sebanyak 5 bilangan, bukan 3 + 4 = 7.
Perhatikan bahwa koordinatnya bisa mencapai 10^9, jadi kamu tidak bisa
menandai satu per satu.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: masing-masing l dan r

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= l <= r <= 10^9

📎 SAMPLE INPUT 1:
3
1 3
2 5
8 9

📎 SAMPLE OUTPUT 1:
7

📎 SAMPLE INPUT 2:
2
1 5
6 9

📎 SAMPLE OUTPUT 2:
9

💡 HINT: Soal ini sebenarnya TIDAK membutuhkan kompresi koordinat sama
         sekali — cukup mengurutkan interval lalu menyapu dari kiri sambil
         mengingat sampai mana yang sudah tertutup.
         Ini pengingat penting: nilai besar tidak otomatis berarti butuh
         kompresi. Kompresi diperlukan hanya kalau kamu butuh ARRAY yang
         diindeks oleh nilai.
         Perhatikan sampel 2: [1,5] dan [6,9] bersambung tanpa celah.

🎯 Learning Goals:
- [ ] Sweep line dasar pada interval
- [ ] Menyadari kapan kompresi TIDAK diperlukan
- [ ] Menangani interval yang bersambung persis
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca interval, urutkan

    // TODO: sapu sambil menjaga variabel "sudah tertutup sampai mana"

    return 0;
}
