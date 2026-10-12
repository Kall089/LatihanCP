/*
============================================================
📋 TUGAS 01: Nested Ranges Check
============================================================
Source: CSES 2168
Difficulty: Medium
Topics: Dominasi interval

PROBLEM:
Diberikan n rentang [a, b]. Untuk setiap rentang, tentukan apakah ia MEMUAT rentang
lain, dan apakah ia TERMUAT di dalam rentang lain.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: a dan b

OUTPUT FORMAT:
Baris 1: n bilangan 0/1 (memuat rentang lain)
Baris 2: n bilangan 0/1 (termuat di rentang lain)

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= a <= b <= 10^9

SAMPLE INPUT 1:
4
1 6
2 4
4 8
3 6

SAMPLE OUTPUT 1:
1 0 0 0
0 1 0 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Urut l menaik, tie-break r menurun. Tambal kasus rentang identik secara terpisah — itulah yang membedakan AC dan WA.

    return 0;
}
