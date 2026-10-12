/*
============================================================
🏋️ Exercise 1: Blok Terkecil (Kompresi String)
============================================================
Day: 214 | Difficulty: Easy
Topic: Periode terkecil dari prefix function
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah string S dikatakan "hasil pengulangan utuh" dari blok B jika S dapat
dibentuk dengan menyalin B sebanyak k kali berturut-turut (k >= 1).
Contohnya "abcabcabc" adalah pengulangan utuh dari "abc" sebanyak 3 kali.
Tugasmu: temukan panjang blok B TERPENDEK sedemikian sehingga S adalah
pengulangan utuh dari B. Perhatikan bahwa jawabannya selalu ada, karena
paling buruk B = S itu sendiri (diulang 1 kali).

📥 INPUT FORMAT:
- Satu baris berisi string S (hanya huruf kecil 'a'..'z')

📤 OUTPUT FORMAT:
- Satu bilangan: panjang blok terpendek

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6

📎 SAMPLE INPUT 1:
abcabcabc

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
abcabca

📎 SAMPLE OUTPUT 2:
7

📎 SAMPLE INPUT 3:
aaaa

📎 SAMPLE OUTPUT 3:
1

💡 HINT: Periode terkecil = n - pi[n-1]. Tapi periode belum tentu membagi n.
         Sampel 2 ada di sini justru untuk menjebakmu.

🎯 Learning Goals:
- [ ] Menurunkan periode terkecil dari pi
- [ ] Ingat bahwa keterbagian n % k == 0 adalah syarat terpisah
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: tulis fungsi bangunPi di sini

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // TODO: hitung pi, ambil k = n - pi[n-1]

    // TODO: kalau n % k != 0, jawabannya bukan k. Apa jawabannya?

    // TODO: cetak hasil

    return 0;
}
