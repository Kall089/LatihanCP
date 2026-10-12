/*
============================================================
✅ SOLUSI Exercise 4: Denda Berbobot
============================================================
Difficulty: Medium | Kompleksitas: O(n * T), T = min(sum t, max d)
                    Di sini T <= min(2000*100, 2*10^5) = 2*10^5
                    -> sekitar 4*10^8 operasi terburuk, tetapi
                       loop dalamnya sangat ringan dan batas
                       atasnya adalah d_i (biasanya jauh lebih kecil)

── KENAPA KEDUA GREEDY GAGAL ───────────────────────────────
(a) Kerangka Exercise 2 (buang durasi terbesar): memaksimalkan
    JUMLAH tugas tepat waktu, bukan bobotnya. Menyelamatkan
    satu tugas bernilai 100 bisa lebih baik daripada tiga tugas
    bernilai 1.
(b) Kerangka Exercise 3 (buang bobot terkecil): benar hanya
    kalau durasi seragam. Dengan durasi bervariasi, membuang
    tugas berbobot kecil belum tentu membebaskan waktu, dan
    membuang tugas yang lama belum tentu mengorbankan sedikit
    bobot.

Akar masalahnya: ada DUA besaran yang bersaing. Invarian Day 77
"di antara himpunan berukuran maksimum, sumber daya minimum"
tidak bisa dirumuskan lagi, karena dua keadaan dengan bobot
terselamatkan sama bisa memakai waktu berbeda dan tidak ada
yang mendominasi.

Aturan umum yang layak dihafal:
   Regret bekerja kalau keadaan bisa diringkas menjadi SATU
   angka yang bisa dibandingkan. Dua besaran bersaing -> DP.

Secara teori, masalah ini (notasi 1 || sum w_j U_j) adalah
NP-HARD secara umum. Batasan kecil pada soal adalah tanda
bahwa DP-lah yang dimaksud.

── RUMUSAN DP ──────────────────────────────────────────────
Urut tenggat MENAIK, lalu:

    dp[w] = bobot maksimum yang bisa DIHINDARI kalau total
            waktu tugas-tugas tepat waktu tepat w

Transisinya knapsack 0/1 biasa:
    dp[w] = max(dp[w], dp[w - t_i] + w_i)

Jawabannya total bobot dikurangi maksimum seluruh dp.

── DUA DETAIL YANG MENENTUKAN KEBENARAN ────────────────────
1) BATAS ATAS LOOP ADALAH d_i, BUKAN T.
   Inilah yang menegakkan tenggat: tugas ini hanya boleh
   selesai pada waktu <= d_i. Kalau kamu memakai T sebagai
   batas, tenggat tidak tertegakkan sama sekali dan jawabanmu
   akan terlalu kecil (denda terlalu rendah).

2) URUT TENGGAT MENAIK.
   Klaim pendukung: kalau sehimpunan tugas bisa diselesaikan
   tepat waktu semua, maka mengerjakannya menurut tenggat
   menaik juga berhasil (exchange argument Exercise 1).
   Karena itu kita boleh membatasi diri pada jadwal terurut
   tenggat — dan DP di atas membangun persis jadwal seperti
   itu, karena tugas diproses menurut tenggat dan dp[w]
   berarti "sudah memakai w waktu dengan tugas bertenggat <=
   tenggat sekarang".
   Tanpa pengurutan, DP-nya SALAH.

── KENAPA LOOP MUNDUR ──────────────────────────────────────
Sama dengan knapsack 0/1 (Day 145): agar tiap tugas dipakai
paling banyak sekali. Loop maju membuat tugas bisa diambil
berkali-kali.

── SENTINEL ────────────────────────────────────────────────
dp diisi -1 untuk keadaan yang belum tercapai, dan transisi
hanya dilakukan kalau dp[w - t_i] >= 0. Memakai 0 sebagai nilai
awal untuk semua w akan salah: ia menyatakan bahwa "waktu w
bisa dicapai dengan bobot 0", padahal belum tentu.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai greedy. Uji dulu dengan brute force.
2. Batas atas loop memakai T alih-alih d_i.
3. Lupa mengurutkan menurut tenggat.
4. Loop MAJU.
5. Nilai awal dp semuanya 0 alih-alih -1.
6. Lupa long long pada bobot.

Diverifikasi: 4.000 kasus acak vs brute force atas SELURUH
permutasi, cocok.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Tugas { ll t, d, w; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<Tugas> j(n);
    ll total = 0, sumT = 0, maxD = 0;
    for (auto& x : j) {
        cin >> x.t >> x.d >> x.w;
        total += x.w;
        sumT  += x.t;
        maxD   = max(maxD, x.d);
    }

    sort(j.begin(), j.end(), [](const Tugas& a, const Tugas& b) {
        return a.d < b.d;                        // tenggat MENAIK — WAJIB
    });

    ll T = min(sumT, maxD);                      // waktu yang relevan
    vector<ll> dp(T + 1, -1);                    // -1 = belum tercapai
    dp[0] = 0;

    for (auto& x : j) {
        ll batas = min(x.d, T);                  // tenggat = BATAS ATAS loop
        for (ll w = batas; w >= x.t; w--)        // MUNDUR: tiap tugas sekali
            if (dp[w - x.t] >= 0)
                dp[w] = max(dp[w], dp[w - x.t] + x.w);
    }

    ll dihindari = 0;
    for (ll w = 0; w <= T; w++) dihindari = max(dihindari, dp[w]);

    cout << total - dihindari << '\n';
    return 0;
}
