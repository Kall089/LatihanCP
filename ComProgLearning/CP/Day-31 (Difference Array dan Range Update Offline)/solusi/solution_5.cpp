/*
============================================================
✅ Solution 5: Kapasitas Bus Wisata
============================================================
Approach: Difference Array + pengecekan batas saat rekonstruksi
Complexity: Time O(N + MAKS_HALTE) | Space O(MAKS_HALTE)
Key Insight:
Rombongan yang berada di bus pada [s, t) adalah range update biasa:
diff[s] += p dan diff[t] -= p. Perhatikan pengurangnya di t, BUKAN t+1,
karena interval yang dimaksud setengah terbuka — pada halte t mereka
sudah turun. Setelah itu cukup satu kali prefix sum sambil memeriksa
apakah jumlah penumpang pernah melewati kapasitas.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAKS_HALTE = 1005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll c;
    if (!(cin >> n >> c)) return 0;

    vector<ll> diff(MAKS_HALTE + 2, 0);

    for (int i = 0; i < n; i++) {
        ll p;
        int s, t;
        cin >> p >> s >> t;
        diff[s] += p;   // naik di halte s
        diff[t] -= p;   // sudah turun tepat di halte t -> pakai t, bukan t+1
    }

    bool bisa = true;
    ll penumpang = 0;
    for (int i = 1; i <= MAKS_HALTE; i++) {
        penumpang += diff[i];
        if (penumpang > c) { bisa = false; break; }   // early exit
    }

    cout << (bisa ? "BISA" : "TIDAK") << "\n";
    return 0;
}
