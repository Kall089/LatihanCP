/*
============================================================
✅ Solution 3: Nilai Terdekat
============================================================
Approach: lower_bound + pemeriksaan dua kasus tepi
Complexity: Time O(n log n + q log n) | Space O(n)
Key Insight: Kandidat jawabannya hanya DUA: elemen pertama yang >= x, dan
             elemen tepat sebelumnya. Semua elemen lain pasti lebih jauh
             karena arraynya terurut. Seluruh kesulitan soal ini bukan pada
             pencariannya, melainkan pada dua situasi di mana salah satu
             kandidat TIDAK ADA.

📖 PENJELASAN PENDEKATAN:
1. Urutkan array.
2. i = lowerBound(x).
3. Tiga kasus:
   - i == 0    : tidak ada elemen < x, jawabannya a[0].
   - i == n    : tidak ada elemen >= x, jawabannya a[n-1].
   - selain itu: bandingkan a[i-1] dan a[i].

⚠️ DUA PEMERIKSAAN BATAS ADALAH INTI SOAL INI.
   Tanpa cek i == n, kamu mengakses a[n] -- di luar array.
   Tanpa cek i == 0, kamu mengakses a[-1] -- di luar array.
   Keduanya adalah perilaku tak terdefinisi yang sering TIDAK crash di
   mesin lokal, sehingga lolos dari pengujianmu lalu RE atau WA di judge.
   Sampel sengaja memuat x = 0 (semua elemen lebih besar) dan x = 100
   (semua elemen lebih kecil) untuk menangkap keduanya.

⚠️ ATURAN SERI: soal meminta yang LEBIH KECIL saat sama dekatnya.
   Karena a[i-1] < x <= a[i], kandidat kiri selalu yang lebih kecil.
   Jadi perbandingannya:
       (x - a[i-1] <= a[i] - x) ? a[i-1] : a[i]
   Perhatikan '<=' -- dengan '<' kamu akan memilih yang lebih besar saat
   seri, dan itu salah. Satu karakter menentukan AC atau WA.

⚠️ OVERFLOW PADA SELISIH: dengan nilai sampai 10^9 dan x sampai -10^9,
   selisih a[i] - x bisa mencapai 2*10^9 yang MELUAP di int.
   Solusi ini memakai long long untuk perhitungan selisih.

VERIFIKASI SAMPEL (array terurut [1,2,4,7,10]):
   x=5   -> lb=3 (nilai 7); kandidat 4 dan 7; |5-4|=1 < |7-5|=2 -> 4   ✓
   x=0   -> lb=0 -> kasus tepi kiri -> 1                                ✓
   x=100 -> lb=5 = n -> kasus tepi kanan -> 10                          ✓
   x=6   -> lb=3 (nilai 7); kandidat 4 dan 7; |6-4|=2 > |7-6|=1 -> 7   ✓

🔄 ALTERNATIVE APPROACHES:
- set<int> dengan lower_bound sebagai fungsi anggota: sama logikanya,
  berguna kalau ada penyisipan atau penghapusan di antara query.
- Kalau query-nya juga terurut, two pointers menggantikan binary search
  dan totalnya menjadi O(n + q) setelah pengurutan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& v : a) cin >> v;
    sort(a.begin(), a.end());

    string out;
    while (q--) {
        int x;
        cin >> x;

        int i = lower_bound(a.begin(), a.end(), x) - a.begin();

        int jawab;
        if (i == 0)            jawab = a[0];        // semua elemen >= x
        else if (i == n)       jawab = a[n - 1];    // semua elemen <  x
        else {
            ll kiri  = (ll)x - a[i - 1];
            ll kanan = (ll)a[i] - x;
            jawab = (kiri <= kanan) ? a[i - 1] : a[i];   // '<=' -> pilih kecil
        }

        out += to_string(jawab);
        out += '\n';
    }
    cout << out;

    return 0;
}
