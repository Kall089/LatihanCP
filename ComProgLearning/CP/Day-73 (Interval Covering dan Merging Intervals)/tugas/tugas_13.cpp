/*
============================================================
📋 TUGAS 13: Union Persegi Panjang 1D per Waktu
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Sapuan + multiset

PROBLEM:
Ada n peristiwa. Peristiwa ke-i menambahkan interval [l, r] pada waktu t[i], dan
interval itu tetap ada sampai waktu berakhir.
Untuk setiap peristiwa (setelah diproses menurut urutan waktu), cetak TOTAL PANJANG
gabungan seluruh interval yang sudah ditambahkan sampai saat itu.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: l dan r (diberikan menurut urutan waktu)

OUTPUT FORMAT:
n baris, masing-masing total panjang gabungan setelah peristiwa ke-i

CONSTRAINTS:
1 <= n <= 2*10^5, 0 <= l < r <= 10^9

SAMPLE INPUT 1:
3
1 5
3 7
10 12

SAMPLE OUTPUT 1:
4
6
8
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Menggabungkan ulang setiap kali adalah O(n^2 log n). Pakai std::map sebagai daftar blok terpisah, lalu saat menyisipkan interval baru hapus blok yang tertelan sambil memperbarui total. Setiap blok dihapus paling banyak sekali, sehingga total O(n log n).

    return 0;
}
