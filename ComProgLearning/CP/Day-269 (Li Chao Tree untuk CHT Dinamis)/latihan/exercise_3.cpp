/*
============================================================
🏋️ Exercise 3: Promo Hanya untuk Zona Tertentu (Line Segments Li Chao)
============================================================
Day: 269 | Difficulty: Hard | Topic: Li Chao Tree (Line Segments Insertion)
Source: Classic Li Chao Tree / Range Updates
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah perusahaan logistik meluncurkan program promo diskon bersyarat.
Setiap promo hanya berlaku untuk rute pengiriman dengan jarak x di dalam ZONA TERTENTU: L <= x <= R.
Terdapat Q operasi yang datang secara berurutan:
- Tipe 1: `1 m b L R`
  Mendaftarkan promo baru dengan fungsi tarif:
  `Tarif(x) = m * x + b`
  yang HANYA VALID untuk jarak x sedemikian sehingga L <= x <= R.
- Tipe 2: `2 x`
  Menanyakan TARIF PROMO TERMURAH yang saat ini mencakup jarak pengiriman x
  (nilai minimum dari m * x + b atas seluruh promo terdaftar yang memenuhi L <= x <= R).
  Jika saat ini tidak ada satu pun promo yang mencakup jarak x, cetak string "EMPTY".

Selesaikan dengan SEGMENT TREE LI CHAO dalam waktu O(Q log^2 Q)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat Q.
- Q baris berikutnya masing-masing berisi salah satu format operasi:
  - `1 m b L R`
  - `2 x`

📤 OUTPUT FORMAT:
- Untuk setiap operasi tipe 2, cetak satu baris: tarif termurah atau `EMPTY`.

📏 CONSTRAINTS:
- 1 <= Q <= 100.000
- Minimal ada 1 operasi kueri (tipe 2).
- -1.000.000 <= m, x, L, R <= 1.000.000
- -1.000.000.000.000 <= b <= 1.000.000.000.000
- L <= R

📎 SAMPLE INPUT 1:
5
1 2 1 0 5
2 -1
2 3
1 -1 8 3 10
2 10

📎 SAMPLE OUTPUT 1:
EMPTY
7
-2

[Penjelasan Sample 1:
1. Tambah promo L1: y = 2x + 1 untuk x in [0, 5].
2. Kueri x = -1 -> di luar zona [0, 5] -> EMPTY.
3. Kueri x = 3 -> masuk zona [0, 5], nilai = 2*3 + 1 = 7.
4. Tambah promo L2: y = -x + 8 untuk x in [3, 10].
5. Kueri x = 10 -> masuk zona [3, 10], nilai = -10 + 8 = -2.]

📎 SAMPLE INPUT 2:
3
1 5 2 3 3
2 3
2 4

📎 SAMPLE OUTPUT 2:
17
EMPTY

📎 SAMPLE INPUT 3:
1
2 0

📎 SAMPLE OUTPUT 3:
EMPTY

💡 HINT:
- Kumpulkan seluruh nilai kueri x dan batas-batas L, R (atau cukup seluruh kueri x jika hanya x yang di-query).
- Gunakan Segment Tree kanonik: pecah interval [L, R] menjadi O(log Q) segmen simpul kanonik.
- Pada setiap simpul kanonik yang tercakup sepenuhnya, lakukan operasi `add_line_internal` Li Chao Tree.
- Total kompleksitas penambahan segmen garis adalah O(log^2 Q).

🎯 Learning Goals:
- [ ] Menguasai penambahan segmen garis terbatas [L, R] pada Li Chao Tree.
- [ ] Memahami dekomposisi kanonik pada segment tree untuk fungsi linear.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    // TODO: Selesaikan dengan Segment Tree Li Chao untuk segmen garis [L, R]

    return 0;
}
