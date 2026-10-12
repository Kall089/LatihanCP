/*
============================================================
✅ Solution 4: Paling Banyak K Jenis
============================================================
Approach: Sliding window + hitungan frekuensi per jenis
Complexity: Time O(n log n) | Space O(n)
Key Insight: Predikat "paling banyak K jenis" bersifat monoton: memperlebar
             window hanya bisa menambah jenis, tidak pernah mengurangi.
             Itu izin yang kita perlukan untuk memakai window.

📖 PENJELASAN PENDEKATAN:
1. cnt[nilai] = berapa kali nilai itu muncul DI DALAM window.
   jenis = berapa nilai berbeda yang cnt-nya > 0.
2. Masuk : if (cnt[x]++ == 0) jenis++;
   Keluar: if (--cnt[x] == 0) jenis--;
   Kedua baris ini harus bercermin. Menulis salah satunya terbalik
   (misalnya ++cnt[x] == 1 di satu tempat dan cnt[x]-- == 1 di tempat lain)
   adalah sumber bug yang sangat sulit dilihat.
3. Susutkan selama jenis > K, lalu catat panjang.

VERIFIKASI SAMPEL 1 (a = [1,2,1,2,3,3], K = 2):
   r=0 {1}         jenis=1  panjang 1
   r=1 {1,2}       jenis=2  panjang 2
   r=2 {1,2}       jenis=2  panjang 3
   r=3 {1,2}       jenis=2  panjang 4   <- best
   r=4 {1,2,3}     jenis=3 -> susut sampai l=4, {3} panjang 1
   r=5 {3}         jenis=1  panjang 2
   jawab 4  ✓

CATATAN MEMORI: cnt tidak pernah dibersihkan, tetapi entri yang nilainya 0
tidak mengganggu kebenaran. Kalau kamu peduli memori, hapus entri saat
mencapai nol -- itu menambah biaya kecil tapi menjaga map tetap ramping.

🔄 ALTERNATIVE APPROACHES:
- Kompresi koordinat + array hitungan: O(n log n) kompresi, lalu O(n).
  Jauh lebih cepat untuk n besar.
- Kalau K = 2 secara khusus, ada solusi dua-variabel tanpa map, tetapi
  tidak bisa digeneralisasi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (int& v : a) cin >> v;

    map<int, int> cnt;
    int l = 0, best = 0, jenis = 0;

    for (int r = 0; r < n; r++) {
        if (cnt[a[r]]++ == 0) jenis++;         // masuk
        while (jenis > K) {
            if (--cnt[a[l]] == 0) jenis--;     // keluar
            l++;
        }
        best = max(best, r - l + 1);
    }

    cout << best << '\n';
    return 0;
}
