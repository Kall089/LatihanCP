/*
============================================================
📋 TUGAS 04: Playlist
============================================================
Source: CSES 1141
Difficulty: Medium
Topics: sliding window variabel + posisi terakhir (Day 34 + 40)

PROBLEM:
Diberikan daftar N lagu. Cari panjang rentang berurutan terpanjang yang
seluruh lagunya BERBEDA (tidak ada yang berulang).

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan, id tiap lagu

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 1 <= id <= 10^9

------------------------------------------------------------
SAMPLE 1 - versi string yang setara: "abcabcbb"
input:
8
1 2 3 1 2 3 2 2
output:
3
penjelasan: rentang terpanjang tanpa pengulangan panjangnya 3,
misalnya [1,2,3].

SAMPLE 2 - semua sama
input:
5
7 7 7 7 7
output:
1

SAMPLE 3 - pengulangan di tengah
input:
6
1 5 5 2 1 3
output:
4
penjelasan: [5,2,1,3] pada posisi 3..6.

SAMPLE 4 - semua berbeda
input:
6
1 2 3 4 5 6
output:
6
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- id sampai 10^9, jadi butuh map (atau kompresi koordinat lebih dulu)
- saat menemukan pengulangan, pointer kiri LOMPAT ke posisiTerakhir+1,
  tapi HANYA kalau posisi itu lebih besar dari l sekarang. Tanpa
  penjaga max(), l bisa mundur dan hasilnya salah
- perbarui posisiTerakhir[id] di setiap langkah
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
