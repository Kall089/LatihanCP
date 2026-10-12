/*
============================================================
TEMPLATE Day 148 — LIS
============================================================
Semua 0-INDEXED. Ingat: isi `tails` BUKAN LIS-nya; hanya ukurannya benar.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

// ------------------------------------------------------------------
// 1. LIS O(n^2) — mudah dimodifikasi (bobot, rekonstruksi, penghitungan)
//    dp[i] = panjang LIS yang BERAKHIR TEPAT di i
// ------------------------------------------------------------------
int lisN2(const vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
    return n ? *max_element(dp.begin(), dp.end()) : 0;   // max(dp), BUKAN dp[n-1]
}

// ------------------------------------------------------------------
// 2. LIS O(n log n) — KETAT NAIK  (lower_bound)
// ------------------------------------------------------------------
int lisStrict(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

// ------------------------------------------------------------------
// 3. LIS O(n log n) — TIDAK MENURUN  (upper_bound)
//    Uji: [1,1,1] -> lisStrict = 1, lisNonDec = 3
// ------------------------------------------------------------------
int lisNonDec(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

// ------------------------------------------------------------------
// 4. LDS (menurun terpanjang) — negasikan nilainya
// ------------------------------------------------------------------
int lds(vector<int> a) {
    for (int& x : a) x = -x;
    return lisStrict(a);
}

// ------------------------------------------------------------------
// 5. REKONSTRUKSI salah satu LIS (ketat naik), O(n log n)
// ------------------------------------------------------------------
vector<int> lisRebuild(const vector<int>& a) {
    int n = a.size();
    if (!n) return {};
    vector<int> tails, idx, par(n, -1);
    for (int i = 0; i < n; i++) {
        int p = lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin();
        if (p > 0) par[i] = idx[p - 1];
        if (p == (int)tails.size()) { tails.push_back(a[i]); idx.push_back(i); }
        else { tails[p] = a[i]; idx[p] = i; }
    }
    vector<int> res;
    for (int v = idx.back(); v != -1; v = par[v]) res.push_back(a[v]);
    reverse(res.begin(), res.end());
    return res;                    // BUKAN tails
}

// ------------------------------------------------------------------
// 6. MENGHITUNG BANYAK LIS — O(n^2)
//    pola: len[j]+1 >  len[i]  -> SALIN cnt
//          len[j]+1 == len[i]  -> TAMBAHKAN cnt
// ------------------------------------------------------------------
ll countLIS(const vector<int>& a) {
    int n = a.size();
    if (!n) return 0;
    vector<int> len(n, 1);
    vector<ll> cnt(n, 1);
    int best = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) {
                if (len[j] + 1 > len[i]) { len[i] = len[j] + 1; cnt[i] = cnt[j]; }
                else if (len[j] + 1 == len[i]) cnt[i] = (cnt[i] + cnt[j]) % MOD;
            }
        best = max(best, len[i]);
    }
    ll total = 0;
    for (int i = 0; i < n; i++) if (len[i] == best) total = (total + cnt[i]) % MOD;
    return total;
}

// ------------------------------------------------------------------
// 7. BOX STACKING / RUSSIAN DOLL
//    w MENAIK; kalau w SAMA, h MENURUN  <- tie-break terbalik itu WAJIB
// ------------------------------------------------------------------
int russianDoll(vector<pair<int,int>> box) {
    sort(box.begin(), box.end(), [](const pair<int,int>& A, const pair<int,int>& B) {
        if (A.first != B.first) return A.first < B.first;
        return A.second > B.second;                 // MENURUN saat w sama
    });
    vector<int> h;
    for (auto& b : box) h.push_back(b.second);
    return lisStrict(h);
}

// ------------------------------------------------------------------
// 8. LIS DUA ARAH — panjang "gunung" terpanjang yang berpuncak di i
//    pre[i] = LIS berakhir di i (dari kiri), suf[i] = LDS mulai di i
//    Berguna untuk LC 1671 dan soal "bitonic".
// ------------------------------------------------------------------
void lisBothSides(const vector<int>& a, vector<int>& pre, vector<int>& suf) {
    int n = a.size();
    pre.assign(n, 1); suf.assign(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) pre[i] = max(pre[i], pre[j] + 1);
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j > i; j--)
            if (a[j] < a[i]) suf[i] = max(suf[i], suf[j] + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // Salin bagian yang dibutuhkan ke solusimu.
    return 0;
}
