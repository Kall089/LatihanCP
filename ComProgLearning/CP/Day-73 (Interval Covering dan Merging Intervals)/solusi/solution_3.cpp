/*
============================================================
✅ SOLUSI Exercise 3: Menyiram Taman
============================================================
Difficulty: Medium | Kompleksitas: O(n log n) waktu, O(n) memori

── IDE UTAMA ────────────────────────────────────────────────
Pelihara penanda 'sampai' = sejauh mana taman sudah tersiram.
Berulang kali: di antara semua alat dengan l <= sampai, ambil
yang r-nya TERBESAR, lalu majukan 'sampai' ke r itu.

── KENAPA BENAR (exchange argument) ────────────────────────
Klaim: ada solusi optimal yang, sebagai alat pertama, memakai
alat dengan r terbesar di antara yang memenuhi l <= 0.

Sebut alat itu x. Ambil solusi optimal O mana pun. O harus
menyirami titik 0, jadi O memuat suatu alat y dengan
l_y <= 0 <= r_y. Menurut definisi x, r_x >= r_y.
Ganti y dengan x. Bagian yang tadinya disirami y di dalam
[0, T] adalah [0, r_y], dan x menyirami [0, r_x] yang memuatnya.
Jadi penyiramannya tetap utuh, dan jumlah alat tidak berubah. ∎

Setelah memakai x, sisa yang harus disirami adalah [r_x, T] —
soal yang sama dalam ukuran lebih kecil. Induksi.

── KENAPA "AMBIL YANG PERTAMA MUAT" SALAH ──────────────────
Sampel 2: [0,5] [4,10] [0,2], T = 10.
  ambil yang pertama muat (setelah urut): [0,2] -> sampai=2
  lalu [0,5] -> sampai=5, lalu [4,10] -> sampai=10  = 3 alat
  ambil yang TERJAUH: [0,5] -> sampai=5, lalu [4,10] = 2 alat
Selisihnya nyata.

── KENAPA PENUNJUK TIDAK PERLU MUNDUR ──────────────────────
'sampai' hanya membesar. Alat yang l-nya sudah <= sampai akan
tetap memenuhi syarat itu selamanya, sehingga sekali diperiksa
tidak perlu diperiksa lagi. Penunjuk i hanya maju, total O(n).
Kalau kamu me-reset i di setiap putaran, kompleksitasnya
menjadi O(n^2) dan TLE pada n = 2*10^5.

── KASUS TIDAK MUNGKIN ─────────────────────────────────────
Kalau pada suatu putaran tidak ada alat yang bisa memajukan
'sampai' (terjauh == sampai), ada lubang yang tak tertutup.
Kembalikan -1. Lupa menangani ini menghasilkan loop tak
berujung, bukan sekadar jawaban salah.

── JEBAKAN ─────────────────────────────────────────────────
1. Memulai dari 'sampai = 0' padahal titik awalnya bisa bukan
   nol pada varian lain. Di sini memang 0, tetapi tulislah
   sebagai variabel agar mudah diadaptasi.
2. Syarat l <= sampai memakai <=, bukan <. Alat yang mulai
   tepat di 'sampai' menyambung dengan sempurna.
3. Loop luar memakai 'sampai < T', bukan '<='.
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
    vector<pair<ll, ll>> a(n);
    for (auto& [l, r] : a) cin >> l >> r;

    sort(a.begin(), a.end());              // urut menurut l

    ll sampai = 0;
    int hit = 0, i = 0;
    while (sampai < T) {
        ll terjauh = sampai;
        // penunjuk i hanya MAJU, tidak pernah di-reset
        while (i < n && a[i].first <= sampai) {
            terjauh = max(terjauh, a[i].second);
            i++;
        }
        if (terjauh == sampai) {           // macet: ada lubang
            cout << -1 << '\n';
            return 0;
        }
        sampai = terjauh;
        hit++;
    }

    cout << hit << '\n';
    return 0;
}
