/*
============================================================
✅ SOLUSI Exercise 6: Boneka Rusia
============================================================
Difficulty: Hard | Kompleksitas: O(n log n)

── IDE UTAMA ────────────────────────────────────────────────
Urutkan lebar MENAIK; saat lebar SERI, urutkan tinggi MENURUN.
Lalu cari barisan naik TEGAS terpanjang pada tinggi saja.

── KENAPA TIE-BREAK MENURUN ITU JENIUS ─────────────────────
Masalahnya: amplop dengan lebar SAMA tidak boleh bersarang
(syaratnya strict pada kedua ukuran).

Kalau tinggi diurutkan MENAIK saat lebar seri, misalnya
      (6,4) (6,7)
maka barisan naik akan menganggap 4 lalu 7 sebagai rantai sah —
padahal keduanya berlebar sama dan tidak boleh bersarang.

Dengan tinggi MENURUN saat lebar seri, urutannya menjadi
      (6,7) (6,4)
dan barisan naik TEGAS tidak akan pernah mengambil keduanya,
karena 7 lalu 4 bukan naik.

Jadi tie-break itu MENEGAKKAN BATASAN SOAL secara otomatis.
Kita tidak perlu menuliskan pemeriksaan tambahan sama sekali.
Ini salah satu pemakaian tie-break paling elegan yang akan kamu
temui, dan polanya muncul di banyak soal lain.

── STRICT vs TIDAK TURUN ───────────────────────────────────
Karena syarat bersarang adalah STRICT pada tinggi juga, kita
butuh barisan naik TEGAS:
      lower_bound  -> naik TEGAS   (yang kita pakai)
      upper_bound  -> tidak turun  (salah untuk soal ini)
Salah memilih akan menghitung dua amplop bertinggi sama sebagai
rantai sah.

Sampel 2 (tiga amplop identik) menguji tepat ini: jawabannya 1,
dan dengan upper_bound kamu akan mendapat 3.

── ALGORITMA BARISAN NAIK O(n log n) ───────────────────────
Pelihara array 'tail', dengan tail[k] = ekor TERKECIL dari
semua barisan naik berpanjang k+1 yang pernah ditemukan.
Array ini selalu terurut menaik, sehingga bisa dicari dengan
pencarian biner.
Untuk tiap tinggi h:
      i = lower_bound(tail, h)
      kalau i == ukuran tail -> tambahkan (barisan bertambah panjang)
      kalau tidak            -> tail[i] = h (ekor jadi lebih kecil)
Jawabannya adalah ukuran akhir tail.
Perhatikan: isi tail BUKAN barisan naik yang sesungguhnya,
hanya panjangnya yang benar.

── JEBAKAN ─────────────────────────────────────────────────
1. Tie-break tinggi MENAIK. Menghasilkan jawaban terlalu besar.
2. Memakai upper_bound. Menghasilkan jawaban terlalu besar.
3. Mengira soal ini bisa diselesaikan dengan greedy murni.
   Bukan — inti selesainya tetap barisan naik terpanjang.
4. Menyangka DP O(n^2) cukup. Dengan n = 10^5 itu 10^10.
5. Generator berentang besar. Untuk menguji tie-break, batasi
   lebar dan tinggi ke 1..4.
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
    vector<pair<ll, ll>> e(n);
    for (auto& [w, h] : e) cin >> w >> h;

    // lebar MENAIK; saat lebar seri, tinggi MENURUN
    // tie-break inilah yang membuat lebar sama otomatis ditolak
    sort(e.begin(), e.end(), [](const pair<ll, ll>& x, const pair<ll, ll>& y) {
        if (x.first != y.first) return x.first < y.first;
        return x.second > y.second;
    });

    // barisan naik TEGAS terpanjang pada tinggi
    vector<ll> tail;
    for (auto& [w, h] : e) {
        auto it = lower_bound(tail.begin(), tail.end(), h);   // TEGAS
        if (it == tail.end()) tail.push_back(h);
        else *it = h;
    }

    cout << tail.size() << '\n';
    return 0;
}
