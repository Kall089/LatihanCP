/*
 * Day 12 — Backtracking
 * File  : solution_5.cpp
 * Topik : Subset Sum — Ada/Tidak & Rekonstruksi
 * -----------------------------------------------
 * Cek apakah ada subset dari array yang jumlahnya = target. Jika ada, cetak salah satu subset tersebut.
 *
 * Input format  : Baris 1: n target
Baris 2: n bilangan positif
 * Output format : YES diikuti subset jika ada, NO jika tidak
 * Constraints   : 1 ≤ n ≤ 20, 1 ≤ A[i] ≤ 10^6, 1 ≤ target ≤ 10^7
 *
 * Sample Input 1:
 * 5 9
 * 3 1 4 2 7
 *
 * Sample Output 1:
 * YES
 * 3 1 4 1
 *
 * Sample Input 2:
 * 4 20
 * 1 5 3 4
 *
 * Sample Output 2:
 * NO
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, target;
vector<int> A;
vector<int> chosen;

bool backtrack(int idx, int remaining) {
    if (remaining == 0) return true;
    if (idx == n || remaining < 0) return false;

    // Ambil A[idx]
    chosen.push_back(A[idx]);
    if (backtrack(idx+1, remaining - A[idx])) return true;
    chosen.pop_back();

    // Skip A[idx]
    if (backtrack(idx+1, remaining)) return true;

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> target;
    A.resize(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    if (backtrack(0, target)) {
        cout << "YES\n";
        for (int x : chosen) cout << x << " ";
        cout << "\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
