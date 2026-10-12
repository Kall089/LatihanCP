/*
============================================================
🏋️ Exercise 6: Memaksimalkan Nilai Portofolio Dinamis (Max Li Chao Tree)
============================================================
Day: 269 | Difficulty: Menantang | Topic: Li Chao Tree (Maximization)
Source: Dynamic Convex Hull Trick Maximization
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah perusahaan manajer investasi mengelola portofolio produk keuangan yang terus bertambah.
Terdapat Q operasi yang datang secara bergantian:
- Tipe 1: `1 m b`
  Menambahkan instrumen investasi baru yang memberikan return linier:
  `Return(x) = m * x + b`.
  Nilai m dan b dapat bernilai sembarang (positif, negatif, atau nol).
- Tipe 2: `2 x`
  Investor dengan modal x menanyakan KEUNTUNGAN MAKSIMUM yang dapat diraih
  (nilai maksimum dari m * x + b di antara seluruh instrumen yang telah terdaftar sejauh ini).
  Jika belum ada instrumen yang terdaftar, cetak string "EMPTY".

Selesaikan dengan MAX LI CHAO TREE dalam waktu O(Q log Q)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat Q.
- Q baris berikutnya masing-masing berisi format operasi:
  - `1 m b`
  - `2 x`

📤 OUTPUT FORMAT:
- Untuk setiap operasi tipe 2, cetak keuntungan maksimum atau string `EMPTY`.

📏 CONSTRAINTS:
- 1 <= Q <= 200.000
- Minimal ada 1 operasi tipe 2.
- -1.000.000 <= m, x <= 1.000.000
- -1.000.000.000.000 <= b <= 1.000.000.000.000

📎 SAMPLE INPUT 1:
6
2 5
1 3 -2
2 5
1 -2 15
2 5
2 2

📎 SAMPLE OUTPUT 1:
EMPTY
13
13
11

[Penjelasan Sample 1:
1. Kueri x=5 -> EMPTY.
2. Tambah L1: y = 3x - 2.
3. Kueri x=5 -> max(3*5 - 2) = 13.
4. Tambah L2: y = -2x + 15.
5. Kueri x=5 -> max(3*5 - 2 = 13, -2*5 + 15 = 5) = 13.
6. Kueri x=2 -> max(3*2 - 2 = 4, -2*2 + 15 = 11) = 11.]

📎 SAMPLE INPUT 2:
1
2 10

📎 SAMPLE OUTPUT 2:
EMPTY

💡 HINT:
- Modifikasi Li Chao Tree untuk kasus MAKSIMASI:
  - Garis inisial pohon adalah `Line(0, -INF)`.
  - Simpan garis yang memberikan nilai MAKSIMUM di x[mid].
  - Jika garis baru mengalahkan garis lama di x[mid], tukar garis tersebut.
  - Turunkan garis yang kalah ke anak kiri jika ia lebih besar di x[l], sebaliknya ke anak kanan.

🎯 Learning Goals:
- [ ] Mengimplementasikan Upper Li Chao Tree untuk maksimasi dinamis.
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

    // TODO: Selesaikan dengan Max Li Chao Tree

    return 0;
}
