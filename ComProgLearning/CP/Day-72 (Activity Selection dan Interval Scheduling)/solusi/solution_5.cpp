/*
============================================================
✅ SOLUSI Exercise 5: Jadwal Berbobot
============================================================
Difficulty: Hard | Kompleksitas: O(n log n) waktu, O(n) memori

── KENAPA GREEDY GAGAL ─────────────────────────────────────
Sampel 2:  [1,10] p=100,  [1,2] p=1,  [3,4] p=1
Greedy "ujung terkecil" mengambil [1,2] lalu [3,4] → 2.
Optimal: [1,10] → 100.

Buktinya rusak di langkah penukaran. Pada versi tanpa bobot kita
mengganti y dengan x dan berkata "jumlahnya sama, jadi tetap
optimal". Dengan bobot, jumlah yang sama TIDAK berarti nilai
yang sama. Greedy choice property hilang.

── IDE DP ──────────────────────────────────────────────────
Urutkan proyek menurut b (hari selesai) menaik. Definisikan
  dp[i] = keuntungan maksimum memakai i proyek pertama saja
Untuk proyek ke-i ada dua pilihan:
  LEWATI : dp[i]
  AMBIL  : p[i] + dp[ p(i) ]
dengan p(i) = banyaknya proyek (dalam urutan terurut) yang
b-nya benar-benar KURANG dari a[i].
  dp[i+1] = max(dp[i], p[i] + dp[p(i)])
Jawabannya dp[n].

── MENCARI p(i) DENGAN CEPAT ───────────────────────────────
Karena array b sudah terurut menaik, p(i) adalah posisi pertama
yang b-nya >= a[i], yaitu lower_bound(b, a[i]).
Kenapa lower_bound dan bukan upper_bound? Interval di sini
TERTUTUP: proyek sebelumnya menempati hari b, jadi ia hanya
boleh dipakai kalau b < a[i]. Nilai b yang sama dengan a[i]
BENTROK dan harus dikeluarkan — itulah yang dilakukan
lower_bound.
(Kalau soalmu setengah terbuka, gantilah dengan upper_bound.)

Pencariannya dibatasi pada b[0..i-1] karena hanya proyek yang
lebih awal yang boleh menjadi pendahulu.

── KENAPA DP INI BENAR ─────────────────────────────────────
Optimal substructure: pada solusi optimal, lihat proyek dengan
b terbesar yang diambil. Segala sesuatu sebelum a-nya adalah
solusi optimal untuk subsoal yang lebih kecil — kalau tidak,
kita bisa menggantinya dan memperbaiki total, kontradiksi.
Overlapping subproblem: dp[p(i)] dipakai berulang oleh banyak i.
Dua syarat DP terpenuhi.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai upper_bound padahal intervalnya tertutup (atau
   sebaliknya). Ini WA yang sangat sulit dilacak.
2. Lupa long long. n = 2*10^5 dan p = 10^9 → total sampai
   2*10^14.
3. Mengurutkan menurut a. DP ini mensyaratkan urutan menurut b.
4. Mencari lower_bound pada SELURUH array b, bukan hanya
   b[0..i-1]. Untuk array terurut hasilnya kebetulan sama
   karena b[j] >= b[i] >= a[i] untuk j >= i... tetapi
   membatasinya secara eksplisit lebih aman dan jelas.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    struct P { ll a, b, p; };
    vector<P> v(n);
    for (auto& x : v) cin >> x.a >> x.b >> x.p;

    sort(v.begin(), v.end(), [](const P& x, const P& y) { return x.b < y.b; });

    vector<ll> B(n);
    for (int i = 0; i < n; i++) B[i] = v[i].b;

    vector<ll> dp(n + 1, 0);
    for (int i = 0; i < n; i++) {
        // pendahulu terakhir yang selesai SEBELUM v[i].a
        int p = (int)(lower_bound(B.begin(), B.begin() + i, v[i].a) - B.begin());
        dp[i + 1] = max(dp[i], v[i].p + dp[p]);
    }

    cout << dp[n] << '\n';
    return 0;
}
