/*
============================================================
📋 TUGAS 12: DP pada Kondensasi SCC
============================================================
Source: Varian kontes (butuh Day 132)
Difficulty: Hard
Topics: SCC -> DAG -> DP

PROBLEM:
Graf berarah BOLEH bersiklus. Setiap simpul punya nilai v[i]. Cari total nilai
terbesar yang bisa dikumpulkan pada satu perjalanan yang berawal di simpul 1
(nilai satu simpul hanya dihitung sekali walaupun dilewati berkali-kali).

INPUT FORMAT:
- Baris 1: N M
- Baris 2: v_1 .. v_N
- M baris: u v

OUTPUT FORMAT:
- satu bilangan (long long)

CONSTRAINTS:
- 1 <= N, M <= 2*10^5, 0 <= v_i <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 3                    6
1 2 3
1 2
2 3
3 1

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 3                    7
1 2 3 4
1 2
2 3
1 4

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 0                    1
1 5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // 1. Cari SCC (Tarjan/Kosaraju - Day 132)
    // 2. Ciutkan tiap SCC jadi satu simpul dengan bobot = jumlah nilai anggota
    // 3. Graf hasilnya DIJAMIN DAG -> DP jalur terpanjang biasa
    // Ini pola paling umum "graf bersiklus tetap bisa di-DP".
    return 0;
}
