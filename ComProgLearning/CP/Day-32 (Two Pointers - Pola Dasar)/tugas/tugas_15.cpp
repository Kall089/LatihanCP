/*
 * Day 19 — Two Pointers
 * File  : tugas_15.cpp
 * Topik : Subarray With Equal Number of 0s and 1s
 * Tingkat: Hard
 * -----------------------------------------------
 * Diberikan binary array A (hanya berisi 0 dan 1) berisi N elemen.
 * Temukan panjang subarray (kontinu) TERPANJANG yang mengandung
 * jumlah 0 dan 1 yang sama.
 *
 * Contoh:
 *   A = [0, 1, 0, 1, 1, 1, 0]
 *   Subarray [0,1,0,1] (indeks 0..3) panjang 4: dua 0 dan dua 1 ✓
 *   Subarray [1,0,1,1,1,0]? dua 0, empat 1 ✗
 *   Jawaban: 4
 *
 * Pendekatan Prefix Sum + HashMap (OPTIMAL O(n)):
 *   Ganti 0 dengan -1. Sekarang "jumlah 0 = jumlah 1" ekuivalen dengan
 *   "sum subarray = 0".
 *   Gunakan prefix sum: prefSum[i] = A[0] + ... + A[i-1] (setelah ganti)
 *   Jika prefSum[i] == prefSum[j] (i < j), subarray A[i..j-1] sum = 0.
 *   Simpan "pertama kali prefSum = x terjadi di indeks berapa" dalam hashmap.
 *
 * Pendekatan Two Pointers (untuk pemahaman):
 *   Two pointers murni tidak langsung bekerja di sini karena elemen bisa +/-1
 *   dan tidak ada properti monoton yang bisa dieksploitasi.
 *   Namun, kita bisa menggunakan varian: setelah transformasi ke {-1, +1},
 *   masalah menjadi mencari subarray dengan sum = 0, yang bisa diselesaikan
 *   dengan prefix sum.
 *
 *   Sebagai latihan two pointers: implementasikan brute force O(n²) dulu,
 *   lalu optimasi dengan prefix sum + hashmap.
 *
 * Input format  : Baris 1: N
 *                 Baris 2: N bilangan (hanya 0 dan 1)
 * Output format : Panjang subarray terpanjang dengan #0 == #1
 *                 (0 jika tidak ada)
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 A[i] ∈ {0, 1}
 *
 * Sample Input 1:      Sample Output 1:
 * 7                    4
 * 0 1 0 1 1 1 0
 *
 * Sample Input 2:      Sample Output 2:
 * 4                    4
 * 0 1 1 0
 *
 * Sample Input 3:      Sample Output 3:
 * 3                    2
 * 1 0 1
 *
 * Sample Input 4:      Sample Output 4:
 * 4                    0
 * 1 1 1 1
 *
 * Penjelasan Sample 1:
 *   A=[0,1,0,1,1,1,0]
 *   Transformasi: [-1,1,-1,1,1,1,-1]
 *   PrefSum: [0,-1,0,-1,0,1,2,1]
 *   prefSum=0 pertama di indeks 0, lalu di indeks 2 (len=2), indeks 4 (len=4)
 *   Maksimum panjang: 4 ✓
 *
 * Penjelasan Sample 2:
 *   A=[0,1,1,0] → [-1,1,1,-1]
 *   PrefSum: [0,-1,0,1,0]
 *   prefSum=0 di indeks 0 dan 4 → len=4 ✓
 *
 * Hint untuk prefix sum approach:
 *   map<int,int> firstSeen;   // prefSum → indeks pertama
 *   firstSeen[0] = 0;         // penting! sum=0 di indeks 0
 *   int sum = 0, ans = 0;
 *   for (int i = 0; i < n; i++) {
 *       sum += (A[i] == 1 ? 1 : -1);
 *       if (firstSeen.count(sum)) ans = max(ans, i+1 - firstSeen[sum]);
 *       else firstSeen[sum] = i + 1;
 *   }
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Tulis solusimu di sini

    return 0;
}
