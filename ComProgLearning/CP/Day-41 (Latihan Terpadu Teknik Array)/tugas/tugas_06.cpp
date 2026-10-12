/*
============================================================
📋 TUGAS 06: Largest Rectangle in Histogram
============================================================
Source: LeetCode 84
Difficulty: Hard
Topics: monotonic stack (Day 36)

PROBLEM:
Diberikan histogram berisi N batang dengan lebar 1 dan tinggi h[i].
Cari LUAS persegi panjang terbesar yang muat seluruhnya di dalam
histogram.

Soal ini adalah inti dari Exercise 5. Kalau versi 1D ini sudah kokoh,
versi grid-nya hanya menjalankannya R kali.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan tinggi

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5
- 0 <= h[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus klasik
input:
6
2 1 5 6 2 3
output:
10
penjelasan: batang ke-3 dan ke-4 (tinggi 5 dan 6) membentuk persegi
panjang 5 x 2 = 10.

SAMPLE 2 - dua batang
input:
2
2 4
output:
4
penjelasan: 4 x 1 mengalahkan 2 x 2.

SAMPLE 3 - N = 1
input:
1
5
output:
5

SAMPLE 4 - semua sama
input:
4
3 3 3 3
output:
12
penjelasan: seluruh histogram. Sample ini menguji perlakuan terhadap
tinggi KEMBAR pada kondisi pop.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- tambahkan sentinel tinggi 0 di ujung supaya stack pasti kosong
- rumus lebar: st.empty() ? i : (i - st.top() - 1). Perhatikan -1 nya
- tinggi 10^9 x lebar 10^5 = 10^14, pakai long long
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
