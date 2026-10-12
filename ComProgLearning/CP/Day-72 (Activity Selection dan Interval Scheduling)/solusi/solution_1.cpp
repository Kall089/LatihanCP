/*
============================================================
✅ SOLUSI Exercise 1: Festival Film
============================================================
Difficulty: Easy | Kompleksitas: O(n log n) waktu, O(n) memori

── IDE UTAMA ────────────────────────────────────────────────
Urutkan menurut waktu SELESAI menaik. Sapu sekali; ambil film
bila waktu mulainya tidak lebih awal dari waktu bebas sekarang.

── KENAPA BENAR (exchange argument) ────────────────────────
Klaim: ada solusi optimal yang memuat film dengan b terkecil.

Misal x film dengan b terkecil secara global, dan S solusi
optimal mana pun. Kalau x sudah di S, selesai. Kalau belum,
ambil y di S yang selesai paling awal. Karena x punya b
terkecil, b_x <= b_y.
Ganti y dengan x. Semua film lain di S mulai pada atau setelah
b_y (karena y selesai paling awal dan S saling lepas), sehingga
otomatis juga mulai pada atau setelah b_x. Jadi hasilnya masih
saling lepas, dan jumlahnya tidak berubah → tetap optimal. ∎

Setelah mengambil x, buang semua film yang bentrok dengannya.
Sisanya adalah soal yang sama dalam ukuran lebih kecil
(optimal substructure). Induksi.

── KENAPA KRITERIA LAIN GAGAL ──────────────────────────────
Urut waktu MULAI    : [1,100] [2,3] [4,5] → greedy 1, optimal 2
Urut DURASI         : [1,10] [9,12] [11,20] → greedy 1, optimal 2
Keduanya gagal karena yang menentukan bukan kapan sesuatu
dimulai atau berapa lama, melainkan kapan sumber daya BEBAS.

── TERTUTUP vs SETENGAH TERBUKA ────────────────────────────
Soal ini menyatakan "BOLEH langsung berpindah ke film yang mulai
tepat saat film sebelumnya selesai" → model SETENGAH TERBUKA.
Syaratnya a[i] >= akhir, memakai >= bukan >.

Bandingkan sampel 1: [3,5] [4,9] [5,8].
  dengan >=  : ambil [3,5] lalu [5,8] → 2 ✓
  dengan >   : ambil [3,5] saja       → 1 ✗
Satu karakter membedakan AC dan WA.

── JEBAKAN ─────────────────────────────────────────────────
1. Menginisialisasi 'akhir' dengan 0. Kalau ada a[i] = 0 film
   pertama terlewat. Pakai LLONG_MIN (atau nilai yang pasti
   lebih kecil dari semua a[i]).
2. Mengurutkan menurut a. Naluri terkuat, dan salah.
3. Lupa fast I/O pada n = 2*10^5.
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
    vector<pair<ll, ll>> f(n);              // (selesai, mulai)
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        f[i] = {b, a};                      // taruh 'selesai' di depan
    }

    sort(f.begin(), f.end());               // otomatis urut menurut selesai

    int hit = 0;
    ll akhir = LLONG_MIN;
    for (auto& [b, a] : f) {
        if (a >= akhir) {                   // setengah terbuka: >= , bukan >
            hit++;
            akhir = b;
        }
    }

    cout << hit << '\n';
    return 0;
}
