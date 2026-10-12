/*
============================================================
🏋️ Exercise 1: Tarif Angkot di Hari Festival (Static Lines Monotone CHT)
============================================================
Day: 268 | Difficulty: Medium | Topic: Convex Hull Trick (Monotone Case)
Source: Classic Convex Hull Trick
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah paguyuban angkutan umum di hari festival menawarkan N jenis tarif perjalanan.
Tarif ke-i dinyatakan sebagai persamaan garis lurus:
`Tarif_i(x) = m[i] * x + b[i]`.
Di mana m[i] adalah biaya per kilometer dan b[i] adalah biaya buka pintu (bisa negatif karena subsidi).
Seluruh N tarif diberikan dengan urutan kemiringan m yang TIDAK MENAIK (m[0] >= m[1] >= ... >= m[N-1]).

Terdapat Q calon penumpang yang masing-masing memiliki jarak perjalanan x.
Seluruh Q jarak x diberikan secara terurut TIDAK MENURUN (x[0] <= x[1] <= ... <= x[Q-1]).

Untuk setiap penumpang, carilah TARIF PALING MURAH (nilai minimum dari m[i] * x + b[i] atas seluruh i)!

Selesaikan dengan algoritma CONVEX HULL TRICK BERBASIS DEQUE dalam waktu O(N + Q)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan Q.
- N baris berikutnya masing-masing berisi dua bilangan bulat m[i] dan b[i].
- Baris terakhir berisi Q bilangan bulat x[0], x[1], ..., x[Q-1].

📤 OUTPUT FORMAT:
- Cetak Q baris, di mana baris ke-q adalah tarif termurah untuk penumpang dengan jarak x[q].

📏 CONSTRAINTS:
- 1 <= N, Q <= 200.000
- -1.000.000 <= m[i], x[q] <= 1.000.000
- -1.000.000.000.000 <= b[i] <= 1.000.000.000.000
- m[0] >= m[1] >= ... >= m[N-1] (slope tidak menaik)
- x[0] <= x[1] <= ... <= x[Q-1] (jarak tidak menurun)

📎 SAMPLE INPUT 1:
4 6
3 0
2 2
1 9
0 12
0 1 2 5 7 10

📎 SAMPLE OUTPUT 1:
0
3
6
12
12
12

[Penjelasan Sample 1:
Garis-garis tarif: y = 3x, y = 2x + 2, y = x + 9, y = 12.
- x = 0: min(0, 2, 9, 12) = 0 (garis 1)
- x = 1: min(3, 4, 10, 12) = 3 (garis 1)
- x = 2: min(6, 6, 11, 12) = 6 (garis 1 atau 2)
- x = 5: min(15, 12, 14, 12) = 12 (garis 2 atau 4)
- x = 7: min(21, 16, 16, 12) = 12 (garis 4)
- x = 10: min(30, 22, 19, 12) = 12 (garis 4).]

📎 SAMPLE INPUT 2:
1 3
1 5
-3 0 2

📎 SAMPLE OUTPUT 2:
2
5
7

📎 SAMPLE INPUT 3:
3 3
2 7
2 1
2 9
0 2 2

📎 SAMPLE OUTPUT 3:
1
5
5

💡 HINT:
- Simpan garis dalam deque.
- Sebelum memasukkan garis baru, uji eliminasi garis di ujung belakang menggunakan perkalian silang `__int128`.
- Tangani kasus kemiringan sama: simpan intersep terkecil.
- Untuk query, karena x monoton menaik, buang garis di depan jika garis berikutnya menghasilkan nilai lebih kecil atau sama pada x.

🎯 Learning Goals:
- [ ] Memahami struktur data Deque untuk pemeliharaan Lower Convex Hull.
- [ ] Menggunakan `__int128` untuk cross-product check anti-overflow.
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

    // TODO: Selesaikan dengan Convex Hull Trick Deque

    return 0;
}
