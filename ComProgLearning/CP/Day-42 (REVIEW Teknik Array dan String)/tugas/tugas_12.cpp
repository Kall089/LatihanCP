/*
============================================================
📋 TUGAS 12: Tiket Konser
============================================================
Source: CSES 1091
Difficulty: Medium
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Ada N tiket dengan harga tertentu dan M pelanggan yang datang satu per satu.
Pelanggan ke-i punya anggaran maksimum t[i]; ia akan membeli tiket TERMAHAL
yang harganya tidak melebihi anggarannya. Kalau tidak ada tiket yang
terjangkau, ia pergi tanpa membeli.

Untuk setiap pelanggan, cetak harga tiket yang ia beli, atau -1.

INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: N harga tiket
- Baris ketiga: M anggaran pelanggan

OUTPUT FORMAT:
- M bilangan, masing-masing di baris sendiri atau dipisah spasi

CONSTRAINTS:
- 1 <= N, M <= 2*10^5
- 1 <= harga, anggaran <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
5 3
5 3 7 8 5
4 8 3
output:
3 8 -1
penjelasan: pelanggan ke-3 hanya punya 3, dan tiket seharga 3 sudah terjual.

SAMPLE 2 - tiket habis
input:
1 2
1
1 1
output:
1 -1

SAMPLE 3 - harga kembar
input:
2 2
2 2
2 2
output:
2 2
penjelasan: dua tiket berharga sama harus bisa terjual keduanya - hati-hati kalau kamu memakai set biasa.

SAMPLE 4 - terlalu mahal
input:
1 1
10
5
output:
-1

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- tiket yang terjual harus DIHAPUS dari koleksi
- harga boleh kembar, jadi struktur yang kamu pakai harus mengizinkan duplikat
- 'termahal yang tidak melebihi X' adalah operasi pencarian standar; pastikan
  kamu memakai varian yang benar (bukan yang mencari lebih besar sama dengan)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TEBAKAN TEKNIK SAYA: ______________________
    // SINYAL DI SOAL     : ______________________

    // TODO: Kerjakan di sini

    return 0;
}
