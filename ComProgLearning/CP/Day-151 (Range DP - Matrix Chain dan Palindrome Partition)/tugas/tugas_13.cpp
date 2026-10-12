/*
============================================================
📋 TUGAS 13: Pohon Pencarian Biner Optimal (Optimal BST)
============================================================
Source: CLRS Chapter 15 / Classic DP
Difficulty: Hard
Topics: Range DP, Binary Search Tree Optimization

PROBLEM:
Diberikan N buah kunci unik yang sudah terurut menaik k[0] < k[1] < ... < k[N-1].
Kunci ke-i memiliki frekuensi pencarian freq[i].
Kita ingin membangun sebuah Pohon Pencarian Biner (Binary Search Tree - BST) yang memuat
seluruh N kunci tersebut sedemikian rupa sehingga BIAYA PENCARIAN EKSPEKTASINYA adalah MINIMAL.

Biaya pencarian sebuah kunci adalah: `(kedalaman simpul di BST + 1) * freq[kunci]`.
(Akar pohon memiliki kedalaman 0, sehingga dikalikan 1).
Total biaya pencarian BST adalah jumlah biaya pencarian seluruh kunci.
Tentukan total biaya pencarian minimum dari BST yang dibangun secara optimal.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat freq[0], freq[1], ..., freq[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: total biaya pencarian minimum.

CONSTRAINTS:
1 <= N <= 150
1 <= freq[i] <= 10^6

SAMPLE INPUT 1:
3
34 8 50

SAMPLE OUTPUT 1:
142
(Penjelasan:
Jadikan kunci 2 (freq 50) sebagai akar: biaya = 1 * 50 = 50.
Anak kirinya adalah kunci 0 (freq 34): biaya = 2 * 34 = 68.
Anak kanan dari kunci 0 adalah kunci 1 (freq 8): biaya = 3 * 8 = 24.
Total biaya = 50 + 68 + 24 = 142.
Jika kunci 0 sebagai akar: 1*34 + 2*50 + 3*8 = 158.
Minimum adalah 142)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> freq(n);
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> freq[i];
        pref[i + 1] = pref[i] + freq[i];
    }

    // TODO: Selesaikan Optimal BST dengan Range DP
    // dp[l][r] = biaya minimum BST untuk rentang kunci l..r
    // dp[l][r] = min_{l <= root <= r} (dp[l][root-1] + dp[root+1][r]) + sum(freq[l..r])

    return 0;
}
