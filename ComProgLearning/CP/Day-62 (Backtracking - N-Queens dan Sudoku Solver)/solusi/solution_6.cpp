/*
 * Day 12 — Backtracking
 * File  : solution_6.cpp
 * Topik : Word Search di Grid 2D
 * -----------------------------------------------
 * Cari apakah kata target ada di grid karakter. Bisa bergerak ke 4 arah (U/D/L/R), tiap sel hanya dipakai sekali.
 *
 * Input format  : Baris 1: R C
Baris 2..R+1: grid
Baris R+2: kata
 * Output format : YES atau NO
 * Constraints   : 1 ≤ R,C ≤ 6, 1 ≤ |kata| ≤ 10
 *
 * Sample Input 1:
 * 3 4
 * ABCE
 * SFCS
 * ADEE
 * ABCCED
 *
 * Sample Output 1:
 * YES
 *
 * Sample Input 2:
 * 3 4
 * ABCE
 * SFCS
 * ADEE
 * ABCB
 *
 * Sample Output 2:
 * NO
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int R, C;
vector<string> grid;
string word;
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

bool dfs(int r, int c, int idx) {
    if (idx == (int)word.size()) return true;
    if (r<0||r>=R||c<0||c>=C||grid[r][c]!=word[idx]) return false;

    char tmp = grid[r][c];
    grid[r][c] = '#';

    for (int d = 0; d < 4; d++)
        if (dfs(r+dr[d], c+dc[d], idx+1)) {
            grid[r][c] = tmp;
            return true;
        }

    grid[r][c] = tmp;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    grid.resize(R);
    for (int i = 0; i < R; i++) cin >> grid[i];
    cin >> word;

    bool found = false;
    for (int r = 0; r < R && !found; r++)
        for (int c = 0; c < C && !found; c++)
            if (dfs(r, c, 0)) found = true;

    cout << (found ? "YES" : "NO") << "\n";
    return 0;
}
