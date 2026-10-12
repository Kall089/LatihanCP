/*
============================================================
✅ Solution 1: Rute Foto Pematang (Frog Jump Path Reconstruction)
============================================================
Approach: Suffix DP + Lexicographically Earliest Forward Reconstruction
Complexity: Time O(N) | Space O(N)
Key Insight:
1. Mengapa Suffix DP?
   Jika kita mengisi DP secara prefix (dari kiri ke kanan), kita mengetahui biaya
   mencapai pos i dari awal. Namun, saat menelusuri mundur dari Pos N ke 1,
   keputusan lokal yang kita ambil di akhir belum tentu menjamin urutan leksikografis
   dari depan ke belakang!
   Dengan Suffix DP:
   dp[i] = biaya minimum dari pos i menuju pos akhir (N - 1).
   Basis: dp[N - 1] = 0.
   dp[i] = min_{j \in {i+1, i+2}} (|H[i] - H[j]| + dp[j]).

2. Rekonstruksi Maju (Forward Traversal):
   Mulai dari i = 0.
   Di setiap langkah, kita mencoba j = i + 1 terlebih dahulu, lalu j = i + 2.
   Kandidat j pertama yang memenuhi:
   dp[i] == abs(H[i] - H[j]) + dp[j]
   pasti berada di jalur optimal dan memberikan indeks pos sekecil mungkin!
   Karena langsung dibangun dari awal, kita TIDAK PERLU membalik (reverse) hasil rute.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    if (n == 1) {
        cout << 0 << "\n";
        cout << 1 << "\n";
        cout << 1 << "\n";
        return 0;
    }

    // dp[i]: biaya energi minimum dari pos i ke pos n - 1
    vector<ll> dp(n, INF);
    dp[n - 1] = 0;

    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n && j <= i + 2; j++) {
            ll cost = llabs(h[i] - h[j]) + dp[j];
            dp[i] = min(dp[i], cost);
        }
    }

    // Rekonstruksi dari pos 0 (Pos 1) ke pos n - 1 (Pos N)
    vector<int> path;
    int cur = 0;
    path.push_back(cur + 1); // 1-indexed

    while (cur < n - 1) {
        // Coba j = cur + 1 dulu, lalu j = cur + 2
        for (int next_pos = cur + 1; next_pos < n && next_pos <= cur + 2; next_pos++) {
            if (dp[cur] == llabs(h[cur] - h[next_pos]) + dp[next_pos]) {
                cur = next_pos;
                path.push_back(cur + 1);
                break;
            }
        }
    }

    cout << dp[0] << "\n";
    cout << path.size() << "\n";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << (i + 1 == path.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
