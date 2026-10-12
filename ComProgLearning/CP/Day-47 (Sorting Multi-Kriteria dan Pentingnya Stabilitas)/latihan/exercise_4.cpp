/*
 * Day 16 — Custom Comparator
 * File  : exercise_4.cpp
 * Topik : priority_queue dengan Custom Comparator (Min-Heap)
 * -----------------------------------------------
 * Implementasikan task scheduler: proses task dengan deadline terkecil dahulu. Gunakan min-heap dengan custom comparator.
 *
 * Input format  : Baris 1: n
Baris 2..n+1: name deadline
Baris n+2: k (jumlah task yang diproses)
 * Output format : k task yang diproses, dalam urutan diambil dari heap
 * Constraints   : 1 ≤ n ≤ 10^5, 1 ≤ k ≤ n
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    C 1
 * A 5                  E 2
 * B 3                  B 3
 * C 1
 * D 4
 * E 2
 * 3
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Task {
    string name;
    int deadline;
};

// TODO: Buat comparator functor untuk min-heap (deadline terkecil di atas)
// struct CompTask {
//     bool operator()(const Task& a, const Task& b) const {
//         return a.deadline > b.deadline; // min-heap: a lebih "rendah" jika deadline lebih besar
//     }
// };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    // TODO: Buat priority_queue dengan CompTask
    // priority_queue<Task, vector<Task>, CompTask> pq;

    for (int i = 0; i < n; i++) {
        string name; int d; cin >> name >> d;
        // pq.push({name, d});
    }

    int k; cin >> k;
    while (k--) {
        // auto t = pq.top(); pq.pop();
        // cout << t.name << " " << t.deadline << "\n";
    }

    return 0;
}
