/*
============================================================
✅ Solution 2: Partisi Genap-Ganjil
============================================================
Approach: Partisi Lomuto dengan predikat kustom
Complexity: Time O(n) | Space O(1)
Key Insight: Partisi bukan hanya "bagian dari quicksort" -- ia adalah pola
             tersendiri: menyusun ulang array berdasarkan sebuah PREDIKAT
             dalam satu sapuan tanpa memori tambahan. Begitu kamu melihatnya
             sebagai pola, ia muncul di banyak soal yang tidak ada
             hubungannya dengan pengurutan.

📖 PENJELASAN PENDEKATAN:
1. Jaga penunjuk `batas`: seluruh a[0 .. batas-1] sudah dipastikan genap.
2. Jelajahi j dari 0 sampai n-1. Kalau a[j] genap, tukar dengan a[batas]
   lalu majukan batas.
3. Setelah selesai, `batas` sekaligus menjadi JUMLAH bilangan genap --
   informasi itu gratis, tidak perlu dihitung ulang.

INVARIANT: a[0 .. batas-1] genap, a[batas .. j-1] ganjil.
Setiap langkah menjaga invariant ini, dan saat j mencapai n, seluruh array
sudah terpartisi.

⚠️ KEGENAPAN BILANGAN NEGATIF: di C++, (-3) % 2 bernilai -1, bukan 1.
   Jadi `x % 2 == 1` GAGAL mendeteksi ganjil negatif.
   Cara aman: `x % 2 == 0` untuk genap -- ini benar untuk seluruh bilangan
   bulat, positif maupun negatif. Solusi ini memakainya.

⚠️ URUTAN DI DALAM KELOMPOK TIDAK TERJAGA. Kalau soal menuntut urutan asli
   di dalam masing-masing kelompok, partisi biasa TIDAK cukup -- kamu butuh
   stable_partition, yang O(n) dengan memori tambahan atau O(n log n) tanpa.
   Baca soal baik-baik untuk memastikan mana yang diminta.

🔄 ALTERNATIVE APPROACHES:
- std::partition(a.begin(), a.end(), pred): melakukan persis ini dalam satu
  baris dan mengembalikan iterator batasnya. Di kontes, pakai ini.
  Kita menulisnya sendiri di sini untuk memahami polanya.
- Dua pointer dari kedua ujung (kiri cari ganjil, kanan cari genap, tukar):
  melakukan lebih SEDIKIT pertukaran, tetapi sedikit lebih rumit.
- Membuat dua vector terpisah lalu menggabungkan: O(n) waktu tetapi O(n)
  memori tambahan, dan melanggar syarat in-place.
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
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int batas = 0;                        // a[0..batas-1] dipastikan genap
    for (int j = 0; j < n; j++)
        if (a[j] % 2 == 0)                // aman untuk bilangan negatif
            swap(a[batas++], a[j]);

    string out;
    for (int i = 0; i < n; i++) {
        out += to_string(a[i]);
        out += (i + 1 == n) ? '\n' : ' ';
    }
    out += to_string(batas);              // batas = jumlah genap, gratis
    out += '\n';
    cout << out;

    return 0;
}
