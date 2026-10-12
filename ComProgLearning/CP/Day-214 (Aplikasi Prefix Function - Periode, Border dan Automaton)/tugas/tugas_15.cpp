/*
============================================================
📋 TUGAS 15: Penggabungan Prefiks
============================================================
Source: AtCoder ABC257 G
Difficulty: Hard
Topics: pi + DP greedy

PROBLEM:
Diberikan string S dan T. Kamu ingin membentuk T dengan menyambung beberapa
prefiks dari S secara berurutan. Cari jumlah potongan MINIMAL yang diperlukan.
Jika tidak mungkin, cetak -1.

INPUT FORMAT:
- Baris pertama: S
- Baris kedua: T

OUTPUT FORMAT:
- Satu bilangan: jumlah potongan minimal, atau -1

CONSTRAINTS:
- 1 <= |S|, |T| <= 5 * 10^5

SAMPLE INPUT 1:
aba
abaaba

SAMPLE OUTPUT 1:
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
    // Bangun pi dari S + '#' + T. Nilai pi memberi 'seberapa jauh mundur' tiap posisi; sisanya DP/greedy jangkauan.

    return 0;
}
