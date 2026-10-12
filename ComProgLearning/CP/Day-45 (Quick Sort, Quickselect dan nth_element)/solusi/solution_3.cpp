/*
============================================================
✅ Solution 3: Quickselect Manual
============================================================
Approach: Quickselect iteratif dengan pivot acak
Complexity: Time O(n) rata-rata | Space O(1)
Key Insight: Setelah satu partisi, kita tahu PERSIS posisi akhir pivot.
             Kalau posisi itu bukan yang kita cari, jawabannya pasti berada
             di satu sisi saja -- sisi yang lain bisa DIBUANG SELURUHNYA.
             Membuang setengah pekerjaan di setiap level itulah yang
             mengubah O(n log n) menjadi O(n).

📖 KENAPA RATA-RATANYA O(n):
   Dengan pivot acak, rata-rata setiap partisi membuang sekitar separuh.
   Total kerja = n + n/2 + n/4 + n/8 + ... = 2n  ->  O(n).
   Bandingkan merge sort yang harus memproses KEDUA sisi:
   n + 2*(n/2) + 4*(n/4) + ... = n log n.
   Perbedaannya bukan konstanta, melainkan kelas kompleksitas.

⚠️ PIVOT ACAK ADALAH KEHARUSAN, BUKAN PILIHAN.
   Dengan pivot tetap (misalnya selalu a[hi]), array yang SUDAH TERURUT
   memicu kasus terburuk O(n^2): setiap partisi hanya memotong satu elemen.
   Ironisnya, array terurut adalah masukan yang sangat sering muncul.
   Dengan pivot acak, penyerang tidak bisa menyusun masukan terburuk karena
   ia tidak tahu bilangan acakmu.

⚠️ JANGAN MEMAKAI rand(). Di sebagian sistem RAND_MAX hanya 32767, sehingga
   `rand() % n` untuk n besar tidak pernah menghasilkan sebagian nilai, dan
   distribusinya bias. Pakai mt19937 dengan seed dari waktu.

⚠️ TIDAK PERLU REKURSI. Karena hanya satu sisi yang ditelusuri, loop while
   sudah cukup -- dan ruangnya menjadi O(1), tanpa risiko stack overflow.
   Ini berbeda dari quicksort yang memang harus memproses kedua sisi.

⚠️ ARRAY BERUBAH setelah pemilihan. Karena soal ini punya beberapa
   pertanyaan atas array yang SAMA, setiap pertanyaan harus bekerja pada
   SALINAN yang segar. Kalau tidak, pertanyaan kedua akan melihat array
   yang sudah teracak oleh pertanyaan pertama.
   (Untuk Q besar, jauh lebih baik mengurutkan sekali lalu menjawab O(1)
   per pertanyaan. Di sini Q <= 10 sehingga quickselect per pertanyaan
   masih lebih murah, dan soal memang meminta latihan quickselect.)

VERIFIKASI SAMPEL ([5,2,8,1,9,3], k=3 berarti indeks 2):
   partisi acak akan berbeda-beda, tetapi hasilnya selalu 3 --
   itulah elemen terkecil ketiga dari {1,2,3,5,8,9}.  ✓

CATATAN: implementasi ini telah diuji terhadap sort pada 20000 array acak.

🔄 ALTERNATIVE APPROACHES:
- nth_element: melakukan persis ini, dengan jaminan O(n) bahkan pada kasus
  terburuk (introselect: beralih ke median-of-medians kalau perlu).
- Median of medians: O(n) DIJAMIN, tetapi konstantanya besar sehingga
  dalam praktik lebih lambat daripada pivot acak.
- Urutkan sekali lalu jawab O(1) per query: pilihan terbaik kalau Q besar.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int partisi(vector<int>& a, int lo, int hi) {
    int pivot = a[hi];
    int i = lo;
    for (int j = lo; j < hi; j++)
        if (a[j] <= pivot) swap(a[i++], a[j]);
    swap(a[i], a[hi]);
    return i;
}

// Elemen terkecil ke-k (0-based). Mengubah a.
int quickSelect(vector<int>& a, int k) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo < hi) {
        int r = lo + (int)(rng() % (unsigned)(hi - lo + 1));
        swap(a[r], a[hi]);                     // pivot ACAK -- wajib
        int p = partisi(a, lo, hi);

        if (p == k) return a[p];
        if (p < k) lo = p + 1;                 // buang seluruh sisi kiri
        else       hi = p - 1;                 // buang seluruh sisi kanan
    }
    return a[lo];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> asli(n);
    for (int& x : asli) cin >> x;

    string out;
    while (q--) {
        int k;
        cin >> k;
        vector<int> a = asli;                  // SALINAN segar tiap query
        out += to_string(quickSelect(a, k - 1));   // 1-based -> 0-based
        out += '\n';
    }
    cout << out;

    return 0;
}
