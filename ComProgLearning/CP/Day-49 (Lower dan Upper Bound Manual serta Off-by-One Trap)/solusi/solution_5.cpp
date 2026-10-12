/*
============================================================
✅ Solution 5: Pasangan dengan Selisih Terbatas
============================================================
Approach: Urutkan, lalu upper_bound untuk setiap elemen
Complexity: Time O(n log n) | Space O(1)
Key Insight: Kondisi |a[i] - a[j]| <= K terlihat rumit karena melibatkan
             nilai absolut dan dua arah. Setelah array DIURUTKAN, kondisi
             itu runtuh menjadi sesuatu yang jauh lebih sederhana: untuk
             setiap i, seluruh pasangannya membentuk rentang KONTIGU yang
             dimulai tepat setelah i.

📖 PENJELASAN PENDEKATAN:
1. Urutkan array. Sekarang untuk i < j berlaku a[i] <= a[j], sehingga
   |a[i] - a[j]| = a[j] - a[i]. Nilai absolutnya hilang.
2. Kondisinya menjadi a[j] <= a[i] + K.
3. Untuk setiap i, cari j terbesar dengan a[j] <= a[i] + K:
       batas = upperBound(a[i] + K) - 1
   Banyaknya pasangan dengan i adalah batas - i.
4. Jumlahkan seluruhnya.

⚠️ KENAPA upper_bound DAN BUKAN lower_bound:
   Kita ingin elemen TERAKHIR yang <= (a[i] + K). upper_bound memberi posisi
   pertama yang > ambang, jadi mundur satu langkah memberi yang kita cari.
   Memakai lower_bound akan melewatkan seluruh elemen yang nilainya TEPAT
   sama dengan a[i] + K -- dan sampel 2 (K = 0, semua elemen sama) memang
   akan salah total kalau begitu.

⚠️ DUA TEMPAT OVERFLOW YANG BERBEDA:
   1. a[i] + K bisa mencapai 10^9 + 10^9 = 2*10^9, MELUAP di int.
      Hitung dalam long long.
   2. Hasil akhirnya bisa mencapai n(n-1)/2 = 2*10^10, MELUAP di int.
      Akumulasi dalam long long.
   Melewatkan salah satunya menghasilkan WA yang sulit dilacak karena
   sampel kecil tetap lolos.

VERIFIKASI SAMPEL 1 (a = [1,3,5,2,4] -> terurut [1,2,3,4,5], K = 2):
   i=0 (1): batas nilai 3, indeks terakhir 2 -> pasangan dengan 2, 3   -> 2
   i=1 (2): batas nilai 4, indeks terakhir 3 -> pasangan dengan 3, 4   -> 2
   i=2 (3): batas nilai 5, indeks terakhir 4 -> pasangan dengan 4, 5   -> 2
   i=3 (4): batas nilai 6, indeks terakhir 4 -> pasangan dengan 5      -> 1
   i=4 (5): batas nilai 7, indeks terakhir 4 -> tidak ada              -> 0
   total = 7  ✓

VERSI TWO POINTERS -- O(n) setelah pengurutan:
   Perhatikan bahwa saat i maju, ambang a[i] + K juga NAIK (array terurut),
   sehingga batas kanannya MONOTON dan tidak pernah mundur:

       int j = 0;
       for (int i = 0; i < n; i++) {
           if (j < i) j = i;
           while (j + 1 < n && (ll)a[j+1] <= (ll)a[i] + K) j++;
           hasil += j - i;
       }

   Ini menghilangkan faktor log. Untuk n = 2*10^5 keduanya lolos, tetapi
   mengenali kapan binary search bisa diganti two pointers (Day 32) adalah
   keterampilan yang sering menentukan pada batas yang lebih ketat.

🔄 ALTERNATIVE APPROACHES:
- Two pointers: O(n) setelah sort, seperti di atas.
- Naif O(n^2): cukup untuk n <= 5000.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll K;
    cin >> n >> K;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    sort(a.begin(), a.end());              // nilai absolut hilang setelah ini

    ll hasil = 0;
    for (int i = 0; i < n; i++) {
        ll ambang = a[i] + K;                                  // long long
        int batas = int(upper_bound(a.begin(), a.end(), ambang) - a.begin()) - 1;
        hasil += batas - i;                                    // long long
    }

    cout << hasil << '\n';
    return 0;
}
