/*
============================================================
📋 TUGAS 10: Pengecatan Papan Iklan 2D
============================================================
Source: Original
Difficulty: Medium
Topics: difference array 2D (Day 30 + 31)

PROBLEM:
Sebuah papan iklan berbentuk grid R x C, semua selnya awalnya bernilai 0.
Ada Q perintah, masing-masing berbunyi "tambahkan V ke semua sel di
dalam persegi panjang dari (R1, C1) sampai (R2, C2)".

Setelah semua perintah, tentukan nilai terbesar pada papan dan ada
berapa sel yang mencapainya.

Ini generalisasi difference array ke dua dimensi. Satu update persegi
panjang menyentuh EMPAT posisi, bukan dua - dan tanda keempatnya
mengikuti pola inklusi-eksklusi yang sama dengan prefix sum 2D.

INPUT FORMAT:
- Baris pertama: R, C, dan Q
- Q baris berikutnya: R1, C1, R2, C2, dan V (semua 1-based)

OUTPUT FORMAT:
- Dua bilangan: nilai terbesar, lalu banyaknya sel yang mencapainya

CONSTRAINTS:
- 1 <= R, C <= 1000
- 1 <= Q <= 2*10^5
- 1 <= V <= 10^9

------------------------------------------------------------
SAMPLE 1 - dua persegi panjang bertumpang tindih
input:
3 3 2
1 1 2 2 5
2 2 3 3 3
output:
8 1
penjelasan: hanya sel (2,2) yang terkena kedua perintah -> 5+3 = 8.

SAMPLE 2 - satu perintah menutupi semuanya
input:
2 2 1
1 1 2 2 7
output:
7 4

SAMPLE 3 - dua pojok terpisah
input:
3 3 2
1 1 1 1 4
3 3 3 3 4
output:
4 2
penjelasan: dua sel bernilai sama-sama 4. Sample ini menguji apakah
kamu menghitung SEMUA sel yang mencapai maksimum, bukan cuma satu.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- satu update: d[r1][c1] += v, d[r1][c2+1] -= v,
               d[r2+1][c1] -= v, d[r2+1][c2+1] += v
- array d berukuran (R+2) x (C+2)
- finalisasi = prefix sum 2D pada d
- Q*V bisa 2*10^14, pakai long long
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
