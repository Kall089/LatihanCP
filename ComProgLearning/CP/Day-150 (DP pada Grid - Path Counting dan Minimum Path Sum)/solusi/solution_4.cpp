/*
============================================================
✅ Solution 4: Jalur Minimum + Rekonstruksi
============================================================
Approach: tabel penuh, lalu telusuri balik dari sudut kanan-bawah
Complexity: Time O(R*C) | Space O(R*C)
Key Insight: Tabel DP sudah menyimpan seluruh informasi jejak secara tersirat.
             Di setiap sel cukup bertanya: "tetangga mana yang lebih kecil?"
             Itulah dari mana nilai sel ini berasal.

📖 ATURAN PENELUSURAN dari (i, j):
   i == 0                  -> hanya bisa dari kiri   -> j--
   j == 0                  -> hanya bisa dari atas   -> i--
   dp[i-1][j] <= dp[i][j-1]-> dari atas              -> i--
   selain itu              -> dari kiri              -> j--

⚠️ LOOP-NYA (i > 0 || j > 0), BUKAN &&.
   Kalau salah satu indeks sudah 0, sisanya TETAP harus ditelusuri sampai
   mencapai (0,0). Memakai && akan menghentikan penelusuran di tepi dan
   menghasilkan jalur yang terpotong. Sampel 3 (satu baris) menguji ini.

⚠️ REKONSTRUKSI MEMBUTUHKAN TABEL PENUH.
   Rolling array O(C) membuang informasi baris sebelumnya, sehingga
   penelusuran mustahil. Ini trade-off yang harus kamu sadari SEBELUM memilih
   optimasi memori -- bukan setelah kodenya jadi.

⚠️ JAWABANNYA TIDAK UNIK. Kalau dua arah memberi nilai yang sama, keduanya
   menghasilkan jalur optimal yang sah. Jangan bandingkan output dengan satu
   jalur tetap.

⚠️ KASUS 1x1. Loop tidak pernah berjalan; jalurnya hanya (0,0). Pastikan
   kodemu tetap mencetaknya. Sampel 2 mengujinya.

VERIFIKASI SAMPEL 1:
   dp = 1  4  5
        2  7  6
        6  8  7
   mulai (2,2): dp[1][2]=6 <= dp[2][1]=8 -> naik ke (1,2)
        (1,2): dp[0][2]=5 <= dp[1][1]=7 -> naik ke (0,2)
        (0,2): i == 0 -> ke kiri (0,1) -> (0,0)
   jalur: (0,0) (0,1) (0,2) (1,2) (2,2), total 1+3+1+1+1 = 7  ✓

🔄 ALTERNATIVE APPROACHES:
- Simpan array arah saat mengisi tabel: penelusuran jadi trivial, memori
  bertambah satu tabel char. Berguna kalau rekurensnya rumit sehingga
  perbandingan ulang tidak bisa diandalkan.
- Kalau butuh rekonstruksi DENGAN memori linear, ada teknik divide and conquer
  ala Hirschberg (lihat Day 149) -- jarang diminta untuk grid.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    cin >> R >> C;
    vector<vector<ll>> a(R, vector<ll>(C));
    for (auto& row : a) for (auto& x : row) cin >> x;

    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i-1][j]);
            if (j > 0) best = min(best, dp[i][j-1]);
            dp[i][j] = a[i][j] + best;
        }

    vector<pair<int,int>> path;
    int i = R - 1, j = C - 1;
    while (i > 0 || j > 0) {                        // "||", BUKAN "&&"
        path.push_back({i, j});
        if (i == 0)                        j--;
        else if (j == 0)                   i--;
        else if (dp[i-1][j] <= dp[i][j-1]) i--;
        else                               j--;
    }
    path.push_back({0, 0});
    reverse(path.begin(), path.end());

    cout << dp[R-1][C-1] << '\n';
    for (size_t k = 0; k < path.size(); k++)
        cout << '(' << path[k].first << ',' << path[k].second << ')'
             << " \n"[k + 1 == path.size()];
    return 0;
}
