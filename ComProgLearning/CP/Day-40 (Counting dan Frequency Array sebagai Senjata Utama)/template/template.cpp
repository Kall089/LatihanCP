/*
============================================================
  Day 40 — Counting & Frequency Array | CP Template
============================================================
  PILIH ALAT
    domain nilai <= 1e6        -> ARRAY (1 ns per akses)
    domain besar, n kecil      -> kompresi (Day 38) lalu ARRAY
    online / domain tak dikenal -> map (~100 ns per akses)

    Untuk n = 1e6, selisih array vs map adalah 1 ms vs 100 ms.
    Itu selisih AC dan TLE.

  DUA POLA SAPUAN
    1) hitung dulu, baca kemudian
    2) PASANGAN: hitung SEBELUM mendaftarkan diri sendiri
       for (x : a) { hasil += cnt[pasangan(x)]; cnt[x]++; }
       Urutan ini otomatis menjamin: tidak berpasangan dengan diri
       sendiri, dan setiap pasangan terhitung tepat sekali.

  MULTI TEST CASE
    JANGAN memset seluruh array tiap kasus -> O(V) per kasus = TLE.
    Bersihkan per ELEMEN: for (x : a) cnt[x] = 0;
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int MAKS = 1000005;
int cnt[MAKS];              // GLOBAL: otomatis nol, tidak membebani stack

// ─── 1. FREKUENSI DASAR ──────────────────────────────────

void bangunFrekuensi(const vector<int>& a) {
    for (int x : a) cnt[x]++;
}

// Bersihkan HANYA slot yang dipakai. O(n), bukan O(MAKS).
void bersihkan(const vector<int>& a) {
    for (int x : a) cnt[x] = 0;
}

// ─── 2. MODE (nilai paling sering) ───────────────────────
// Kalau seri, mengembalikan nilai TERKECIL (karena memakai '>').

pair<int, int> mode(const vector<int>& a) {
    for (int x : a) cnt[x]++;
    int nilai = -1, terbanyak = 0;
    for (int x : a)
        if (cnt[x] > terbanyak || (cnt[x] == terbanyak && x < nilai)) {
            terbanyak = cnt[x];
            nilai = x;
        }
    for (int x : a) cnt[x] = 0;
    return {nilai, terbanyak};
}

// ─── 3. ANAGRAM ──────────────────────────────────────────

bool anagram(const string& s, const string& t) {
    if (s.size() != t.size()) return false;      // cek murah dulu
    int c[26] = {0};
    for (char ch : s) c[ch - 'a']++;
    for (char ch : t) if (--c[ch - 'a'] < 0) return false;
    return true;
}

// ─── 4. PASANGAN DENGAN SELISIH TEPAT K ──────────────────
// Menghitung pasangan indeks (i, j) dengan i < j dan |a[i]-a[j]| == K.

ll pasanganSelisih(const vector<int>& a, int K) {
    map<int, ll> c;
    ll hasil = 0;
    for (int x : a) {
        if (K == 0) {
            hasil += c[x];                       // K=0 HARUS dipisah,
        } else {                                 // kalau tidak terhitung 2x
            auto i1 = c.find(x - K); if (i1 != c.end()) hasil += i1->second;
            auto i2 = c.find(x + K); if (i2 != c.end()) hasil += i2->second;
        }
        c[x]++;                                  // daftarkan SETELAH menghitung
    }
    return hasil;
}

// ─── 5. PASANGAN DENGAN JUMLAH TEPAT K ───────────────────

ll pasanganJumlah(const vector<int>& a, ll K) {
    map<ll, ll> c;
    ll hasil = 0;
    for (int x : a) {
        auto it = c.find(K - x);
        if (it != c.end()) hasil += it->second;
        c[x]++;
    }
    return hasil;
}

// ─── 6. FREKUENSI -> PREFIX SUM (query rentang nilai) ────
// Setelah diubah, cnt[v] berarti "berapa elemen bernilai <= v".

void jadikanPrefix(int batas) {
    for (int v = 1; v <= batas; v++) cnt[v] += cnt[v - 1];
}

int banyakDalamRentang(int L, int R) {
    return cnt[R] - (L > 0 ? cnt[L - 1] : 0);
}

// ─── 7. FREKUENSI PREFIKS PER HURUF ──────────────────────
// pre[i][c] = berapa huruf c di dalam s[0..i-1].  Memori O(26n).

vector<array<int, 26>> prefiksHuruf(const string& s) {
    int n = s.size();
    vector<array<int, 26>> pre(n + 1);
    pre[0].fill(0);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i];
        pre[i + 1][s[i] - 'a']++;
    }
    return pre;
}

// berapa huruf c di dalam s[l..r], 0-based inklusif
int hitungHuruf(const vector<array<int, 26>>& pre, int l, int r, char c) {
    return pre[r + 1][c - 'a'] - pre[l][c - 'a'];
}

// ─── 8. FREKUENSI DARI FREKUENSI ─────────────────────────
// "berapa nilai yang muncul tepat k kali" -- dua lapis penghitungan.

map<int, int> frekuensiDariFrekuensi(const vector<int>& a) {
    map<int, int> c, hasil;
    for (int x : a) c[x]++;
    for (auto& pr : c) hasil[pr.second]++;
    return hasil;
}

// ─── 9. MAJORITY (Boyer-Moore, O(1) ruang) ───────────────
// Benar HANYA kalau dijamin ada elemen yang muncul > n/2 kali.
// Kalau tidak dijamin, hasilnya WAJIB diverifikasi ulang.

int majority(const vector<int>& a) {
    int kandidat = a[0], hitung = 0;
    for (int x : a) {
        if (hitung == 0) kandidat = x;
        hitung += (x == kandidat) ? 1 : -1;
    }
    int cek = 0;
    for (int x : a) cek += (x == kandidat);
    return (cek * 2 > (int)a.size()) ? kandidat : -1;   // -1 = tidak ada
}

// ─── 10. COUNTING SORT (pratinjau Day 46) ────────────────

void countingSort(vector<int>& a, int batas) {
    vector<int> c(batas + 1, 0);
    for (int x : a) c[x]++;
    int idx = 0;
    for (int v = 0; v <= batas; v++)
        while (c[v]--) a[idx++] = v;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    auto md = mode(a);
    cout << "mode              : " << md.first << " (" << md.second << " kali)\n";
    cout << "pasangan selisih 2: " << pasanganSelisih(a, 2) << '\n';
    cout << "pasangan jumlah 6 : " << pasanganJumlah(a, 6) << '\n';
    cout << "majority          : " << majority(a) << '\n';

    return 0;
}
