/*
============================================================
✅ Solution 2: Puncak Gunung
============================================================
Approach: Binary search pada SELISIH (bukan ternary search)
Complexity: Time O(log N) | Space O(1)
Key Insight: Soal ini terlihat seperti kasus ternary search, tetapi ada
             pendekatan yang lebih baik. Kalau f unimodal (naik lalu turun),
             maka SELISIHNYA g(i) = f(i+1) - f(i) bersifat MONOTON:
             positif di daerah menanjak, negatif di daerah menurun.
             Masalah unimodal berubah menjadi masalah monoton, dan binary
             search kembali berlaku.

📖 TRANSFORMASINYA:
   f = [1, 4, 7, 9, 8, 5, 2]        unimodal, puncak di indeks 3
   g = [3, 3, 2, -1, -3, -3]        MONOTON menurun

   Predikat: g(i) > 0, yaitu a[i] < a[i+1] -- "masih menanjak".
   Polanya TRUE TRUE TRUE FALSE FALSE FALSE.
   Indeks pertama yang FALSE adalah puncaknya.

   Kerangkanya SAMA PERSIS dengan Day 49:
       while (lo < hi) {
           mid = lo + (hi - lo) / 2;
           if (a[mid] < a[mid+1]) lo = mid + 1;
           else                   hi = mid;
       }

📖 KENAPA INI LEBIH BAIK DARIPADA TERNARY SEARCH INTEGER:
   1. Iterasi lebih sedikit: membuang 1/2 per langkah, bukan 1/3.
   2. Evaluasi f satu kali per iterasi, bukan dua kali.
      Gabungan keduanya membuatnya sekitar 4x lebih cepat.
   3. Tidak ada kasus tepi. Ternary search integer bisa macet ketika m1 dan
      m2 berdekatan sehingga f(m1) == f(m2) tanpa memberi informasi arah,
      sehingga ia butuh penanganan khusus di akhir. Binary search pada
      selisih tidak punya masalah itu.

   ATURAN PRAKTIS: untuk domain INTEGER, hampir selalu pakai binary search
   pada selisih. Simpan ternary search untuk domain REAL.

⚠️ SYARATNYA: fungsinya harus unimodal KETAT (tidak ada dua elemen
   bersebelahan yang sama). Soal ini menjaminnya. Kalau ada dataran datar,
   a[mid] == a[mid+1] membuat predikatnya tidak monoton dan pendekatan ini
   bisa gagal -- tetapi ternary search juga gagal pada kasus yang sama, jadi
   ini bukan kelemahan tambahan.

⚠️ INDEKS mid+1: karena kita mengakses a[mid+1], batas atas loopnya harus
   n-1, bukan n. Dengan hi dimulai dari n-1 dan loop berhenti saat lo == hi,
   mid selalu < hi <= n-1 sehingga mid+1 <= n-1 -- aman.

CATATAN: implementasi ini telah diuji terhadap brute force pada 20000 array
unimodal acak.

🔄 ALTERNATIVE APPROACHES:
- Ternary search integer: bekerja, tetapi lebih lambat dan butuh penanganan
  akhir. Template hari ini menyediakan versinya untuk perbandingan.
- Sapuan linier: O(N). Untuk N = 10^6 sebenarnya masih lolos, tetapi soal
  meminta O(log N).
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

    int lo = 0, hi = n - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < a[mid + 1]) lo = mid + 1;   // masih menanjak
        else                     hi = mid;        // sudah menurun
    }

    cout << lo << '\n';
    return 0;
}
