/*
============================================================
✅ Solution 1: Jumlah Subarray Maksimum
============================================================
Approach: Kadane (DP satu dimensi dengan rolling variable)
Complexity: Time O(n) | Space O(1)
Key Insight: dp[i] = jumlah maksimum subarray yang BERAKHIR TEPAT di i.
             Hanya ada dua pilihan: perpanjang yang sebelumnya, atau mulai
             baru. Karena dp[i] cuma butuh dp[i-1], arraynya bisa diganti
             satu variabel -- itulah kenapa Kadane terlihat seperti "trik"
             padahal ia DP biasa.

📖 PENJELASAN PENDEKATAN:
1. dp[i] = max(dp[i-1] + a[i], a[i]) = a[i] + max(dp[i-1], 0).
   Terjemahan intuitifnya: kalau beban yang dibawa dari belakang bernilai
   negatif, buang saja -- beban itu tidak akan pernah membantu.
2. Jawabannya max atas seluruh dp[i].

⚠️ INISIALISASI ADALAH SELURUH SOALNYA.
   best = 0        -> berarti "subarray boleh kosong"
   best = LLONG_MIN -> berarti "subarray tidak boleh kosong"   <- soal ini
   Pada a = [-5,-2,-9], versi pertama menjawab 0 (SALAH) dan versi kedua
   menjawab -2 (BENAR). Sampel 2 memang ditaruh untuk menangkap ini.

CARA PANDANG SETARA (prefix sum):
   jumlah a[l..r] = pre[r+1] - pre[l]
   Untuk r tetap, maksimalkan dengan memakai pre[l] TERKECIL sejauh ini:
       cur += x; best = max(best, cur - minPre); minPre = min(minPre, cur);
   Urutan penting: hitung best DULU, baru perbarui minPre -- kalau dibalik,
   kamu mengizinkan subarray kosong.
   Dua cara pandang ini benar-benar setara; pakai yang lebih jelas bagimu.

⚠️ OVERFLOW: 2*10^5 elemen bernilai 10^9 -> 2*10^14. long long wajib.

🔄 ALTERNATIVE APPROACHES:
- Naif O(n^2): coba semua (l, r). Cukup untuk n <= 5000, dan sangat berguna
  sebagai pembanding saat stress test.
- Divide and conquer O(n log n): jawaban ada di kiri, kanan, atau melintasi
  tengah. Lebih lambat, tetapi polanya penting untuk segment tree
  (Day 174 -- "max subarray segment").
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

    ll best = LLONG_MIN, cur = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        cur = max(x, cur + x);         // mulai baru, atau lanjutkan
        best = max(best, cur);
    }

    cout << best << '\n';
    return 0;
}
