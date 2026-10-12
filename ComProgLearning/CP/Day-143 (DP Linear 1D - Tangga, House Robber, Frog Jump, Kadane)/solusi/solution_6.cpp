/*
============================================================
✅ Solution 6: Kadane + Rekonstruksi Indeks
============================================================
Approach: DP "berakhir tepat di i" dengan memori digulung
Complexity: Time O(N) | Space O(1)
Key Insight: Definisi yang benar BUKAN "jumlah terbaik sampai i" -- itu buntu,
             karena kita tidak tahu apakah subarray terbaik sampai i-1 bisa
             DISAMBUNG dengan a[i]. Definisi yang bekerja adalah "jumlah
             terbaik dari subarray yang BERAKHIR TEPAT di i".

📖 MENURUNKAN KADANE (ia BUKAN trik, ia DP):
   dp[i] = jumlah maksimum subarray yang berakhir tepat di i
   keputusan terakhir: subarray itu hanya berisi a[i], ATAU merupakan
   perpanjangan dari yang berakhir di i-1.
       dp[i] = max(a[i], dp[i-1] + a[i])
   Karena definisinya "berakhir TEPAT di i", jawabannya adalah
       max atas SELURUH dp[i]   <-- BUKAN dp[n-1]
   Ini perbedaan pokok dengan house robber (Solution 3).
   Karena dp[i] hanya butuh dp[i-1], satu variabel cur sudah cukup.

⚠️ best DIINISIALISASI a[0], BUKAN 0.
   Kalau semua elemen negatif, jawaban benar adalah elemen terbesar (subarray
   tidak boleh kosong). Dengan best = 0 kamu akan menjawab 0. Sampel 2
   menguji ini secara khusus, dan ini adalah kesalahan paling umum pada
   soal Kadane.
   PENGECUALIAN: beberapa soal MENGIZINKAN subarray kosong. Baca soalnya.

⚠️ REKONSTRUKSI -- DUA if YANG TERPISAH.
   s  (calon awal) diperbarui HANYA saat MULAI ULANG.
   bs/be diperbarui HANYA saat ada REKOR BARU.
   Menggabungkannya menjadi satu if adalah bug klasik: indeks awalnya lalu
   ikut berubah pada iterasi yang tidak memecahkan rekor.

⚠️ "INDEKS AWAL TERKECIL" -> pakai perbandingan KETAT.
   cur > best  (bukan >=) untuk rekor, dan a[i] > cur + a[i] (bukan >=) untuk
   mulai ulang. Dengan >= kamu akan bergeser ke jawaban yang lebih kanan.

⚠️ long long. 2*10^5 * 10^9 = 2*10^14.

VERIFIKASI SAMPEL 1 ([-2,1,-3,4,-1,2,1,-5,4]):
   i=0: cur=-2 best=-2 s=0
   i=1: 1 > -2+1=-1 -> cur=1 s=1 ; best=1 bs=be=1
   i=2: cur=1-3=-2  ; tidak rekor
   i=3: 4 > -2+4=2  -> cur=4 s=3 ; best=4 bs=3 be=3
   i=4: cur=3       ; tidak rekor
   i=5: cur=5       ; best=5 bs=3 be=5
   i=6: cur=6       ; best=6 bs=3 be=6
   i=7: cur=1 ; i=8: cur=5 ; tidak rekor
   jawaban 6, [3,6]  ✓

VERIFIKASI SAMPEL 2 ([-5,-2,-9]):
   i=0: cur=best=-5
   i=1: -2 > -5-2=-7 -> cur=-2 s=1 ; -2 > -5 -> best=-2 bs=be=1
   i=2: -9 > -2-9=-11 -> cur=-9 s=2 ; tidak rekor
   jawaban -2, [1,1]  ✓

🔄 ALTERNATIVE APPROACHES:
- Prefix sum + minimum prefiks sejauh ini: best = max(P[i] - minP[j<i]).
  Setara, dan lebih mudah diperluas ke "subarray dengan panjang minimum L".
- Divide and conquer O(n log n): berguna sebagai latihan, tapi kalah cepat.
- Varian: MELINGKAR (max(kadaneMax, total - kadaneMin), hati-hati kalau semua
  negatif) dan PRODUK maksimum (simpan max DAN min karena negatif membalik
  peran). Keduanya ada di template.
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
    vector<ll> a(n);
    for (auto& x : a) cin >> x;

    ll cur = a[0], best = a[0];
    int s = 0, bs = 0, be = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > cur + a[i]) { cur = a[i]; s = i; }   // MULAI ULANG
        else                     cur = cur + a[i];
        if (cur > best) { best = cur; bs = s; be = i; } // REKOR BARU
    }

    cout << best << '\n' << bs << ' ' << be << '\n';
    return 0;
}
