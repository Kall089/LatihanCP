/*
============================================================
  Day 215 — Z-Function | CP Template
============================================================
  ARTI z[i]
    panjang awalan bersama antara S dan S[i..n-1]
    z[0] = 0  (konvensi template ini — JANGAN diubah setengah jalan)

  INTI (konvensi r EKSKLUSIF: s[l..r-1] terbukti = awalan S)
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r) { l = i; r = i + z[i]; }

  KENAPA O(n)
    setiap perbandingan manual yang berhasil mendorong r maju,
    dan r tidak pernah mundur -> total dorongan <= n

  TURUNAN LANGSUNG
    border         : z[i] == n - i
    periode kecil  : i terkecil dengan z[i] == n - i
    kompresi       : + syarat n % i == 0
    cari pola      : z pada P + SEP + T, cek z[i] >= |P|

  SEPARATOR
    pakai '\1' bukan '#'. '#' bisa saja muncul di input.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const char SEP = '\1';

// ─── 1. Z-ARRAY ──────────────────────────────────────────

vector<int> bangunZ(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;                       // z-box: s[l..r-1]
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);          // salin dari kembaran
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])   // perluas manual
            z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }       // z-box baru
    }
    return z;
}

// ─── 2. PENCARIAN POLA ───────────────────────────────────
// Semua posisi awal (0-based). Tumpang tindih ikut terhitung.

vector<int> cariZ(const string& teks, const string& pola) {
    vector<int> hasil;
    int m = pola.size(), n = teks.size();
    if (m == 0 || m > n) return hasil;

    string g = pola + SEP + teks;
    vector<int> z = bangunZ(g);
    for (int i = m + 1; i < (int)g.size(); i++)
        if (z[i] >= m) hasil.push_back(i - m - 1);
    return hasil;
}

// ─── 3. BORDER, PERIODE, KOMPRESI ────────────────────────

// Semua panjang border, urut MENAIK.
vector<int> semuaBorderZ(const string& s) {
    int n = s.size();
    vector<int> z = bangunZ(s), res;
    for (int i = 1; i < n; i++)
        if (z[i] == n - i) res.push_back(n - i);
    reverse(res.begin(), res.end());        // i naik -> panjang border turun
    return res;
}

// Periode terkecil (paling buruk = n).
int periodeTerkecilZ(const string& s) {
    int n = s.size();
    vector<int> z = bangunZ(s);
    for (int i = 1; i < n; i++)
        if (z[i] == n - i) return i;
    return n;
}

// Blok terkecil yang bila diulang UTUH menghasilkan s.
int blokKompresiZ(const string& s) {
    int n = s.size();
    vector<int> z = bangunZ(s);
    for (int i = 1; i < n; i++)
        if (n % i == 0 && z[i] == n - i) return i;
    return n;
}

// ─── 4. ROTASI ───────────────────────────────────────────

bool rotasiDari(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    if (a.empty()) return true;
    string g = a + SEP + b + b;
    vector<int> z = bangunZ(g);
    int m = a.size();
    for (int i = m + 1; i + m <= (int)g.size(); i++)
        if (z[i] >= m) return true;
    return false;
}

// ─── 5. JUMLAH SUBSTRING BERBEDA (O(n^2), n <= ~5000) ────

ll substringBerbedaZ(const string& s) {
    ll total = 0;
    string cur;
    for (char ch : s) {
        cur += ch;
        string r(cur.rbegin(), cur.rend());
        vector<int> z = bangunZ(r);
        int mx = 0;
        for (int v : z) mx = max(mx, v);
        total += (ll)cur.size() - mx;
    }
    return total;
}

// ─── 6. TUMPANG TINDIH DUA STRING ────────────────────────
// Panjang sufiks a yang sekaligus prefiks b, maksimal.

int overlap(const string& a, const string& b) {
    if (a.empty() || b.empty()) return 0;
    string g = b + SEP + a;
    int n = g.size(), m = b.size();
    vector<int> z = bangunZ(g);
    int best = 0;
    for (int i = m + 1; i < n; i++)
        if (z[i] == n - i) best = max(best, min((int)m, n - i));
    return best;
}

// ─── 7. KONVERSI z -> pi ─────────────────────────────────

vector<int> piDariZ(const vector<int>& z) {
    int n = z.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++)
        if (z[i] > 0) pi[i + z[i] - 1] = max(pi[i + z[i] - 1], z[i]);
    for (int i = n - 2; i >= 0; i--)
        pi[i] = max(pi[i], pi[i + 1] - 1);
    return pi;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    string s;
    if (!(cin >> s)) return 0;

    vector<int> z = bangunZ(s);
    cout << "z                :";
    for (int v : z) cout << ' ' << v;
    cout << '\n';
    cout << "periode terkecil : " << periodeTerkecilZ(s) << '\n';
    cout << "blok kompresi    : " << blokKompresiZ(s) << '\n';
    cout << "border           :";
    for (int b : semuaBorderZ(s)) cout << ' ' << b;
    cout << '\n';

    return 0;
}
