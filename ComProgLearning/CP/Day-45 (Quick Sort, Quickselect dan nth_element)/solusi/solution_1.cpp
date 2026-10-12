/*
============================================================
✅ Solution 1: Elemen Terbesar ke-K
============================================================
Approach: nth_element (introselect)
Complexity: Time O(n) | Space O(1)
Key Insight: Kalau kamu hanya butuh SATU nilai pada posisi tertentu, kamu
             tidak perlu mengurutkan seluruh array. nth_element menempatkan
             satu elemen di posisi finalnya dan mempartisi sisanya --
             pekerjaan yang jauh lebih sedikit daripada pengurutan penuh.

📖 PENJELASAN PENDEKATAN:
1. "Terbesar ke-K" pada array yang diurutkan MENAIK berada di indeks n - K.
   Verifikasi cepat: terbesar ke-1 -> indeks n-1 (elemen terakhir). Benar.
2. nth_element(a.begin(), a.begin() + (n - K), a.end());
3. Jawabannya a[n - K].

SETELAH nth_element, JAMINANNYA:
   a[0 .. pos-1]  <=  a[pos]  <=  a[pos+1 .. n-1]
   Tetapi kedua sisi TIDAK terurut. Jangan mengira array sudah rapi.

⚠️ KONVERSI INDEKS adalah satu-satunya jebakan di soal ini.
   "terbesar ke-K"  -> indeks n - K   (pada urutan menaik)
   "terkecil ke-K"  -> indeks K - 1
   Salah satu langkah ini adalah penyebab off-by-one paling sering.

⚠️ ELEMEN KEMBAR tetap dihitung terpisah. Pada [3,3,1], terbesar ke-2
   adalah 3, bukan 1. nth_element menanganinya dengan benar tanpa
   perlakuan khusus -- sampel 2 memang menguji ini.

⚠️ nth_element MENGUBAH array. Kalau kamu masih membutuhkan urutan aslinya,
   bekerjalah pada salinan.

PERBANDINGAN KECEPATAN untuk n = 10^6, K = 10:
   sort         : ~2 * 10^7 operasi
   partial_sort : ~3 * 10^6
   nth_element  : ~10^6            <- sekitar 20x lebih cepat dari sort

🔄 ALTERNATIVE APPROACHES:
- sort lalu ambil a[n-K]: O(n log n). Benar, tetapi membuang pekerjaan.
- partial_sort: berguna kalau kamu butuh K elemen dalam keadaan TERURUT.
- Min-heap ukuran K: O(n log K) waktu, O(K) ruang. Menang kalau data
  berbentuk aliran atau memori sangat ketat (lihat Exercise 6).
- Quickselect tulis sendiri: sama saja, tetapi nth_element sudah
  memakai introselect yang menjamin O(n) bahkan pada kasus terburuk.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int pos = n - K;                            // terbesar ke-K, urutan menaik
    nth_element(a.begin(), a.begin() + pos, a.end());

    cout << a[pos] << '\n';
    return 0;
}
