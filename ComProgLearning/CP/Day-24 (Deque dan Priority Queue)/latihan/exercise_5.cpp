/*
 * Day 39 — Priority Queue & Heap Applications
 * File  : exercise_5.cpp
 * Topik : K Closest Points to Origin
 * -----------------------------------------------
 * Temukan K titik terdekat ke origin (0,0) dari sekumpulan titik.
 *
 * Input format:
 * Baris 1: n k
Baris berikutnya: n pasang x y
 *
 * Output format:
 * K baris, masing-masing x y (urutan bebas)
 *
 * Constraints:
 * 1 ≤ k ≤ n ≤ 10^4, -10^4 ≤ x,y ≤ 10^4
 *
 * Sample Input 1:
 * 3 2
 * 1 3
 * -2 2
 * 0 1
 *
 * Sample Output 1:
 * 0 1
 * -2 2
 *
 * Sample Input 2:
 * 4 2
 * 3 3
 * 5 -1
 * -2 4
 * 0 2
 *
 * Sample Output 2:
 * 0 2
 * -2 4
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> pts(n);
    for (auto& [x,y] : pts) cin >> x >> y;

    // TODO: Temukan K titik terdekat ke origin
    // Hint: Gunakan max-heap ukuran K berdasarkan jarak kuadrat
    // priority_queue<pair<int,pii>> maxPQ; // (dist2, {x,y})
    // Pertahankan K elemen terkecil

    // cetak K titik
    return 0;
}
