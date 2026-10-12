/*
============================================================
📋 TUGAS 09: Rekonstruksi Rute Lompatan Katak K-Langkah
============================================================
Source: AtCoder Educational DP Contest B (Frog 2)
Difficulty: Medium
Topics: 1D DP, K-Step Jump, Parent Array

PROBLEM:
Katak berada di batu 1 dan ingin menuju batu N.
Ketinggian batu ke-i adalah H[i].
Dari batu i, katak dapat melompat ke batu mana pun di antara i + 1 hingga i + K.
Biaya energi lompatan adalah |H[i] - H[j]|.
Tentukan energi minimum di baris pertama, dan daftar indeks batu (1-indexed) yang dikunjungi di baris kedua.
Jika ada seri, pilih jalur dengan jumlah lompatan paling sedikit; jika masih seri, pilih yang leksikografis terkecil.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat H[0], H[1], ..., H[N-1].

OUTPUT FORMAT:
Baris pertama: energi minimum.
Baris kedua: daftar indeks batu dipisahkan spasi.

CONSTRAINTS:
1 <= N <= 2.000
1 <= K <= 100
0 <= H[i] <= 10^9

SAMPLE INPUT 1:
5 3
10 30 40 50 20

SAMPLE OUTPUT 1:
30
1 2 5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<ll> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // TODO: Selesaikan Frog 2 dengan Parent Array / Suffix DP

    return 0;
}
