/*
============================================================
✅ Solution 2: Subarray Maksimum Beserta Posisinya
============================================================
Approach: Kadane + satu variabel penanda awal
Complexity: Time O(n) | Space O(1)
Key Insight: Indeks awal subarray yang sedang dibangun hanya berubah pada
             SATU momen: saat kita memutuskan untuk memulai baru. Kalau kamu
             memperbaruinya di tempat lain, jawabannya akan meleset.

📖 PENJELASAN PENDEKATAN:
1. curL = indeks awal subarray yang sedang dibangun.
2. Kalau cur + a[i] < a[i], berarti membawa beban lama merugikan:
   mulai baru, cur = a[i], curL = i.
   Selain itu, cur += a[i] dan curL tidak berubah.
3. Kalau cur > best, simpan best beserta [curL, i].

⚠️ TIE-BREAKING lewat pilihan operator:
   `if (cur > best)`  -> menyimpan yang PERTAMA kali mencapai nilai maksimum,
                         sehingga indeks awalnya paling kecil.  <- soal ini
   `if (cur >= best)` -> akan terus menimpa dengan yang lebih belakang.
   Satu karakter, dua perilaku berbeda. Perhatikan permintaan soal.

⚠️ KONDISI MULAI BARU: pakai `cur + a[i] < a[i]` (setara dengan `cur < 0`).
   Kalau ditulis `<=`, saat cur == 0 kamu akan memulai baru padahal tidak
   perlu, dan indeks awalnya jadi lebih besar dari yang diminta.

VERIFIKASI SAMPEL 1 (a = [-2,1,-3,4,-1,2,1,-5,4]):
   i=3: cur = -2, -2+4 = 2 < 4 -> mulai baru, curL = 3
   i=6: cur = 6 -> best = 6, [3, 6] 0-based -> [4, 7] 1-based  ✓

🔄 ALTERNATIVE APPROACHES:
- Versi prefix: simpan indeks di mana minPre tercapai; l = indeks itu + 1.
  Setara, tapi sedikit lebih rawan off-by-one.
- Rekonstruksi setelah selesai: jalankan Kadane dua kali, sekali untuk nilai
  dan sekali mundur untuk mencari batasnya. Tidak perlu -- lebih rumit.
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
    for (ll& v : a) cin >> v;

    ll best = LLONG_MIN, cur = 0;
    int bl = 0, br = 0, curL = 0;

    for (int i = 0; i < n; i++) {
        if (cur + a[i] < a[i]) {       // membawa beban lama merugikan
            cur = a[i];
            curL = i;
        } else {
            cur += a[i];
        }
        if (cur > best) {              // '>' bukan '>=': ambil yang paling awal
            best = cur;
            bl = curL;
            br = i;
        }
    }

    cout << best << ' ' << bl + 1 << ' ' << br + 1 << '\n';
    return 0;
}
