/*
============================================================
📋 TUGAS 03: Langkah Katak dengan Jarak Pilihan
============================================================
Source: Classic DP / CSES
Difficulty: Easy
Topics: Unbounded Counting DP (Permutation)

PROBLEM:
Seekor katak berada di titik koordinat 0 dan ingin mencapai koordinat X.
Katak memiliki N pilihan panjang lompatan berbeda d[0], ..., d[N-1].
Setiap pilihan panjang lompatan dapat digunakan berkali-kali tanpa batas.
Urutan lompatan diperhitungkan (lompatan 1 lalu 2 berbeda dengan 2 lalu 1).
Hitung banyaknya cara berbeda katak mencapai tepat koordinat X.
Karena hasilnya bisa sangat besar, keluarkan jawaban modulo 1.000.000.007.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat d[0], ..., d[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: banyak cara modulo 1.000.000.007.

CONSTRAINTS:
1 <= N <= 100
0 <= X <= 10.000
1 <= d[i] <= 10.000

SAMPLE INPUT 1:
3 4
1 2 3

SAMPLE OUTPUT 1:
7
(Penjelasan: 1+1+1+1, 1+1+2, 1+2+1, 2+1+1, 2+2, 1+3, 3+1)

SAMPLE INPUT 2:
2 5
2 4

SAMPLE OUTPUT 2:
0
(Penjelasan: Kedua lompatan bernilai genap, tidak mungkin mencapai koordinat ganjil 5)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    // TODO: Selesaikan dengan Counting DP (Loop koordinat di luar, jarak di dalam)
    // dp[0] = 1.
    // dp[i] = (dp[i] + dp[i - d[k]]) % MOD.

    return 0;
}
