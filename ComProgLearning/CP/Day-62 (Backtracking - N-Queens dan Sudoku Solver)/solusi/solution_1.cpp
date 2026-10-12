/*
 * Day 12 — Backtracking
 * File  : solution_1.cpp
 * Topik : Generate All Permutations
 * -----------------------------------------------
 * Generate semua permutasi dari bilangan 1..n secara backtracking (bukan next_permutation).
 *
 * Input format  : Satu bilangan n
 * Output format : Semua permutasi dalam urutan lexicographic, satu per baris
 * Constraints   : 1 ≤ n ≤ 8
 *
 * Sample Input 1:
 * 3
 *
 * Sample Output 1:
 * 1 2 3
 * 1 3 2
 * 2 1 3
 * 2 3 1
 * 3 1 2
 * 3 2 1
 *
 * Sample Input 2:
 * 2
 *
 * Sample Output 2:
 * 1 2
 * 2 1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> perm;
vector<bool> used;
int n;

void backtrack() {
    if ((int)perm.size() == n) {
        for (int i = 0; i < n; i++) cout << perm[i] << "\n"[i==n-1];
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            perm.push_back(i);
            backtrack();
            perm.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    used.assign(n+1, false);
    backtrack();
    return 0;
}
