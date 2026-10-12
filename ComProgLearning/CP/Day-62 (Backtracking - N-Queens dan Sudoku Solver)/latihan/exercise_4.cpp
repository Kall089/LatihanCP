/*
 * Day 12 — Backtracking
 * File  : exercise_4.cpp
 * Topik : N-Queens Problem
 * -----------------------------------------------
 * Tempatkan N ratu di papan catur N×N sehingga tidak ada dua ratu yang saling serang. Hitung semua solusi.
 *
 * Input format  : Satu bilangan n
 * Output format : Jumlah total solusi
 * Constraints   : 1 ≤ n ≤ 13
 *
 * Sample Input 1:
 * 4
 *
 * Sample Output 1:
 * 2
 *
 * Sample Input 2:
 * 8
 *
 * Sample Output 2:
 * 92
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int solutions = 0;

// Gunakan bitmask untuk efisiensi: cols, diag1, diag2
// cols: kolom yang sudah terisi
// diag1: diagonal kiri-atas ke kanan-bawah (row - col)
// diag2: diagonal kanan-atas ke kiri-bawah (row + col)

void solve(int row, vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2) {
    // Base case
    if (row == n) {
        solutions++;
        return;
    }

    // TODO: Coba tempatkan ratu di setiap kolom pada baris ini
    // for (int col = 0; col < n; col++) {
    //     // Cek apakah posisi (row, col) aman
    //     if (cols[col] || diag1[row-col+n] || diag2[row+col]) continue;
    //
    //     // Tandai
    //     cols[col] = diag1[row-col+n] = diag2[row+col] = true;
    //     solve(row+1, cols, diag1, diag2);
    //     // Undo
    //     cols[col] = diag1[row-col+n] = diag2[row+col] = false;
    // }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    vector<bool> cols(n, false), diag1(2*n, false), diag2(2*n, false);
    solve(0, cols, diag1, diag2);
    cout << solutions << "\n";
    return 0;
}
