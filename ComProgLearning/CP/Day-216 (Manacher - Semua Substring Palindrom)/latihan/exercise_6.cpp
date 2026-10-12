/*
============================================================
🏋️ Exercise 6: Pasangan Palindrom Bersinggungan
============================================================
Day: 216 | Difficulty: Hard (Contest-level)
Topic: Manacher + difference array + counting
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S sepanjang N. Hitung banyaknya PASANGAN substring
palindrom (A, B) yang saling BERSINGGUNGAN, yaitu A dan B memiliki
setidaknya satu posisi yang sama di dalam S.
Dua substring dibedakan berdasarkan posisinya, bukan isinya. Pasangan
(A, B) dan (B, A) dianggap sama dan dihitung sekali. Sebuah substring
tidak dipasangkan dengan dirinya sendiri.
Karena jawabannya besar, cetak hasilnya modulo 51123987.

Strategi yang disarankan: hitung TOTAL pasangan lalu kurangi pasangan yang
TIDAK bersinggungan. Dua palindrom tidak bersinggungan berarti yang satu
berakhir sebelum yang lain dimulai.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: string S (huruf kecil)

📤 OUTPUT FORMAT:
- Satu bilangan mod 51123987

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^6

📎 SAMPLE INPUT 1:
4
babb

📎 SAMPLE OUTPUT 1:
6

📎 SAMPLE INPUT 2:
2
aa

📎 SAMPLE OUTPUT 2:
2

💡 HINT: Misalkan T = total palindrom, maka total pasangan = T*(T-1)/2.
         Untuk pasangan yang tidak bersinggungan: untuk setiap posisi j,
         hitung berapa palindrom yang BERAKHIR tepat di j dan berapa yang
         MULAI setelah j. Dua besaran itu bisa didapat dengan menyebar
         kontribusi radius Manacher lewat difference array — jangan
         menandai satu per satu, itu O(N^2).
         Hati-hati: modulusnya 51123987, BUKAN 1e9+7, dan pembagian dengan 2
         tidak bisa dilakukan begitu saja karena modulus ini tidak prima
         relatif terhadap semua hal — bagi 2 SEBELUM mengambil modulo.

🎯 Learning Goals:
- [ ] Menyebar kontribusi radius ke array dengan difference array (Day 31)
- [ ] Teknik komplemen: hitung total lalu kurangi yang tidak diinginkan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 51123987;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;

    // TODO: Manacher

    // TODO: mulai[i] = berapa palindrom MULAI di i, akhir[i] = berapa BERAKHIR di i
    //       gunakan difference array untuk menyebar kontribusi tiap pusat

    // TODO: total pasangan - pasangan terpisah

    return 0;
}
