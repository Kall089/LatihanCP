/*
============================================================
📋 TUGAS 15 (Final Boss): Elevator Rides
============================================================
Source: CSES 1653
Difficulty: Hard
Topics: bitmask DP, subset DP, greedy + DP

PROBLEM:
Terdapat n orang dengan berat w[i]. Sebuah elevator memiliki
kapasitas maksimum X (berat total penumpang tidak boleh melebihi X).
Hitung jumlah minimum perjalanan elevator yang dibutuhkan
untuk membawa semua orang ke lantai atas.

INPUT FORMAT:
- Baris 1: dua integer n dan X
- Baris 2: n buah integer w[0..n-1]

OUTPUT FORMAT:
- Satu integer: jumlah minimum perjalanan

CONSTRAINTS:
- 1 ≤ n ≤ 20
- 1 ≤ X ≤ 10^9
- 1 ≤ w[i] ≤ X

SAMPLE INPUT 1:
4 10
4 8 6 1

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
5 10
3 3 3 3 3

SAMPLE OUTPUT 2:
3

NOTE: Sample 1: {8,1}=9 dan {4,6}=10 → 2 perjalanan.
      Sample 2: {3,3,3}=9, {3,3}=6 → atau {3,3,3},{3,3} → 3 perjalanan
      (tidak bisa kurang dari 3 karena total=15 > 2*10).
      
      Hint Bitmask DP:
        dp[mask] = (rides, weight_last) menggunakan pair<int,long long>
        Minimisasi rides lebih dulu, lalu weight_last.
        dp[0] = {1, 0} (1 perjalanan, berat 0 di perjalanan terakhir)
        Transisi: tambahkan orang i ke mask:
          Jika weight_last + w[i] <= X: masuk perjalanan yang sama
          Jika tidak: butuh perjalanan baru
        Jawaban: dp[(1<<n)-1].first
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,ll> pil;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
