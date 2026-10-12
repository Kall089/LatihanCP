/*
============================================================
✅ Solution 3: Perampok Rumah
============================================================
Approach: DP 1D "sampai i", rolling variable
Complexity: Time O(N) | Space O(1)
Key Insight: Untuk setiap rumah hanya ada dua kemungkinan -- dirampok atau
             tidak. Kalau dirampok, tetangga kirinya haram, jadi kita
             menyambung dari dp[i-2]. Kalau tidak, hasilnya sama dengan
             dp[i-1]. Ambil yang lebih besar.

📖 REKURENS:
   dp[i] = max(dp[i-1], dp[i-2] + a[i])
   dp[i] didefinisikan sebagai "SAMPAI i" (rumah i boleh dipakai atau tidak),
   sehingga jawabannya dp[n-1] -- BUKAN max atas seluruh dp.
   (Bandingkan dengan Kadane di Solution 6, yang definisinya berbeda.)

⚠️ GREEDY SELANG-SELING SALAH.
   Sampel 1 [2,1,1,2]: indeks genap memberi 2+1=3, indeks ganjil memberi
   1+2=3, tapi jawaban benar 2+2=4 (rumah 0 dan 3, yang TIDAK bersebelahan).
   Soal ini sering "kelihatan greedy" dan itulah jebakannya.

⚠️ URUTAN PENUGASAN ROLLING VARIABLE.
       c = max(p1, p2 + x);
       p2 = p1;        <-- HARUS mendahului
       p1 = c;
   Terbalik, keduanya rusak dan hasilnya salah tanpa peringatan.

⚠️ INISIALISASI p1 = p2 = 0 SUDAH MENANGANI n=1 DAN n=2.
   Ini bukan kebetulan: dp[-1] = dp[-2] = 0 adalah definisi yang konsisten
   ("tidak ada rumah, hasilnya nol"). Jadi kamu TIDAK perlu if khusus.
   Sampel 3 mengujinya.

⚠️ long long. 2*10^5 rumah * 10^9 = 2*10^14.

VERIFIKASI SAMPEL 1 ([2,1,1,2]):
   x=2: c=max(0, 0+2)=2 ; p2=0 p1=2
   x=1: c=max(2, 0+1)=2 ; p2=2 p1=2
   x=1: c=max(2, 2+1)=3 ; p2=2 p1=3
   x=2: c=max(3, 2+2)=4 ; p2=3 p1=4
   jawaban 4  ✓

🔄 ALTERNATIVE APPROACHES:
- Dua state eksplisit: ambil[i] dan lewat[i]. Lebih panjang tapi lebih mudah
  diperluas (misalnya kalau larangannya "tidak boleh dua dalam jarak 3").
- Rekonstruksi (rumah mana saja): butuh array dp penuh; telusuri balik dan
  bandingkan dp[i] dengan dp[i-1]. Lihat template bagian 2c.
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
    ll p2 = 0, p1 = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        ll c = max(p1, p2 + x);
        p2 = p1;                     // URUTAN INI WAJIB
        p1 = c;
    }
    cout << p1 << '\n';
    return 0;
}
