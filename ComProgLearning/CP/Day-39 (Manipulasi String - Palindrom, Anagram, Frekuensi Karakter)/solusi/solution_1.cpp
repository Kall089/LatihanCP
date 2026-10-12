/*
============================================================
✅ Solution 1: Cek Palindrom
============================================================
Approach: Dua pointer dari kedua ujung
Complexity: Time O(N) | Space O(1)
Key Insight:
Palindrom berarti huruf ke-i selalu sama dengan huruf ke-(N-1-i).
Cukup periksa separuh string sambil menggerakkan dua penunjuk saling
mendekat. Begitu ada satu perbedaan, jawabannya sudah pasti TIDAK,
jadi kita bisa langsung berhenti.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int kiri = 0, kanan = (int)s.size() - 1;
    bool ya = true;
    while (kiri < kanan) {
        if (s[kiri] != s[kanan]) { ya = false; break; }
        kiri++;
        kanan--;
    }
    cout << (ya ? "YA" : "TIDAK") << "\n";

    return 0;
}
