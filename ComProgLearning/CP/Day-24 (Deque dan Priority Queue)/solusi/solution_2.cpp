/*
 * Day 39 — Priority Queue & Heap Applications
 * File  : solution_2.cpp
 * Topik : Merge K Sorted Lists (arrays)
 * -----------------------------------------------
 * Gabungkan K array yang sudah terurut menjadi satu array terurut. Gunakan min-heap.
 *
 * Input format:
 * Baris 1: K (jumlah list)
Baris berikutnya: setiap list diawali panjang, diikuti elemen
 *
 * Output format:
 * Semua elemen terurut dalam satu baris
 *
 * Constraints:
 * 1 ≤ K ≤ 100, total elemen ≤ 10^5
 *
 * Sample Input 1:
 * 3
 * 3 1 4 7
 * 2 2 5
 * 3 3 6 9
 *
 * Sample Output 1:
 * 1 2 3 4 5 6 7 9
 *
 * Sample Input 2:
 * 2
 * 2 1 3
 * 2 2 4
 *
 * Sample Output 2:
 * 1 2 3 4
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K;
    cin >> K;
    vector<vector<int>> lists(K);
    for (int i = 0; i < K; i++) {
        int sz; cin >> sz;
        lists[i].resize(sz);
        for (int j = 0; j < sz; j++) cin >> lists[i][j];
    }

    // min-heap: (nilai, list_idx, elemen_idx)
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    for (int i = 0; i < K; i++)
        if (!lists[i].empty())
            pq.push({lists[i][0], i, 0});

    bool first = true;
    while (!pq.empty()) {
        auto [val, li, ei] = pq.top(); pq.pop();
        if (!first) cout << " ";
        cout << val;
        first = false;
        if (ei + 1 < (int)lists[li].size())
            pq.push({lists[li][ei+1], li, ei+1});
    }
    cout << "\n";
    return 0;
}
