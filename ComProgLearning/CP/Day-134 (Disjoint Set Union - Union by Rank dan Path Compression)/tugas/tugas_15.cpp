/*
============================================================
📋 TUGAS 15: Offline Dynamic Connectivity
============================================================
Source: Original
Difficulty: Hard
Topics: DSU rollback + divide and conquer

PROBLEM:
N simpul. Ada Q operasi: '+ u v' menambah sisi, '- u v' menghapus sisi
yang ada, dan '? ' menanyakan banyaknya komponen saat itu.
Cetak jawaban untuk setiap operasi '?'.

INPUT FORMAT:
- Baris pertama: N dan Q
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi '?'

CONSTRAINTS:
- 1 <= N, Q <= 10^5

SAMPLE INPUT 1:
3 5
+ 1 2
?
+ 2 3
- 1 2
?

SAMPLE OUTPUT 1:
2
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
    // Setiap sisi hidup pada suatu INTERVAL waktu. Bangun segment tree atas waktu, sisipkan tiap sisi ke O(log Q) simpul, lalu DFS dengan DSU ROLLBACK (tanpa path compression). Materi lengkapnya Day 191.

    return 0;
}
