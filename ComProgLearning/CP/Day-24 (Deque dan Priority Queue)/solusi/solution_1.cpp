/*
 * Day 39 — Priority Queue & Heap Applications
 * File  : solution_1.cpp
 * Topik : Kth Largest Element in Array
 * -----------------------------------------------
 * Temukan elemen terbesar ke-K dari array. Gunakan min-heap ukuran K.
 *
 * Input format:
 * Baris 1: n k
Baris 2: n bilangan bulat
 *
 * Output format:
 * Satu bilangan: elemen terbesar ke-K
 *
 * Constraints:
 * 1 ≤ k ≤ n ≤ 10^5, -10^4 ≤ A[i] ≤ 10^4
 *
 * Sample Input 1:
 * 6 2
 * 3 2 1 5 6 4
 *
 * Sample Output 1:
 * 5
 *
 * Sample Input 2:
 * 4 4
 * 3 2 3 1
 *
 * Sample Output 2:
 * 1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int kthLargest(vector<int>& A, int k) {
    // min-heap ukuran K — top = elemen terkecil dari K terbesar
    priority_queue<int, vector<int>, greater<int>> minPQ;
    for (int x : A) {
        minPQ.push(x);
        if ((int)minPQ.size() > k) minPQ.pop();
    }
    return minPQ.top();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    cout << kthLargest(A, k) << "\n";
    return 0;
}
