/*
============================================================
✅ SOLUSI Exercise 4: Mencari Contoh Tandingan
============================================================
Difficulty: Medium | Kompleksitas: O(N log N + N*T)

── IDE UTAMA ────────────────────────────────────────────────
Dua hitungan terpisah lalu dibandingkan:
  (a) simulasi strategi greedy "ambil koin terbesar yang muat"
  (b) jawaban optimal sesungguhnya lewat DP koin (unbounded)

── (a) SIMULASI GREEDY ─────────────────────────────────────
Urutkan koin menurun. Untuk tiap koin c, ambil sisa/c keping
sekaligus (jangan satu-satu — kalau T = 10^4 dan koin = 1,
loop satu-satu masih aman, tetapi kebiasaan membagi lebih baik).
Karena nilai 1 dijamin ada, greedy SELALU berhasil membayar
tepat T. Tanpa jaminan itu, greedy bisa "tersangkut".

── (b) DP OPTIMAL ──────────────────────────────────────────
dp[x] = jumlah koin minimum untuk membayar tepat x.
  dp[0] = 0
  dp[x] = 1 + min(dp[x - c]) untuk setiap koin c <= x
Ini DP "unbounded" (koin boleh dipakai berkali-kali), sehingga
loopnya MAJU, berbeda dengan knapsack 0/1 yang loopnya mundur.
O(N*T) = 20 * 10^4 = 2*10^5 operasi, sangat ringan.

── PELAJARAN YANG SESUNGGUHNYA ─────────────────────────────
Greedy koin benar untuk sistem "kanonik" seperti {1,5,10,25}
(mata uang nyata dirancang begitu). Tetapi untuk sistem
sembarang seperti {1,3,4}, greedy gagal: bayar 6 →
greedy 4+1+1 = 3 keping, optimal 3+3 = 2 keping.

Tidak ada cara cepat untuk "melihat" apakah sebuah sistem
kanonik hanya dengan menatapnya. Inilah alasan kebiasaan
menguji greedy terhadap brute force sangat berharga: kesalahan
greedy sering baru muncul pada masukan yang tidak kamu
bayangkan.

── JEBAKAN ─────────────────────────────────────────────────
1. Lupa mengurutkan koin sebelum simulasi greedy.
2. Memakai nilai sentinel dp yang bisa meluap saat ditambah 1.
   Pakai nilai besar seperti T+1 (bukan INT_MAX).
3. Membalik arah loop DP → itu menjadi knapsack 0/1, yaitu
   tiap koin hanya boleh dipakai sekali. Soal ini bukan itu.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, T;
    if (!(cin >> n >> T)) return 0;
    vector<int> c(n);
    for (int &x : c) cin >> x;

    // ── (a) simulasi strategi greedy ──
    vector<int> turun = c;
    sort(turun.rbegin(), turun.rend());
    int sisa = T, kepingGreedy = 0;
    for (int v : turun) {
        if (v <= sisa) {
            kepingGreedy += sisa / v;
            sisa %= v;
        }
    }
    // sisa dijamin 0 karena koin bernilai 1 selalu ada.

    // ── (b) DP optimal (unbounded coin change) ──
    const int INF = T + 1;                 // aman: jawaban tak pernah > T
    vector<int> dp(T + 1, INF);
    dp[0] = 0;
    for (int x = 1; x <= T; x++)           // MAJU: koin boleh dipakai ulang
        for (int v : c)
            if (v <= x && dp[x - v] + 1 < dp[x])
                dp[x] = dp[x - v] + 1;

    int kepingOptimal = dp[T];

    if (kepingGreedy == kepingOptimal) cout << "OPTIMAL\n";
    else cout << kepingGreedy << ' ' << kepingOptimal << '\n';

    return 0;
}
