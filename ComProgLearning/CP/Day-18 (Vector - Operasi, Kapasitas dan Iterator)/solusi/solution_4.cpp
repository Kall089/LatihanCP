/*
============================================================
✅ Solution 4: Rotate Vector (Rotasi Array)
============================================================
Approach: Triple Reverse Trick
Complexity: Time O(N) | Space O(1) (in-place)
Key Insight: Rotasi kanan K posisi = reverse semua, reverse [0..K-1],
             reverse [K..N-1]. Ini teknik klasik!

📖 PENJELASAN PENDEKATAN:
1. K = K % N (handle K >= N)
2. Reverse seluruh array [0..N-1]
3. Reverse bagian kiri [0..K-1]
4. Reverse bagian kanan [K..N-1]

Contoh: [1,2,3,4,5], K=2
- Reverse all:    [5,4,3,2,1]
- Reverse [0..1]: [4,5,3,2,1]
- Reverse [2..4]: [4,5,1,2,3] ✓

🔄 ALTERNATIVE APPROACHES:
- STL rotate(): rotate(v.begin(), v.begin()+n-k, v.end()) — O(N)
- Buat vector baru: O(N) time, O(N) space
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Step 1: Baca input
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int &x : v) cin >> x;

    // Step 2: Handle K >= N
    k = k % n;
    if (k == 0) {
        // Tidak perlu rotasi
        for (int i = 0; i < n; i++) {
            cout << v[i] << " \n"[i == n - 1];
        }
        return 0;
    }

    // Step 3: Triple reverse trick
    reverse(v.begin(), v.end());           // reverse semua
    reverse(v.begin(), v.begin() + k);     // reverse [0..K-1]
    reverse(v.begin() + k, v.end());       // reverse [K..N-1]

    // Step 4: Output
    for (int i = 0; i < n; i++) {
        cout << v[i] << " \n"[i == n - 1];
    }

    return 0;
}
