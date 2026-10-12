/*
============================================================
📋 TUGAS 08: Maximum Subarray Sum with One Deletion
============================================================
Source: LeetCode 1186
Difficulty: Medium
Topics: kadane + satu state tambahan

PROBLEM:
Cari jumlah subarray TIDAK KOSONG terbesar, dengan tambahan: kamu boleh
menghapus PALING BANYAK satu elemen dari dalam subarray itu. Setelah
penghapusan, subarray harus tetap berisi minimal satu elemen.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5
- -10^4 <= a[i] <= 10^4

------------------------------------------------------------
SAMPLE 1 - penghapusan menolong
input:
5
1 -2 0 3 -1
output:
4
penjelasan: ambil [1,-2,0,3] lalu hapus -2 -> 1+0+3 = 4.
Tanpa penghapusan jawabannya cuma 3.

SAMPLE 2 - semua negatif, jatah tidak terpakai
input:
3
-1 -1 -1
output:
-1
penjelasan: hasil akhir harus tidak kosong, jadi kamu tidak boleh
menghapus satu-satunya elemen yang tersisa. Kalau kodemu mencetak 0,
berarti state "sudah menghapus" kamu izinkan berisi nol elemen.

SAMPLE 3 - penghapusan tidak menolong
input:
4
1 -2 -2 3
output:
3
penjelasan: menghapus satu -2 hanya memberi 2, kalah dari [3] saja.
Jatah hapus boleh tidak dipakai - kata kuncinya "PALING BANYAK".

SAMPLE 4 - satu penghapusan menyambung dua bagian besar
input:
6
2 1 -5 3 4 0
output:
10
penjelasan: [2,1,-5,3,4,0] hapus -5 -> 2+1+3+4+0 = 10. Tanpa
penghapusan yang terbaik cuma 7.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- dp0 = belum pakai jatah, dp1 = jatah sudah terpakai
- dp1[i] = max(dp1[i-1] + a[i], dp0[i-1])   <- dp0 yang LAMA
- dp1 di indeks 0 harus sentinel negatif besar, bukan 0
- hitung dp1 sebelum menimpa dp0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dua state: sudah pernah menghapus, atau belum.

    return 0;
}
