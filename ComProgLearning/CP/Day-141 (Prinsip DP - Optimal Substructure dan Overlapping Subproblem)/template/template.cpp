/*
============================================================
  Day 85 — Konsep DP & DP 1D | CP Template
============================================================
  TIGA PERTANYAAN SEBELUM MENULIS KODE:
    1. STATE    : dp[i] artinya apa? (tulis sebagai kalimat!)
    2. TRANSISI : dp[i] dihitung dari state mana?
    3. BASIS    : nilai terkecil berapa?

  POLA TRANSISI:
    "berapa cara"     -> dp[i] = dp[i-1] + dp[i-2]
    "maksimum"        -> dp[i] = max(dp[i-1], dp[i-2] + a[i])
    "minimal langkah" -> dp[i] = min(dp[i], dp[j] + 1)
    "bisa/tidak"      -> dp[i] = dp[i-1] || dp[i-k]
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;
const int INF = 1e9;
const int MAXN = 1000005;

// ─── 1. MEMOISASI (TOP-DOWN) ─────────────────────────────
// Pakai -1 sebagai penanda "belum dihitung", JANGAN 0
// (karena 0 bisa jadi jawaban yang sah).

ll memo[MAXN];

ll fibMemo(int n) {
    if (n <= 1) return n;                     // basis
    if (memo[n] != -1) return memo[n];        // sudah ada di catatan
    return memo[n] = (fibMemo(n - 1) + fibMemo(n - 2)) % MOD;
}
// Pemakaian: memset(memo, -1, sizeof(memo)); lalu fibMemo(n);

// ─── 2. TABULASI (BOTTOM-UP) ─────────────────────────────

ll fibTab(int n) {
    vector<ll> dp(n + 1);
    dp[0] = 0;                                 // basis
    if (n >= 1) dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD; // transisi
    return dp[n];
}

// ─── 3. ROLLING VARIABLE (MEMORI O(1)) ───────────────────

ll fibHemat(int n) {
    if (n <= 1) return n;
    ll dua = 0, satu = 1;
    for (int i = 2; i <= n; i++) {
        ll kini = (dua + satu) % MOD;
        dua = satu;
        satu = kini;
    }
    return satu;
}

// ─── 4. POLA "BERAPA CARA" — NAIK TANGGA ─────────────────
// dp[i] = banyaknya cara mencapai tangga ke-i

ll naikTangga(int n, const vector<int>& langkah) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;                                  // basis: 1 cara untuk diam
    for (int i = 1; i <= n; i++)
        for (int l : langkah)
            if (i - l >= 0) dp[i] = (dp[i] + dp[i - l]) % MOD;
    return dp[n];
}

// ─── 5. POLA "MAKSIMUM" — HOUSE ROBBER ───────────────────
// dp[i] = untung maksimum dari elemen 1..i (tidak boleh dua bertetangga)

ll houseRobber(const vector<ll>& a, int n) {
    vector<ll> dp(n + 1, 0);
    if (n >= 1) dp[1] = max(0LL, a[1]);
    for (int i = 2; i <= n; i++)
        dp[i] = max(dp[i - 1],                  // lewati elemen ke-i
                    dp[i - 2] + a[i]);          // ambil elemen ke-i
    return dp[n];
}

// ─── 6. POLA "MINIMAL" — COIN CHANGE ─────────────────────
// dp[v] = jumlah koin minimal untuk membentuk nilai v

int coinChangeMin(const vector<int>& koin, int target) {
    vector<int> dp(target + 1, INF);
    dp[0] = 0;                                   // basis
    for (int v = 1; v <= target; v++)
        for (int k : koin)
            if (k <= v && dp[v - k] != INF)
                dp[v] = min(dp[v], dp[v - k] + 1);
    return dp[target] == INF ? -1 : dp[target];
}

// ─── 7. POLA "BERAPA CARA" — COIN CHANGE (KOMBINASI) ─────
// PERHATIKAN urutan loop! koin di LUAR = kombinasi ({1,2} == {2,1})

ll coinChangeCaraKombinasi(const vector<int>& koin, int target) {
    vector<ll> dp(target + 1, 0);
    dp[0] = 1;
    for (int k : koin)
        for (int v = k; v <= target; v++)
            dp[v] = (dp[v] + dp[v - k]) % MOD;
    return dp[target];
}

// nilai di LUAR = permutasi ({1,2} != {2,1})
ll coinChangeCaraPermutasi(const vector<int>& koin, int target) {
    vector<ll> dp(target + 1, 0);
    dp[0] = 1;
    for (int v = 1; v <= target; v++)
        for (int k : koin)
            if (k <= v) dp[v] = (dp[v] + dp[v - k]) % MOD;
    return dp[target];
}

// ─── 8. REKONSTRUKSI JAWABAN (bukan cuma nilainya) ───────

vector<int> jalurHouseRobber(const vector<ll>& a, int n) {
    vector<ll> dp(n + 1, 0);
    vector<int> dari(n + 1, 0);
    if (n >= 1) { dp[1] = a[1]; dari[1] = 0; }
    for (int i = 2; i <= n; i++) {
        if (dp[i - 1] >= dp[i - 2] + a[i]) { dp[i] = dp[i - 1];        dari[i] = i - 1; }
        else                               { dp[i] = dp[i - 2] + a[i]; dari[i] = i - 2; }
    }
    vector<int> ambil;
    for (int i = n; i >= 1; ) {
        if (dari[i] == i - 2 || i == 1) { ambil.push_back(i); i -= 2; }
        else i--;
    }
    reverse(ambil.begin(), ambil.end());
    return ambil;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;

    cout << "fib(" << n << ") = " << fibHemat(n) << "\n";
    cout << "cara naik tangga (1/2 langkah) = " << naikTangga(n, {1, 2}) << "\n";

    return 0;
}
