/*
============================================================
📋 TUGAS 11: Pembagian Harta Adil
============================================================
Source: Latihan mandiri
Difficulty: Medium
Topics: Knapsack menyamar

PROBLEM:
Ada n barang berharga dengan nilai v[i]. Bagi seluruh barang menjadi DUA bagian
sehingga SELISIH total nilai kedua bagian sekecil mungkin. Cetak selisih minimum.

INPUT FORMAT:
Baris 1: n
Baris 2: n nilai v[i]

OUTPUT FORMAT:
Satu bilangan: selisih minimum

CONSTRAINTS:
1 <= n <= 100, 1 <= v[i] <= 1000

SAMPLE INPUT 1:
4
3 1 4 2

SAMPLE OUTPUT 1:
0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ini knapsack dalam penyamaran. Kalau total seluruh nilai adalah S, salah satu bagian punya nilai t dan yang lain S-t. Nilai t mana saja yang bisa dicapai? Setelah tahu itu, jawabannya langsung terlihat.

    return 0;
}
