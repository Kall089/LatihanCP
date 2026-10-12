/*
============================================================
✅ Solution 5: Sum of Two Values (Two Sum)
============================================================
Approach: Hash map complement search
Complexity: Time O(N) average | Space O(N)
Key Insight: Untuk setiap a[i], kita butuh (X - a[i]) yang sudah
             pernah muncul sebelumnya. Simpan value→index di map.

📖 PENJELASAN PENDEKATAN:
1. Iterasi array dari kiri ke kanan
2. Untuk setiap a[i], hitung complement = X - a[i]
3. Cek apakah complement ada di map
4. Jika ya → output kedua index (1-indexed)
5. Jika tidak → simpan a[i] → i ke map
6. Jika selesai tanpa hasil → "IMPOSSIBLE"

🔄 ALTERNATIVE APPROACHES:
- Sort + two pointers: O(N log N) — perlu simpan original index
- Brute force O(N²): TLE untuk N = 200,000
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for (int &v : a) cin >> v;

    unordered_map<int, int> seen;  // value → index (0-based)

    for (int i = 0; i < n; i++) {
        int complement = x - a[i];
        if (seen.count(complement)) {
            // Output 1-indexed
            cout << seen[complement] + 1 << ' ' << i + 1 << '\n';
            return 0;
        }
        seen[a[i]] = i;
    }

    cout << "IMPOSSIBLE" << '\n';

    return 0;
}
