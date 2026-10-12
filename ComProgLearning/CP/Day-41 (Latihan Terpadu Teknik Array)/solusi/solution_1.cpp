/*
============================================================
✅ Solution 1: Rata-rata Tertinggi Periode Tetap
============================================================
Approach: jendela geser ukuran tetap (prefix sum implisit)
Complexity: Time O(N) | Space O(1) di luar array input
Key Insight: jumlah jendela berikutnya = jumlah sekarang + elemen masuk
             - elemen keluar. Prefix sum eksplisit juga benar, tapi versi
             geser ini memakai memori O(1) tambahan.

📖 PENJELASAN PENDEKATAN:
1. Hitung jumlah K elemen pertama sebagai jendela awal.
2. Untuk tiap posisi berikutnya, tambahkan a[r] dan kurangi a[r-K].
3. Bandingkan dengan jawaban terbaik.

⚠️ TIE-BREAKING: pakai `>` bukan `>=`. Dengan `>`, jendela pertama yang
   mencapai nilai maksimum yang tersimpan, sehingga indeksnya paling kecil.
   Sample 3 ([4,0,4,0,4,0], K=2) ada khusus untuk menguji ini: semua jendela
   bernilai 4, jawabannya harus indeks 1.

⚠️ OVERFLOW: 2*10^5 elemen bernilai 10^9 -> 2*10^14. Wajib long long.

🔄 ALTERNATIVE APPROACHES:
- Prefix sum eksplisit: P[r+1]-P[l], sama-sama O(N) tapi butuh O(N) memori
  tambahan. Pilih ini kalau soalnya juga punya query rentang lain.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll sum = 0;
    for (int i = 0; i < k; i++) sum += a[i];

    ll best = sum;
    int bestL = 0;

    for (int r = k; r < n; r++) {
        sum += a[r] - a[r - k];
        if (sum > best) { best = sum; bestL = r - k + 1; }
    }

    cout << best << " " << bestL + 1 << "\n";
    return 0;
}
