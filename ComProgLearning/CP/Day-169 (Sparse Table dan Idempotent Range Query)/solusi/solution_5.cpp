/*
============================================================
✅ Solution 5: Selisih Maksimum-Minimum Terbatas
============================================================
Approach: Two pointers (O(n)), dengan sparse table sebagai pembanding
Complexity: Time O(n) | Space O(n)
Key Insight: Sifat kuncinya: kalau sebuah subarray memenuhi syarat, maka
             SETIAP potongan di dalamnya juga memenuhi. Sifat itu bernama
             MONOTONISITAS, dan ia membuka dua pendekatan sekaligus --
             binary search per ujung kiri, atau two pointers yang lebih baik.

📖 KENAPA MONOTON:
   Menghapus elemen dari sebuah subarray tidak mungkin MENAIKKAN maksimumnya
   maupun MENURUNKAN minimumnya. Jadi selisih (maks - min) hanya bisa
   mengecil atau tetap. Kalau subarray besar sudah memenuhi (selisih <= L),
   seluruh isinya pasti memenuhi juga.

📖 PENDEKATAN 1 -- sparse table + binary search, O(n log n):
   Untuk setiap ujung kiri l, cari ujung kanan terjauh r dengan binary
   search, memakai sparse table untuk menjawab maks dan min dalam O(1).
   Benar, dan inilah cara yang paling langsung memakai materi hari ini.

📖 PENDEKATAN 2 -- two pointers, O(n)  <- dipakai di solusi ini:
   Perhatikan lebih jauh: saat ujung kiri MAJU, ujung kanan terjauh juga
   TIDAK PERNAH MUNDUR. Sebab menghapus elemen dari kiri hanya melonggarkan
   syarat, sehingga r yang tadinya sah tetap sah.
   Jadi kedua pointer hanya bergerak MAJU, total 2n langkah -- faktor log
   hilang sepenuhnya.

   Untuk menjaga maksimum dan minimum pada jendela yang bergeser, kita
   butuh struktur yang mendukung "tambah di kanan, buang di kiri":
   MONOTONIC DEQUE (Day 37). Dua deque -- satu menurun untuk maksimum,
   satu menaik untuk minimum.

📖 KENAPA MONOTONIC DEQUE BEKERJA:
   Deque maksimum menyimpan indeks dengan nilai MENURUN. Saat elemen baru
   masuk, seluruh elemen di belakang yang nilainya <= elemen baru dibuang --
   mereka tidak akan pernah menjadi maksimum lagi karena elemen baru lebih
   besar DAN bertahan lebih lama. Puncak deque selalu maksimum jendela.
   Setiap elemen masuk dan keluar deque tepat sekali -> O(n) total.

⚠️ URUTAN OPERASI PADA TWO POINTERS: masukkan a[r] ke kedua deque DULU,
   baru periksa apakah jendela masih sah. Kalau tidak sah, majukan l dan
   buang elemen yang keluar dari deque (hanya kalau indeksnya memang
   di depan).

⚠️ MEMBUANG DARI DEPAN HARUS BERSYARAT: buang hanya kalau indeks di depan
   deque SAMA DENGAN l yang sedang dibuang. Kalau tidak, elemen itu sudah
   terbuang sebelumnya lewat pemangkasan di belakang.

VERIFIKASI SAMPEL 1 (a = [8,2,4,7,2], L = 2):
   Subarray dengan selisih <= 2: [8], [2], [4], [7], [2], [2,4], [4,7]? 
   selisih 4-2=2 <= 2  ya, panjang 2. [7,2] selisih 5, tidak.
   Terpanjang = 2   ✓
VERIFIKASI SAMPEL 2 (a = [3,3,3,1], L = 0):
   [3,3,3] selisih 0, panjang 3. Menambahkan 1 membuat selisih 2 > 0.
   jawab 3   ✓

🔄 ALTERNATIVE APPROACHES:
- Sparse table + binary search: O(n log n), memakai materi hari ini secara
  langsung. Untuk n = 2*10^5 keduanya lolos; two pointers lebih cepat.
- Multiset yang menyimpan isi jendela: O(n log n), lebih mudah ditulis
  tetapi lebih lambat. begin() memberi minimum, rbegin() memberi maksimum.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll L;
    cin >> n >> L;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    deque<int> dqMax, dqMin;                 // menyimpan INDEKS
    int l = 0, best = 0;

    for (int r = 0; r < n; r++) {
        // masukkan a[r]: buang yang tidak akan pernah menang lagi
        while (!dqMax.empty() && a[dqMax.back()] <= a[r]) dqMax.pop_back();
        dqMax.push_back(r);
        while (!dqMin.empty() && a[dqMin.back()] >= a[r]) dqMin.pop_back();
        dqMin.push_back(r);

        // susutkan dari kiri selama jendela tidak sah
        while ((ll)a[dqMax.front()] - a[dqMin.front()] > L) {
            if (dqMax.front() == l) dqMax.pop_front();   // buang HANYA kalau di depan
            if (dqMin.front() == l) dqMin.pop_front();
            l++;
        }

        best = max(best, r - l + 1);
    }

    cout << best << '\n';
    return 0;
}
