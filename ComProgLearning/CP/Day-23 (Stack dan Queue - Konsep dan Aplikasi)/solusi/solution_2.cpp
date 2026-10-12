/*
============================================================
✅ Solution 2: Queue Simulation (Kasir)
============================================================
Approach: Queue simulation + prefix sum
Complexity: Time O(N) | Space O(N)
Key Insight: Waktu selesai = prefix sum dari waktu layanan.

📖 PENJELASAN PENDEKATAN:
1. Masukkan semua ke queue
2. Track current_time
3. Pop dari depan, tambah waktu layanan ke current_time
4. Output current_time

🔄 ALTERNATIVE APPROACHES:
- Langsung prefix sum tanpa queue: sama saja O(N)
  (tapi exercise ini untuk latihan queue)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    queue<int> q;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        q.push(t);
    }

    long long current_time = 0;
    bool first = true;
    while (!q.empty()) {
        current_time += q.front();
        q.pop();
        if (!first) cout << ' ';
        cout << current_time;
        first = false;
    }
    cout << '\n';

    return 0;
}
