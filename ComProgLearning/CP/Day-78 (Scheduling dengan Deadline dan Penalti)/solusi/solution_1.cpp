/*
============================================================
✅ SOLUSI Exercise 1: Keterlambatan Terkecil
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── JAWABANNYA: EDF (URUT TENGGAT MENAIK) ───────────────────
Yang mengejutkan: DURASI sama sekali tidak muncul dalam
kriteria pengurutan. Naluri menyarankan "kerjakan yang cepat
dulu" atau "urut menurut d - t". Keduanya salah.

── BUKTI (exchange argument) ───────────────────────────────
Ambil jadwal optimal. Andaikan ada dua pekerjaan BERDAMPINGAN
i lalu j dengan d_i > d_j (melanggar EDF). Misal waktu sebelum
keduanya adalah S.

  urutan (i, j):
      L_i = S + t_i - d_i
      L_j = S + t_i + t_j - d_j        <- ini yang terbesar
  urutan (j, i):
      L_j = S + t_j - d_j              (TURUN)
      L_i = S + t_i + t_j - d_i

Setelah ditukar, L_j jelas turun. Yang perlu ditunjukkan adalah
L_i yang baru tetap tidak melebihi maksimum yang lama:

      S + t_i + t_j - d_i  <  S + t_i + t_j - d_j
                              ^^^^^^^^^^^^^^^^^^^^
                              = L_j pada urutan SEMULA

Pertidaksamaan itu benar karena d_i > d_j. Jadi maksimum baru
tidak melebihi maksimum lama. ∎

Pekerjaan lain tidak terpengaruh karena t_i + t_j tetap sama,
sehingga waktu mulai pekerjaan berikutnya identik.

── KENAPA DURASI TIDAK RELEVAN ─────────────────────────────
Karena SEMUA pekerjaan dikerjakan, waktu selesai TERAKHIR
selalu sum(t) apa pun urutannya. Yang bisa kita atur hanyalah
pekerjaan mana yang menanggung akumulasi waktu itu — dan kita
ingin pekerjaan bertenggat longgar yang menanggungnya.

── LATENESS vs TARDINESS ───────────────────────────────────
  lateness  = C - d          (boleh NEGATIF)
  tardiness = max(0, C - d)  (tidak pernah negatif)
Soal ini meminta lateness, sehingga jawabannya boleh negatif
(sampel 1 memberi -3).
Kalau soal meminta tardiness, jawabannya max(0, hasil ini).
EDF meminimalkan KEDUANYA sekaligus.

── JEBAKAN ─────────────────────────────────────────────────
1. Menginisialisasi maksimum dengan 0. Jawaban bisa negatif.
   Pakai LLONG_MIN.
2. Mengurutkan menurut durasi atau d - t.
3. Lupa long long: d sampai 10^18, dan akumulasi t sampai
   2*10^5 * 10^9 = 2*10^14. Selisihnya bisa mendekati -10^18.
4. Menyangka soal ini sama dengan Exercise 2. Bukan.

Diverifikasi: 4.000 kasus acak vs seluruh permutasi, cocok.
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
    vector<pair<ll, ll>> j(n);                  // (tenggat, durasi)
    for (int i = 0; i < n; i++) {
        ll t, d;
        cin >> t >> d;
        j[i] = {d, t};
    }

    sort(j.begin(), j.end());                   // tenggat MENAIK (EDF)

    ll t = 0, worst = LLONG_MIN;                // BUKAN 0
    for (auto& [d, dur] : j) {
        t += dur;
        worst = max(worst, t - d);
    }

    cout << worst << '\n';
    return 0;
}
