/*
============================================================
✅ Solution 4: Apakah Pengurutan Ini Stabil?
============================================================
Approach: Insertion sort (stabil), atau stable_sort
Complexity: Time O(n^2) | Space O(1)
Key Insight: Stabilitas bukan sifat masalah, melainkan sifat ALGORITMA.
             Dari tiga algoritma hari ini, bubble dan insertion stabil,
             sedangkan selection TIDAK. Memilih algoritma yang salah di sini
             menghasilkan WA meski kodenya "benar".

📖 PENJELASAN PENDEKATAN:
1. Baca pasangan (berat, nama) dalam urutan input.
2. Insertion sort berdasarkan berat, dengan kondisi geser a[j].berat > kunci.berat
   -- perhatikan '>' dan bukan '>='.
3. Cetak nama-nama secara berurutan.

⚠️ KENAPA '>' MENJAGA STABILITAS:
   Saat kunci bertemu elemen dengan berat SAMA, kondisi berat > berat bernilai
   salah, sehingga pergeseran BERHENTI dan kunci disisipkan SETELAH elemen itu.
   Karena kunci datang belakangan pada input, ia memang seharusnya berada
   setelahnya. Ganti '>' menjadi '>=' dan kunci akan melompati kembarannya --
   stabilitas hilang.

⚠️ KENAPA SELECTION SORT GAGAL DI SINI:
   Selection sort menukar elemen yang BERJAUHAN. Pada sampel 1:
       (3,a) (1,b) (3,c) (2,d) (1,e)
   putaran pertama menukar posisi 0 dengan posisi 1:
       (1,b) (3,a) (3,c) (2,d) (1,e)
   Sejauh ini aman, tetapi pola tukar-jauh ini secara umum bisa melompatkan
   sebuah elemen melewati kembarannya. Contoh minimal yang pasti rusak:
       [(2,a), (2,b), (1,c)]  ->  tukar posisi 0 dan 2  ->  [(1,c), (2,b), (2,a)]
   'b' kini mendahului 'a'. Itulah sebabnya selection sort tidak boleh dipakai
   kalau soal peduli urutan asli.

⚠️ std::sort TIDAK MENJAMIN STABILITAS.
   Ini kesalahan yang sangat sering terjadi. std::sort adalah introsort
   (quicksort + heapsort + insertion sort) dan boleh menukar elemen berkunci
   sama secara sembarang. Untuk soal ini kamu harus memakai std::stable_sort,
   ATAU menambahkan indeks asli sebagai kunci pemecah seri:
       sort(v.begin(), v.end(), [](auto& x, auto& y){
           if (x.berat != y.berat) return x.berat < y.berat;
           return x.indeksAsli < y.indeksAsli;      // pemecah seri
       });
   Trik pemecah seri ini bekerja dengan sort mana pun dan sering lebih
   disukai karena eksplisit.

🔄 ALTERNATIVE APPROACHES:
- std::stable_sort: O(n log n), satu baris. Untuk kontes, ini pilihan wajar.
- sort + pemecah seri indeks: O(n log n), eksplisit dan tidak bergantung
  pada jaminan pustaka.
- Bubble sort: stabil juga, tetapi tidak ada alasan memilihnya.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Benda { ll berat; char nama; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<Benda> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].berat >> a[i].nama;

    // Insertion sort -- stabil karena berhenti menggeser saat berat SAMA
    for (int i = 1; i < n; i++) {
        Benda kunci = a[i];
        int j = i - 1;
        while (j >= 0 && a[j].berat > kunci.berat) {   // '>' bukan '>='
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = kunci;
    }

    string out;
    for (int i = 0; i < n; i++) out += a[i].nama;
    cout << out << '\n';

    return 0;
}
