/*
============================================================
📋 TUGAS 09: Pembagian Tugas Pabrik dengan Overhead Mesin
============================================================
Source: Classic CHT Partitioning
Difficulty: Hard
Topics: Convex Hull Trick, Monotone Deque

PROBLEM:
Sebuah pabrik memiliki N pesanan berurutan. Pesanan ke-i memiliki waktu pengerjaan t[i] dan penalti d[i].
Waktu pengerjaan t kumulatif selalu bertambah (T[i] = sum_{k=1}^i t[k]).
Koefisien penalti d kumulatif dari belakang adalah D[i] = sum_{k=i}^N d[k].
Jika kita mematikan mesin sejenak untuk pendinginan (memerlukan biaya S), setiap pemotongan batch di posisi j
menambahkan biaya penalti terhadap pesanan berikutnya sebesar:
`Cost = S * D[j+1] + T[i] * (D[j+1] - D[i+1])`.

Tentukan TOTAL BIAYA MINIMUM untuk menyelesaikan seluruh pesanan!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan S.
N baris berikutnya masing-masing berisi dua bilangan bulat t[i] dan d[i].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= S <= 50
1 <= t[i], d[i] <= 100

SAMPLE INPUT 1:
3 1
1 2
2 3
3 1

SAMPLE OUTPUT 1:
22

SAMPLE INPUT 2:
1 10
5 5

SAMPLE OUTPUT 2:
75
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll s;
    if (!(cin >> n >> s)) return 0;

    // TODO: Selesaikan dengan Batch Scheduling CHT Deque

    return 0;
}
