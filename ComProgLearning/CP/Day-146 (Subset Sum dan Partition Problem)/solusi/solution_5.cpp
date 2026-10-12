/*
============================================================
✅ Solution 5: Berapa Banyak Cara?
============================================================
Approach: Counting subset sum
Complexity: Time O(N*K) | Space O(K)
Key Insight: Boolean subset sum hanya menyimpan bisa/tidak. Untuk menghitung
             jumlah subset, state diubah menjadi cara[s] = banyak subset
             yang menghasilkan sum s.

📖 PENJELASAN PENDEKATAN:
1. cara[0] = 1 karena subset kosong menghasilkan sum 0.
2. Untuk setiap x, update s dari K turun ke x.
3. Tambahkan cara[s-x] ke cara[s].
4. Modulo setiap transisi.

⚠️ ELEMEN 0:
Jika x = 0, loop dari K turun ke 0 membuat cara[s] += cara[s].
Ini benar, karena setiap subset lama punya dua pilihan: ambil 0 atau tidak.

🔄 ALTERNATIVE APPROACHES:
- Rekursi + memoization: sama kompleksitasnya, tetapi lebih rawan stack dan
  overhead.
- DP 2D: lebih mudah divisualkan, tetapi memori O(N*K).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    cin >> n >> K;

    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<ll> cara(K + 1, 0);
    cara[0] = 1;

    for (int x : a) {
        for (int s = K; s >= x; s--) {
            cara[s] += cara[s - x];
            if (cara[s] >= MOD) cara[s] %= MOD;
        }
    }

    cout << cara[K] % MOD << '\n';
    return 0;
}
