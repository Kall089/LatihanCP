/*
 * Day 39 — Priority Queue & Heap Applications
 * File  : exercise_2.cpp
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

    // TODO: Merge K sorted arrays menggunakan min-heap
    // Hint: simpan (nilai, list_idx, elemen_idx) di PQ
    // priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;

    vector<int> result;
    // ... isi result
    for (int x : result) cout << x << " ";
    cout << "\n";
    return 0;
}
