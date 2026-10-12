/*
============================================================
✅ SOLUSI Exercise 1: Menguji Klaim Tukar Uang
============================================================
Difficulty: Easy | Kompleksitas: O(N log N + N*T)

── URUTAN PENGERJAAN ───────────────────────────────────────
Tulis bagian yang PASTI BENAR lebih dulu, yaitu jawaban
optimal. Baru setelah itu simulasikan greedy.
Urutan ini penting: kalau kamu menulis greedy dulu, kamu akan
tergoda "memperbaikinya" saat hasilnya terlihat aneh, padahal
tugasmu adalah MENGUJI klaim, bukan memperbaikinya.

── JAWABAN OPTIMAL: DP UNBOUNDED ───────────────────────────
    dp[x] = jumlah koin minimum untuk membayar tepat x
    dp[0] = 0
    dp[x] = 1 + min(dp[x - c]) untuk tiap koin c <= x

Loop MAJU, karena koin boleh dipakai BERKALI-KALI. Kalau kamu
membalik arahnya menjadi mundur, kamu justru menyelesaikan
knapsack 0/1 — soal yang berbeda, dan jawabannya akan lebih
besar. Arah loop menentukan soal apa yang kamu pecahkan.

O(N*T) = 20 * 10^4 = 2*10^5 operasi. Sangat ringan.

── SIMULASI GREEDY ─────────────────────────────────────────
Urut koin menurun, ambil sisa/c keping sekaligus. Karena nilai
1 dijamin ada, greedy selalu berhasil membayar tepat T.
(Tanpa jaminan itu, greedy bisa "tersangkut" dan gagal
membayar sama sekali — kasus yang perlu ditangani terpisah.)

── ANGKA YANG LAYAK DIINGAT ────────────────────────────────
Pada 20.000 sistem koin acak berukuran 2 sampai 4 dengan nilai
sampai 12 dan target sampai 30, greedy koin terbesar gagal
sekitar 10% kasus.

Contoh tandingan yang ditemukan: koin {1, 6, 8, 11}, target 27
    greedy  : 11 + 11 + 1 + 1 + 1 + 1 + 1 = 7 keping
    optimal : 11 + 8 + 8                  = 3 keping
Selisihnya lebih dari dua kali lipat.

Contoh yang paling ringkas untuk dihafal: koin {1, 3, 4},
bayar 6.  greedy 4+1+1 = 3 keping, optimal 3+3 = 2 keping.

── KENAPA ANGKA 10% ITU PENTING ────────────────────────────
Kalau kamu menguji sebuah ide greedy pada LIMA sampel dan
semuanya lolos, sementara ide itu sebenarnya gagal 10% dari
waktu, peluang lolos lima kali berturut-turut adalah
0,9^5 = 59%.

    Lima sampel tidak membuktikan apa pun.

Bahkan pada tingkat kegagalan 2%, kamu butuh sekitar 150 kasus
untuk punya peluang 95% menemukannya. Karena itu stress test
harus RIBUAN kasus. Dan itu murah: 20.000 kasus kecil biasanya
selesai dalam hitungan detik.

── KENAPA SISTEM UANG NYATA AMAN ───────────────────────────
Sistem seperti {1, 5, 10, 25} disebut "kanonik" — greedy benar
untuknya. Mata uang nyata memang dirancang begitu. Tetapi tidak
ada cara cepat untuk "melihat" apakah sebuah sistem kanonik
hanya dengan menatapnya; ada algoritma pemeriksa, tetapi jauh
lebih rumit daripada sekadar memakai DP.

── JEBAKAN ─────────────────────────────────────────────────
1. Membalik arah loop DP.
2. Memakai INT_MAX sebagai sentinel lalu meluap saat + 1.
   Pakai T + 1, yang aman karena jawaban tak pernah melebihi T.
3. Lupa mengurutkan koin sebelum simulasi greedy.
4. "Memperbaiki" strategi greedy alih-alih mengujinya.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll T;
    if (!(cin >> n >> T)) return 0;
    vector<ll> c(n);
    for (ll& x : c) cin >> x;

    // ── (1) jawaban optimal: DP unbounded, loop MAJU ──
    const ll INF = T + 1;                       // aman: jawaban <= T
    vector<ll> dp(T + 1, INF);
    dp[0] = 0;
    for (ll x = 1; x <= T; x++)
        for (ll v : c)
            if (v <= x && dp[x - v] + 1 < dp[x]) dp[x] = dp[x - v] + 1;
    ll optimal = dp[T];

    // ── (2) simulasi greedy, apa adanya ──
    vector<ll> turun = c;
    sort(turun.rbegin(), turun.rend());
    ll sisa = T, greedy = 0;
    for (ll v : turun) if (v <= sisa) { greedy += sisa / v; sisa %= v; }

    if (greedy == optimal) cout << "OPTIMAL\n";
    else cout << greedy << ' ' << optimal << '\n';

    return 0;
}
