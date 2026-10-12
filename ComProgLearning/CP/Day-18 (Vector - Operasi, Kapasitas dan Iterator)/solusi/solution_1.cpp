/*
============================================================
✅ Solution 1: Distinct Numbers (Hitung Elemen Unik)
============================================================
Approach: Sort + Unique + Erase
Complexity: Time O(N log N) | Space O(N)
Key Insight: Setelah sort, elemen duplikat pasti bersebelahan.
             unique() menghapus duplikat bersebelahan.

📖 PENJELASAN PENDEKATAN:
1. Baca semua elemen ke vector
2. Sort vector (O(N log N))
3. unique() memindahkan elemen duplikat ke akhir, return iterator
4. erase() hapus elemen setelah iterator
5. size() = jumlah elemen unik

🔄 ALTERNATIVE APPROACHES:
- Set: masukkan semua ke set, output set.size() — O(N log N) juga
- Unordered_set: O(N) average, tapi constant factor besar
- Sort + manual count: iterasi dan hitung jika v[i] != v[i-1]
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Step 1: Baca input
    int n;
    cin >> n;
    vector<int> v(n);
    for (int &x : v) cin >> x;

    // Step 2: Sort
    sort(v.begin(), v.end());

    // Step 3: Remove duplicates
    v.erase(unique(v.begin(), v.end()), v.end());

    // Step 4: Output
    cout << v.size() << '\n';

    return 0;
}
