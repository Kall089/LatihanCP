/*
============================================================
✅ Solution 1: Segmen Terpanjang dengan Jumlah Terbatas
============================================================
Approach: Sliding window ukuran variabel, varian TERPANJANG
Complexity: Time O(n) | Space O(1)
Key Insight: Karena semua a[i] positif, menambah elemen SELALU menaikkan
             jumlah. Sifat monoton inilah yang membuat ujung kiri tidak
             pernah perlu mundur — dan tanpa sifat itu, seluruh teknik ini
             tidak sah.

📖 PENJELASAN PENDEKATAN:
1. Perluas ujung kanan satu langkah: sum += a[r].
2. Selama window TIDAK layak (sum > T), majukan ujung kiri.
3. Catat panjang SETELAH window kembali layak.

MENGAPA O(n) DAN BUKAN O(n^2): kelihatannya ada loop bersarang, tetapi l
hanya bisa maju, maksimal n langkah sepanjang SELURUH program. Jadi total
kerja = n (gerakan r) + n (gerakan l) = O(n). Ini argumen amortisasi yang
sama dengan KMP.

EDGE CASE a[i] > T: window akan menyusut sampai kosong, l menjadi r+1,
dan r - l + 1 bernilai 0 -- bukan negatif. Kerangka ini aman tanpa
penanganan khusus, seperti terlihat pada sampel 2.

⚠️ Kalau soal mengizinkan a[i] = 0, teknik ini TETAP sah (jumlah tidak
   pernah turun). Yang merusak adalah a[i] NEGATIF.

🔄 ALTERNATIVE APPROACHES:
- Prefix sum + binary search: O(n log n). Bekerja juga, tapi lebih lambat
  dan lebih panjang.
- Naif O(n^2): cukup untuk n <= 5000.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll T;
    cin >> n >> T;
    vector<ll> a(n);
    for (ll& v : a) cin >> v;

    int l = 0, best = 0;
    ll sum = 0;

    for (int r = 0; r < n; r++) {
        sum += a[r];                       // masuk
        while (sum > T) {                  // selama TIDAK layak
            sum -= a[l];
            l++;
        }
        best = max(best, r - l + 1);       // catat SETELAH menyusut
    }

    cout << best << '\n';
    return 0;
}
