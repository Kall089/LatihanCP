/*
============================================================
🏋️ Exercise 2: Membagi Tali
============================================================
Day: 51 | Difficulty: Easy
Topic: Binary search real dengan predikat greedy
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N potong tali dengan panjang masing-masing. Kamu harus memotong
tali-tali itu menjadi tepat K potongan yang panjangnya SAMA (potongan sisa
boleh dibuang, dan sebuah tali boleh menghasilkan beberapa potongan).
Cari panjang potongan MAKSIMUM yang memungkinkan. Cetak dengan 6 desimal.
Jika bahkan potongan sepanjang 1e-9 pun tidak cukup untuk menghasilkan K
potongan, cetak 0.000000.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- N baris berikutnya: masing-masing satu bilangan real panjang tali

📤 OUTPUT FORMAT:
- Satu bilangan real dengan 6 desimal

📏 CONSTRAINTS:
- 1 <= N <= 10^4
- 1 <= K <= 10^4
- 0 < panjang <= 10^5

📎 SAMPLE INPUT 1:
4 11
8.02
7.43
4.57
5.39

📎 SAMPLE OUTPUT 1:
2.005000

Penjelasan: dengan potongan sepanjang 2.005, tali pertama menghasilkan
tepat 4 potongan (8.02 / 2.005 = 4), dan sisanya 3 + 2 + 2, total 11.
Sedikit lebih panjang dari itu, tali pertama hanya menghasilkan 3 potongan
sehingga totalnya turun menjadi 10.

📎 SAMPLE INPUT 2:
2 100
1.0
1.0

📎 SAMPLE OUTPUT 2:
0.020000

💡 HINT: Predikatnya: "dengan panjang potongan x, berapa potongan yang bisa
         dihasilkan?" Jumlahkan floor(panjang[i] / x) untuk seluruh tali.
         Predikat itu MENURUN terhadap x — semakin panjang potongannya,
         semakin sedikit yang bisa dibuat. Jadi kamu mencari nilai
         TERBESAR yang masih layak, bukan terkecil.
         Batas atasnya: berapa panjang potongan maksimum yang mungkin
         masuk akal?

🎯 Learning Goals:
- [ ] Menulis varian "cari nilai terbesar yang layak"
- [ ] Menyadari arah monotonisitas predikat
- [ ] Menentukan batas atas dari struktur soal
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: predikat bisa(x) = total potongan >= K

    // TODO: perhatikan arah: bisa(x) true untuk x KECIL

    return 0;
}
