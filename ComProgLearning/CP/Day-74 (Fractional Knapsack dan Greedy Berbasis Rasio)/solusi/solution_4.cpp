/*
============================================================
✅ SOLUSI Exercise 4: Knapsack Bertingkat
============================================================
Difficulty: Medium | Kompleksitas: O(W * sum(log c[i])) ~ O(n*W*log c)

── KENAPA PENDEKATAN NAIF GAGAL ────────────────────────────
Memperlakukan tiap buah sebagai barang terpisah menghasilkan
sampai n * max(c) = 100 * 10^4 = 10^6 barang. Dikalikan
W = 10^4 menjadi 10^10 operasi. Jauh terlalu lambat.

── DEKOMPOSISI BINER ───────────────────────────────────────
Pecah c[i] buah menjadi potongan berukuran 1, 2, 4, 8, ... dan
satu potongan sisa. Setiap potongan diperlakukan sebagai satu
barang 0/1 dengan berat w[i]*ukuran dan nilai v[i]*ukuran.

Kenapa ini tidak kehilangan apa pun: dengan potongan
1, 2, 4, ..., 2^(k-1) dan sisa r, setiap bilangan dari 0 sampai
c[i] bisa dibentuk sebagai jumlah sebagian potongan.
  - bilangan 0..2^k - 1 : representasi biner biasa
  - bilangan 2^k..c[i]  : ambil potongan sisa r, lalu bentuk
                          selisihnya dari potongan biner
                          (selisihnya <= 2^k - 1, jadi selalu bisa)

Jumlah potongan per jenis adalah O(log c[i]) = paling banyak
sekitar 14 untuk c = 10^4. Total barang menjadi 100 * 14 = 1400,
dikalikan W = 10^4 menjadi 1.4 * 10^7 operasi. Sangat cepat.

── POTONGAN TERAKHIR ───────────────────────────────────────
Potongan terakhir TIDAK selalu berupa pangkat dua. Kode di
bawah memakai min(k, cnt) sehingga totalnya selalu tepat c[i].
Menuliskannya sebagai pangkat dua terus-menerus akan
menghasilkan jumlah yang melebihi c[i] — bug yang menghasilkan
jawaban terlalu besar dan sulit dilacak.

── ALTERNATIF: DP MONOTONIC DEQUE ──────────────────────────
Bounded knapsack juga bisa diselesaikan O(n*W) dengan deque
monoton (Day 37), memanfaatkan bahwa dp untuk sisa modulo w[i]
yang sama membentuk sliding window maximum. Lebih cepat tetapi
jauh lebih rawan bug. Dekomposisi biner adalah pilihan default
yang tepat kecuali batasannya benar-benar ketat.

── JEBAKAN ─────────────────────────────────────────────────
1. Potongan terakhir salah hitung.
2. Lupa bahwa c[i] bisa jauh lebih besar dari W/w[i] (sampel 2:
   c = 100 tetapi hanya 2 buah yang muat). Dekomposisi tetap
   benar, hanya sedikit boros. Kalau mau, batasi
   c[i] = min(c[i], W / w[i]) lebih dulu.
3. Arah loop DP harus MUNDUR — tiap POTONGAN dipakai sekali.
4. Lupa long long: v sampai 10^9 dikali banyak buah.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll W;
    if (!(cin >> n >> W)) return 0;

    vector<pair<ll, ll>> barang;                  // (berat, nilai) hasil pecahan
    for (int i = 0; i < n; i++) {
        ll w, v, c;
        cin >> w >> v >> c;
        c = min(c, W / w);                        // lebih dari ini tak akan muat
        for (ll k = 1; c > 0; k <<= 1) {
            ll ambil = min(k, c);                 // potongan terakhir bukan pangkat dua
            barang.push_back({w * ambil, v * ambil});
            c -= ambil;
        }
    }

    vector<ll> dp(W + 1, 0);
    for (auto& [bw, bv] : barang)
        for (ll cap = W; cap >= bw; cap--)        // MUNDUR: tiap potongan sekali
            dp[cap] = max(dp[cap], dp[cap - bw] + bv);

    cout << dp[W] << '\n';
    return 0;
}
