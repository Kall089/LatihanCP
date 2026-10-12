/*
============================================================
📋 TUGAS 03: Subarray Divisibility
============================================================
Source: CSES 1662
Difficulty: Medium
Topics: prefix sum modulo + counting (Day 29 + 40)

PROBLEM:
Diberikan N bilangan bulat. Hitung ada berapa subarray yang jumlahnya
habis dibagi N.

Transformasinya: jumlah subarray (l..r) habis dibagi m tepat ketika
P[r+1] dan P[l] memberikan SISA yang sama saat dibagi m. Jadi soal ini
berubah menjadi "hitung pasangan prefix dengan sisa sama".

INPUT FORMAT:
- Baris pertama: N (yang juga menjadi pembagi m)
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
5
3 1 2 7 4
output:
1
penjelasan: hanya [1,2,7] yang berjumlah 10 dan habis dibagi 5.

SAMPLE 2 - semua kelipatan
input:
3
5 10 15
output:
3
penjelasan: [15], [5,10], dan [5,10,15]. Perhatikan m = N = 3 di sini,
bukan 5 - pembaginya adalah N, bukan nilai elemennya.

SAMPLE 3 - N = 1
input:
1
1
output:
1
penjelasan: apa pun habis dibagi 1.

SAMPLE 4 - ADA ELEMEN NEGATIF
input:
4
-2 2 -2 2
output:
10
penjelasan: di C++, (-2) % 4 menghasilkan -2, BUKAN 2. Kalau kamu
memakai sisa negatif sebagai indeks array, program akan crash atau
salah. Normalkan dengan ((x % m) + m) % m. Sample ini ada khusus
untuk itu.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- normalkan sisa agar selalu 0..m-1
- cnt berukuran m, cnt[0] = 1 di awal
- jawabannya bisa ~2*10^10, pakai long long
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
