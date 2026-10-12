/*
============================================================
✅ SOLUSI Exercise 3: Ruang Rapat Minimum
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── IDE UTAMA ────────────────────────────────────────────────
Jawabannya adalah TUMPANG TINDIH MAKSIMUM: berapa banyak rapat
yang paling banyak berlangsung bersamaan pada satu titik waktu.

── KENAPA ITU JAWABANNYA ───────────────────────────────────
Batas bawah: kalau pada suatu waktu t ada m rapat berlangsung,
kamu jelas butuh minimal m ruangan.
Batas atas: algoritma di bawah tidak pernah membuka ruangan baru
kecuali semua ruangan yang ada sedang terpakai. Saat ruangan
ke-m dibuka, berarti pada saat itu ada m rapat berlangsung
bersamaan. Jadi jumlah ruangan yang dibuka tidak pernah melebihi
tumpang tindih maksimum.
Batas bawah = batas atas → itulah nilai optimal. ∎

── SAPUAN EVENT ────────────────────────────────────────────
Tiap rapat menjadi dua event: (s, +1) dan (e, -1). Urutkan
semuanya, lalu jalan dari kiri ke kanan sambil menjumlahkan.

Urutan pada waktu yang SAMA sangat menentukan. Soal ini
menyatakan rapat baru boleh mulai tepat saat rapat sebelumnya
selesai → model setengah terbuka → event SELESAI harus diproses
lebih dulu.
Kebetulan yang menguntungkan: pair mengurutkan {t, -1} sebelum
{t, +1} karena -1 < +1. Jadi penulisan naif justru benar untuk
model ini.
Kalau soalmu TERTUTUP, ubah event selesai menjadi {e + 1, -1}
(untuk waktu bilangan bulat) atau balik urutannya secara
eksplisit.

── ALTERNATIF: HEAP ────────────────────────────────────────
Simpan waktu selesai ruangan yang sedang terpakai di dalam
min-heap. Untuk tiap rapat (diurutkan menurut waktu mulai):
kalau ruangan yang paling cepat bebas sudah bebas, pakai ulang;
kalau tidak, buka ruangan baru. Jawabannya ukuran heap di akhir.
Kedua cara sama-sama O(n log n); pilih yang lebih kamu pahami.

── KENAPA INI BUKAN EXERCISE 1 ─────────────────────────────
Di Exercise 1 kita MEMBUANG rapat untuk memaksimalkan yang
terpakai pada satu ruangan. Di sini tidak ada yang dibuang;
yang dicari adalah jumlah ruangan. Kata "semuanya harus
terlaksana" adalah penanda soal yang berbeda.

── JEBAKAN ─────────────────────────────────────────────────
1. Menjalankan activity selection berulang kali sampai habis.
   Itu memberikan jawaban yang benar untuk soal ini secara
   kebetulan pada banyak kasus, tetapi TIDAK selalu, dan jauh
   lebih lambat.
2. Salah urutan event pada waktu yang sama.
3. Lupa bahwa jumlah event adalah 2n, bukan n.
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

    vector<pair<ll, int>> ev;
    ev.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        ll s, e;
        cin >> s >> e;
        ev.push_back({s, +1});
        ev.push_back({e, -1});     // -1 < +1 → selesai diproses lebih dulu
    }

    sort(ev.begin(), ev.end());

    int cur = 0, best = 0;
    for (auto& [t, d] : ev) {
        cur += d;
        best = max(best, cur);
    }

    cout << best << '\n';
    return 0;
}
