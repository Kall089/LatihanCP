/*
============================================================
TEMPLATE Day 149 — LCS & Edit Distance
============================================================
KONVENSI: tabel (n+1) x (m+1) 1-INDEXED; string 0-INDEXED.
Huruf terakhir prefiks i adalah a[i-1]. Ini sumber bug nomor satu.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------------------------------
// 1. LCS — panjang saja, O(n*m) waktu & memori
// ------------------------------------------------------------------
int lcsLen(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    return dp[n][m];
}

// ------------------------------------------------------------------
// 2. LCS — memori O(min(n,m)) dengan rolling array
//    TIDAK BISA direkonstruksi. Simpan diagonal SEBELUM ditimpa.
// ------------------------------------------------------------------
int lcsRolling(string a, string b) {
    if (a.size() < b.size()) swap(a, b);       // gulung dimensi yang KECIL
    int n = a.size(), m = b.size();
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        int prevDiag = 0;                      // = dp[i-1][j-1]
        for (int j = 1; j <= m; j++) {
            int simpan = dp[j];                // masih dp[i-1][j]
            if (a[i-1] == b[j-1]) dp[j] = prevDiag + 1;
            else                  dp[j] = max(dp[j], dp[j-1]);
            prevDiag = simpan;
        }
    }
    return dp[m];
}

// ------------------------------------------------------------------
// 3. LCS — rekonstruksi barisannya
// ------------------------------------------------------------------
string lcsString(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) { res += a[i-1]; i--; j--; }
        else if (dp[i-1][j] >= dp[i][j-1]) i--;
        else j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

// ------------------------------------------------------------------
// 4. EDIT DISTANCE (Levenshtein)
//    BASE-NYA BUKAN NOL: dp[i][0] = i, dp[0][j] = j
// ------------------------------------------------------------------
int editDistance(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;     // hapus semua
    for (int j = 0; j <= m; j++) dp[0][j] = j;     // sisipkan semua
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];               // gratis
            else dp[i][j] = 1 + min({ dp[i-1][j-1],   // GANTI
                                      dp[i-1][j],     // HAPUS a[i-1]
                                      dp[i][j-1] });  // SISIP b[j-1]
    return dp[n][m];
}

// ------------------------------------------------------------------
// 5. EDIT DISTANCE — daftar operasinya
// ------------------------------------------------------------------
vector<string> editOps(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});

    vector<string> ops;
    int i = n, j = m;
    while (i > 0 || j > 0) {                     // "||", BUKAN "&&"
        if (i > 0 && j > 0 && a[i-1] == b[j-1]) { i--; j--; }          // cocok DULU
        else if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + 1) {
            ops.push_back(string("GANTI ") + a[i-1] + " -> " + b[j-1]); i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + 1) {
            ops.push_back(string("HAPUS ") + a[i-1]); i--;
        } else {
            ops.push_back(string("SISIP ") + b[j-1]); j--;
        }
    }
    reverse(ops.begin(), ops.end());
    return ops;
}

// ------------------------------------------------------------------
// 6. LONGEST COMMON SUBSTRING (berdekatan)
//    beda -> RESET 0 ; jawaban = MAX SELURUH TABEL
// ------------------------------------------------------------------
int lcSubstring(const string& a, const string& b, int& endA) {
    int n = a.size(), m = b.size(), best = 0; endA = -1;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else                  dp[i][j] = 0;              // RESET
            if (dp[i][j] > best) { best = dp[i][j]; endA = i; }
        }
    return best;
}

// ------------------------------------------------------------------
// 7. TURUNAN LANGSUNG DARI LCS
// ------------------------------------------------------------------
int minDeletions(const string& a, const string& b) {         // hanya sisip/hapus
    return (int)a.size() + (int)b.size() - 2 * lcsLen(a, b);
}
int scsLength(const string& a, const string& b) {            // supersequence terpendek
    return (int)a.size() + (int)b.size() - lcsLen(a, b);
}

// 7b. Rekonstruksi SCS
string scsString(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) { res += a[i-1]; i--; j--; }
        else if (dp[i-1][j] >= dp[i][j-1]) { res += a[i-1]; i--; }
        else { res += b[j-1]; j--; }
    }
    while (i > 0) { res += a[i-1]; i--; }
    while (j > 0) { res += b[j-1]; j--; }
    reverse(res.begin(), res.end());
    return res;
}

// ------------------------------------------------------------------
// 8. EDIT DISTANCE DENGAN BIAYA BERBEDA
//    Kalau cr > ci + cd, min() otomatis memilih hapus+sisip.
// ------------------------------------------------------------------
long long editWeighted(const string& a, const string& b,
                       long long ci, long long cd, long long cr) {
    int n = a.size(), m = b.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = 1LL * i * cd;
    for (int j = 0; j <= m; j++) dp[0][j] = 1LL * j * ci;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = min({ dp[i-1][j-1] + (a[i-1] == b[j-1] ? 0 : cr),
                             dp[i-1][j] + cd,
                             dp[i][j-1] + ci });
    return dp[n][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // Salin bagian yang dibutuhkan ke solusimu.
    return 0;
}
