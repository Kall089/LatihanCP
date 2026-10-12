/*
============================================================
🏋️ Exercise 4: Potongan Palindrom Minimal
============================================================
Day: 216 | Difficulty: Medium
Topic: Manacher + DP partisi
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S, bagi S menjadi beberapa potongan berurutan yang
tidak kosong, sedemikian sehingga SETIAP potongan merupakan palindrom.
Cari banyaknya potongan MINIMAL yang diperlukan.
Perhatikan bahwa jawaban selalu ada: paling buruk, setiap huruf menjadi
satu potongan sendiri (huruf tunggal selalu palindrom).

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah potongan minimal

📏 CONSTRAINTS:
- 1 <= |S| <= 5000

📎 SAMPLE INPUT 1:
abacaba

📎 SAMPLE OUTPUT 1:
1

📎 SAMPLE INPUT 2:
abcd

📎 SAMPLE OUTPUT 2:
4

📎 SAMPLE INPUT 3:
aabbaacd

📎 SAMPLE OUTPUT 3:
3

Penjelasan: "aabbaa" + "c" + "d" -> 3 potongan.

💡 HINT: dp[i] = potongan minimal untuk membagi S[0..i-1]. Transisinya
         memerlukan pengecekan "apakah S[j..i-1] palindrom" — yang jadi
         O(1) berkat Manacher. Tanpa itu, DP-nya jadi O(N^3).

🎯 Learning Goals:
- [ ] Memakai Manacher sebagai ORACLE untuk DP, bukan sebagai jawaban akhir
- [ ] Memahami mengapa cek O(1) menurunkan O(N^3) jadi O(N^2)
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

    // TODO: preprocessing Manacher untuk cek O(1)

    // TODO: dp[0] = 0; untuk i = 1..n, coba semua j < i
    //       kalau S[j..i-1] palindrom, dp[i] = min(dp[i], dp[j] + 1)

    return 0;
}
