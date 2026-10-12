/*
============================================================
  Day 34 — Sliding Window Ukuran Variabel | CP Template
============================================================
  SYARAT PAKAI
    predikat harus MONOTON terhadap pelebaran window.
    Ada bilangan NEGATIF -> biasanya TIDAK monoton -> pakai
    prefix sum + map (Day 29), BUKAN sliding window.

  DUA KERANGKA (bedanya cuma letak baris "catat")

    TERPANJANG                     TERPENDEK
      masuk a[r]                     masuk a[r]
      while (TIDAK layak)            while (MASIH layak)
          keluar a[l], l++               catat (r-l+1)
      catat (r-l+1)                      keluar a[l], l++

  HITUNG BANYAK SUBARRAY
    hasil += r - l + 1      <- long long, bisa ~5e9 untuk n=1e5

  TEPAT K  =  atMost(K) - atMost(K-1)

  KENAPA O(n): l dan r HANYA MAJU, total gerakan <= 2n
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. TERPANJANG DENGAN JUMLAH <= S (elemen >= 0) ──────

int terpanjangJumlahMaks(const vector<ll>& a, ll S) {
    int n = a.size(), l = 0, best = 0;
    ll sum = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];                        // masuk
        while (sum > S) { sum -= a[l]; l++; }   // keluar sampai layak
        best = max(best, r - l + 1);        // catat SETELAH menyusut
    }
    return best;
}

// ─── 2. TERPENDEK DENGAN JUMLAH >= S (elemen >= 0) ───────
// Mengembalikan 0 kalau tidak ada yang memenuhi.

int terpendekJumlahMin(const vector<ll>& a, ll S) {
    int n = a.size(), l = 0, best = INT_MAX;
    ll sum = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum >= S) {
            best = min(best, r - l + 1);    // catat SEBELUM menyusut
            sum -= a[l];
            l++;
        }
    }
    return (best == INT_MAX) ? 0 : best;
}

// ─── 3. TERPANJANG TANPA ELEMEN BERULANG ─────────────────

int terpanjangUnik(const vector<int>& a) {
    unordered_map<int, int> lastSeen;       // nilai -> indeks terakhir
    int l = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        auto it = lastSeen.find(a[r]);
        if (it != lastSeen.end() && it->second >= l)  // syarat >= l WAJIB
            l = it->second + 1;                       // supaya l tidak MUNDUR
        lastSeen[a[r]] = r;
        best = max(best, r - l + 1);
    }
    return best;
}

// Versi string dengan alfabet kecil (lebih cepat).
int terpanjangUnikStr(const string& s) {
    vector<int> lastSeen(256, -1);
    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        unsigned char c = s[r];
        if (lastSeen[c] >= l) l = lastSeen[c] + 1;
        lastSeen[c] = r;
        best = max(best, r - l + 1);
    }
    return best;
}

// ─── 4. PALING BANYAK K JENIS BERBEDA ────────────────────

int terpanjangAtMostK(const vector<int>& a, int K) {
    if (K <= 0) return 0;
    unordered_map<int, int> cnt;
    int l = 0, best = 0, jenis = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        if (cnt[a[r]]++ == 0) jenis++;      // masuk
        while (jenis > K) {
            if (--cnt[a[l]] == 0) jenis--;  // keluar
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}

// ─── 5. MENGHITUNG BANYAK SUBARRAY ───────────────────────
// Banyaknya subarray dengan PALING BANYAK K jenis berbeda.

ll atMostKJenis(const vector<int>& a, int K) {
    if (K < 0) return 0;
    unordered_map<int, int> cnt;
    ll hasil = 0;
    int l = 0, jenis = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        if (cnt[a[r]]++ == 0) jenis++;
        while (jenis > K) {
            if (--cnt[a[l]] == 0) jenis--;
            l++;
        }
        hasil += r - l + 1;                 // semua subarray berakhir di r
    }
    return hasil;
}

// Banyaknya subarray dengan TEPAT K jenis berbeda.
ll tepatKJenis(const vector<int>& a, int K) {
    return atMostKJenis(a, K) - atMostKJenis(a, K - 1);
}

// ─── 6. BANYAK SUBARRAY DENGAN JUMLAH <= S (elemen >= 0) ─

ll atMostJumlah(const vector<ll>& a, ll S) {
    if (S < 0) return 0;
    int l = 0;
    ll sum = 0, hasil = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > S) { sum -= a[l]; l++; }
        hasil += r - l + 1;
    }
    return hasil;
}

// Banyak subarray dengan jumlah TEPAT S (elemen >= 0 saja!).
ll tepatJumlah(const vector<ll>& a, ll S) {
    return atMostJumlah(a, S) - atMostJumlah(a, S - 1);
}

// ─── 7. BOLEH MENGGANTI PALING BANYAK K KARAKTER ─────────
// Substring terpanjang berisi huruf sama setelah <= K penggantian.

int terpanjangSetelahGanti(const string& s, int K) {
    vector<int> cnt(26, 0);
    int l = 0, best = 0, maxFreq = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        maxFreq = max(maxFreq, ++cnt[s[r] - 'A']);
        while ((r - l + 1) - maxFreq > K) { cnt[s[l] - 'A']--; l++; }
        best = max(best, r - l + 1);
    }
    return best;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    ll S;
    if (!(cin >> n >> S)) return 0;
    vector<ll> a(n);
    vector<int> ai(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; ai[i] = (int)a[i]; }

    cout << "terpanjang sum <= S : " << terpanjangJumlahMaks(a, S) << '\n';
    cout << "terpendek  sum >= S : " << terpendekJumlahMin(a, S) << '\n';
    cout << "terpanjang unik     : " << terpanjangUnik(ai) << '\n';
    cout << "banyak sum <= S     : " << atMostJumlah(a, S) << '\n';

    return 0;
}
