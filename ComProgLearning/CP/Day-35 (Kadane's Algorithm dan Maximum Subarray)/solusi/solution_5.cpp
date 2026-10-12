/*
============================================================
✅ Solution 5: Hasil Kali Subarray Maksimum
============================================================
Approach: Kadane dengan DUA nilai berjalan (maksimum dan minimum)
Complexity: Time O(n) | Space O(1)
Key Insight: Pada penjumlahan, nilai yang buruk selalu tetap buruk. Pada
             perkalian, nilai yang SANGAT NEGATIF adalah aset terpendam --
             sekali bertemu bilangan negatif lain, ia berubah menjadi
             positif yang sangat besar. Karena itu minimum harus ikut
             dilacak, bukan dibuang.

📖 PENJELASAN PENDEKATAN:
1. curMax dan curMin = hasil kali terbesar dan terkecil yang berakhir di i.
2. Kalau a[i] < 0, kalikan dengan negatif membalik urutan: yang terbesar
   menjadi terkecil dan sebaliknya. Jadi TUKAR keduanya sebelum memperbarui.
3. curMax = max(x, curMax * x); curMin = min(x, curMin * x);
   Opsi "x sendirian" mewakili keputusan memulai rantai baru dari sini.
4. best = max(best, curMax).

PERAN ANGKA NOL: kalau x = 0, maka curMax dan curMin keduanya menjadi 0
(karena max(0, apa pun * 0) = 0). Itu benar -- nol memutus rantai perkalian,
dan rantai berikutnya akan dimulai ulang dari elemen setelahnya. Tidak perlu
penanganan khusus, tetapi bagus untuk diyakini lewat sampel 2.

VERIFIKASI SAMPEL 1 (a = [2,-3,-2,4]):
   i=0            curMax=2   curMin=2   best=2
   i=1 x=-3 tukar curMax=-3  curMin=-6  best=2
   i=2 x=-2 tukar (curMax=-6, curMin=-3)
                  curMax=12  curMin=-2  best=12
   i=3 x=4        curMax=48  curMin=-8  best=48   ✓
   Perhatikan langkah i=2: curMin = -6 yang tadinya terlihat buruk berubah
   menjadi 12. Di situlah alasan melacak minimum menjadi nyata.

⚠️ OVERFLOW: soal ini membatasi |a[i]| <= 10 justru supaya hasil kalinya
   tetap muat. Pada soal lain, periksa batasnya -- perkalian meledak jauh
   lebih cepat daripada penjumlahan.

🔄 ALTERNATIVE APPROACHES:
- Sapu dua arah (kiri ke kanan, lalu kanan ke kiri) sambil me-reset saat
  bertemu nol: lebih pendek, tetapi lebih sulit dijelaskan.
- Menghitung lewat logaritma: tidak sah karena ada bilangan negatif dan nol.
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

    ll best = a[0], curMax = a[0], curMin = a[0];

    for (int i = 1; i < n; i++) {
        ll x = a[i];
        if (x < 0) swap(curMax, curMin);    // negatif membalik peran
        curMax = max(x, curMax * x);
        curMin = min(x, curMin * x);
        best = max(best, curMax);
    }

    cout << best << '\n';
    return 0;
}
