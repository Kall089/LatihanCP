/*
============================================================
🏋️ Exercise 1: Papan Tarif yang Terus Berubah (Dynamic Li Chao Tree)
============================================================
Day: 269 | Difficulty: Medium | Topic: Li Chao Tree (Dynamic Lines & Queries)
Source: Classic Dynamic CHT
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah penyedia layanan transportasi daring memperbarui tarif layanannya secara dinamis sepanjang hari.
Terdapat Q operasi yang datang secara berurutan. Masing-masing operasi dapat berupa salah satu dari dua jenis:
- Tipe 1: `1 m b`
  Menambahkan jenis tarif baru berupa garis lurus:
  `Tarif(x) = m * x + b`.
  Tarif ini aktif dan dapat digunakan untuk seluruh kueri yang datang setelahnya.
  Kemiringan m dan intersep b dapat bernilai berapa saja (tidak harus terurut).
- Tipe 2: `2 x`
  Calon penumpang menanyakan TARIF TERMURAH (nilai minimum dari m * x + b atas seluruh tarif yang telah terdaftar sejauh ini)
  untuk jarak perjalanan x.
  Jika belum ada satu pun tarif yang terdaftar pada saat kueri dilakukan, cetak string "EMPTY".

Selesaikan dengan LI CHAO TREE dalam waktu O(Q log Q)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat Q.
- Q baris berikutnya masing-masing berisi salah satu format operasi:
  - `1 m b` (penambahan tarif baru)
  - `2 x` (kueri tarif minimum untuk jarak x)

📤 OUTPUT FORMAT:
- Untuk setiap operasi tipe 2, cetak satu baris berisi tarif minimum, atau string `EMPTY` jika belum ada tarif terdaftar.

📏 CONSTRAINTS:
- 1 <= Q <= 200.000
- Minimal terdapat 1 operasi kueri (tipe 2).
- -1.000.000 <= m, x <= 1.000.000
- -1.000.000.000.000 <= b <= 1.000.000.000.000

📎 SAMPLE INPUT 1:
6
2 3
1 2 1
2 3
1 -1 8
2 -2
2 10

📎 SAMPLE OUTPUT 1:
EMPTY
7
-3
-2

[Penjelasan Sample 1:
1. Kueri x = 3 -> belum ada tarif -> cetak EMPTY.
2. Tambah tarif L1: y = 2x + 1.
3. Kueri x = 3 -> min(2*3 + 1) = 7.
4. Tambah tarif L2: y = -x + 8.
5. Kueri x = -2 -> min(2*(-2) + 1, -(-2) + 8) = min(-3, 10) = -3.
6. Kueri x = 10 -> min(2*(10) + 1, -(10) + 8) = min(21, -2) = -2.]

📎 SAMPLE INPUT 2:
1
2 0

📎 SAMPLE OUTPUT 2:
EMPTY

📎 SAMPLE INPUT 3:
4
1 0 5
1 0 -3
2 1
2 1

📎 SAMPLE OUTPUT 3:
-3
-3

💡 HINT:
- Kumpulkan seluruh titik kueri x terlebih dahulu (offline coordinate compression).
- Urutkan dan hapus duplikat koordinat kueri.
- Bangun Li Chao Tree di atas indeks koordinat terkompresi.
- Jalankan simulasi operasi sesuai urutan waktu aslinya (kronologis).
- Pada saat kueri, ambil nilai minimum dari seluruh garis di sepanjang root-to-leaf path.

🎯 Learning Goals:
- [ ] Mengimplementasikan struktur data Li Chao Tree berbasis kompresi koordinat offline.
- [ ] Menangani kueri dinamis dengan kemiringan acak dan koordinat kueri acak.
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

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
