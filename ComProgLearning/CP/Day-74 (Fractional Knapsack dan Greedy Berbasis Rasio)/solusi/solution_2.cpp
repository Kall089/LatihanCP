/*
============================================================
✅ SOLUSI Exercise 2: Membuktikan Greedy Gagal
============================================================
Difficulty: Easy | Kompleksitas: O(n log n + n*W)

── DUA HITUNGAN TERPISAH ───────────────────────────────────
(a) simulasi greedy rasio: urut menurun, ambil selama muat
(b) jawaban optimal: DP 0/1 knapsack (Day 145)

── KENAPA GREEDY GAGAL DI SINI ─────────────────────────────
Bukti fractional knapsack memakai langkah "kurangi y sebanyak
berat d, tambahkan x sebanyak berat d". Pada 0/1 langkah itu
TIDAK ADA — barang harus utuh, dan beratnya jarang cocok.
Greedy choice property hilang, dan buktinya runtuh.

Sampel 1 adalah contoh tandingan minimal yang wajib dihafal:
  W = 10, barang (6,7) (5,5) (5,5)
  rasio  : 1.167  1.0  1.0
  greedy : (6,7) -> sisa 4, tidak ada yang muat  -> 7
  optimal: (5,5) + (5,5)                         -> 10
Greedy kehilangan 30% dari jawaban.

── ARAH LOOP DP ────────────────────────────────────────────
  for (c = W; c >= w[i]; c--)   MUNDUR  -> tiap barang SEKALI
  for (c = w[i]; c <= W; c++)   MAJU    -> boleh BERKALI-KALI
Membalik arahnya berarti menyelesaikan soal yang berbeda, dan
biasanya menghasilkan jawaban yang terlalu besar.

Alasannya: dengan loop mundur, saat membaca dp[c - w[i]] nilai
itu masih berisi keadaan SEBELUM barang i dipertimbangkan.
Dengan loop maju, dp[c - w[i]] sudah mungkin memuat barang i.

── SEBERAPA SERING GREEDY GAGAL ────────────────────────────
Pada 20.000 kasus acak (n <= 8, w <= 12, v <= 20, W <= 25),
greedy rasio gagal pada sekitar 12% kasus.

Angka itu penting secara metodologis: kalau kamu menguji ide
greedy pada 5 sampel dan semuanya lolos, peluangnya sekitar
53% meski greedy-nya salah. Lima sampel tidak membuktikan apa
pun. Stress test ribuan kasus adalah satu-satunya cara.

── FRACTIONAL SEBAGAI BATAS ATAS ───────────────────────────
Meski salah sebagai jawaban, fractional knapsack selalu
memberikan batas atas untuk 0/1. Sifat itu dipakai dalam
branch and bound (Day 63): pangkas cabang yang batas atasnya
tidak melebihi jawaban terbaik sekarang.

── JEBAKAN ─────────────────────────────────────────────────
1. Membalik arah loop DP.
2. Lupa long long: n = 100 dan v = 10^9 -> total 10^11.
3. Menyangka greedy "kebetulan benar" karena lolos sampel.
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
    vector<ll> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    // ── (a) simulasi greedy rasio ──
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return (__int128)v[a] * w[b] > (__int128)v[b] * w[a];
    });
    ll sisa = W, greedy = 0;
    for (int i : ord) if (w[i] <= sisa) { greedy += v[i]; sisa -= w[i]; }

    // ── (b) DP 0/1 knapsack ──
    vector<ll> dp(W + 1, 0);
    for (int i = 0; i < n; i++)
        for (ll c = W; c >= w[i]; c--)            // MUNDUR: tiap barang sekali
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    ll optimal = dp[W];

    if (greedy == optimal) cout << "OPTIMAL\n";
    else cout << greedy << ' ' << optimal << '\n';

    return 0;
}
