/*
============================================================
✅ Solution 3: Counting Sort dengan Nilai Negatif
============================================================
Approach: Offset berdasarkan nilai minimum yang benar-benar ada
Complexity: Time O(n + rentang) | Space O(rentang)
Key Insight: Indeks array tidak boleh negatif, tetapi masalahnya mudah
             diselesaikan dengan menggeser seluruh nilai. Yang lebih menarik
             adalah PILIHAN offset: memakai minimum yang benar-benar ada di
             data, bukan batas teoretis dari soal, bisa menghemat memori
             secara drastis.

📖 PENJELASAN PENDEKATAN:
1. Cari mn dan mx yang benar-benar ada di array.
2. Alokasikan cnt berukuran mx - mn + 1.
3. cnt[x - mn]++ untuk seluruh elemen.
4. Sapu dan cetak v + mn.

PERBANDINGAN DUA PILIHAN OFFSET, pada sampel 2 ([-5,-5,-5]):
   memakai batas soal (-10^6 sampai 10^6) : array 2000001 slot  = 8 MB
   memakai data (mn = mx = -5)            : array 1 slot        = 4 byte
   Selisihnya enam orde besaran. Untuk soal dengan batas memori ketat,
   pilihan ini menentukan MLE atau AC.

⚠️ INDEKS NEGATIF ADALAH BUG SENYAP.
   Di C++, `cnt[-3]` bukan error kompilasi dan sering tidak menyebabkan
   crash -- ia hanya membaca atau menulis memori sembarang di depan array.
   Programmu mungkin berjalan "normal" di mesinmu dan menghasilkan jawaban
   yang benar untuk sampel, lalu WA atau RE di judge. Ini salah satu bug
   paling sulit dilacak, dan pencegahannya sepele: selalu periksa apakah
   nilai bisa negatif sebelum memakainya sebagai indeks.

⚠️ TIPE DATA UNTUK RENTANG: mx - mn bisa mencapai 2*10^6 di sini, masih muat
   di int. Tetapi kalau soal mengizinkan nilai sampai 10^9, mx - mn mencapai
   2*10^9 yang MELUAP di int -- dan array sebesar itu juga mustahil.
   Dalam kasus itu, counting sort memang bukan alat yang tepat; pakai radix
   sort atau std::sort.

⚠️ ARRAY KOSONG: min_element pada vector kosong adalah perilaku tak
   terdefinisi. Soal menjamin n >= 1, tetapi biasakan memeriksanya.

🔄 ALTERNATIVE APPROACHES:
- Radix sort dengan pembalikan bit tanda: bekerja untuk seluruh rentang int
  tanpa peduli seberapa lebar, O(4n).
- std::sort: selalu benar, O(n log n).
- Memisahkan negatif dan non-negatif menjadi dua counting sort: bekerja,
  tetapi lebih panjang tanpa keuntungan.
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

    int mn = *min_element(a.begin(), a.end());
    int mx = *max_element(a.begin(), a.end());

    // Ukuran berdasarkan DATA, bukan batas soal -- bisa jauh lebih hemat
    vector<int> cnt(mx - mn + 1, 0);
    for (int x : a) cnt[x - mn]++;

    string out;
    out.reserve(n * 8);
    bool pertama = true;
    for (int v = 0; v < (int)cnt.size(); v++)
        while (cnt[v]--) {
            if (!pertama) out += ' ';
            out += to_string(v + mn);                 // geser KEMBALI
            pertama = false;
        }
    out += '\n';
    cout << out;

    return 0;
}
