/*
============================================================
✅ Solution 5: Pasangan Kabel
============================================================
🔑 TEKNIK: SORTING + TWO POINTERS  (Day 32 + Day 43-47)
Complexity: Time O(N log N) | Space O(1) di luar array

📖 FRASA PENENTUNYA: soal meminta PASANGAN, bukan SUBARRAY.
   Kata "berurutan" tidak muncul sama sekali. Itu izin untuk MENGURUTKAN
   data - sesuatu yang haram di Exercise 3, karena di sana urutan asli
   adalah bagian dari soal.

   Mengenali kapan kamu boleh mengurutkan adalah keterampilan tersendiri.
   Tanyakan: apakah jawabannya berubah kalau saya acak urutan inputnya?
   Kalau tidak, kamu boleh sort.

📖 SETELAH DIURUTKAN: kunci pointer kanan j. Semua i < j dengan
   a[i] + a[j] <= S membentuk awalan yang rapat, jadi cukup cari batasnya.
   Karena batas itu bergerak monoton saat j mengecil, two pointers sah.

⚠️ MENGHITUNG SEKALIGUS: saat a[l] + a[r] <= S, SEMUA indeks antara l dan r
   berpasangan sah dengan r. Tambahkan (r - l) sekaligus, jangan satu per
   satu - kalau satu per satu, kompleksitasnya kembali O(N^2).

⚠️ Sample 3 ([1,1,1,1], S = 2 -> 6): semua pasangan sah, jawabannya C(4,2).
   Menguji apakah penambahan borongan kamu benar.

⚠️ N = 1 -> tidak ada pasangan -> 0.

🩺 DIAGNOSIS DIRI:
   Mencoba sliding window      -> kamu mengira ini soal subarray
   Menghitung satu per satu    -> O(N^2), lihat catatan penambahan borongan
   Lupa i < j                  -> jawabanmu jadi dua kali lipat
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll s;
    cin >> n >> s;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    ll res = 0;
    int l = 0, r = n - 1;
    while (l < r) {
        if (a[l] + a[r] <= s) { res += (r - l); l++; }   // borongan
        else r--;
    }

    cout << res << "\n";
    return 0;
}
