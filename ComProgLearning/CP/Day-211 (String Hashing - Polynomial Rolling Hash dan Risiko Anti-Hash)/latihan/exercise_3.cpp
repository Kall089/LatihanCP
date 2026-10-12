/*
============================================================
🏋️ Exercise 3: Palindrom Substring
============================================================
Day: 33 | Difficulty: Medium
Topic: Hash maju + hash mundur
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah string S dan Q pertanyaan. Setiap pertanyaan berisi dua
bilangan l dan r, dan menanyakan apakah potongan S[l..r] merupakan palindrom.
Indeks dimulai dari 1 dan kedua ujungnya termasuk.

Mengecek satu per satu butuh O(panjang) per pertanyaan. Dengan hash, tiap
pertanyaan bisa dijawab dalam O(1).

📥 INPUT FORMAT:
- Baris pertama: string S
- Baris kedua: bilangan Q
- Q baris berikutnya: dua bilangan l dan r

📤 OUTPUT FORMAT:
- Q baris: "YA" jika palindrom, "TIDAK" jika bukan.

📏 CONSTRAINTS:
- 1 <= |S| <= 2 x 10^5
- 1 <= Q <= 2 x 10^5
- 1 <= l <= r <= |S|

📎 SAMPLE INPUT 1:
abacaba
3
1 7
1 3
2 4

📎 SAMPLE OUTPUT 1:
YA
YA
TIDAK

📎 SAMPLE INPUT 2:
abba
2
1 4
1 2

📎 SAMPLE OUTPUT 2:
YA
TIDAK

💡 HINT:
- Bangun DUA prefix hash: satu untuk S, satu untuk S yang dibalik.
- Potongan S[l..r] adalah palindrom kalau hash-nya sama dengan hash potongan
  yang bersesuaian pada string terbalik.
- Pemetaan indeksnya: S[l..r] pada string terbalik menempati [n-1-r .. n-1-l].
- Perhatikan pemetaan ini baik-baik, di sinilah kesalahan paling sering terjadi.

🎯 Learning Goals:
- [ ] Memakai dua hash sekaligus
- [ ] Memetakan indeks ke string terbalik dengan benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca S, buat juga versi terbaliknya

    // TODO: Bangun prefix hash untuk keduanya

    // TODO: Untuk tiap pertanyaan, bandingkan hash maju dengan hash mundur

    return 0;
}
