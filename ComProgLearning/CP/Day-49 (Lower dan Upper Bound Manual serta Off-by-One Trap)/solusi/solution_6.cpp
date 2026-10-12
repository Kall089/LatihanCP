/*
============================================================
✅ Solution 6: Penjadwalan Tiket
============================================================
Approach: multiset + upper_bound (fungsi anggota) + penghapusan by iterator
Complexity: Time O((n + m) log n) | Space O(n)
Key Insight: Karena tiket dihapus setelah dibeli, array statis tidak cukup.
             Kita butuh struktur yang sekaligus: terurut, mengizinkan
             DUPLIKAT, mendukung pencarian O(log n), dan mendukung
             penghapusan O(log n). multiset memenuhi keempatnya.

📖 PENJELASAN PENDEKATAN:
1. Masukkan seluruh harga tiket ke multiset.
2. Untuk setiap pelanggan dengan batas b:
   - it = s.upper_bound(b) memberi iterator ke harga pertama yang > b.
   - Kalau it == s.begin(), berarti seluruh tiket lebih mahal -> cetak -1.
   - Kalau tidak, mundur satu (--it) untuk mendapat harga TERMAHAL yang <= b.
   - Cetak nilainya, lalu HAPUS iterator itu.

⚠️ JEBAKAN TERBESAR -- FUNGSI ANGGOTA vs ALGORITMA BEBAS:
       s.upper_bound(b)                        O(log n)   BENAR
       std::upper_bound(s.begin(), s.end(), b) O(n)       TLE SENYAP

   Versi kedua BERHASIL DIKOMPILASI dan memberi JAWABAN YANG BENAR --
   ia hanya berjalan linier, karena iterator multiset bukan random-access
   sehingga std::upper_bound harus melangkah satu per satu.
   Akibatnya: 2*10^5 * 2*10^5 = 4*10^10 operasi -> TLE, tanpa petunjuk apa
   pun tentang penyebabnya. Ini salah satu bug kinerja paling menjengkelkan
   di C++, dan hampir setiap peserta pernah tertipu sekali.

⚠️ MENGHAPUS TEPAT SATU SALINAN:
       s.erase(it)      menghapus SATU elemen yang ditunjuk iterator  BENAR
       s.erase(nilai)   menghapus SELURUH salinan bernilai itu        SALAH
   Pada sampel ada dua tiket berharga 5. Kalau kamu memakai s.erase(5),
   kedua-duanya lenyap dan pelanggan berikutnya kehilangan tiket yang
   seharusnya tersedia.

⚠️ MEMERIKSA s.begin() SEBELUM MUNDUR:
   --it pada s.begin() adalah perilaku tak terdefinisi. Periksa
   it == s.begin() DULU. Ini analog persis dengan pemeriksaan i != 0 pada
   versi array (Exercise 3) -- pola yang sama muncul dalam bentuk berbeda.

VERIFIKASI SAMPEL (tiket {3,5,5,7,8} setelah terurut, pelanggan 4, 8, 3):
   b=4 : upper_bound(4) menunjuk ke 5; mundur -> 3
         beli 3, sisa {5,5,7,8}
   b=8 : upper_bound(8) menunjuk ke end; mundur -> 8
         beli 8, sisa {5,5,7}
   b=3 : upper_bound(3) menunjuk ke 5 yang PERSIS s.begin()
         -> seluruh tiket tersisa lebih mahal -> cetak -1
   keluaran: 3, 8, -1   ✓

   Perhatikan pelanggan ketiga: batasnya 3 dan tiket berharga 3 memang ada
   di awal, tetapi sudah terjual ke pelanggan pertama. Inilah alasan soal
   ini butuh struktur DINAMIS -- dengan array statis, pelanggan ketiga akan
   salah dilaporkan membeli tiket 3 untuk kedua kalinya.

🔄 ALTERNATIVE APPROACHES:
- policy-based ordered_multiset: mendukung order-statistics, berlebihan di sini.
- Segment tree pada nilai terkompresi: O(log n) juga, dan diperlukan kalau
  soal menuntut operasi yang lebih kaya (misalnya "harga ke-k yang tersisa").
- Sort + pointer: TIDAK bekerja, karena penghapusan membuat urutan aksesnya
  tidak monoton.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    multiset<int> s;
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        s.insert(h);
    }

    string out;
    for (int j = 0; j < m; j++) {
        int b;
        cin >> b;

        auto it = s.upper_bound(b);        // FUNGSI ANGGOTA, O(log n)

        if (it == s.begin()) {             // seluruh tiket lebih mahal
            out += "-1\n";
        } else {
            --it;                          // termahal yang <= b
            out += to_string(*it);
            out += '\n';
            s.erase(it);                   // hapus TEPAT SATU salinan
        }
    }
    cout << out;

    return 0;
}
