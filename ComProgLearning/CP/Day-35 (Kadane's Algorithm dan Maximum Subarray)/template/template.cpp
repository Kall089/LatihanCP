/*
============================================================
  Day 35 — Kadane's Algorithm | CP Template
============================================================
  INTI
    dp[i] = jumlah maksimum subarray yang BERAKHIR di i
          = max(dp[i-1] + a[i], a[i])
    "kalau beban yang dibawa dari belakang negatif, buang."

  PERTANYAAN PERTAMA SEBELUM MENULIS
    Subarray boleh KOSONG atau tidak?
      tidak boleh -> best = LLONG_MIN   <- default kebanyakan soal
      boleh       -> best = 0
    Ini satu-satunya hal yang membedakan AC dan WA di separuh soal Kadane.

  KAPAN BUKAN KADANE
    panjang dibatasi <= k  -> prefix + monotonic deque (Day 37)
    panjang tepat k        -> window ukuran tetap (Day 33)
    semua elemen >= 0 dan ada batas jumlah -> sliding window (Day 34)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. KADANE DASAR ─────────────────────────────────────
// Subarray TIDAK boleh kosong.

ll kadane(const vector<ll>& a) {
    ll best = LLONG_MIN, cur = 0;
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}

// Versi yang MEMPERBOLEHKAN subarray kosong (jawaban minimal 0).
ll kadaneBolehKosong(const vector<ll>& a) {
    ll best = 0, cur = 0;
    for (ll x : a) {
        cur = max(0LL, cur + x);
        best = max(best, cur);
    }
    return best;
}

// ─── 2. VERSI PREFIX SUM (setara, kadang lebih jelas) ────

ll kadanePrefix(const vector<ll>& a) {
    ll best = LLONG_MIN, minPre = 0, cur = 0;
    for (ll x : a) {
        cur += x;
        best = max(best, cur - minPre);   // hitung DULU
        minPre = min(minPre, cur);        // baru perbarui
    }
    return best;
}

// ─── 3. KADANE + INDEKS ──────────────────────────────────
// mengembalikan {jumlah, l, r}, l dan r inklusif 0-based

tuple<ll, int, int> kadaneIdx(const vector<ll>& a) {
    ll best = LLONG_MIN, cur = 0;
    int bl = 0, br = 0, curL = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (cur + a[i] < a[i]) { cur = a[i]; curL = i; }  // mulai baru
        else                     cur += a[i];
        if (cur > best) { best = cur; bl = curL; br = i; }
    }
    return {best, bl, br};
}

// ─── 4. VARIAN MELINGKAR ─────────────────────────────────

ll kadaneMelingkar(const vector<ll>& a) {
    ll total = 0, maxSum = LLONG_MIN, minSum = LLONG_MAX;
    ll curMax = 0, curMin = 0;
    for (ll x : a) {
        total += x;
        curMax = max(x, curMax + x); maxSum = max(maxSum, curMax);
        curMin = min(x, curMin + x); minSum = min(minSum, curMin);
    }
    if (maxSum < 0) return maxSum;        // semua negatif: jangan ambil yang kosong
    return max(maxSum, total - minSum);
}

// ─── 5. MAXIMUM PRODUCT SUBARRAY ─────────────────────────
// Kadane biasa GAGAL: minimum yang sangat negatif adalah ASET.

ll maxProduct(const vector<ll>& a) {
    ll best = a[0], curMax = a[0], curMin = a[0];
    for (int i = 1; i < (int)a.size(); i++) {
        ll x = a[i];
        if (x < 0) swap(curMax, curMin);  // negatif membalik peran
        curMax = max(x, curMax * x);
        curMin = min(x, curMin * x);
        best = max(best, curMax);
    }
    return best;
}

// ─── 6. BOLEH MENGHAPUS PALING BANYAK SATU ELEMEN ────────

ll maxSatuHapus(const vector<ll>& a) {
    if (a.size() == 1) return a[0];
    ll tanpaHapus = a[0], denganHapus = LLONG_MIN, best = a[0];
    for (int i = 1; i < (int)a.size(); i++) {
        denganHapus = max(denganHapus == LLONG_MIN ? LLONG_MIN : denganHapus + a[i],
                          tanpaHapus);          // hapus a[i], atau bawa yang sudah dihapus
        tanpaHapus  = max(tanpaHapus + a[i], a[i]);
        best = max(best, max(tanpaHapus, denganHapus));
    }
    return best;
}

// ─── 7. SUBMATRIKS DENGAN JUMLAH MAKSIMUM ────────────────
// Kunci baris atas & bawah -> masalah runtuh jadi 1D. O(R^2 * C).
// 300x300 -> 2.7e7 lolos.  1000x1000 -> 1e9 TIDAK lolos.

ll maxSubmatriks(const vector<vector<ll>>& g) {
    int R = g.size();
    if (R == 0) return 0;
    int C = g[0].size();
    ll best = LLONG_MIN;

    for (int atas = 0; atas < R; atas++) {
        vector<ll> kolom(C, 0);
        for (int bawah = atas; bawah < R; bawah++) {
            for (int c = 0; c < C; c++) kolom[c] += g[bawah][c];
            ll cur = 0, lokal = LLONG_MIN;
            for (int c = 0; c < C; c++) {
                cur = max(kolom[c], cur + kolom[c]);
                lokal = max(lokal, cur);
            }
            best = max(best, lokal);
        }
    }
    return best;
}

// ─── 8. NAIF (untuk stress test) ─────────────────────────

ll kadaneNaif(const vector<ll>& a) {
    int n = a.size();
    ll best = LLONG_MIN;
    for (int l = 0; l < n; l++) {
        ll s = 0;
        for (int r = l; r < n; r++) { s += a[r]; best = max(best, s); }
    }
    return best;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (ll& v : a) cin >> v;

    auto [jml, l, r] = kadaneIdx(a);

    cout << "kadane          : " << kadane(a) << '\n';
    cout << "  indeks        : [" << l << ", " << r << "] jumlah " << jml << '\n';
    cout << "boleh kosong    : " << kadaneBolehKosong(a) << '\n';
    cout << "melingkar       : " << kadaneMelingkar(a) << '\n';
    cout << "produk maksimum : " << maxProduct(a) << '\n';
    cout << "cek naif        : " << kadaneNaif(a) << '\n';

    return 0;
}
