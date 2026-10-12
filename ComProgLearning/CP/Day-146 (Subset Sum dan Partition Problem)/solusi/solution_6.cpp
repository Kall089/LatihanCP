/*
============================================================
✅ Solution 6: Banyak Query Target
============================================================
Approach: Bitset subset sum preprocessing
Complexity: Preprocess O(N*MAX_SUM/64) | Query O(1) | Space O(MAX_SUM)
Key Insight: `bs[s] = 1` berarti sum s reachable. Operasi `bs << x`
             menggeser semua sum lama menjadi sum baru setelah mengambil x.
             `bs |= bs << x` berarti tidak ambil x atau ambil x.

📖 PENJELASAN PENDEKATAN:
1. Set bs[0] = 1.
2. Untuk setiap x, lakukan bs |= (bs << x).
3. Setelah preprocessing, setiap query target T dijawab dengan membaca bs[T].

🔄 ALTERNATIVE APPROACHES:
- vector<char> DP: O(N*total), masih benar tetapi lebih lambat.
- set<int>: query tetap bisa cepat setelah precompute, tetapi preprocessing
  lebih mahal.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_SUM = 200000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    bitset<MAX_SUM + 1> bs;
    bs[0] = 1;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        bs |= (bs << x);
    }

    while (q--) {
        int target;
        cin >> target;
        cout << (target <= MAX_SUM && bs[target] ? "YES" : "NO") << '\n';
    }

    return 0;
}
