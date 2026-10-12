/*
============================================================
  Day 33 — String Hashing | CP Template
============================================================
  RUMUS INTI
    hash(s) = SUM s[i] * p^i   (mod m)
    prefix : h[i+1] = h[i] + (s[i]-'a'+1) * p[i]
    substr : get(l, r) = h[r+1] - h[l]      (masih berbobot p^l)
    banding: get(a,b)*p[c] == get(c,d)*p[a] (kalikan silang, jangan bagi)

  ATURAN WAJIB
    1. Semua variabel long long (perkalian bisa 10^18)
    2. Petakan huruf ke 1..26, JANGAN 0..25
    3. Tambahkan +M sebelum modulo pada pengurangan
    4. n > 10^4 atau ada fase hack -> pakai HashGanda
============================================================
*/
#include <bits/stdc++.h>
#include <unordered_set>   // sebagian bits/stdc++.h tidak memuatnya
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. HASH TUNGGAL (cukup untuk n kecil / tanpa hack) ──

const ll P = 131;              // base: prima, harus > ukuran alfabet
const ll M = 1000000009;       // mod: prima besar

struct Hash {
    int n;
    vector<ll> h, p;           // h[i] = hash s[0..i-1], p[i] = P^i

    Hash() : n(0) {}

    explicit Hash(const string& s) : n(s.size()), h(n + 1, 0), p(n + 1, 1) {
        for (int i = 0; i < n; i++) {
            h[i + 1] = (h[i] + (ll)(s[i] - 'a' + 1) * p[i]) % M;
            p[i + 1] = p[i] * P % M;
        }
    }

    // Hash mentah s[l..r], masih berbobot p^l
    ll get(int l, int r) const {
        if (l > r) return 0;
        return (h[r + 1] - h[l] + M) % M;
    }

    // Hash s[l..r] yang sudah dinormalkan ke bobot p^0.
    // Dipakai kalau hash perlu dimasukkan ke set / map.
    // Caranya: kalikan dengan p^(n-l) supaya semua panjang sama punya acuan sama.
    ll getNormal(int l, int r) const {
        return get(l, r) * p[n - l] % M;
    }

    // Apakah s[a..b] == s[c..d]? Panjang harus sama.
    bool sama(int a, int b, int c, int d) const {
        if (b - a != d - c) return false;
        return get(a, b) * p[c] % M == get(c, d) * p[a] % M;
    }
};

// ─── 2. HASH GANDA (aman dari anti-hash test) ────────────

struct HashGanda {
    static const ll M1 = 1000000007, M2 = 998244353;
    ll P1, P2;
    int n;
    vector<ll> h1, h2, p1, p2;

    explicit HashGanda(const string& s) : n(s.size()),
        h1(n + 1, 0), h2(n + 1, 0), p1(n + 1, 1), p2(n + 1, 1) {
        // Base acak: lawan tidak bisa menyiapkan anti-hash test lebih dulu
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        P1 = 131 + (ll)(rng() % 50) * 2;
        P2 = 137 + (ll)(rng() % 50) * 2;

        for (int i = 0; i < n; i++) {
            ll c = s[i] - 'a' + 1;
            h1[i + 1] = (h1[i] + c * p1[i]) % M1;
            h2[i + 1] = (h2[i] + c * p2[i]) % M2;
            p1[i + 1] = p1[i] * P1 % M1;
            p2[i + 1] = p2[i] * P2 % M2;
        }
    }

    pair<ll,ll> get(int l, int r) const {
        if (l > r) return {0, 0};
        return {(h1[r + 1] - h1[l] + M1) % M1, (h2[r + 1] - h2[l] + M2) % M2};
    }

    // Dinormalkan -> aman dimasukkan ke set / unordered_set
    pair<ll,ll> getNormal(int l, int r) const {
        auto [a, b] = get(l, r);
        return {a * p1[n - l] % M1, b * p2[n - l] % M2};
    }

    bool sama(int a, int b, int c, int d) const {
        if (b - a != d - c) return false;
        auto x = get(a, b), y = get(c, d);
        return x.first  * p1[c] % M1 == y.first  * p1[a] % M1
            && x.second * p2[c] % M2 == y.second * p2[a] % M2;
    }
};

// ─── 3. RABIN-KARP: cari semua kemunculan pola ───────────

vector<int> rabinKarp(const string& teks, const string& pola) {
    vector<int> hasil;
    int n = teks.size(), m = pola.size();
    if (m == 0 || m > n) return hasil;

    Hash ht(teks);
    ll hp = 0, pw = 1;
    for (int i = 0; i < m; i++) {
        hp = (hp + (ll)(pola[i] - 'a' + 1) * pw) % M;
        pw = pw * P % M;
    }

    for (int i = 0; i + m <= n; i++)
        if (ht.get(i, i + m - 1) == hp * ht.p[i] % M)
            hasil.push_back(i);          // kemunculan tumpang tindih ikut terhitung
    return hasil;
}

// ─── 4. CEK PALINDROM SUBSTRING (hash maju + mundur) ─────

struct HashPalindrom {
    int n;
    Hash maju, mundur;

    explicit HashPalindrom(const string& s) : n(s.size()), maju(s), mundur(balik(s)) {}

    static string balik(string s) { reverse(s.begin(), s.end()); return s; }

    // Apakah s[l..r] palindrom?
    bool cek(int l, int r) const {
        // s[l..r] pada string terbalik menempati [n-1-r .. n-1-l]
        int l2 = n - 1 - r, r2 = n - 1 - l;
        return maju.get(l, r) * mundur.p[l2] % M
            == mundur.get(l2, r2) * maju.p[l] % M;
    }
};

// ─── 5. SUBSTRING BERULANG TERPANJANG (binary search) ────

int substringBerulangTerpanjang(const string& s) {
    int n = s.size();
    HashGanda hg(s);

    auto ada = [&](int len) {
        if (len == 0) return true;
        set<pair<ll,ll>> terlihat;
        for (int i = 0; i + len <= n; i++) {
            auto k = hg.getNormal(i, i + len - 1);
            if (terlihat.count(k)) return true;
            terlihat.insert(k);
        }
        return false;
    };

    int lo = 0, hi = n - 1, jawab = 0;
    while (lo <= hi) {                  // sifatnya monoton -> binary search
        int mid = (lo + hi) / 2;
        if (ada(mid)) { jawab = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    return jawab;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    string s;
    if (!(cin >> s)) return 0;

    Hash h(s);
    cout << "panjang            : " << s.size() << "\n";
    cout << "hash seluruh string: " << h.get(0, s.size() - 1) << "\n";
    cout << "substring berulang terpanjang: " << substringBerulangTerpanjang(s) << "\n";

    return 0;
}
