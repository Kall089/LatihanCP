/*
============================================================
  Exercise 6: BFS Level Order Traversal (Queue Preview)
============================================================
Diberikan binary tree dalam format level-order: nilai node dipisah spasi,
-1 artinya null. Lakukan BFS dan cetak setiap level dalam satu baris.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^3 node

📎 SAMPLE INPUT:
  7
  1 2 3 4 5 -1 6

📎 SAMPLE OUTPUT:
  Level 0: 1
  Level 1: 2 3
  Level 2: 4 5 6

📎 SAMPLE INPUT 2:
  3
  5 3 8

📎 SAMPLE OUTPUT 2:
  Level 0: 5
  Level 1: 3 8

💡 HINT:
  Bangun tree dari array input. Gunakan queue untuk BFS.
  Track jumlah node per level: saat masuk level baru,
  proses tepat q.size() node (ukuran queue saat awal level).
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, left, right; // index ke array nodes (-1 = null)
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> vals(n);
    for (int i = 0; i < n; i++) cin >> vals[i];

    // Build tree: node i punya child di 2i+1 dan 2i+2
    // (hanya pakai nodes dengan vals != -1)

    queue<int> q; // menyimpan index
    if (n > 0 && vals[0] != -1) q.push(0);

    int level = 0;
    while (!q.empty()) {
        int sz = q.size();
        cout << "Level " << level << ": ";
        while (sz--) {
            int idx = q.front(); q.pop();
            cout << vals[idx];
            if (sz) cout << ' ';

            int l = 2*idx+1, r = 2*idx+2;
            if (l < n && vals[l] != -1) q.push(l);
            if (r < n && vals[r] != -1) q.push(r);
        }
        cout << "\n";
        level++;
    }
    return 0;
}
