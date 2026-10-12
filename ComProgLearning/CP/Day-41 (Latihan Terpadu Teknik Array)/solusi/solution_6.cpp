/*
============================================================
✅ Solution 6: Kepadatan Pengunjung Maksimum
============================================================
Approach: sweep line (difference array pada koordinat terkompresi)
Complexity: Time O(N log N) karena sorting | Space O(N)
Key Insight: difference array bekerja dengan menyimpan PERUBAHAN, bukan nilai.
             Kalau sumbu waktunya terlalu besar untuk dijadikan array, simpan
             saja perubahan-perubahan itu sebagai daftar peristiwa dan urutkan.
             Sweep line dan difference array adalah gagasan yang sama; yang satu
             pada array padat, yang satu pada daftar jarang.

📖 PENJELASAN PENDEKATAN:
1. Setiap interval [L, R] menghasilkan dua peristiwa: (L, +1) dan (R+1, -1).
2. Urutkan semua 2N peristiwa berdasarkan waktu.
3. Sapu dari kiri ke kanan sambil menjumlahkan delta; nilai tertinggi yang
   pernah dicapai adalah jawabannya.

⚠️ KENAPA R+1, BUKAN R: intervalnya TERTUTUP, jadi pengunjung masih ada di
   dalam pada detik R. Kalau kamu memakai (R, -1), ia dianggap sudah keluar
   tepat di detik R dan jawabannya akan kurang satu.
   Sample 2 ([1,5], [5,9], [5,5] -> 3) dirancang khusus untuk menangkap ini.
   Dengan R saja jawabannya keliru menjadi 2.

⚠️ URUTAN PERISTIWA PADA WAKTU SAMA: begitu kamu memakai R+1, urutan +1 dan
   -1 pada waktu yang sama TIDAK lagi berpengaruh pada nilai maksimum. Sebab
   peristiwa -1 pada waktu t berarti "sudah keluar sejak awal detik t", dan
   peristiwa +1 pada waktu t berarti "masuk di awal detik t" - keduanya sah
   diproses dalam urutan apa pun karena keduanya menggambarkan keadaan pada
   detik t yang sama. Kalau kamu memakai (R, -1), urutannya jadi krusial, dan
   itu sumber bug tambahan. Satu lagi alasan memilih R+1.

⚠️ OVERFLOW: R + 1 dengan R = 10^9 masih muat di int, tapi pakai long long
   saja supaya tidak perlu memikirkannya.

🔄 ALTERNATIVE APPROACHES:
- Kompresi koordinat eksplisit + difference array pada indeks terkompresi:
  benar-benar setara, hanya lebih panjang. Berguna kalau kamu juga perlu
  MENANYAI keadaan pada waktu tertentu, bukan sekadar maksimumnya.
- Dua array terpisah (semua L diurutkan, semua R diurutkan) lalu two pointers:
  juga O(N log N), sedikit lebih pendek, tapi kurang bisa digeneralisasi.
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

    vector<pair<ll,int>> ev;      // (waktu, delta)
    ev.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        ev.push_back({l, +1});
        ev.push_back({r + 1, -1});
    }

    sort(ev.begin(), ev.end());

    ll cur = 0, best = 0;
    for (auto& e : ev) {
        cur += e.second;
        best = max(best, cur);
    }

    cout << best << "\n";
    return 0;
}
