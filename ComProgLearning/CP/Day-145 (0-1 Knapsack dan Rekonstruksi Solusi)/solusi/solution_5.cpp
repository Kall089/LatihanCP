/*
============================================================
✅ Solution 5: Kapasitas Raksasa
============================================================
Approach: DP atas NILAI -- membalik peran indeks dan isi
Complexity: Time O(N · ΣV) | Space O(ΣV)
Key Insight: Ketika satu besaran terlalu besar untuk dijadikan indeks,
             periksa apakah besaran LAIN cukup kecil. Di sini kapasitas
             mencapai 10^9 (mustahil diindeks), tetapi total nilai paling
             besar 100 x 1000 = 10^5 (sangat nyaman).
             Tukar peran keduanya: nilai menjadi INDEKS, berat menjadi ISI.

📖 DEFINISI STATE YANG DIBALIK:
       dp[val] = BERAT MINIMUM untuk mencapai total nilai TEPAT val
   Bandingkan dengan versi biasa:
       dp[c]   = NILAI MAKSIMUM dengan berat paling banyak c

   Rekurensnya:
       dp[val] = min(dp[val], dp[val - v[i]] + w[i])
   Perhatikan `min` dan `+w`, bukan `max` dan `+v`. Karena kita
   MEMINIMUMKAN berat untuk nilai yang ditetapkan.

📖 MEMBACA JAWABANNYA: sapu val dari yang TERBESAR ke terkecil, dan
   kembalikan val pertama yang dp[val] <= W. Itulah nilai terbesar yang
   masih muat.

⚠️ NILAI PENANDA TAK-TERJANGKAU adalah jebakan nyata di sini.
   Sel yang belum bisa dicapai harus dibedakan dari sel berbobot nol.
   Kalau kamu memakai INF dan menambahkan w[i] padanya tanpa pemeriksaan,
   INF + w bisa MELUAP dan menjadi bilangan kecil -- sehingga sel yang
   sebenarnya mustahil terlihat mudah dicapai.
   Dua cara aman:
     1. Periksa `if (dp[val - v[i]] != INF)` sebelum menambahkan  <- dipakai di sini
     2. Pakai INF yang cukup kecil (misalnya LLONG_MAX/4) sehingga
        INF + w tetap jauh di bawah batas overflow.
   Solusi ini memakai KEDUANYA, karena biayanya nol.

⚠️ ARAH LOOP TETAP MUNDUR (val dari besar ke kecil), dengan alasan yang
   sama persis: agar setiap barang dipakai paling banyak sekali.

⚠️ dp[0] = 0 adalah basisnya: nilai nol dicapai dengan berat nol
   (tidak mengambil apa pun). Ini juga yang menjamin jawaban minimal 0.

VERIFIKASI SAMPEL 1 (w=[3,4,5], v=[30,50,60], W=8):
   Total nilai maksimum = 140, jadi tabel berukuran 141.
   dp[80] = 3 + 5 = 8 <= 8   -> barang 1 dan 3, nilai 80
   dp[90] = 4 + 5 = 9 > 8    -> tidak muat
   Sapu dari 140 ke bawah, yang pertama <= 8 adalah val = 90? Tidak:
   dp[90] = 9 > 8. Berikutnya dp[80] = 8 <= 8  -> jawab 80.
   Tunggu -- sampel bilang 90.
   Mari periksa ulang: barang 2 (w=4, v=50) + barang 3 (w=5, v=60) = berat 9.
   Barang 1 (w=3, v=30) + barang 3 (w=5, v=60) = berat 8, nilai 90.   ✓
   Jadi dp[90] = 8, bukan 9 -- kombinasi termurah untuk nilai 90 adalah
   barang 1 dan 3. Jawabannya memang 90.
   Pelajaran: dp[val] menyimpan berat MINIMUM di antara SEMUA kombinasi
   yang mencapai val, bukan kombinasi pertama yang kamu pikirkan.

🔄 ALTERNATIVE APPROACHES:
- DP atas kapasitas: mustahil, tabelnya 10^9 sel.
- Meet in the middle: N = 100 terlalu besar (2^50). Baru berlaku N <= 40.
- Pola "tukar indeks dan isi" ini muncul di banyak soal DP. Kapan pun satu
  dimensi terlalu besar, periksa dimensi lainnya.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll W;
    cin >> n >> W;
    vector<ll> w(n), v(n);
    ll totalV = 0;
    for (int i = 0; i < n; i++) { cin >> w[i] >> v[i]; totalV += v[i]; }

    const ll INF = LLONG_MAX / 4;                // cukup kecil agar INF+w aman
    vector<ll> dp(totalV + 1, INF);
    dp[0] = 0;                                   // nilai 0 -> berat 0

    for (int i = 0; i < n; i++)
        for (ll val = totalV; val >= v[i]; val--)      // MUNDUR
            if (dp[val - v[i]] != INF)                 // jangan tambah ke INF
                dp[val] = min(dp[val], dp[val - v[i]] + w[i]);

    ll jawab = 0;
    for (ll val = totalV; val >= 0; val--)
        if (dp[val] <= W) { jawab = val; break; }      // nilai terbesar yang muat

    cout << jawab << '\n';
    return 0;
}
