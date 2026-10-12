/*
============================================================
  Day 216 — Manacher | CP Template
============================================================
  MASALAH
    palindrom genap & ganjil punya jenis pusat berbeda
  SOLUSI
    T = # a # b # ... #   -> semua palindrom jadi GANJIL, |T| = 2n+1

  INTI (cermin = REFLEKSI, bandingkan dengan z-box yang translasi)
    if (i < r) p[i] = min(r - i, p[2*c - i]);
    while (aman && t[i-p[i]-1] == t[i+p[i]+1]) p[i]++;
    if (i + p[i] > r) { c = i; r = i + p[i]; }

  KONVERSI INDEKS  <- INI yang paling sering salah, bukan algoritmanya
    panjang palindrom asli = p[i]
    posisi awal di S       = (i - p[i]) / 2
    pusat untuk (l, r)     = l + r + 1
    S[l..r] palindrom      = p[l + r + 1] >= r - l + 1

  PERINGATAN
    Manacher menghitung KEMUNCULAN, bukan palindrom BERBEDA.
    "aaa" -> 6 kemunculan, tapi hanya 3 yang berbeda. Untuk distinct: Eertree.
    Total kemunculan bisa ~5e11 -> WAJIB long long.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. MANACHER (VERSI TRANSFORMASI) ────────────────────
// p[i] = radius pada T; panjang palindrom asli berpusat di i = p[i].
// Pakai SEP = '\1' kalau input boleh memuat '#'.

vector<int> manacher(const string& s, char SEP = '#') {
    string t(1, SEP);
    for (char c : s) { t += c; t += SEP; }

    int n = t.size();
    vector<int> p(n, 0);
    int c = 0, r = 0;                       // palindrom terkanan: pusat c, batas r

    for (int i = 0; i < n; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);         // cermin
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n
               && t[i - p[i] - 1] == t[i + p[i] + 1])       // ekspansi manual
            p[i]++;
        if (i + p[i] > r) { c = i; r = i + p[i]; }          // palindrom terkanan baru
    }
    return p;
}

// ─── 2. PEMBACAAN HASIL ──────────────────────────────────

// Substring palindrom terpanjang.
string palindromTerpanjang(const string& s) {
    if (s.empty()) return "";
    vector<int> p = manacher(s);
    int best = 0, pos = 0;
    for (int i = 0; i < (int)p.size(); i++)
        if (p[i] > best) { best = p[i]; pos = (i - p[i]) / 2; }
    return s.substr(pos, best);
}

// Total KEMUNCULAN substring palindrom (termasuk yang panjang 1).
ll totalPalindrom(const string& s) {
    vector<int> p = manacher(s);
    ll tot = 0;
    for (int v : p) tot += (v + 1) / 2;     // banyak suku deret v, v-2, v-4, ...
    return tot;
}

// ─── 3. QUERY O(1) ───────────────────────────────────────

struct CekPalindrom {
    vector<int> p;
    explicit CekPalindrom(const string& s) : p(manacher(s)) {}
    // l, r inklusif, 0-based pada S
    bool cek(int l, int r) const { return p[l + r + 1] >= r - l + 1; }
};

// ─── 4. AWALAN / AKHIRAN PALINDROMIK ─────────────────────

// Semua panjang awalan yang berupa palindrom (urut menaik).
vector<int> awalanPalindrom(const string& s) {
    vector<int> p = manacher(s), res;
    for (int i = 0; i < (int)p.size(); i++)
        if (i - p[i] == 0 && p[i] > 0) res.push_back(p[i]);
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

// Semua panjang akhiran yang berupa palindrom (urut menaik).
vector<int> akhiranPalindrom(const string& s) {
    int n = s.size();
    vector<int> p = manacher(s), res;
    for (int i = 0; i < (int)p.size(); i++)
        if (i + p[i] == 2 * n && p[i] > 0) res.push_back(p[i]);
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

// ─── 5. VERSI DUA ARRAY (n sangat besar, tanpa string baru) ──
// d1[i] = jumlah palindrom GANJIL berpusat di i   (terpanjang: 2*d1[i]-1)
// d2[i] = jumlah palindrom GENAP, pusat di celah SEBELUM i (terpanjang: 2*d2[i])
// Konvensi ini harus konsisten — jangan campur dengan sumber lain.

pair<vector<int>, vector<int>> manacher2(const string& s) {
    int n = s.size();
    vector<int> d1(n), d2(n);

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) { l = i - k; r = i + k; }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) { l = i - k - 1; r = i + k; }
    }
    return {d1, d2};
}

ll totalPalindrom2(const string& s) {
    auto pr = manacher2(s);
    ll t = 0;
    for (int v : pr.first)  t += v;
    for (int v : pr.second) t += v;
    return t;
}

// ─── 6. POLA UMUM: DP PARTISI PALINDROM ──────────────────
// Bagi s jadi bagian-bagian palindrom, minimalkan jumlah bagian. O(n^2).

int minPotonganPalindrom(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    CekPalindrom cp(s);
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (dp[j] != INT_MAX && cp.cek(j, i - 1))
                dp[i] = min(dp[i], dp[j] + 1);
    return dp[n];
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    string s;
    if (!(cin >> s)) return 0;

    cout << "terpanjang       : " << palindromTerpanjang(s) << '\n';
    cout << "total kemunculan : " << totalPalindrom(s) << '\n';
    cout << "cek versi 2array : " << totalPalindrom2(s) << '\n';
    cout << "min potongan     : " << minPotonganPalindrom(s) << '\n';

    return 0;
}
