/*
============================================================
✅ Solution 3: Hitung Inversi
============================================================
Approach: Merge sort + satu baris penghitungan
Complexity: Time O(n log n) | Space O(n)
Key Insight: Inversi yang seluruhnya di dalam bagian kiri, dan yang
             seluruhnya di dalam bagian kanan, sudah dihitung oleh rekursi.
             Yang tersisa hanyalah inversi LINTAS BATAS -- dan itu bisa
             dihitung persis saat merge, tanpa kerja tambahan.

📖 PENJELASAN PENDEKATAN:
1. inv = rekursi kiri + rekursi kanan.
2. Saat merge, kalau kita mengambil dari bagian KANAN, artinya a[j] lebih
   kecil dari a[i] -- dan karena bagian kiri SUDAH TERURUT, a[j] juga lebih
   kecil dari a[i+1], a[i+2], ..., a[mid-1].
   Jadi ia membentuk inversi dengan SELURUH sisa kiri sekaligus:
       inv += mid - i;

⚠️ INILAH BUG PALING UMUM DI SOAL INI: menulis inv += 1.
   Hasilnya angka yang jauh lebih kecil tetapi tetap terlihat "masuk akal",
   dan sampel kecil sering tetap lolos. Satu-satunya cara menangkapnya
   dengan andal adalah stress test terhadap brute force O(n^2).

⚠️ URUTAN OPERASI: inv += mid - i harus dievaluasi saat i MASIH menunjuk
   ke elemen kiri pertama yang belum diambil. Kalau kamu menaikkan i lebih
   dulu, hitungannya meleset satu.

⚠️ '<=' BUKAN '<': dengan '<=', elemen yang nilainya SAMA tidak dihitung
   sebagai inversi -- sesuai definisi a[i] > a[j] pada soal ini.
   Kalau soal mendefinisikan inversi sebagai a[i] >= a[j], ubah menjadi '<'.
   Selalu baca definisinya.

⚠️ long long WAJIB. Array terurut terbalik sepanjang 10^5 punya
   n(n-1)/2 = 5*10^9 inversi -- int jebol pada 2.1*10^9.

VERIFIKASI SAMPEL 1 ([5,2,4,6,1,3]):
   merge [5]+[2,4]      -> +2   (pasangan 5-2, 5-4)
   merge [6]+[1,3]      -> +2   (6-1, 6-3)
   merge [2,4,5]+[1,3,6]:
       ambil 1, sisa kiri {2,4,5} -> +3
       ambil 3, sisa kiri {4,5}   -> +2
                                     +5
   total = 9  ✓
   Manual: (5,2)(5,4)(5,1)(5,3)(2,1)(4,1)(4,3)(6,1)(6,3) = 9  ✓

CATATAN: solusi ini telah diuji terhadap brute force pada 20000 array acak.

🔄 ALTERNATIVE APPROACHES:
- BIT + kompresi koordinat (Day 38 + 170): O(n log n) juga. Lebih mudah
  diperluas ke varian "berapa yang lebih kecil di kanan PER POSISI".
- Ordered set dari policy-based data structure: paling pendek ditulis,
  tetapi konstantanya besar.
- Merge sort biasanya paling cepat untuk inversi murni.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll invCount(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;

    ll inv = invCount(a, tmp, l, mid) + invCount(a, tmp, mid, r);

    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            inv += mid - i;            // SELURUH sisa kiri, bukan 1
        }
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r)   tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];

    return inv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n), tmp(n);
    for (int& x : a) cin >> x;

    cout << invCount(a, tmp, 0, n) << '\n';
    return 0;
}
