/*
============================================================
✅ Solution 4: K-th Largest Element (Priority Queue)
============================================================
Approach: Min-heap of size K
Complexity: Time O(N log K) | Space O(K)
Key Insight: Min-heap size K → top() = K-th largest.
             Elemen di heap = K elemen terbesar yang pernah masuk.
             Yang terkecil di antara K terbesar = K-th largest.

📖 PENJELASAN PENDEKATAN:
1. Maintain min-heap
2. Untuk setiap elemen baru: push ke heap
3. Jika heap size > K: pop (buang terkecil)
4. Jika heap size == K: output top (= K-th largest)
5. Jika heap size < K: output -1

🔄 ALTERNATIVE APPROACHES:
- Sort + index: O(N log N) tapi offline
- Order statistics tree: O(log N) per query tapi complex
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    priority_queue<int, vector<int>, greater<int>> min_pq;  // min heap

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        min_pq.push(x);

        if ((int)min_pq.size() > k) {
            min_pq.pop();  // buang terkecil, sisakan K terbesar
        }

        if (i > 0) cout << ' ';
        if ((int)min_pq.size() < k) {
            cout << -1;
        } else {
            cout << min_pq.top();  // K-th largest
        }
    }
    cout << '\n';

    return 0;
}
