/*
 * Day 22 — Aritmatika Modular
 * Template C++ berisi seluruh utilitas modular yang dipakai hari ini.
 *
 * Copy fungsi yang dibutuhkan ke solusimu. Simpan file ini —
 * modpow dan norm akan terpakai terus sampai Day 150.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;      // alternatif umum: 998244353
const ll INF = 1e18;         // WAJIB ll, bukan int

// ──────────────────────────────────────────────────────────────────
// 1. OPERASI MODULAR DASAR
// Asumsi: a, b sudah di [0, MOD). Kalau belum, pakai norm() dulu.
// ──────────────────────────────────────────────────────────────────

// Normalisasi ke [0, m-1] — WAJIB untuk input yang mungkin negatif
ll norm(ll a, ll m = MOD) { return ((a % m) + m) % m; }

ll addmod(ll a, ll b, ll m = MOD) { return (a + b) % m; }
ll submod(ll a, ll b, ll m = MOD) { return (a - b + m) % m; }   // +m cegah negatif
ll mulmod(ll a, ll b, ll m = MOD) { return (a % m) * (b % m) % m; }

// Versi cepat tanpa operator % (berguna di loop panas)
// % butuh ~20-40 cycle, conditional subtract jauh lebih murah
inline void addTo(ll &a, ll b, ll m = MOD) { a += b; if (a >= m) a -= m; }
inline void subFrom(ll &a, ll b, ll m = MOD) { a -= b; if (a < 0) a += m; }

// ──────────────────────────────────────────────────────────────────
// 2. BINARY EXPONENTIATION — a^b mod m dalam O(log b)
// JANGAN pakai pow() dari <cmath> (double, hilang presisi)
// ──────────────────────────────────────────────────────────────────

ll modpow(ll base, ll exp, ll m = MOD) {
    ll result = 1 % m;              // 1%m menangani kasus m == 1
    base %= m;
    if (base < 0) base += m;
    while (exp > 0) {
        if (exp & 1) result = result * base % m;    // bit menyala → kalikan
        base = base * base % m;                     // kuadratkan
        exp >>= 1;
    }
    return result;
}

// Versi rekursif (setara, O(log b) stack)
// ll modpowRec(ll b, ll e, ll m) {
//     if (e == 0) return 1 % m;
//     ll half = modpowRec(b, e / 2, m);
//     ll res = half * half % m;
//     if (e & 1) res = res * (b % m) % m;
//     return res;
// }

// ──────────────────────────────────────────────────────────────────
// 3. PERKALIAN AMAN UNTUK MODULUS BESAR (m sampai ~9×10^18)
// Perlu ketika m > ~3×10^9, karena a*b overflow long long
// ──────────────────────────────────────────────────────────────────

ll mulmodBig(ll a, ll b, ll m) {
    return (ll)((__int128)a * b % m);
}

// Alternatif portable tanpa __int128 — O(log b)
ll mulmodBinary(ll a, ll b, ll m) {
    ll res = 0;
    a %= m; if (a < 0) a += m;
    while (b > 0) {
        if (b & 1) { res += a; if (res >= m) res -= m; }
        a += a; if (a >= m) a -= m;
        b >>= 1;
    }
    return res;
}

// ──────────────────────────────────────────────────────────────────
// 4. MODULO BILANGAN RAKSASA (input berupa string)
// Horner's rule: N = (((d0*10 + d1)*10 + d2)*10 + ...)
// ──────────────────────────────────────────────────────────────────

ll bigMod(const string& s, ll m = MOD) {
    ll res = 0;
    for (char c : s) res = (res * 10 + (c - '0')) % m;
    return res;
}

// ──────────────────────────────────────────────────────────────────
// 5. FAKTORIAL MODULAR (precompute untuk banyak query)
// Fondasi untuk nCr di Day 26-27
// ──────────────────────────────────────────────────────────────────

// const int MAXN = 1000005;
// ll fact[MAXN];
// void precomputeFact(int n = MAXN - 1) {
//     fact[0] = 1;
//     for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
// }

// ──────────────────────────────────────────────────────────────────
// 6. PREFIX SUM MODULAR + RANGE QUERY
// Pitfall #1 di contest: lupa +MOD saat mengurangkan
// ──────────────────────────────────────────────────────────────────

// vector<ll> pre(n + 1, 0);
// for (int i = 1; i <= n; i++)
//     pre[i] = ((pre[i-1] + A[i]) % MOD + MOD) % MOD;
// ll rangeSum = (pre[r] - pre[l-1] + MOD) % MOD;      // +MOD WAJIB

// ──────────────────────────────────────────────────────────────────
// 7. DERET GEOMETRI TANPA PEMBAGIAN — 1 + a + ... + a^(n-1)
// Rumus tertutup butuh inverse; divide & conquer tidak
// ──────────────────────────────────────────────────────────────────

ll geoSum(ll a, ll n, ll m = MOD) {
    if (n == 0) return 0;
    if (n & 1) return (geoSum(a, n - 1, m) + modpow(a, n - 1, m)) % m;
    ll half = geoSum(a, n / 2, m);
    return half * ((1 + modpow(a, n / 2, m)) % m) % m;
}

// ──────────────────────────────────────────────────────────────────
// 8. PREVIEW DAY 27 — MODULAR INVERSE (hanya jika MOD PRIMA)
// Fermat: a^(p-1) ≡ 1 → a^(-1) ≡ a^(p-2) (mod p)
// ──────────────────────────────────────────────────────────────────

ll modinv(ll a, ll m = MOD) { return modpow(a, m - 2, m); }   // m harus PRIMA
ll divmod(ll a, ll b, ll m = MOD) { return a % m * modinv(b, m) % m; }

// ──────────────────────────────────────────────────────────────────
// CHECKLIST SEBELUM SUBMIT SOAL MODULAR
//   [ ] Semua variabel modular bertipe long long?
//   [ ] Setiap pengurangan punya +MOD?
//   [ ] Setiap perkalian sudah dalam konteks long long (bukan int*int)?
//   [ ] Input yang mungkin negatif sudah di-norm()?
//   [ ] MOD dideklarasikan sebagai const ll, bukan const int?
//   [ ] Tidak ada pembagian langsung (/) pada nilai modular?
//   [ ] Output akhir berada di [0, MOD-1]?
// ──────────────────────────────────────────────────────────────────

void solve() {
    // Solusi untuk satu test case
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;   // Uncomment jika multi test case
    while (t--) solve();

    return 0;
}
