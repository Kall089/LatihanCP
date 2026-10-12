/*
============================================================
✅ Solution 2: Nilai Tertinggi Setelah Semua Perintah
============================================================
Approach: Difference Array + pelacakan maksimum dalam satu loop
Complexity: Time O(N + Q) | Space O(N)
Key Insight:
Rekonstruksi array final adalah satu kali jalan dari kiri ke kanan.
Karena itu perhitungan lain (maksimum, minimum, jumlah) bisa
ditumpangkan pada loop yang sama tanpa biaya tambahan.
Memakai ">" (bukan ">=") menjamin indeks terkecil yang tersimpan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<ll> diff(n + 2, 0);

    for (int i = 0; i < q; i++) {
        int l, r;
        ll v;
        cin >> l >> r >> v;
        diff[l]     += v;
        diff[r + 1] -= v;
    }

    ll jalan = 0, terbaik = LLONG_MIN;
    int lantai = 1;
    for (int i = 1; i <= n; i++) {
        jalan += diff[i];
        if (jalan > terbaik) {   // ">" -> indeks terkecil menang saat seri
            terbaik = jalan;
            lantai = i;
        }
    }

    cout << terbaik << " " << lantai << "\n";
    return 0;
}
