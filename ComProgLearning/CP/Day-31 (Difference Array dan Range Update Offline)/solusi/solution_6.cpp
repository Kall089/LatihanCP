/*
============================================================
✅ Solution 6: Menyiram Tanaman (Difference Array Terbalik)
============================================================
Approach: Difference Array dibaca terbalik + greedy
Complexity: Time O(N) | Space O(1) selain input
Key Insight:
Satu kali "tambah 1 pada rentang [l, r]" mengubah difference array
tepat di dua tempat: diff[l] += 1 dan diff[r+1] -= 1.
Artinya setiap pemakaian alat menyumbang TEPAT SATU unit kenaikan
pada difference array.

Maka jumlah pemakaian minimal = total seluruh kenaikan yang dibutuhkan
difference array dari array target, yaitu:
    jawaban = sum over i of max(0, b[i] - b[i-1]),  dengan b[0] = 0

Bagian yang menurun (b[i] < b[i-1]) tidak perlu dibayar, karena itu
hanyalah akibat dari rentang yang berakhir — dan berakhirnya rentang
tidak memerlukan pemakaian alat baru.
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

    ll sebelumnya = 0, jawaban = 0;
    for (int i = 0; i < n; i++) {
        ll b;
        cin >> b;
        if (b > sebelumnya) jawaban += b - sebelumnya;   // hanya bayar kenaikan
        sebelumnya = b;
    }

    cout << jawaban << "\n";
    return 0;
}
