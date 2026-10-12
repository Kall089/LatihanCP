/*
============================================================
✅ SOLUSI Exercise 6: Denda dengan Waktu Rilis
============================================================
Difficulty: Hard | Kompleksitas: O(2^n * n) waktu, O(2^n) memori
                   n = 18 -> 18 * 262144 = 4.7 juta operasi

── KENAPA PENDEKATAN EXERCISE 4 GAGAL ──────────────────────
DP di atas waktu pada Exercise 4 bekerja karena "waktu
sekarang" sama dengan jumlah durasi tugas yang sudah
dikerjakan. Dengan waktu rilis, itu TIDAK BERLAKU lagi: mesin
bisa MENGANGGUR menunggu sebuah pekerjaan tersedia, sehingga
waktu sekarang bisa lebih besar dari jumlah durasi.

── MEMBACA BATASAN ─────────────────────────────────────────
N <= 18. Angka itu sangat spesifik: 2^18 = 262144, cukup kecil
untuk menyimpan satu nilai per HIMPUNAN BAGIAN. Batasan
n <= 20 hampir selalu berarti bitmask (Day 60, Day 68).

── PENGAMATAN YANG MENYEDERHANAKAN SEGALANYA ───────────────
Pekerjaan yang TERLAMBAT tidak punya batasan apa pun — ia hanya
harus dikerjakan suatu saat. Jadi kita bisa menjadwalkan
SELURUH pekerjaan terlambat di paling belakang, setelah semua
pekerjaan tepat waktu selesai.

Akibatnya, soalnya menjadi:
    pilih himpunan S yang bisa dijadwalkan TEPAT WAKTU semua,
    dan maksimalkan total bobot S.
Jawabannya total bobot dikurangi bobot S terbaik.

── DP KELAYAKAN ────────────────────────────────────────────
    f[mask] = waktu selesai MINIMUM untuk menjadwalkan
              seluruh pekerjaan di mask, semuanya tepat waktu
              (INF kalau tidak mungkin)

Transisinya: untuk tiap j di dalam mask,
    kandidat = max( f[mask tanpa j], r[j] ) + t[j]
    kalau kandidat <= d[j], maka f[mask] = min(f[mask], kandidat)

── KENAPA MEMINIMALKAN WAKTU SELESAI ITU BENAR ─────────────
Di dalam himpunan S, tujuan kita hanyalah KELAYAKAN, bukan
optimasi lain. Dan waktu selesai bersifat monoton: kalau sebuah
prefiks bisa diselesaikan lebih awal, setiap kelanjutan yang
sah untuk prefiks yang lebih lambat juga sah untuk yang lebih
awal (karena max(f, r) + t monoton naik terhadap f).
Jadi menyimpan hanya waktu selesai minimum per himpunan sudah
cukup — tidak perlu menyimpan seluruh kemungkinan.

Perhatikan bahwa argumen ini BERGANTUNG pada pemisahan
"kelayakan" dari "bobot". Kalau kita mencoba menyimpan
(denda minimum, waktu selesai) sekaligus per himpunan, kedua
besaran itu bisa bertentangan dan DP-nya menjadi salah.
Memisahkan keduanya adalah kunci soal ini.

── MENGHITUNG JAWABAN ──────────────────────────────────────
Setelah f terisi, sapu seluruh mask yang f[mask] < INF dan
ambil bobot terbesar. Jawabannya total - bobot terbesar itu.

── VERIFIKASI SAMPEL 3 ─────────────────────────────────────
Pekerjaan A (r=0, t=5, d=5, w=3) dan B (r=1, t=1, d=2, w=100).
  {}    : f = 0
  {A}   : max(0,0)+5 = 5 <= 5  -> f = 5
  {B}   : max(0,1)+1 = 2 <= 2  -> f = 2
  {A,B} : dari {A}: max(5,1)+1 = 6 > 2  gagal
          dari {B}: max(2,0)+5 = 7 > 5  gagal
          -> INF
Terbaik: {B} dengan bobot 100. Denda = 103 - 100 = 3. ✓

── JEBAKAN ─────────────────────────────────────────────────
1. Menyimpan (denda, waktu) sekaligus per himpunan. Kedua
   besaran bertentangan dan DP-nya salah.
2. Lupa max(f, r): mesin harus menunggu kalau belum rilis.
3. Memakai int untuk INF lalu meluap saat ditambah t.
4. Menyangka pekerjaan terlambat harus dijadwalkan di posisi
   tertentu. Tidak — taruh saja di belakang.
5. Lupa long long: d sampai 10^18.
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
    vector<ll> r(n), t(n), d(n), w(n);
    ll total = 0;
    for (int i = 0; i < n; i++) {
        cin >> r[i] >> t[i] >> d[i] >> w[i];
        total += w[i];
    }

    const ll INF = LLONG_MAX / 4;
    int FULL = 1 << n;
    vector<ll> f(FULL, INF);                     // waktu selesai minimum
    f[0] = 0;

    for (int mask = 1; mask < FULL; mask++) {
        for (int j = 0; j < n; j++) {
            if (!(mask >> j & 1)) continue;
            ll prev = f[mask ^ (1 << j)];
            if (prev >= INF) continue;
            ll selesai = max(prev, r[j]) + t[j]; // mesin menunggu bila perlu
            if (selesai <= d[j])                 // harus tepat waktu
                f[mask] = min(f[mask], selesai);
        }
    }

    ll terbaik = 0;
    for (int mask = 0; mask < FULL; mask++) {
        if (f[mask] >= INF) continue;
        ll s = 0;
        for (int j = 0; j < n; j++) if (mask >> j & 1) s += w[j];
        terbaik = max(terbaik, s);
    }

    cout << total - terbaik << '\n';
    return 0;
}
