/*
============================================================
🏋️ Exercise 2: Semua Border
============================================================
Day: 214 | Difficulty: Easy
Topic: Rantai prefix function
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Border sebuah string S adalah string non-kosong yang merupakan awalan
sekaligus akhiran dari S, tetapi bukan S itu sendiri. Sebagai contoh,
string "abacaba" punya border "a" (panjang 1) dan "aba" (panjang 3).
Cetak semua panjang border dari S, terurut MENAIK. Jika S tidak punya
border sama sekali, cetak baris kosong.

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- Satu baris berisi panjang-panjang border, dipisah spasi, urut menaik
- Baris kosong jika tidak ada border

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6

📎 SAMPLE INPUT 1:
abacaba

📎 SAMPLE OUTPUT 1:
1 3

📎 SAMPLE INPUT 2:
aaaaa

📎 SAMPLE OUTPUT 2:
1 2 3 4

📎 SAMPLE INPUT 3:
abcd

📎 SAMPLE OUTPUT 3:


💡 HINT: Border dari border tetap border. Mulai dari pi[n-1] lalu lompat
         terus ke pi[k-1]. Rantai itu turun, sedangkan output diminta naik.

🎯 Learning Goals:
- [ ] Menelusuri rantai pi
- [ ] Sadar bahwa rantai menghasilkan urutan menurun
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

    // TODO: bangun pi

    // TODO: telusuri rantai k = pi[n-1], lalu k = pi[k-1], sampai k == 0

    // TODO: balik urutan, lalu cetak

    return 0;
}
