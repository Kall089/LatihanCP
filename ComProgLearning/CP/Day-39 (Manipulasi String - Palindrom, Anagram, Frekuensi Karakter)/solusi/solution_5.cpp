/*
============================================================
✅ Solution 5: Menghitung Kemunculan Pola
============================================================
Approach: Pencarian pola naif dengan penghentian dini
Complexity: Time O(|T| x |P|) | Space O(1)
Key Insight:
Kita mencoba setiap posisi awal yang mungkin, lalu membandingkan huruf
demi huruf sampai ada yang berbeda. Karena setelah satu kecocokan kita
tetap melanjutkan dari posisi i+1 (bukan i+|P|), kemunculan yang saling
tumpang tindih ikut terhitung. Untuk |T| sampai 2000 ini masih sangat
aman; di atas itu gunakan KMP yang berjalan O(|T| + |P|).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string t, p;
    if (!(cin >> t >> p)) return 0;

    int n = t.size(), m = p.size(), total = 0;
    for (int i = 0; i + m <= n; i++) {
        bool cocok = true;
        for (int j = 0; j < m; j++)
            if (t[i + j] != p[j]) { cocok = false; break; }
        if (cocok) total++;          // posisi berikutnya tetap dicoba -> tumpang tindih dihitung
    }
    cout << total << "\n";

    return 0;
}
