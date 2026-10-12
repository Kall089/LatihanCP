/*
============================================================
🏋️ Exercise 6: Memaksimalkan Keuntungan Investasi (Upper Convex Hull CHT)
============================================================
Day: 268 | Difficulty: Menantang | Topic: Upper Convex Hull Trick (Maximization)
Source: Classic CHT Maximization
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah perusahaan modal ventura menganalisis N skema investasi potensial.
Skema ke-i memberikan potensi imbal hasil linier terhadap modal investasi x:
`Profit_i(x) = m[i] * x + b[i]`.
Di mana m[i] adalah faktor pengali keuntungan dan b[i] adalah bonus dasar proyek.
Seluruh N skema investasi diberikan dengan nilai faktor m yang TIDAK MENURUN:
`m[0] <= m[1] <= ... <= m[N-1]`.

Terdapat Q calon investor yang masing-masing membawa dana modal x.
Seluruh dana modal investor diberikan dalam urutan TIDAK MENURUN:
`x[0] <= x[1] <= ... <= x[Q-1]`.

Untuk setiap calon investor, carilah KEUNTUNGAN MAKSIMUM yang dapat dihasilkan di antara seluruh N skema investasi yang ada!

Selesaikan dengan UPPER CONVEX HULL TRICK BERBASIS DEQUE dalam waktu O(N + Q)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan Q.
- N baris berikutnya masing-masing berisi dua bilangan bulat m[i] dan b[i].
- Baris terakhir berisi Q bilangan bulat x[0], x[1], ..., x[Q-1].

📤 OUTPUT FORMAT:
- Cetak Q baris, di mana baris ke-q berisi keuntungan maksimum untuk modal x[q].

📏 CONSTRAINTS:
- 1 <= N, Q <= 200.000
- -1.000.000 <= m[i], x[q] <= 1.000.000
- -1.000.000.000.000 <= b[i] <= 1.000.000.000.000
- m[0] <= m[1] <= ... <= m[N-1] (slope tidak menurun / menaik)
- x[0] <= x[1] <= ... <= x[Q-1] (modal tidak menurun / menaik)

📎 SAMPLE INPUT 1:
3 4
1 10
2 5
4 0
0 3 5 10

📎 SAMPLE OUTPUT 1:
10
13
20
40

[Penjelasan Sample 1:
Garis profit:
L1: y = 1x + 10
L2: y = 2x + 5
L3: y = 4x + 0
- x = 0: max(10, 5, 0) = 10 (L1)
- x = 3: max(13, 11, 12) = 13 (L1)
- x = 5: max(15, 15, 20) = 20 (L3)
- x = 10: max(20, 25, 40) = 40 (L3)]

📎 SAMPLE INPUT 2:
2 2
-2 10
-1 5
0 10

📎 SAMPLE OUTPUT 2:
10
-5

💡 HINT:
- Ini adalah masalah MAKTIMASI, sehingga kita mencari UPPER CONVEX HULL (amplop atas).
- Pada Upper Hull dengan kemiringan m menaik:
  Garis B di antara A dan C (dengan A.m < B.m < C.m) tidak berguna jika titik potong x_{AB} >= x_{BC}.
  `(A.b - B.b) / (B.m - A.m) >= (B.b - C.b) / (C.m - B.m)`
  <=> `(A.b - B.b) * (C.m - B.m) >= (B.b - C.b) * (B.m - A.m)`.
- Pada query dengan x menaik, buang garis depan jika garis ke-1 menghasilkan nilai >= garis ke-0!

🎯 Learning Goals:
- [ ] Mengadaptasi Convex Hull Trick dari minimasi ke maksimasi (Upper Hull).
- [ ] Menjaga keakuratan cross-product check pada garis-garis ber-slope menaik.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // TODO: Selesaikan dengan Upper Convex Hull Trick Deque

    return 0;
}
