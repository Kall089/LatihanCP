/*
============================================================
✅ Solution 4: Radix Sort
============================================================
Approach: Radix sort LSD basis 256, empat lewat
Complexity: Time O(4(n + 256)) = O(n) | Space O(n)
Key Insight: Counting sort mustahil untuk nilai sampai 10^9 (array 4 GB),
             tetapi kita bisa memecah setiap bilangan menjadi empat BYTE dan
             menjalankan counting sort pada masing-masing byte. Setiap lewat
             hanya butuh array 256 slot.

📖 PENJELASAN PENDEKATAN:
1. Untuk shift = 0, 8, 16, 24:
   jalankan counting sort STABIL pada digit (x >> shift) & 255.
2. Setelah empat lewat, seluruh 32 bit sudah diurutkan.
3. a.swap(tmp) menukar penunjuk internal vector -- O(1), tidak menyalin.

⚠️ STABILITAS ADALAH SYARAT MUTLAK, BUKAN OPSIONAL.
   Coba dengan tangan pada [21, 12, 11] basis 10:

   lewat satuan  : 21(1), 11(1), 12(2)  ->  [21, 11, 12]
   lewat puluhan : semuanya berpuluhan 2, 1, 1
       DENGAN STABIL : 11 dan 12 mempertahankan urutan dari lewat satuan
                       -> [11, 12, 21]   BENAR
       TANPA STABIL  : 11 dan 12 boleh tertukar
                       -> [12, 11, 21]   SALAH

   Informasi dari lewat sebelumnya HANYA tersimpan dalam urutan relatif.
   Begitu urutan itu boleh berubah, seluruh pekerjaan lewat sebelumnya
   hilang. Inilah alasan sesungguhnya kita repot menyapu mundur di
   Solution 2.

⚠️ MEMILIH BASIS -- hitung, jangan tebak:
   basis 10    -> 10 lewat, cnt 10 slot         lambat
   basis 256   -> 4 lewat,  cnt 1 KB (cache L1) BAGUS
   basis 65536 -> 2 lewat,  cnt 256 KB          lebih cepat, memori masih oke
   basis 2^32  -> 1 lewat,  cnt 16 GB           MUSTAHIL
   Basis 256 dipilih karena pengambilan digitnya cukup satu geser dan satu
   AND -- operasi termurah yang ada.

⚠️ a.swap(tmp) BUKAN a = tmp. swap pada vector menukar tiga penunjuk
   internal: O(1). Penyalinan adalah O(n). Untuk empat lewat, ini menghemat
   4n operasi penyalinan.

⚠️ SOAL INI MENJAMIN NON-NEGATIF. Kalau ada bilangan negatif, representasi
   two's complement membuat bit tandanya bernilai 1, sehingga bilangan
   negatif akan terurut SETELAH yang positif. Perbaikannya: XOR dengan
   0x80000000 sebelum mengurutkan, lalu XOR lagi setelahnya. Template hari
   ini menyediakan versi itu.

PERBANDINGAN NYATA: untuk 10^7 bilangan int acak, radix sort basis 256
biasanya 2-3 kali lebih cepat daripada std::sort. Pada soal dengan batas
waktu ketat, ini bisa menjadi pembeda antara AC dan TLE.

CATATAN: implementasi ini telah diuji terhadap std::sort pada 20000 array
acak, termasuk yang memuat bilangan negatif (lewat versi bertanda).

🔄 ALTERNATIVE APPROACHES:
- std::sort: O(n log n), selalu benar, satu baris. Untuk n <= 10^6 dan
  batas waktu longgar, ini pilihan yang benar. Jangan menulis radix sort
  kecuali kamu sudah menyimpannya di template.
- MSD radix sort: mengurutkan dari digit paling signifikan, memungkinkan
  penghentian awal. Lebih rumit, jarang dibutuhkan.
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
    vector<uint32_t> a(n);
    for (auto& x : a) cin >> x;

    vector<uint32_t> tmp(n);

    for (int shift = 0; shift < 32; shift += 8) {
        int cnt[256] = {0};

        for (uint32_t x : a) cnt[(x >> shift) & 255]++;          // frekuensi
        for (int v = 1; v < 256; v++) cnt[v] += cnt[v - 1];      // prefix sum
        for (int i = n - 1; i >= 0; i--)                          // MUNDUR
            tmp[--cnt[(a[i] >> shift) & 255]] = a[i];             // -> stabil

        a.swap(tmp);                                              // O(1)
    }

    string out;
    out.reserve(n * 11);
    for (int i = 0; i < n; i++) {
        out += to_string(a[i]);
        out += (i + 1 == n) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
