/*
============================================================
✅ Solution 5: Selisih Terbesar Antar Tetangga
============================================================
Approach: Bucket sort + prinsip pigeonhole
Complexity: Time O(n) | Space O(n)
Key Insight: Kita tidak perlu mengurutkan sama sekali. Dengan membagi
             rentang menjadi n-1 ember dan memasukkan n bilangan, prinsip
             pigeonhole menjamin ada setidaknya satu ember KOSONG (kecuali
             pada kasus tepi). Ember kosong itu memaksa jawabannya lebih
             besar daripada lebar ember -- yang berarti jawaban TIDAK PERNAH
             berada DI DALAM satu ember.

📖 ARGUMEN LENGKAPNYA:
   Misalkan mn dan mx nilai terkecil dan terbesar, dan lebar ember
   w = (mx - mn) / (n - 1), dibulatkan ke atas.

   Rata-rata selisih antar tetangga pada array terurut adalah
   (mx - mn) / (n - 1) = w. Karena rata-ratanya w, pasti ada setidaknya satu
   selisih yang >= w.

   Sekarang, dua bilangan yang berada di ember yang SAMA berselisih < w.
   Karena jawabannya >= w, jawaban itu tidak mungkin berasal dari sepasang
   bilangan di ember yang sama.

   Kesimpulan: jawaban selalu berupa selisih antara MAKSIMUM sebuah ember
   dan MINIMUM ember tak-kosong BERIKUTNYA. Kita hanya perlu menyimpan dua
   angka per ember, bukan isinya.

📖 PENJELASAN PENDEKATAN:
1. Cari mn dan mx. Kalau n < 2 atau mn == mx, jawabannya 0.
2. Buat n-1 ember (atau n untuk kesederhanaan indeks), simpan hanya min dan
   max tiap ember.
3. Sapu ember dari kiri, lewati yang kosong, dan ambil selisih terbesar
   antara maxSebelumnya dan minSekarang.

⚠️ INDEKS EMBER: idx = (x - mn) * (n - 1) / (mx - mn). Nilai mx menghasilkan
   idx = n - 1, sehingga arraynya harus berukuran n, bukan n - 1. Perkalian
   (x - mn) * (n - 1) bisa mencapai 10^9 * 10^6 = 10^15 -> WAJIB long long.
   Ini overflow yang sangat mudah terlewat.

⚠️ KASUS TEPI:
   n = 1        -> jawabannya 0 (tidak ada pasangan)
   semua sama   -> mn == mx, pembagian dengan nol! Tangani terpisah.
   n = 2        -> jawabannya mx - mn secara langsung; rumus umum juga benar

⚠️ EMBER KOSONG HARUS DILEWATI, bukan dianggap punya min/max nol.
   Inisialisasi dengan penanda (misalnya min = INT_MAX, max = -1) dan
   periksa sebelum memakai.

🔄 ALTERNATIVE APPROACHES:
- std::sort lalu sapu tetangga: O(n log n). Jauh lebih pendek dan untuk
  n <= 10^6 sudah cukup cepat. Kalau soal tidak menuntut O(n), ini pilihan
  yang benar. Versi ember ada di sini karena SOALNYA menuntut O(n) --
  dan karena argumen pigeonhole-nya layak dipelajari.
- Radix sort lalu sapu tetangga: O(n) juga, dan lebih mudah dibuktikan
  benar. Pilihan yang sah kalau kamu sudah punya radix sort di template.
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

    if (n < 2) { cout << 0 << '\n'; return 0; }

    int mn = *min_element(a.begin(), a.end());
    int mx = *max_element(a.begin(), a.end());
    if (mn == mx) { cout << 0 << '\n'; return 0; }   // hindari bagi nol

    // n ember; simpan HANYA min dan max tiap ember
    vector<int> bMin(n, INT_MAX), bMax(n, INT_MIN);
    for (int x : a) {
        // (x-mn)*(n-1) bisa 10^15 -> long long WAJIB
        int idx = (int)((ll)(x - mn) * (n - 1) / (mx - mn));
        bMin[idx] = min(bMin[idx], x);
        bMax[idx] = max(bMax[idx], x);
    }

    int jawab = 0, sebelumnya = mn;
    for (int i = 0; i < n; i++) {
        if (bMin[i] == INT_MAX) continue;            // ember KOSONG, lewati
        jawab = max(jawab, bMin[i] - sebelumnya);
        sebelumnya = bMax[i];
    }

    cout << jawab << '\n';
    return 0;
}
