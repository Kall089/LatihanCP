/*
============================================================
✅ SOLUSI Exercise 2: Menghapus Jadwal Bentrok
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── IDE UTAMA ────────────────────────────────────────────────
Ini Exercise 1 dalam penyamaran. Kalau jumlah maksimum acara
yang bisa DIPERTAHANKAN tanpa bentrok adalah k, maka jumlah
minimum yang harus DIHAPUS adalah n - k.

── KENAPA HUBUNGAN ITU BENAR ───────────────────────────────
Himpunan yang tersisa setelah penghapusan harus saling lepas.
Jadi setiap cara penghapusan yang sah berpasangan satu-satu
dengan sebuah himpunan saling lepas. Menghapus sesedikit
mungkin sama persis dengan mempertahankan sebanyak mungkin.
Tidak ada algoritma baru yang perlu dipelajari.

── PERBEDAAN PENTING DARI EXERCISE 1 ───────────────────────
Di sini rentangnya TERTUTUP, dan bersentuhan di satu titik pun
dihitung bentrok. Maka syaratnya l[i] > akhir (STRICT).

Periksa sampel 1: [1,2] [2,3] [3,4] [1,3].
Urut menurut r: [1,2](r=2), [1,3](r=3), [2,3](r=3), [3,4](r=4).
  ambil [1,2], akhir = 2
  [1,3] : 1 > 2 ? tidak
  [2,3] : 2 > 2 ? tidak  ← inilah gunanya STRICT
  [3,4] : 3 > 2 ? ya → ambil, akhir = 4
Maksimal 2, jadi dihapus 4 - 2 = 2. ✓

Kalau kamu memakai >= (seperti Exercise 1), kamu akan mendapat
3 acara dan menjawab 1 — salah.

── PELAJARAN ───────────────────────────────────────────────
Dua soal ini SENGAJA dipasangkan berurutan agar kamu terbiasa
bertanya "tertutup atau setengah terbuka?" setiap kali melihat
soal interval, bukan hanya saat WA.

── JEBAKAN ─────────────────────────────────────────────────
1. Menulis algoritma baru untuk "minimal dihapus". Tidak perlu.
2. Menyalin > atau >= dari soal sebelumnya tanpa berpikir.
3. l[i] boleh sama dengan r[i] (acara sesaat). Kode ini tetap
   benar — periksa sendiri pada sampel 2.
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

    int simpan = 0;
    ll akhir = LLONG_MIN;
    for (auto& [r, l] : a) {
        if (l > akhir) {                    // TERTUTUP: strict
            simpan++;
            akhir = r;
        }
    }

    cout << n - simpan << '\n';
    return 0;
}
