/*
============================================================
✅ Solution 3: Ketat vs Tidak Menurun
============================================================
Approach: dua kali tails, beda fungsi binary search
Complexity: Time O(N log N) | Space O(N)
Key Insight: Perbedaan antara "naik ketat" dan "tidak menurun" seluruhnya
             terkandung dalam SATU pilihan fungsi.

📖 KENAPA:
   lower_bound(x) menemukan elemen PERTAMA yang >= x, lalu kita menggantinya.
   Artinya nilai yang SAMA DENGAN x ikut tergantikan -- x tidak bisa
   menyambung dirinya sendiri. Hasilnya: KETAT NAIK.

   upper_bound(x) menemukan elemen PERTAMA yang > x. Nilai yang sama dengan x
   DILEWATI, sehingga x boleh disambung di belakang nilai yang sama.
   Hasilnya: TIDAK MENURUN.

⚠️ UJI CEPAT DENGAN [1,1,1].
   ketat harus 1 ; tidak menurun harus 3.
   Kalau kodemu memberi angka lain, kamu tertukar. Lakukan uji ini SETIAP KALI
   sebelum submit -- 10 detik yang menyelamatkan satu WA.

⚠️ JANGAN MENCOBA MEMBUAT VERSI "TIDAK MENURUN" DENGAN MENAMBAH EPSILON
   (misalnya lower_bound(x + 1)). Itu bekerja untuk bilangan bulat tetapi
   gagal untuk desimal, dan overflow kalau x = INT_MAX. Pakai upper_bound.

VERIFIKASI SAMPEL 2 ([2,2,3,1,3,3,4]):
   KETAT (lower_bound):
     2->[2] ; 2->[2] ; 3->[2,3] ; 1->[1,3] ; 3->[1,3] ; 3->[1,3] ; 4->[1,3,4]
     ukuran 3  ✓  (2 3 4)
   TIDAK MENURUN (upper_bound):
     2->[2] ; 2->[2,2] ; 3->[2,2,3] ; 1->[1,2,3] ; 3->[1,2,3,3] ;
     3->[1,2,3,3,3] ; 4->[1,2,3,3,3,4]
     ukuran 6  ✓  (2 2 3 3 3 4)

🔄 ALTERNATIVE APPROACHES:
- Versi O(N^2): ganti a[j] < a[i] menjadi a[j] <= a[i]. Sama sederhananya,
  dan lebih jelas terbaca -- berguna kalau kamu ragu saat kontes.
- Barisan TIDAK NAIK / MENURUN: negasikan nilainya lalu pakai aturan di atas.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int lisStrict(const vector<int>& a) {
    vector<int> t;
    for (int x : a) {
        auto it = lower_bound(t.begin(), t.end(), x);
        if (it == t.end()) t.push_back(x); else *it = x;
    }
    return t.size();
}

int lisNonDec(const vector<int>& a) {
    vector<int> t;
    for (int x : a) {
        auto it = upper_bound(t.begin(), t.end(), x);
        if (it == t.end()) t.push_back(x); else *it = x;
    }
    return t.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    cout << lisStrict(a) << ' ' << lisNonDec(a) << '\n';
    return 0;
}
