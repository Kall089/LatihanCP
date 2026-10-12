/*
 * Day 12 — Backtracking
 * File  : exercise_3.cpp
 * Topik : Combination Sum — Elemen Boleh Diulang
 * -----------------------------------------------
 * Temukan semua kombinasi unik dari kandidat (boleh diulang) yang jumlahnya = target.
 *
 * Input format  : Baris 1: n target
 *                 Baris 2: n kandidat (distinct, positif)
 * Output format : Setiap kombinasi dalam satu baris (sorted, tanpa duplikat)
 * Constraints   : 1 ≤ n ≤ 30, 1 ≤ target ≤ 40, 1 ≤ candidates[i] ≤ 40
 *
 * Sample Input 1:      Sample Output 1:
 * 4 7                  2 2 3
 * 2 3 6 7              7
 *
 * Sample Input 2:      Sample Output 2:
 * 3 8                  2 2 2 2
 * 2 3 5                2 3 3
 *                      3 5
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int>> result;
vector<int> current;

void backtrack(vector<int>& cands, int start, int target) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    // TODO: Coba setiap kandidat dari index start
    // for (int i = start; i < (int)cands.size(); i++) {
    //     if (cands[i] > target) break; // pruning: cands harus sorted!
    //     current.push_back(cands[i]);
    //     backtrack(cands, i, target - cands[i]); // i bukan i+1: boleh ulang
    //     current.pop_back();                      // undo
    // }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, target; cin >> n >> target;
    vector<int> cands(n);
    for (int i = 0; i < n; i++) cin >> cands[i];
    sort(cands.begin(), cands.end()); // PENTING untuk pruning

    backtrack(cands, 0, target);

    for (auto& combo : result) {
        for (int i = 0; i < (int)combo.size(); i++)
            cout << combo[i] << " \n"[i==(int)combo.size()-1];
    }
    return 0;
}
