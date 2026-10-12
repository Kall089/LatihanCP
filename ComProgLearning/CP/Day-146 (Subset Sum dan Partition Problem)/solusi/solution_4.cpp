/*
============================================================
✅ Solution 4: Selisih Terkecil
============================================================
Approach: Minimum partition difference dengan reachable sums
Complexity: Time O(N*T) | Space O(T), T = total semua elemen
Key Insight: Jika satu kelompok memiliki sum s, kelompok lain memiliki
             total-s. Selisihnya |total - 2s|. Nilai terbaik terjadi saat
             s sedekat mungkin dengan total/2.

📖 PENJELASAN PENDEKATAN:
1. Hitung seluruh reachable sum memakai subset sum DP.
2. Scan s dari total/2 turun ke 0.
3. Sum pertama yang reachable adalah yang paling dekat dengan total/2.
4. Jawaban = total - 2*s.

🔄 ALTERNATIVE APPROACHES:
- Brute force semua subset: O(2^N), hanya untuk N kecil.
- bitset: mempercepat DP boolean jika total besar tetapi masih dibatasi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n);
    int total = 0;
    for (int& x : a) {
        cin >> x;
        total += x;
    }

    vector<char> bisa(total + 1, 0);
    bisa[0] = 1;

    for (int x : a) {
        for (int s = total; s >= x; s--) {
            bisa[s] |= bisa[s - x];
        }
    }

    for (int s = total / 2; s >= 0; s--) {
        if (bisa[s]) {
            cout << total - 2 * s << '\n';
            return 0;
        }
    }

    return 0;
}
