/*
============================================================
✅ Solution 5: Berapa Interval Menutupi Tiap Titik
============================================================
Approach: Sweep line berbasis kejadian + kontribusi per SEGMEN
Complexity: Time O(n log n) | Space O(n)
Key Insight: Kita tidak bisa menandai 10^9 titik satu per satu, tetapi
             hitungan "berapa interval aktif" hanya BERUBAH di 2n tempat:
             di setiap l (naik satu) dan di setiap r+1 (turun satu).
             Di antara dua kejadian berurutan, hitungannya KONSTAN --
             sehingga seluruh segmen itu bisa disumbangkan sekaligus.

📖 PENJELASAN PENDEKATAN:
1. Untuk tiap interval [l, r], buat dua kejadian: (l, +1) dan (r+1, -1).
2. Urutkan seluruh kejadian berdasarkan koordinat.
3. Sapu dari kiri. Sebelum memproses kejadian di koordinat x, seluruh
   bilangan bulat dari koordinat kejadian sebelumnya sampai x-1 tertutup
   oleh `aktif` interval. Tambahkan (x - sebelumnya) ke jawaban[aktif].
4. Baru setelah itu terapkan seluruh delta di koordinat x.

⚠️ KENAPA r+1 DAN BUKAN r:
   Interval [l, r] menutupi r, jadi ia baru berhenti aktif MULAI dari r+1.
   Kalau kamu menaruh kejadian -1 di r, koordinat r akan salah dihitung.
   Ini alasan yang sama persis dengan kenapa kompresi interval harus
   memasukkan r+1 ke dalam kamus: setengah terbuka [l, r+1) jauh lebih
   mudah dikelola daripada tertutup [l, r].

⚠️ KEJADIAN DENGAN KOORDINAT SAMA harus diproses BERSAMAAN, setelah
   menyumbangkan segmen sebelumnya. Kalau kamu memprosesnya satu per satu
   sambil menyumbang di antaranya, kamu akan menyumbang segmen berpanjang
   nol dengan hitungan yang salah -- tidak berbahaya untuk panjang nol,
   tetapi menandakan logika yang rapuh.

⚠️ TIPE DATA: panjang segmen bisa mencapai 2*10^9, dan jumlahnya lebih
   besar lagi. long long wajib. Koordinat r+1 juga bisa melewati 10^9,
   jadi bacalah sebagai long long sejak awal.

VERIFIKASI SAMPEL 1 (interval [0,3], [1,3], [3,8]):
   kejadian: (0,+1) (1,+1) (3,+1) (4,-1) (4,-1) (9,-1)
   0..0  aktif 1 -> jawab[1] += 1
   1..2  aktif 2 -> jawab[2] += 2
   3..3  aktif 3 -> jawab[3] += 1
   4..8  aktif 1 -> jawab[1] += 5
   hasil: jawab[1] = 6, jawab[2] = 2, jawab[3] = 1  ✓

🔄 ALTERNATIVE APPROACHES:
- Kompresi koordinat + difference array atas indeks terkompresi: setara
  persis, hanya beda cara mengorganisasi. Berguna kalau kamu juga butuh
  menyimpan sesuatu per segmen.
- Menandai tiap titik: O(rentang koordinat) -- mustahil di sini.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<ll, int>> ev;
    ev.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        ev.push_back({l, +1});
        ev.push_back({r + 1, -1});     // berhenti aktif MULAI dari r+1
    }
    sort(ev.begin(), ev.end());

    vector<ll> jawab(n + 2, 0);
    ll aktif = 0, sebelumnya = 0;
    bool mulai = false;

    for (size_t i = 0; i < ev.size(); ) {
        ll x = ev[i].first;

        // segmen [sebelumnya, x-1] tertutup oleh `aktif` interval
        if (mulai && aktif > 0 && x > sebelumnya)
            jawab[aktif] += x - sebelumnya;

        // proses SEMUA kejadian di koordinat x sekaligus
        while (i < ev.size() && ev[i].first == x) {
            aktif += ev[i].second;
            i++;
        }
        sebelumnya = x;
        mulai = true;
    }

    string out;
    for (int k = 1; k <= n; k++) {
        out += to_string(jawab[k]);
        out += (k == n) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
