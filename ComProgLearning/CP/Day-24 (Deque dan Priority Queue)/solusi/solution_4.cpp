/*
 * Day 39 — Priority Queue & Heap Applications
 * File  : solution_4.cpp
 * Topik : Find Median from Data Stream
 * -----------------------------------------------
 * Implementasikan struktur data yang dapat menambah angka dan query median kapan saja.
 *
 * Input format:
 * Baris 1: q (jumlah operasi)
Setiap baris: 'A x' (add x) atau 'M' (print median)
 *
 * Output format:
 * Setiap operasi 'M': cetak median (format N atau N.5)
 *
 * Constraints:
 * 1 ≤ q ≤ 10^5, -10^5 ≤ x ≤ 10^5
 *
 * Sample Input 1:
 * 5
 * A 1
 * A 2
 * M
 * A 3
 * M
 *
 * Sample Output 1:
 * 1.5
 * 2
 *
 * Sample Input 2:
 * 4
 * A 5
 * M
 * A 3
 * M
 *
 * Sample Output 2:
 * 5
 * 4
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

struct MedianFinder {
    priority_queue<int> maxH;                           // lower half
    priority_queue<int, vector<int>, greater<int>> minH; // upper half

    void addNum(int num) {
        maxH.push(num);
        // Balance: pindahkan max dari maxH ke minH
        minH.push(maxH.top()); maxH.pop();
        // Pastikan maxH.size() >= minH.size()
        if (maxH.size() < minH.size()) {
            maxH.push(minH.top()); minH.pop();
        }
    }

    double findMedian() {
        if (maxH.size() > minH.size()) return maxH.top();
        return (maxH.top() + minH.top()) / 2.0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> q;
    MedianFinder mf;
    while (q--) {
        char op; cin >> op;
        if (op == 'A') {
            int x; cin >> x;
            mf.addNum(x);
        } else {
            double med = mf.findMedian();
            if (med == (int)med) cout << (int)med << "\n";
            else cout << fixed << setprecision(1) << med << "\n";
        }
    }
    return 0;
}
