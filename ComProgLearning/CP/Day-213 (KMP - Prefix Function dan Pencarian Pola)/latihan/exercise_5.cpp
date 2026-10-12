/*
============================================================
🏋️ Exercise 5: Semua Border
============================================================
Day: 213 | Difficulty: Hard
Topic: Rantai pi
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Cetak SEMUA panjang border dari string S secara menaik.
Border adalah potongan yang menjadi awalan sekaligus akhiran dari S,
tetapi bukan seluruh S.
Jika tidak ada border sama sekali, cetak -1.

Contoh: "abcababcab" punya dua border, yaitu "ab" (panjang 2) dan
"abcab" (panjang 5).

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu baris berisi panjang seluruh border secara menaik, atau -1.

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6

📎 SAMPLE INPUT 1:
abcababcab

📎 SAMPLE OUTPUT 1:
2 5

📎 SAMPLE INPUT 2:
aaaa

📎 SAMPLE OUTPUT 2:
1 2 3

📎 SAMPLE INPUT 3:
abcd

📎 SAMPLE OUTPUT 3:
-1

💡 HINT:
- Sifat kuncinya: BORDER DARI BORDER JUGA MERUPAKAN BORDER.
- Karena itu semua border membentuk rantai: mulai dari k = pi[n-1],
  lalu k = pi[k-1], terus sampai k mencapai 0.
- Rantai ini menghasilkan border dari yang terpanjang ke terpendek,
  jadi jangan lupa dibalik sebelum dicetak.
- Panjang rantainya paling banyak O(log n) untuk string acak, tetapi bisa
  mencapai O(n) untuk string seperti "aaaa".

🎯 Learning Goals:
- [ ] Memahami sifat rantai border
- [ ] Menelusuri pi secara berantai
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca S, bangun pi

    // TODO: Mulai dari k = pi[n-1], terus k = pi[k-1] sampai 0

    // TODO: Balik hasilnya agar menaik, lalu cetak

    return 0;
}
