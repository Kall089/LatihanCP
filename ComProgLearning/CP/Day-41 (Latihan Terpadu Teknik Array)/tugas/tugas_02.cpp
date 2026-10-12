/*
============================================================
📋 TUGAS 02: Subarray Sums II
============================================================
Source: CSES 1661
Difficulty: Medium
Topics: prefix sum + hash map (Day 29 + 40)

PROBLEM:
Sama seperti tugas 01, TAPI bilangannya boleh negatif dan nol.
Hitung ada berapa subarray yang jumlahnya tepat X.

Bandingkan dengan tugas 01 dan pahami kenapa tekniknya harus berubah:
dengan elemen negatif, memperlebar subarray tidak lagi menjamin jumlahnya
naik, sehingga two pointers kehilangan dasarnya.

INPUT FORMAT:
- Baris pertama: N dan X
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= X, a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
6 5
2 -1 3 5 -2 3
output:
2
penjelasan: [2,-1,3,5,-2,-... ] mari eksplisit: [2,-1,3,5,-2,3] punya
subarray [5] dan [3,5,-2,-1... ] - kerjakan sendiri, jawabannya 2.

SAMPLE 2 - X = 0 dengan banyak pembatalan
input:
4 0
1 -1 1 -1
output:
4
penjelasan: [1,-1], [-1,1], [1,-1], dan [1,-1,1,-1].

SAMPLE 3 - N = 1 dan X negatif
input:
1 -3
-3
output:
1

SAMPLE 4 - semua nol
input:
3 0
0 0 0
output:
6
penjelasan: SEMUA 6 subarray berjumlah 0. Sample ini menguji apakah
kamu menghitung setiap kemunculan prefix, bukan hanya yang pertama.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- cnt[0] = 1 sebelum loop, mewakili prefix kosong
- res += cnt[pre - X] DULU, baru cnt[pre]++ (kalau dibalik, subarray
  kosong ikut terhitung saat X = 0)
- pakai map, bukan unordered_map: CSES dan CF punya tes anti-hash
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
