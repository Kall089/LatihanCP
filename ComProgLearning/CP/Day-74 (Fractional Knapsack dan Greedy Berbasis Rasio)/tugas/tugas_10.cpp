/*
============================================================
📋 TUGAS 10: Branch and Bound Knapsack
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Batas atas fractional

PROBLEM:
Selesaikan 0/1 knapsack dengan n <= 35 dan W sampai 10^9 memakai branch and bound:
telusuri pohon keputusan ambil/lewati, dan pada setiap simpul hitung BATAS ATAS
memakai fractional knapsack atas barang yang tersisa. Pangkas cabang yang batas
atasnya tidak melebihi jawaban terbaik sekarang.

INPUT FORMAT:
Baris 1: n dan W
n baris berikutnya: w[i] dan v[i]

OUTPUT FORMAT:
Satu bilangan: nilai maksimum

CONSTRAINTS:
1 <= n <= 35, 1 <= W <= 10^9, 1 <= w[i] <= 10^9, 1 <= v[i] <= 10^9

SAMPLE INPUT 1:
3 10
6 7
5 5
5 5

SAMPLE OUTPUT 1:
10
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Urutkan barang menurut rasio menurun lebih dulu — itu membuat batas atas fractional bisa dihitung dalam satu sapuan maju dan membuat pemangkasan jauh lebih efektif. Bandingkan waktu jalannya dengan brute force 2^n murni.

    return 0;
}
