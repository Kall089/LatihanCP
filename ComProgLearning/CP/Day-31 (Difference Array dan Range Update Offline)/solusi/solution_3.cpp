/*
============================================================
✅ Solution 3: Pengunjung Restoran Terbanyak
============================================================
Approach: Sweep Line (difference array dengan koordinat terkompresi)
Complexity: Time O(N log N) karena sorting | Space O(N)
Key Insight:
Difference array biasa butuh array sepanjang sumbu waktu. Kalau waktunya
sampai 1e9, kita cukup menyimpan TITIK-TITIK PERUBAHANNYA saja, karena
di antara dua kejadian jumlah pengunjung tidak berubah.

Tie-breaking: saat waktu sama, kejadian "pergi" (-1) diproses lebih dulu
daripada "datang" (+1), karena pelanggan yang pergi pada waktu b sudah
tidak dihitung pada waktu b itu sendiri. Mengurutkan pasangan
(waktu, delta) secara menaik otomatis melakukan ini, sebab -1 < +1.
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

    vector<pair<int,int>> ev;    // (waktu, delta)
    ev.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        ev.push_back({a, +1});   // satu pelanggan masuk
        ev.push_back({b, -1});   // satu pelanggan keluar
    }

    // Urut menaik. Saat waktu sama, -1 diproses dulu karena -1 < +1.
    sort(ev.begin(), ev.end());

    int jalan = 0, terbaik = 0;
    for (auto& [waktu, delta] : ev) {
        jalan += delta;
        terbaik = max(terbaik, jalan);
    }

    cout << terbaik << "\n";
    return 0;
}
