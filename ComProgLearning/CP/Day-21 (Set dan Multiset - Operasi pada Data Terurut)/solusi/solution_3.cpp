/*
============================================================
✅ Solution 3: Concert Tickets (Multiset)
============================================================
Approach: Multiset + upper_bound + decrement
Complexity: Time O((N+M) log N) | Space O(N)
Key Insight: Untuk cari elemen terbesar ≤ x di sorted set:
             upper_bound(x) menunjuk ke elemen > x,
             mundur 1 langkah = elemen terbesar ≤ x.

📖 PENJELASAN PENDEKATAN:
1. Masukkan semua harga tiket ke multiset
2. Untuk setiap customer budget:
   a. it = tickets.upper_bound(budget) → elemen pertama > budget
   b. Jika it == begin() → tidak ada tiket ≤ budget → output -1
   c. Jika tidak: --it → tiket termahal ≤ budget → output *it, erase it

🔄 ALTERNATIVE APPROACHES:
- Sort tickets + binary search: O(N log N + M log N) tapi erase mahal
- Policy-based tree (order_of_key): overkill
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    multiset<int> tickets;
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        tickets.insert(h);
    }

    for (int i = 0; i < m; i++) {
        int budget;
        cin >> budget;

        auto it = tickets.upper_bound(budget);
        if (it == tickets.begin()) {
            cout << -1 << '\n';
        } else {
            --it;
            cout << *it << '\n';
            tickets.erase(it);
        }
    }

    return 0;
}
