/*
============================================================
✅ Solution 6: Optimal Stock Trading (CF 865D Buy Low Sell High)
============================================================
Approach: Slope Trick / Regret Greedy with Min-Heap
Complexity: Time O(N log N) | Space O(N)
Key Insight:
1. Konkavitas Keuntungan Saham:
   Fungsi keuntungan terhadap jumlah saham yang dimiliki membentuk kurva konkaf sepotong-sepotong.
   Setiap harga P[i] memberikan opsi:
   - Membeli saham seharga P[i] (menambah lereng kemiringan)
   - Menjual saham seharga P[i] (menurunkan lereng kemiringan)

2. Mekanisme Penyesuaian Penyesalan (Regret Mechanism):
   Untuk setiap harga P[i]:
   - Jika pq.top() < P[i]: kita dapat memasangkan transaksi: beli di harga pq.top() dan jual di P[i].
     Keuntungan bertambah P[i] - pq.top().
     Setelah itu, pq.top() di-pop dan P[i] dimasukkan ke pq.
     Mengapa P[i] dimasukkan kembali?
     Karena jika di kemudian hari ada harga P[j] > P[i], kita dapat mengganti keputusan:
     alih-alih menjual di P[i], kita menjual di P[j]!
     Keuntungan tambahan adalah P[j] - P[i], sehingga total untung menjadi (P[i] - pq.top()) + (P[j] - P[i]) = P[j] - pq.top().
   - P[i] juga selalu dimasukkan sekali lagi ke pq sebagai saham baru yang berpotensi dibeli di hari ke-i.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve_stock(int n, const vector<ll>& p) {
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    ll ans = 0;

    for (int i = 0; i < n; i++) {
        if (!pq.empty() && pq.top() < p[i]) {
            ans += p[i] - pq.top();
            pq.pop();
            pq.push(p[i]);
        }
        pq.push(p[i]);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    cout << solve_stock(n, p) << "\n";

    return 0;
}
