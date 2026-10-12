/*
============================================================
✅ Solution 3: Bagi Rata
============================================================
Approach: Equal partition -> subset sum total/2
Complexity: Time O(N*total) | Space O(total)
Key Insight: Dua kelompok punya sum sama hanya mungkin jika total genap.
             Setelah itu, cukup cari satu subset dengan sum total/2.

📖 PENJELASAN PENDEKATAN:
1. Hitung total seluruh elemen.
2. Jika total ganjil, cetak NO.
3. Jika total genap, targetkan sum total/2.
4. Jalankan subset sum boolean sampai target tersebut.

🔄 ALTERNATIVE APPROACHES:
- Backtracking: O(2^N), tidak cukup untuk N=200.
- DP sampai total penuh: benar, tetapi target total/2 sudah cukup.
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

    if (total % 2 == 1) {
        cout << "NO\n";
        return 0;
    }

    int target = total / 2;
    vector<char> bisa(target + 1, 0);
    bisa[0] = 1;

    for (int x : a) {
        for (int s = target; s >= x; s--) {
            bisa[s] |= bisa[s - x];
        }
    }

    cout << (bisa[target] ? "YES" : "NO") << '\n';
    return 0;
}
