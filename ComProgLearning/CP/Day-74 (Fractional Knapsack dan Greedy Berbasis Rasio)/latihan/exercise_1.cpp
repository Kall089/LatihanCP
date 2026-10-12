/*
============================================================
🏋️ Exercise 1: Perampokan Gudang Emas
============================================================
Day: 74 | Difficulty: Easy
Topic: Fractional knapsack dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah gudang berisi N karung bubuk emas. Karung ke-i memiliki berat w[i]
kilogram dan nilai total v[i].
Karena isinya berupa bubuk, kamu BOLEH mengambil sebagian dari sebuah karung:
mengambil sebanyak x kilogram dari karung ke-i memberimu nilai
v[i] * x / w[i].
Tas kamu hanya kuat menahan W kilogram.
Cari NILAI TOTAL MAKSIMUM yang bisa kamu bawa. Cetak dengan enam angka di
belakang koma.

📥 INPUT FORMAT:
- Baris pertama: N dan W
- N baris berikutnya: w[i] dan v[i]

📤 OUTPUT FORMAT:
- Satu bilangan real dengan enam angka di belakang koma

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= W <= 10^9
- 1 <= w[i] <= 10^9
- 1 <= v[i] <= 10^9

📎 SAMPLE INPUT 1:
3 10
6 7
5 5
5 5

📎 SAMPLE OUTPUT 1:
11.000000

📎 SAMPLE INPUT 2:
1 100
5 20

📎 SAMPLE OUTPUT 2:
20.000000

💡 HINT: Kata kunci soal ini ada di kalimat "kamu BOLEH mengambil sebagian".
         Satu kata itu mengubah seluruh pendekatannya.
         Kalau setiap kilogram ruang di tasmu harus dibelanjakan, ukuran apa
         yang paling masuk akal untuk membandingkan dua karung? Bukan nilai
         total, dan bukan berat.
         Setelah kamu menemukan ukurannya, urutkan dan ambil serakah.
         Perhatikan sampel 2: kapasitas jauh lebih besar dari total berat,
         jadi kamu mengambil semuanya dan tidak ada yang dipotong. Pastikan
         kodemu tidak mencoba memotong apa pun di situ.
         Terakhir, jangan membandingkan rasio dengan pembagian double.
         Dengan v dan w sampai 10^9 itu berisiko. Ada bentuk lain yang eksak.

🎯 Learning Goals:
- [ ] Mengenali kata kunci "boleh dipotong"
- [ ] Menemukan bahwa rasio adalah ukuran pembanding yang tepat
- [ ] Membandingkan rasio tanpa pembagian
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan menurut ukuran pembanding yang tepat

    // TODO: ambil utuh selama muat, potong yang terakhir

    return 0;
}
