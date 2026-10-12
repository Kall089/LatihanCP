/*
============================================================
✅ Solution 2: Hitung Inversi
============================================================
Approach: BIT atas nilai terkompresi, sapu dari kanan
Complexity: Time O(N log N) | Space O(N)
Key Insight: BIT diindeks oleh NILAI, bukan posisi. Dengan menyapu dari
             kanan dan memasukkan elemen ke BIT setelah memprosesnya, saat
             kita sampai di a[i] seluruh elemen di kanannya sudah ada di
             dalam BIT -- sehingga "berapa yang lebih kecil" menjadi satu
             query prefiks.

📖 ALGORITMANYA:
   for (i = n-1 turun ke 0):
       inv += query(rank(a[i]) - 1)     // berapa yang SUDAH masuk dan lebih kecil
       update(rank(a[i]), 1)            // daftarkan a[i]

   Setiap pasangan inversi (i, j) dengan i < j dihitung TEPAT SEKALI, yaitu
   saat i diproses (karena j sudah masuk lebih dulu).

⚠️ KOMPRESI KOORDINAT WAJIB. Nilai mencapai 10^9 dan boleh negatif, tetapi
   BIT butuh indeks dalam rentang kecil. Setelah kompresi, indeksnya
   1..(banyak nilai berbeda) -- ingat BIT tidak boleh memakai indeks 0.
   Karena itu kompresi di sini menghasilkan indeks 1-BASED.

⚠️ query(rank - 1), BUKAN query(rank).
   Kita ingin yang BENAR-BENAR lebih kecil. Memakai query(rank) akan ikut
   menghitung elemen yang nilainya SAMA, dan inversi didefinisikan sebagai
   a[i] > a[j] (ketat). Perbedaan satu angka menentukan benar atau salah;
   uji dengan array yang seluruh elemennya sama -- jawabannya harus 0.

⚠️ PILIH SATU ARAH DAN KONSISTEN.
   Ada dua cara yang sama benarnya:
     (a) sapu dari KANAN, hitung yang LEBIH KECIL   <- dipakai di sini
     (b) sapu dari KIRI, hitung yang LEBIH BESAR
   Keduanya menghitung himpunan pasangan yang sama. Tetapi mencampur
   keduanya (misalnya sapu dari kanan tetapi menghitung yang lebih besar)
   memberi jawaban yang salah. Hafalkan SATU saja.

⚠️ OVERFLOW: array terurut menurun sepanjang 2*10^5 punya n(n-1)/2 = 2*10^10
   inversi. int jebol; long long wajib untuk akumulator.

VERIFIKASI SAMPEL 1 (a = [2,4,1,3,5], peringkat = [2,4,1,3,5]):
   i=4 (5): query(4) = 0        inv=0    update(5)
   i=3 (3): query(2) = 0        inv=0    update(3)
   i=2 (1): query(0) = 0        inv=0    update(1)
   i=1 (4): query(3) = 2        inv=2    update(4)   [1 dan 3 lebih kecil]
   i=0 (2): query(1) = 1        inv=3    update(2)   [1 lebih kecil]
   total 3   ✓  Manual: (2,1), (4,1), (4,3)

🔄 ALTERNATIVE APPROACHES:
- Merge sort (Day 44): O(n log n) juga, tidak butuh kompresi, dan sedikit
  lebih cepat. Tetapi BIT jauh lebih mudah DIPERLUAS -- lihat Exercise 3
  (hasil per posisi) dan varian "a[i] > 2*a[j]" yang sulit dengan merge sort.
- Policy-based ordered set: paling pendek ditulis, konstanta besar.
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

    int m;
    cin >> m;
    vector<ll> a(m);
    for (ll& x : a) cin >> x;

    // Kompresi koordinat -> indeks 1-BASED (BIT tidak boleh pakai 0)
    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    n = v.size();
    t.assign(n + 2, 0);

    ll inv = 0;
    for (int i = m - 1; i >= 0; i--) {            // sapu dari KANAN
        int p = int(lower_bound(v.begin(), v.end(), a[i]) - v.begin()) + 1;
        inv += query(p - 1);                      // yang BENAR-BENAR lebih kecil
        update(p, 1);
    }

    cout << inv << '\n';
    return 0;
}
