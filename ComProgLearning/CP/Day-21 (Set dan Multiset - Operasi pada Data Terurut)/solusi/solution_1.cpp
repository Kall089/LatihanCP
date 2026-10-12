/*
============================================================
✅ Solution 1: Distinct Numbers (Set)
============================================================
Approach: Insert all to set
Complexity: Time O(N log N) | Space O(N)
Key Insight: Set otomatis deduplicate. size() = jumlah distinct.

📖 PENJELASAN PENDEKATAN:
1. Baca semua elemen
2. Insert ke set (duplikat otomatis ditolak)
3. Output set.size()

🔄 ALTERNATIVE APPROACHES:
- Sort + unique (Day 3 approach): O(N log N) time, O(N) space
- Unordered_set: O(N) average time
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    set<int> s;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }

    cout << s.size() << '\n';

    return 0;
}
