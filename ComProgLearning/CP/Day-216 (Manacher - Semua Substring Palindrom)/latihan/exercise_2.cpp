/*
============================================================
🏋️ Exercise 2: Hitung Substring Palindrom
============================================================
Day: 216 | Difficulty: Easy
Topic: Menjumlahkan radius
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S, hitung berapa banyak PASANGAN (l, r) dengan l <= r
sedemikian sehingga substring S[l..r] merupakan palindrom.
Perhatikan bahwa yang dihitung adalah KEMUNCULAN, bukan palindrom berbeda:
pada string "aaa", jawabannya 6 (tiga huruf tunggal, dua "aa", satu "aaa"),
bukan 3.
Substring sepanjang 1 selalu dihitung sebagai palindrom.

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- Satu bilangan: total kemunculan substring palindrom

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- Jawaban bisa mencapai ~5 * 10^11

📎 SAMPLE INPUT 1:
aaa

📎 SAMPLE OUTPUT 1:
6

📎 SAMPLE INPUT 2:
abba

📎 SAMPLE OUTPUT 2:
6

📎 SAMPLE INPUT 3:
abcd

📎 SAMPLE OUTPUT 3:
4

💡 HINT: Palindrom berpusat di i dengan radius p[i] juga memuat palindrom
         yang lebih pendek dengan pusat yang sama: panjang p[i], p[i]-2,
         p[i]-4, ... Berapa banyak suku dalam deret itu?
         Dan jangan pakai int untuk totalnya.

🎯 Learning Goals:
- [ ] Menurunkan rumus (p[i] + 1) / 2 sendiri
- [ ] Sadar bahwa kemunculan != palindrom berbeda
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // TODO: jalankan Manacher

    // TODO: jumlahkan berapa palindrom yang berpusat di setiap i

    // TODO: cetak (pakai long long!)

    return 0;
}
