/*
============================================================
📋 TUGAS 04: Penggabungan Tumpukan Batu Maksimum
============================================================
Source: Classic DP Variation
Difficulty: Medium
Topics: Range DP Maximization, Adjacent Merging

PROBLEM:
Terdapat N tumpukan batu berjajar dalam satu garis.
Tumpukan ke-i memiliki bobot a[i].
Kamu ingin menggabungkan seluruh tumpukan menjadi satu tumpukan tunggal
dengan aturan: setiap langkah hanya boleh menggabungkan dua tumpukan yang saling BERSEBELAHAN.
Biaya yang kamu DAPATKAN (reward) pada setiap penggabungan adalah jumlah bobot kedua tumpukan yang digabung.
Tentukan total reward MAKSIMUM yang dapat kamu kumpulkan.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: total reward maksimum yang bisa didapat.

CONSTRAINTS:
1 <= N <= 180
0 <= a[i] <= 10^9

SAMPLE INPUT 1:
3
10 20 30

SAMPLE OUTPUT 1:
110
(Penjelasan: Gabungkan tumpukan 1 dan 2 dulu (20 + 30 = 50, reward 50).
Lalu gabungkan dengan tumpukan 0 (50 + 10 = 60, reward 60).
Total reward = 50 + 60 = 110)

SAMPLE INPUT 2:
1
500

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    // TODO: Selesaikan Stone Merging Maksimum
    // dp[l][r] = max_{k} (dp[l][k] + dp[k+1][r]) + (pref[r+1] - pref[l])

    return 0;
}
