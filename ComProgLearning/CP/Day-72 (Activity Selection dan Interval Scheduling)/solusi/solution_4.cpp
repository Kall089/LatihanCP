/*
============================================================
✅ SOLUSI Exercise 4: Kelas dengan Dua Ruangan
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── KENAPA "JALANKAN DUA KALI" SALAH ────────────────────────
Ide naif: jalankan activity selection, buang yang terpilih,
jalankan lagi pada sisanya. Ini bisa kurang optimal karena
pilihan putaran pertama dibuat tanpa mempertimbangkan bahwa ada
ruangan kedua — ia bisa "mengunci" interval yang seharusnya
disisakan.

── IDE YANG BENAR ──────────────────────────────────────────
Tetap urutkan menurut waktu selesai. Simpan DUA waktu bebas,
f1 dan f2. Untuk tiap kelas [l, r):
  - kalau muat di kedua ruangan, pakai ruangan yang waktu
    bebasnya PALING AKHIR (di antara yang muat)
  - kalau hanya muat di satu, pakai yang itu
  - kalau tidak muat di mana pun, lewati

── KENAPA "PALING AKHIR YANG MUAT" ─────────────────────────
Setelah menempatkan kelas ini, kedua ruangan punya waktu bebas
{r, f_lain}. Nilai r sudah pasti (kelas ini akan selesai di r
apa pun ruangannya). Yang bisa kita pilih adalah f_lain, dan
kita ingin f_lain SEKECIL mungkin agar ruangan kedua lebih
longgar untuk kelas berikutnya.
Karena f_lain adalah ruangan yang TIDAK dipakai, kita harus
memakai yang lebih BESAR agar yang tersisa lebih kecil.
Formalnya: menukar pilihan menghasilkan keadaan {r, f_besar}
yang didominasi oleh {r, f_kecil} — setiap kelas yang muat pada
keadaan pertama pasti juga muat pada keadaan kedua. Jadi
memilih ruangan dengan waktu bebas terbesar tidak pernah
merugikan. ∎

── PENGURUTAN MENURUT r TETAP PENTING ──────────────────────
Argumen dominasi di atas mengandalkan fakta bahwa r kelas
berikutnya tidak lebih kecil dari r kelas sekarang. Itu dijamin
oleh pengurutan.

── PERLUASAN KE K RUANGAN ──────────────────────────────────
Untuk K ruangan, simpan seluruh waktu bebas dalam multiset dan
ambil yang TERBESAR di antara yang <= l memakai upper_bound.
Kompleksitasnya O(n log K). Coba tulis sendiri sebagai latihan;
kode di bawah adalah kasus khusus K = 2.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai ruangan yang bebas paling AWAL. Itu kebalikannya
   dan bisa kurang optimal.
2. Menginisialisasi f1 dan f2 dengan 0 padahal l bisa 0.
3. Setengah terbuka: syaratnya l >= f, bukan l > f.
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
    vector<pair<ll, ll>> a(n);              // (r, l)
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        a[i] = {r, l};
    }

    sort(a.begin(), a.end());

    ll f1 = LLONG_MIN, f2 = LLONG_MIN;      // waktu bebas kedua ruangan
    int hit = 0;
    for (auto& [r, l] : a) {
        bool muat1 = (l >= f1), muat2 = (l >= f2);
        if (!muat1 && !muat2) continue;

        // pakai ruangan dengan waktu bebas TERBESAR di antara yang muat
        if (muat1 && muat2) {
            if (f1 >= f2) f1 = r;
            else          f2 = r;
        } else if (muat1) {
            f1 = r;
        } else {
            f2 = r;
        }
        hit++;
    }

    cout << hit << '\n';
    return 0;
}
