/*
============================================================
  Day 214 — Aplikasi Prefix Function | CP Template
============================================================
  SEMUANYA TURUNAN DARI SATU TABEL pi

    border terpanjang  = pi[n-1]
    semua border       = rantai pi[k-1] sampai 0
    periode terkecil   = n - pi[n-1]
    pengulangan utuh   = n % (n - pi[n-1]) == 0     <- JANGAN LUPA
    automaton          = while KMP di-unroll jadi tabel

  KAPAN AUTOMATON
    - teks berbentuk stream (tidak bisa mundur)
    - teks di-generate DP
    - butuh worst case O(1)/karakter
  HARGANYA  O(m * A) memori -> m besar = MLE, pakai KMP biasa
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll MOD = 1e9 + 7;

// ─── 1. FONDASI: TABEL PI ────────────────────────────────

vector<int> bangunPi(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// ─── 2. PERIODE & KOMPRESI ───────────────────────────────

// Periode terkecil. Selalu terdefinisi (paling buruk = n).
int periodeTerkecil(const string& s) {
    if (s.empty()) return 0;
    return (int)s.size() - bangunPi(s).back();
}

// Panjang blok terkecil yang bila diulang UTUH menghasilkan s.
// Kalau s bukan pengulangan utuh -> kembalikan n.
int blokKompresi(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    int k = n - bangunPi(s).back();
    return (n % k == 0) ? k : n;
}

// Berapa huruf minimal ditambahkan di akhir agar s jadi pengulangan utuh.
int tambahanAgarPeriodik(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    int k = n - bangunPi(s).back();
    return (n % k == 0) ? 0 : k - n % k;
}

// ─── 3. BORDER ───────────────────────────────────────────

// Semua panjang border, urut MENAIK (tidak termasuk 0 dan n).
vector<int> semuaBorder(const string& s) {
    vector<int> res;
    if (s.empty()) return res;
    vector<int> pi = bangunPi(s);
    int k = pi.back();
    while (k > 0) { res.push_back(k); k = pi[k - 1]; }
    reverse(res.begin(), res.end());
    return res;
}

// ─── 4. HITUNG KEMUNCULAN TIAP PREFIKS ───────────────────
// cnt[len] = berapa kali prefiks sepanjang len muncul sebagai substring.

vector<ll> hitungPrefiks(const string& s) {
    int n = s.size();
    vector<int> pi = bangunPi(s);
    vector<ll> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) cnt[pi[i]]++;
    for (int len = n; len > 0; len--) cnt[pi[len - 1]] += cnt[len];
    for (int len = 1; len <= n; len++) cnt[len]++;
    cnt[0] = 0;
    return cnt;
}

// ─── 5. KMP AUTOMATON ────────────────────────────────────
// aut[state][c] = state berikutnya. State = "sudah cocok berapa huruf".
// State |pola| berarti pola BARU SAJA ditemukan.
// Sentinel '#' membuat state terakhir aman diakses.

vector<array<int, 26>> bangunAutomaton(string pola, char basis = 'a') {
    pola += '#';
    int m = pola.size();
    vector<int> pi = bangunPi(pola);
    vector<array<int, 26>> aut(m);
    for (int i = 0; i < m; i++)
        for (int c = 0; c < 26; c++) {
            if (i > 0 && basis + c != pola[i]) aut[i][c] = aut[pi[i - 1]][c];
            else                               aut[i][c] = i + (basis + c == pola[i]);
        }
    return aut;
}

// Contoh pemakaian: hitung kemunculan pola di teks, tanpa menyimpan teks.
ll jalankanAutomaton(const vector<array<int, 26>>& aut, int m,
                     const string& teks, char basis = 'a') {
    ll hit = 0;
    int st = 0;
    for (char ch : teks) {
        st = aut[st][ch - basis];
        if (st == m) hit++;
    }
    return hit;
}

// ─── 6. DP DI ATAS AUTOMATON ─────────────────────────────
// Banyaknya string panjang L atas A huruf pertama yang TIDAK memuat pola.
// Untuk "HARUS memuat": jawabannya A^L - hasil fungsi ini.

ll hitungTanpaPola(int L, int A, const string& pola) {
    int m = pola.size();
    auto aut = bangunAutomaton(pola);
    vector<ll> dp(m, 0), nx;
    dp[0] = 1;
    for (int step = 0; step < L; step++) {
        nx.assign(m, 0);
        for (int s = 0; s < m; s++) {
            if (!dp[s]) continue;
            for (int c = 0; c < A; c++) {
                int t = aut[s][c];
                if (t == m) continue;           // pola muncul -> buang cabang
                nx[t] = (nx[t] + dp[s]) % MOD;
            }
        }
        dp.swap(nx);
    }
    ll tot = 0;
    for (ll v : dp) tot = (tot + v) % MOD;
    return tot;
}

// ─── 7. JUMLAH SUBSTRING BERBEDA (O(n^2), n <= ~5000) ────

ll jumlahSubstringBerbeda(const string& s) {
    ll total = 0;
    string cur;
    for (char ch : s) {
        cur += ch;
        string r(cur.rbegin(), cur.rend());
        vector<int> pi = bangunPi(r);
        int mx = 0;
        for (int v : pi) mx = max(mx, v);
        total += (ll)cur.size() - mx;
    }
    return total;
}

// ─── 8. TURUNAN LAIN ─────────────────────────────────────

// pi terakhir dari rev(s) + SEP + s = panjang AKHIRAN palindromik terpanjang.
// Sisanya harus dicerminkan DI AWAL. Arah ini SERING TERTUKAR — verifikasi
// dengan "aacecaaa": jawabannya 5 (di awal), sedangkan di akhir hanya 1.
int tambahanPalindromDepan(const string& s) {
    string r(s.rbegin(), s.rend());
    string t = r + '\1' + s;
    return (int)s.size() - bangunPi(t).back();
}

// Kebalikannya: huruf minimal ditambahkan DI AKHIR s agar s jadi palindrom.
int tambahanPalindromBelakang(const string& s) {
    string r(s.rbegin(), s.rend());
    string t = s + '\1' + r;
    return (int)s.size() - bangunPi(t).back();
}

// Prefiks terpanjang s yang juga sufiks t (dan panjangnya <= min(|s|,|t|)).
int overlap(const string& s, const string& t) {
    string g = s + '#' + t;
    return bangunPi(g).back();
}

// Apakah a adalah rotasi dari b?
bool rotasiDari(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    string g = a + '#' + b + b;
    for (int v : bangunPi(g)) if (v == (int)a.size()) return true;
    return false;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    string s;
    if (!(cin >> s)) return 0;

    cout << "periode terkecil : " << periodeTerkecil(s) << '\n';
    cout << "blok kompresi    : " << blokKompresi(s) << '\n';
    cout << "border           :";
    for (int b : semuaBorder(s)) cout << ' ' << b;
    cout << '\n';
    cout << "tambah di awal   : " << tambahanPalindromDepan(s) << '\n';
    cout << "tambah di akhir  : " << tambahanPalindromBelakang(s) << '\n';

    return 0;
}
