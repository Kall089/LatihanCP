/*
============================================================
  Day 34 — KMP | CP Template
============================================================
  ARTI pi[i]
    panjang awalan TERPANJANG dari p[0..i] yang juga menjadi
    akhirannya, tetapi bukan seluruh potongan itu sendiri.

  INTI KMP
    j = pi[j - 1];     // satu baris ini seluruh keajaibannya
    indeks teks TIDAK PERNAH mundur -> O(n + m)

  TURUNAN LANGSUNG dari pi
    border terpanjang = pi[n-1]
    semua border      = rantai pi[k-1] sampai 0
    periode terkecil  = n - pi[n-1]
    pengulangan utuh  = n % (n - pi[n-1]) == 0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. FAILURE FUNCTION (TABEL PI) ──────────────────────

vector<int> bangunPi(const string& p) {
    int m = p.size();
    vector<int> pi(m, 0);                  // pi[0] selalu 0

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];                 // sudah cocok berapa huruf
        while (j > 0 && p[i] != p[j])      // mundur ke border lebih pendek
            j = pi[j - 1];
        if (p[i] == p[j]) j++;             // cocok -> bertambah 1
        pi[i] = j;
    }
    return pi;
}

// ─── 2. PENCARIAN POLA ───────────────────────────────────
// Mengembalikan semua posisi awal kemunculan (0-based).
// Kemunculan tumpang tindih ikut terhitung.

vector<int> cariKMP(const string& teks, const string& pola) {
    vector<int> hasil;
    int n = teks.size(), m = pola.size();
    if (m == 0 || m > n) return hasil;

    vector<int> pi = bangunPi(pola);
    int j = 0;

    for (int i = 0; i < n; i++) {          // i tidak pernah mundur
        while (j > 0 && teks[i] != pola[j]) j = pi[j - 1];
        if (teks[i] == pola[j]) j++;
        if (j == m) {
            hasil.push_back(i - m + 1);
            j = pi[j - 1];                 // BUKAN j = 0, agar overlap terhitung
        }
    }
    return hasil;
}

// ─── 3. TRIK PENGGABUNGAN (tanpa fungsi cari terpisah) ───
// Pemisah '#' wajib karakter yang tidak muncul di kedua string.

vector<int> cariGabung(const string& teks, const string& pola) {
    string g = pola + '#' + teks;
    vector<int> pi = bangunPi(g), hasil;
    int m = pola.size();
    for (int i = m + 1; i < (int)g.size(); i++)
        if (pi[i] == m) hasil.push_back(i - 2 * m);   // 0-based pada teks
    return hasil;
}

// ─── 4. SEMUA BORDER (rantai pi) ─────────────────────────

vector<int> semuaBorder(const string& s) {
    vector<int> pi = bangunPi(s), b;
    int k = pi.empty() ? 0 : pi.back();
    while (k > 0) {                        // border dari border juga border
        b.push_back(k);
        k = pi[k - 1];
    }
    reverse(b.begin(), b.end());           // urut menaik
    return b;
}

// ─── 5. PERIODE ──────────────────────────────────────────

int periodeTerkecil(const string& s) {
    vector<int> pi = bangunPi(s);
    return (int)s.size() - (pi.empty() ? 0 : pi.back());
}

bool pengulanganUtuh(const string& s) {
    int n = s.size(), p = periodeTerkecil(s);
    return p < n && n % p == 0;
}

// ─── 6. HITUNG KEMUNCULAN TIAP PREFIKS ───────────────────
// cnt[i] = berapa kali prefiks sepanjang (i+1) muncul di dalam s

vector<ll> hitungPrefiks(const string& s) {
    int n = s.size();
    vector<int> pi = bangunPi(s);
    vector<ll> cnt(n, 1);                  // tiap prefiks minimal muncul sekali

    // WAJIB mundur: kontribusi prefiks panjang turun ke border-nya
    for (int i = n - 1; i > 0; i--)
        if (pi[i] > 0) cnt[pi[i] - 1] += cnt[i];

    return cnt;
}

// ─── 7. KMP AUTOMATON (untuk DP di atas string) ──────────
// aut[j][c] = keadaan berikutnya kalau sudah cocok j huruf lalu bertemu huruf c

vector<array<int,26>> bangunAutomaton(const string& p) {
    int m = p.size();
    vector<int> pi = bangunPi(p);
    vector<array<int,26>> aut(m + 1);
    for (int j = 0; j <= m; j++)
        for (int c = 0; c < 26; c++) {
            if (j < m && c == p[j] - 'a') aut[j][c] = j + 1;
            else aut[j][c] = (j == 0 ? 0 : aut[pi[j - 1]][c]);
        }
    return aut;
}

// ─── 8. TURUNAN LAIN ─────────────────────────────────────

// Apakah b merupakan rotasi dari a?
bool rotasi(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    return !cariKMP(a + a, b).empty();
}

// Berapa huruf minimal ditambahkan DI DEPAN agar s jadi palindrom?
int tambahJadiPalindrom(const string& s) {
    string t = s;
    reverse(t.begin(), t.end());
    vector<int> pi = bangunPi(s + '#' + t);
    return (int)s.size() - pi.back();
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    string teks, pola;
    if (!(cin >> teks >> pola)) return 0;

    vector<int> pos = cariKMP(teks, pola);
    cout << "kemunculan : " << pos.size() << "\n";
    for (int p : pos) cout << p + 1 << " ";      // cetak 1-based
    cout << "\n";

    vector<int> pi = bangunPi(teks);
    cout << "pi teks    : ";
    for (int x : pi) cout << x << " ";
    cout << "\n";
    cout << "periode    : " << periodeTerkecil(teks) << "\n";

    return 0;
}
