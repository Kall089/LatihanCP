#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Backtracking Template:
//
// void backtrack(state, ...) {
//     if (goal reached) {
//         record/print solution;
//         return;
//     }
//     for (each choice) {
//         if (valid choice && pruning condition) {
//             make choice;       // modify state
//             backtrack(next state);
//             undo choice;       // restore state
//         }
//     }
// }
//
// Pruning Tips:
// - Sort candidates untuk early termination (if cands[i] > remaining break)
// - Track visited[] untuk permutasi
// - Mark grid sel sementara untuk DFS grid

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Kode di sini

    return 0;
}
