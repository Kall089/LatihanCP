/*
============================================================
📋 TUGAS 09: Percampuran Ramuan Sihir (Harry Potter and Mixtures)
============================================================
Source: SPOJ MIXTURES
Difficulty: Hard
Topics: Range DP with Modulo Colors, Smoke Minimization

PROBLEM:
Di kelas ramuan Hogwarts, terdapat N cawan ramuan kimia berwarna berjajar dari 1 sampai N.
Ramuan ke-i memiliki warna berupa bilangan bulat a[i] (0 <= a[i] < 100).
Dua cawan ramuan yang BERSEBELAHAN dapat dicampur menjadi satu cawan baru.
Aturan percampuran:
- Warna ramuan baru hasil percampuran adalah: `(warna_1 + warna_2) % 100`.
- Percampuran tersebut menghasilkan asap beracun sebanyak: `warna_1 * warna_2` gram.

Kamu harus mencampur seluruh ramuan hingga hanya tersisa satu cawan tunggal.
Tentukan jumlah asap minimum yang dihasilkan dari seluruh proses percampuran.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: jumlah total asap minimum.

CONSTRAINTS:
1 <= N <= 100
0 <= a[i] < 100

SAMPLE INPUT 1:
3
40 60 20

SAMPLE OUTPUT 1:
2400
(Penjelasan:
Campur 40 dan 60 dulu: warna baru = (40+60)%100 = 0. Asap = 40 * 60 = 2400.
Lalu campur ramuan 0 dengan 20: warna baru = (0+20)%100 = 20. Asap = 0 * 20 = 0.
Total asap = 2400 + 0 = 2400.
Jika campur 60 dan 20 dulu: warna baru (60+20)%100 = 80, asap = 1200.
Lalu campur 40 dengan 80: asap = 40 * 80 = 3200. Total asap = 1200 + 3200 = 4400.
Minimum adalah 2400)

SAMPLE INPUT 2:
2
18 19

SAMPLE OUTPUT 2:
342
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

    vector<ll> a(n);
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    auto getColor = [&](int l, int r) -> ll {
        return (pref[r + 1] - pref[l]) % 100;
    };

    // TODO: Selesaikan SPOJ Mixtures dengan Range DP
    // dp[l][r] = min_{k} (dp[l][k] + dp[k+1][r] + getColor(l, k) * getColor(k+1, r))

    return 0;
}
