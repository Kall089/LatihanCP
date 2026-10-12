/*
============================================================
✅ SOLUSI Exercise 1: Menggabungkan Rentang
============================================================
Difficulty: Easy | Kompleksitas: O(n log n) waktu, O(n) memori

── IDE UTAMA ────────────────────────────────────────────────
Urutkan menurut ujung KIRI. Sapu dari kiri ke kanan sambil
memelihara satu blok gabungan yang sedang terbuka.

── KENAPA URUT MENURUT l, BUKAN r ──────────────────────────
Day 72 menanamkan refleks "interval selalu urut menurut r".
Refleks itu berlaku untuk soal MEMILIH himpunan bagian.
Soal ini berbeda: kita MENYAPU sumbu dari kiri ke kanan.
Aturan umumnya:
   menyapu sumbu          -> urut menurut l
   memilih himpunan bagian -> urut menurut r

── INVARIAN YANG MEMBUATNYA O(n) ───────────────────────────
Setelah diurutkan menurut l, interval berikutnya punya l yang
tidak lebih kecil dari semua yang sudah diproses. Jadi kalau ia
tidak beririsan dengan blok TERAKHIR, ia pasti juga tidak
beririsan dengan blok mana pun sebelumnya — blok-blok itu
berakhir bahkan lebih awal.
Karena itu cukup membandingkan dengan res.back() saja.

── JEBAKAN UTAMA: LUPA max ─────────────────────────────────
   res.back().second = a[i].second;                  ❌
   res.back().second = max(res.back().second, ...);  ✅

Contoh yang menghancurkan versi salah: [1,10] lalu [2,3].
Versi salah memendekkan [1,10] menjadi [1,3].
Bug ini butuh interval yang TERMUAT PENUH untuk muncul, sehingga
sering lolos dari sampel. Sampel 2 sengaja mengujinya.

── BERSENTUHAN: DIGABUNG ATAU TIDAK ────────────────────────
Soal ini menyatakan "beririsan ATAU bersentuhan" digabung,
sehingga syaratnya l <= akhir. Kalau soalmu memakai rentang
setengah terbuka [l, r), gantilah menjadi l < akhir.

── JEBAKAN LAIN ────────────────────────────────────────────
1. l bisa negatif (-10^9). Jangan menginisialisasi dengan 0.
2. Kode di bawah menangani n = 1 secara alami karena res
   diisi lebih dulu dengan a[0].
3. Output bisa sampai 2*10^5 baris — pakai '\n', bukan endl.
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
    vector<pair<ll, ll>> a(n);
    for (auto& [l, r] : a) cin >> l >> r;

    sort(a.begin(), a.end());              // urut l, lalu r

    vector<pair<ll, ll>> res;
    res.push_back(a[0]);
    for (int i = 1; i < n; i++) {
        auto [l, r] = a[i];
        if (l <= res.back().second)
            res.back().second = max(res.back().second, r);   // max WAJIB
        else
            res.push_back({l, r});
    }

    cout << res.size() << '\n';
    for (auto& [l, r] : res) cout << l << ' ' << r << '\n';
    return 0;
}
