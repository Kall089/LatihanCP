/*
============================================================
📋 TUGAS 12: Good Subarrays
============================================================
Source: Codeforces 1398C
Difficulty: Hard
Topics: transformasi + prefix sum + map (Day 29 + 40)

PROBLEM:
Diberikan string berisi N digit. Sebuah subarray (l..r) disebut BAIK
kalau jumlah digitnya sama persis dengan PANJANGNYA, yaitu r - l + 1.
Hitung ada berapa subarray yang baik.

Bandingkan dengan tugas 02. Di sana kamu mencari "jumlah = X" dengan X
tetap; di sini targetnya berubah-ubah mengikuti panjang. Kelihatannya
lebih sulit, padahal ada satu transformasi yang mengembalikannya ke
bentuk yang sudah kamu kuasai. Petunjuk: apa yang terjadi kalau setiap
digit kamu kurangi 1?

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: string sepanjang N berisi digit

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5
- setiap karakter adalah digit '0'..'9'

------------------------------------------------------------
SAMPLE 1 - kasus kecil
input:
3
120
output:
3
penjelasan: subarray yang baik: [1], [1,2,0], dan [2,0].

SAMPLE 2 - semua digit 1
input:
5
11111
output:
15
penjelasan: SEMUA subarray baik, karena jumlah digit selalu sama
dengan panjangnya. Ada 5*6/2 = 15.

SAMPLE 3 - berselang-seling
input:
4
2020
output:
4

SAMPLE 4 - tidak ada yang baik
input:
1
3
output:
0
penjelasan: satu digit bernilai 3 tapi panjangnya 1. Jawaban 0 sah.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- setelah b[i] = digit[i] - 1, soalnya menjadi "hitung subarray dengan
  jumlah = 0" - persis tugas 02 dengan X = 0
- cnt[0] = 1 sebelum loop
- jawabannya bisa ~5*10^9, pakai long long
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
