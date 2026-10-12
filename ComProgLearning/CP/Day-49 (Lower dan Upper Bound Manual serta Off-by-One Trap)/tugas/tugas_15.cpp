/*
============================================================
📋 TUGAS 15: Bound pada Struktur Dinamis
============================================================
Source: Original
Difficulty: Hard
Topics: set + operasi campuran

PROBLEM:
Mula-mula himpunan kosong. Ada Q operasi: '+ x' menyisipkan x, '- x'
menghapus satu salinan x, '? x' menanyakan nilai terkecil dalam himpunan
yang >= x (cetak -1 kalau tidak ada), dan '! x' menanyakan nilai terbesar
yang <= x. Dijamin operasi penghapusan selalu valid.

INPUT FORMAT:
- Baris pertama: Q
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi '?' atau '!'

CONSTRAINTS:
- 1 <= Q <= 2*10^5
- 1 <= x <= 10^9

SAMPLE INPUT 1:
5
+ 5
+ 2
? 3
! 3
- 2

SAMPLE OUTPUT 1:
5
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Gunakan multiset dengan FUNGSI ANGGOTA lower_bound dan upper_bound. Periksa begin() dan end() sebelum mendereferensi.

    return 0;
}
