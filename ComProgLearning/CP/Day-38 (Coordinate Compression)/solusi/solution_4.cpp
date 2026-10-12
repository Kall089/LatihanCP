/*
============================================================
✅ Solution 4: Total Panjang Tertutup
============================================================
Approach: Sort + sweep satu arah
Complexity: Time O(n log n) | Space O(n)
Key Insight: Soal ini sengaja ditaruh di hari kompresi koordinat justru
             karena ia TIDAK MEMBUTUHKAN kompresi sama sekali. Nilai besar
             tidak otomatis berarti butuh kompresi -- kompresi diperlukan
             hanya kalau kamu butuh ARRAY yang diindeks oleh nilai.
             Di sini kita cuma perlu mengurutkan dan menyapu.

📖 PENJELASAN PENDEKATAN:
1. Urutkan interval berdasarkan ujung kiri.
2. Jaga variabel `akhir` = koordinat terbesar yang sudah tertutup.
3. Untuk tiap interval, bagian barunya dimulai di max(l, akhir + 1).
   Kalau r >= mulai, tambahkan r - mulai + 1 ke total.
4. Perbarui akhir = max(akhir, r).

⚠️ INTERVAL BERSAMBUNG PERSIS: [1,5] dan [6,9] tidak tumpang tindih tetapi
   juga tidak berjarak. Dengan rumus max(l, akhir + 1), interval kedua
   dimulai di max(6, 6) = 6 dan menyumbang 4 -- total 9. Benar.
   Kalau kamu menulis max(l, akhir) tanpa +1, kamu akan menghitung
   koordinat 5 dua kali.

⚠️ INISIALISASI `akhir`: memakai LLONG_MIN lalu menambahkan 1 padanya akan
   overflow. Solusi ini menanganinya dengan pemeriksaan khusus pada
   interval pertama.

VERIFIKASI SAMPEL 1 ([1,3], [2,5], [8,9]):
   [1,3] -> mulai 1, tambah 3, akhir = 3
   [2,5] -> mulai max(2,4) = 4, tambah 2, akhir = 5
   [8,9] -> mulai max(8,6) = 8, tambah 2, akhir = 9
   total = 7  ✓

🔄 ALTERNATIVE APPROACHES:
- Kompresi + difference array: bekerja juga, O(n log n), tetapi lebih
  panjang. Baru sepadan kalau kamu juga butuh informasi PER TITIK
  (lihat Exercise 5).
- Kejadian +1/-1 lalu sweep: setara, dan lebih fleksibel kalau nanti
  soal berkembang.
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
    vector<pair<ll, ll>> iv(n);
    for (auto& pr : iv) cin >> pr.first >> pr.second;

    sort(iv.begin(), iv.end());

    ll total = 0, akhir = 0;
    bool pertama = true;

    for (auto& pr : iv) {
        ll l = pr.first, r = pr.second;
        ll mulai = pertama ? l : max(l, akhir + 1);
        if (r >= mulai) total += r - mulai + 1;
        akhir = pertama ? r : max(akhir, r);
        pertama = false;
    }

    cout << total << '\n';
    return 0;
}
