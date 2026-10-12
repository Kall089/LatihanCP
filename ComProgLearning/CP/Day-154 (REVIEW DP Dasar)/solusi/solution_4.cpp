/*
============================================================
✅ Solution 4: Pembagian Cerita Bergambar Terpanjang (LCS + Lexicographical Reconstruction)
============================================================
Approach: 2D Suffix DP + Next Occurrence Array (Greedy Forward)
Complexity: Time O(|S| * |T| + 26 * (|S| + |T|)) | Space O(|S| * |T|)
Key Insight:
1. Mengapa Suffix DP?
   Jika kita mencari string yang leksikografis terkecil dari depan ke belakang,
   kita ingin membuat keputusan terbaik pada karakter pertama, lalu karakter kedua, dst.
   Suffix DP dp[i][j] menyatakan panjang LCS dari sufiks S[i..N-1] dan T[j..M-1].
   Dengan cara ini, saat berada di state (i, j), kita tahu persis apakah mengambil
   karakter tertentu akan mempertahankan panjang LCS optimal.

2. Prekomputasi Posisi Karakter Berikutnya:
   Agar pencarian karakter 'a'..'z' cepat, buat tabel:
   next_s[i][c] = kemunculan pertama karakter c di S pada indeks >= i.
   next_t[j][c] = kemunculan pertama karakter c di T pada indeks >= j.

3. Rekonstruksi Maju Greedy:
   Dari state saat ini (cur_i, cur_j):
   Iterasi c dari 'a' sampai 'z':
     Cari pi = next_s[cur_i][c] dan pj = next_t[cur_j][c].
     Jika pi dan pj valid, dan 1 + dp[pi + 1][pj + 1] == dp[cur_i][cur_j]:
       Karakter c adalah pilihan leksikografis terkecil yang valid!
       Tambahkan c ke hasil, perbarui cur_i = pi + 1, cur_j = pj + 1, lalu break.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    int n = s.size();
    int m = t.size();

    // 1. Suffix DP: dp[i][j] = panjang LCS dari s[i..n-1] dan t[j..m-1]
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (s[i] == t[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }

    int max_lcs = dp[0][0];
    cout << max_lcs << "\n";

    if (max_lcs == 0) {
        cout << "\n";
        return 0;
    }

    // 2. Prekomputasi kemunculan karakter berikutnya
    vector<vector<int>> next_s(n + 1, vector<int>(26, -1));
    for (int c = 0; c < 26; c++) {
        int last = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] - 'a' == c) last = i;
            next_s[i][c] = last;
        }
    }

    vector<vector<int>> next_t(m + 1, vector<int>(26, -1));
    for (int c = 0; c < 26; c++) {
        int last = -1;
        for (int j = m - 1; j >= 0; j--) {
            if (t[j] - 'a' == c) last = j;
            next_t[j][c] = last;
        }
    }

    // 3. Rekonstruksi Leksikografis Terkecil
    int cur_i = 0, cur_j = 0;
    string lcs_str = "";

    while (cur_i < n && cur_j < m && dp[cur_i][cur_j] > 0) {
        int target = dp[cur_i][cur_j];
        for (int c = 0; c < 26; c++) {
            int pi = next_s[cur_i][c];
            int pj = next_t[cur_j][c];

            if (pi != -1 && pj != -1 && 1 + dp[pi + 1][pj + 1] == target) {
                lcs_str += (char)('a' + c);
                cur_i = pi + 1;
                cur_j = pj + 1;
                break;
            }
        }
    }

    cout << lcs_str << "\n";

    return 0;
}
