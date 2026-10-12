/*
============================================================
📋 TUGAS 01: Papan yang Dipotong (Cutting Plank)
============================================================
Source: Classic DP / UVa 10003
Difficulty: Medium
Topics: Range DP on Coordinates

PROBLEM:
Kamu memiliki sebilah papan kayu dengan panjang awal L meter, terbentang dari titik 0 sampai L.
Terdapat N titik pemotongan pada posisi c[0], c[1], ..., c[N-1] yang harus dipotong.
Setiap kali kamu memotong sebuah potongan papan, biaya yang harus dibayar adalah
panjang potongan papan yang sedang dipotong saat itu.
Setelah dipotong, papan terbelah menjadi dua sub-potongan.

Tentukan biaya total pemotongan MINIMUM untuk memotong seluruh N titik tersebut.
Jika N = 0, biaya pemotongan adalah 0.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat L dan N.
Baris kedua berisi N bilangan bulat unik c[0], ..., c[N-1] dalam urutan menaik (kosong jika N = 0).

OUTPUT FORMAT:
Satu bilangan bulat: biaya pemotongan minimum.

CONSTRAINTS:
1 <= L <= 10^9
0 <= N <= 150
0 < c[i] < L

SAMPLE INPUT 1:
10 2
4 7

SAMPLE OUTPUT 1:
16
(Penjelasan: Array titik = [0, 4, 7, 10].
Potong di 4 (biaya 10, papan terbelah jadi [0,4] dan [4,10]), lalu potong di 7 pada [4,10] (biaya 6).
Total biaya = 10 + 6 = 16)

SAMPLE INPUT 2:
10 0

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll L;
    int n;
    if (!(cin >> L >> n)) return 0;

    vector<ll> cuts;
    cuts.push_back(0);
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        cuts.push_back(x);
    }
    cuts.push_back(L);

    // TODO: Selesaikan dengan Range DP
    // m = cuts.size()
    // dp[l][r] = min_{l < k < r} (dp[l][k] + dp[k][r]) + (cuts[r] - cuts[l])

    return 0;
}
