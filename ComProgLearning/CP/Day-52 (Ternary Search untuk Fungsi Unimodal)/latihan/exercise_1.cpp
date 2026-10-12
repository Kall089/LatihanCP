/*
============================================================
🏋️ Exercise 1: Titik Minimum Parabola
============================================================
Day: 52 | Difficulty: Easy
Topic: Ternary search real
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan Q buah parabola dalam bentuk f(x) = a*x^2 + b*x + c dengan a > 0.
Untuk setiap parabola, cari nilai x pada rentang [-1000, 1000] yang membuat
f(x) sekecil mungkin, lalu cetak nilai f(x) minimum itu dengan 6 desimal.
Perhatikan bahwa titik minimum sesungguhnya mungkin berada DI LUAR rentang
[-1000, 1000] — dalam kasus itu, jawabannya adalah nilai di salah satu ujung
rentang.
Untuk latihan ini, kerjakan dengan ternary search, bukan dengan rumus.

📥 INPUT FORMAT:
- Baris pertama: Q
- Q baris berikutnya: masing-masing tiga bilangan a, b, c

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan real dengan 6 desimal

📏 CONSTRAINTS:
- 1 <= Q <= 10^4
- 1 <= a <= 100
- -1000 <= b, c <= 1000

📎 SAMPLE INPUT 1:
2
1 -6 9
1 0 0

📎 SAMPLE OUTPUT 1:
0.000000
0.000000

💡 HINT: Fungsi kuadrat dengan a > 0 berbentuk cekung ke atas, sehingga ia
         turun lalu naik — persis definisi unimodal (berupa lembah).
         Evaluasi f di dua titik yang membagi rentang menjadi tiga bagian,
         lalu putuskan sepertiga mana yang aman dibuang.
         Peringatan: mudah sekali membalik tanda perbandingan dan justru
         menemukan MAKSIMUM. Uji implementasimu dengan f(x) = (x-3)^2
         yang jawabannya kamu tahu sebelum mempercayainya.
         Catatan: parabola punya rumus eksak -b/(2a). Pakai itu untuk
         MEMVERIFIKASI jawabanmu, bukan untuk menjawab.

🎯 Learning Goals:
- [ ] Menulis kerangka ternary search dengan tanda yang benar
- [ ] Memverifikasi implementasi dengan fungsi yang jawabannya diketahui
- [ ] Menangani kasus minimum berada di luar rentang
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: untuk tiap parabola, ternary search pada [-1000, 1000]

    // TODO: m1 = lo + (hi-lo)/3, m2 = hi - (hi-lo)/3

    return 0;
}
