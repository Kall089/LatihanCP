/*
============================================================
✅ Solution 4: Cari Batas dengan Predikat
============================================================
Approach: Kerangka first-true pada ruang NILAI
Complexity: Time O(n log(maks)) | Space O(1)
Key Insight: Kerangka yang sama persis dengan lower_bound bekerja pada ruang
             pencarian apa pun yang predikatnya MONOTON -- termasuk ruang
             nilai jawaban, bukan hanya indeks array. Ini adalah jembatan
             menuju "binary search on answer" (Day 50), dan salah satu
             teknik paling sering terpakai di seluruh CP.

📖 PENJELASAN PENDEKATAN:
1. Predikatnya: bisa(x) = "dalam x detik, total produk >= T".
   Monoton karena kalau x detik cukup, x+1 detik pasti juga cukup --
   tidak ada mesin yang menjadi lebih lambat seiring waktu.
2. lo = 1 (0 detik pasti tidak cukup karena T >= 1), hi = batas atas.
3. Kerangka baku, jawabannya lo.

⚠️ MENENTUKAN BATAS ATAS ADALAH BAGIAN NYATA DARI SOAL INI.
   Kasus terburuk: satu mesin dengan t = 10^9 harus membuat T = 10^9 produk,
   sehingga butuh 10^9 * 10^9 = 10^18 detik. Sampel 2 memang menguji ini.
   Kalau kamu memasang hi = 10^9 (tergoda oleh batas t[i] dan T), jawabanmu
   akan terpotong dan salah untuk kasus itu.
   Aturan praktis: hitung kasus TERBURUK secara eksplisit, lalu tambahkan
   sedikit margin. Batas atas yang terlalu besar hanya menambah satu-dua
   iterasi (log2 dari 10^18 adalah 60), jadi kelebihan jauh lebih murah
   daripada kekurangan.

⚠️ OVERFLOW SAAT MENGEVALUASI PREDIKAT:
   Total produk bisa mencapai n * (x / t_min) = 2*10^5 * 10^18 = 2*10^23,
   yang MELUAP bahkan di long long.
   Solusinya: berhenti menjumlahkan segera setelah totalnya mencapai T.
   Kita tidak peduli berapa TEPATNYA totalnya -- hanya apakah sudah >= T.
   Pola "hentikan akumulasi setelah cukup" ini sering diperlukan pada
   binary search on answer, dan mudah terlewat.

⚠️ mid = lo + (hi - lo) / 2 BUKAN LAGI KEBIASAAN BAIK, MELAINKAN KEHARUSAN.
   Dengan lo dan hi mendekati 10^18, (lo + hi) meluap di long long dan
   menghasilkan bilangan negatif. Di sinilah kebiasaan yang dibentuk pada
   Exercise 1 membayar dirinya sendiri.

VERIFIKASI SAMPEL 1 (t = [3,2,5], T = 7):
   x = 8 : 8/3 + 8/2 + 8/5 = 2 + 4 + 1 = 7 >= 7   cukup
   x = 7 : 7/3 + 7/2 + 7/5 = 2 + 3 + 1 = 6 <  7   tidak cukup
   Jadi 8 adalah nilai terkecil yang cukup.  ✓

🔄 ALTERNATIVE APPROACHES:
- Simulasi dengan priority queue: O(T log n) -- untuk T = 10^9 jauh terlalu
  lambat. Ini contoh khas di mana binary search on answer mengubah masalah
  yang mustahil menjadi mudah.
- Pencarian linier atas x: O(maks * n), mustahil.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, T;
    cin >> n >> T;
    vector<ll> t(n);
    for (ll& v : t) cin >> v;

    // Kasus terburuk: satu mesin terlambat harus membuat seluruh T produk
    ll lo = 1, hi = *max_element(t.begin(), t.end()) * T;

    auto bisa = [&](ll x) {
        ll total = 0;
        for (ll ti : t) {
            total += x / ti;
            if (total >= T) return true;   // HENTIKAN: cegah overflow
        }
        return total >= T;
    };

    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;       // WAJIB, (lo+hi) meluap di sini
        if (bisa(mid)) hi = mid;
        else           lo = mid + 1;
    }

    cout << lo << '\n';
    return 0;
}
