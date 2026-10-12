/*
============================================================
✅ Solution 5: Closest Pair of Points (1D)
============================================================
Approach: Sort + Adjacent Difference
Complexity: Time O(N log N) | Space O(N)
Key Insight: Setelah sort, jarak minimum PASTI antara dua elemen
             bersebelahan. Tidak mungkin jarak minimum antara
             elemen yang tidak bersebelahan (dalam array sorted).

📖 PENJELASAN PENDEKATAN:
1. Baca N bilangan ke vector (gunakan long long!)
2. Sort vector
3. Iterasi adjacent pairs: hitung |v[i] - v[i-1]|
4. Track minimum

Bukti: Jika a ≤ b ≤ c (sorted), maka:
       |c - a| = |c - b| + |b - a| ≥ min(|c-b|, |b-a|)
       Jadi jarak non-adjacent selalu ≥ jarak adjacent terdekat.

🔄 ALTERNATIVE APPROACHES:
- Brute force O(N²): cek semua pair — TLE untuk N = 200,000
- Divide and conquer O(N log N): overkill untuk 1D, cocok untuk 2D
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Step 1: Baca input (long long karena bisa negatif & besar)
    int n;
    cin >> n;
    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    // Step 2: Sort
    sort(v.begin(), v.end());

    // Step 3: Cari minimum adjacent difference
    long long min_dist = LLONG_MAX;
    for (int i = 1; i < n; i++) {
        long long diff = v[i] - v[i - 1];  // pasti >= 0 karena sorted
        min_dist = min(min_dist, diff);
    }

    // Step 4: Output
    cout << min_dist << '\n';

    return 0;
}
