/*
============================================================
📋 TUGAS 11: Membantah Greedy Interval
============================================================
Source: Latihan mandiri
Difficulty: Medium
Topics: Verifikasi greedy

PROBLEM:
Diberikan n interval [l, r]. Seorang teman mengusulkan cara memilih interval saling
lepas sebanyak mungkin: 'pilih terus interval TERPENDEK yang masih tersedia'.
Tentukan apakah strategi itu optimal untuk masukan yang diberikan.
Cetak OPTIMAL, atau dua bilangan: hasil strategi teman dan hasil optimal.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: l dan r

OUTPUT FORMAT:
OPTIMAL atau dua bilangan

CONSTRAINTS:
1 <= n <= 18, 1 <= l < r <= 100

SAMPLE INPUT 1:
3
1 10
9 12
11 20

SAMPLE OUTPUT 1:
1 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // n <= 18 adalah petunjuk keras: jawaban optimal boleh dihitung dengan mencoba seluruh himpunan bagian. Setelah selesai, jalankan pada interval acak dan hitung seberapa sering greedy 'terpendek dulu' gagal.

    return 0;
}
