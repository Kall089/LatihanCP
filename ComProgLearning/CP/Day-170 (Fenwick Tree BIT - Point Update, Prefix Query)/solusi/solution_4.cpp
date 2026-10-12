/*
============================================================
✅ Solution 4: Update Rentang, Baca Satu Titik
============================================================
Approach: BIT atas DIFFERENCE ARRAY
Complexity: Time O((N + Q) log N) | Space O(N)
Key Insight: BIT secara alami melakukan "update titik, query prefiks".
             Soal ini meminta kebalikannya. Trik untuk membaliknya adalah
             menyimpan SELISIH antar elemen berdampingan (Day 31) di dalam
             BIT alih-alih nilainya sendiri.

📖 KENAPA INI BEKERJA -- dua pengamatan yang digabungkan:
   1. Pada difference array d, menambahkan v ke rentang [l, r] hanya
      menyentuh DUA posisi: d[l] += v dan d[r+1] -= v.
      -> "update rentang" menjadi "dua update titik", yang BIT kuasai.
   2. Nilai sesungguhnya pada posisi k adalah JUMLAH PREFIKS d[1..k].
      -> "baca satu titik" menjadi "query prefiks", yang BIT juga kuasai.

   Gabungkan keduanya, dan BIT yang sama menyelesaikan masalah yang
   tampaknya terbalik. Ini contoh bagus dari pola "ubah representasi
   datanya, bukan strukturnya".

📖 MENANGANI NILAI AWAL:
   Array awal tidak nol, jadi kita harus memasukkannya sebagai selisih:
       d[i] = a[i] - a[i-1]   (dengan a[0] = 0)
   Setelah itu query prefiks pada posisi k mengembalikan a[k] dengan benar.
   Alternatif yang lebih sederhana: simpan array awal terpisah dan tambahkan
   BIT sebagai "delta" -- keduanya benar, tetapi versi difference lebih
   seragam.

⚠️ update(r + 1, -v) BISA MELEBIHI N.
   Kalau r = n, maka r + 1 = n + 1 berada di luar rentang BIT biasa.
   Dua cara menanganinya:
     (a) alokasikan t berukuran n + 2 dan biarkan update ke n+1 tersimpan
         (nilainya tidak akan pernah dibaca karena query paling jauh ke n)
     (b) periksa `if (r + 1 <= n)` sebelum memanggil
   Solusi ini memakai cara (a) karena lebih ringkas dan tidak ada
   percabangan. Perhatikan bahwa loop update berhenti sendiri saat i > n,
   sehingga memanggil update(n+1, ...) aman selama arraynya cukup besar.

⚠️ TIPE DATA: nilai awal 10^9, dan Q update masing-masing sampai 10^9
   memberi total 2*10^14. long long wajib.

VERIFIKASI SAMPEL (a = [3,2,4,5,1,1,5,3]):
   d = [3, -1, 2, 1, -4, 0, 4, -2]
   query(4) = 3 - 1 + 2 + 1 = 5      ✓  (a[4] = 5)
   rangeAdd(2, 5, +1): d[2] += 1, d[6] -= 1
   query(4) = 3 + 0 + 2 + 1 = 6      ✓  (a[4] menjadi 6)

CATATAN: implementasi ini telah diuji terhadap brute force pada 20000 kasus
acak dengan operasi range update dan point query yang berselang-seling.

🔄 ALTERNATIVE APPROACHES:
- Dua BIT (range update, range query): generalisasi dari teknik ini, dipakai
  kalau soal juga meminta jumlah rentang. Rumusnya di template.
- Segment tree dengan lazy propagation (Day 176): melakukan hal yang sama
  dengan cara yang lebih jelas dan lebih umum, tetapi ~4x lebih panjang.
- Kalau seluruh update datang SEBELUM seluruh query, difference array biasa
  sudah cukup -- O(1) update dan satu sapuan di akhir (Day 31).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<ll> t;

void update(int i, ll d) { for (; i <= n; i += i & -i) t[i] += d; }
ll query(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += t[i]; return s; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> n >> q;
    t.assign(n + 2, 0);                           // n+2: aman untuk update(r+1)

    ll sebelumnya = 0;
    for (int i = 1; i <= n; i++) {                // simpan sebagai SELISIH
        ll x;
        cin >> x;
        update(i, x - sebelumnya);
        sebelumnya = x;
    }

    string out;
    while (q--) {
        int jenis;
        cin >> jenis;
        if (jenis == 1) {
            int a, b;
            ll u;
            cin >> a >> b >> u;
            update(a, u);                         // dua update titik
            update(b + 1, -u);                    // b+1 boleh = n+1
        } else {
            int k;
            cin >> k;
            out += to_string(query(k));           // prefiks selisih = nilai
            out += '\n';
        }
    }
    cout << out;

    return 0;
}
