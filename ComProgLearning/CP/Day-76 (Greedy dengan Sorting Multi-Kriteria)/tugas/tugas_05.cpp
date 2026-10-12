/*
============================================================
📋 TUGAS 05: Queue Reconstruction by Height
============================================================
Source: LeetCode 406
Difficulty: Medium
Topics: Tie-break + penyisipan

PROBLEM:
Ada n orang; orang ke-i punya tinggi h[i] dan bilangan k[i] yang menyatakan berapa
orang di DEPANNYA yang tingginya lebih besar atau sama dengan h[i].
Rekonstruksi antreannya.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: h[i] dan k[i]

OUTPUT FORMAT:
n baris berisi h dan k sesuai urutan antrean

CONSTRAINTS:
1 <= n <= 2000, 0 <= h[i] <= 10^6, 0 <= k[i] < n

SAMPLE INPUT 1:
6
7 0
4 4
7 1
5 0
6 1
5 2

SAMPLE OUTPUT 1:
5 0
7 0
5 2
6 1
4 4
7 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Urut tinggi MENURUN, tie-break k MENAIK. Lalu sisipkan tiap orang pada posisi ke-k. Buktikan sendiri kenapa penyisipan berikutnya tidak pernah merusak yang sudah terpasang.

    return 0;
}
