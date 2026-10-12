/*
============================================================
  Exercise 6: Trapping Rain Water
============================================================
Diberikan peta ketinggian (elevation map) dengan n blok.
Setiap blok punya lebar 1 unit. Hitung total volume air hujan
yang tertampung di antara blok-blok tersebut.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - 0 ≤ h[i] ≤ 10^4

📎 SAMPLE INPUT:
  12
  0 1 0 2 1 0 1 3 2 1 2 1

📎 SAMPLE OUTPUT:
  6

📎 SAMPLE INPUT 2:
  6
  4 2 0 3 2 5

📎 SAMPLE OUTPUT 2:
  9

💡 HINT:
  - Air di posisi i = min(max_kiri, max_kanan) - h[i]
  - Pendekatan 1: precompute left_max[] dan right_max[]
  - Pendekatan 2: Two pointer O(n) O(1) space
  - Pendekatan 3: Monotonic stack
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    // Pendekatan: precompute left_max dan right_max
    vector<int> left_max(n), right_max(n);

    // TODO: hitung left_max[i] = max(h[0..i])
    // TODO: hitung right_max[i] = max(h[i..n-1])

    ll total = 0;
    for (int i = 0; i < n; i++) {
        int water = min(left_max[i], right_max[i]) - h[i];
        if (water > 0) total += water;
    }

    cout << total << "\n";
    return 0;
}
