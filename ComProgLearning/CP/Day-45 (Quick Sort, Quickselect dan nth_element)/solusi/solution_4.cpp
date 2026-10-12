/*
============================================================
✅ Solution 4: Urutkan Tiga Warna
============================================================
Approach: Partisi tiga arah (Dutch national flag)
Complexity: Time O(n), satu sapuan | Space O(1)
Key Insight: Menjaga TIGA daerah sekaligus dengan tiga penunjuk.
             Yang membuat algoritma ini elegan sekaligus mudah salah adalah
             satu detail: ketika elemen ditukar dengan daerah KANAN,
             penunjuk penjelajah TIDAK BOLEH MAJU.

📖 PENJELASAN PENDEKATAN:
   Tiga daerah yang dijaga sepanjang waktu:
     a[0 .. lt-1]   = sudah pasti 0
     a[lt .. i-1]   = sudah pasti 1
     a[i .. gt]     = BELUM diperiksa
     a[gt+1 .. n-1] = sudah pasti 2

   Aturan pada a[i]:
     == 0 : tukar dengan a[lt], lalu lt++ DAN i++
     == 1 : cukup i++
     == 2 : tukar dengan a[gt], lalu gt--, tetapi i TIDAK MAJU

⚠️ KENAPA i TIDAK BOLEH MAJU SAAT MENUKAR DENGAN gt:
   Elemen yang baru saja dipindahkan ke posisi i berasal dari daerah
   "BELUM diperiksa" (posisi gt). Kita belum tahu nilainya 0, 1, atau 2.
   Kalau i maju, elemen itu terlewat begitu saja dan bisa berakhir di
   daerah yang salah.
   Bandingkan dengan kasus == 0: elemen yang datang dari posisi lt berasal
   dari daerah "sudah pasti 1", jadi kita sudah tahu nilainya dan aman
   untuk maju.
   Perbedaan halus ini adalah inti soal.

⚠️ SYARAT LOOP adalah i <= gt, BUKAN i < n.
   Begitu i melewati gt, seluruh sisanya sudah dipastikan bernilai 2.
   Memakai i < n akan memproses ulang daerah yang sudah selesai.

KENAPA SATU SAPUAN: setiap iterasi selalu memperkecil daerah "belum
diperiksa" tepat satu (baik lewat i++ maupun gt--). Karena daerahnya
berukuran n di awal, loop berjalan paling banyak n kali.

VERIFIKASI SAMPEL 1 ([2,0,2,1,1,0]):
   i=0 a=2 -> tukar a[0] dengan a[5], gt=4  -> [0,0,2,1,1,2], i TETAP 0
   i=0 a=0 -> tukar a[0] dengan a[0], lt=1, i=1
   i=1 a=0 -> lt=2, i=2
   i=2 a=2 -> tukar a[2] dengan a[4], gt=3  -> [0,0,1,1,2,2], i TETAP 2
   i=2 a=1 -> i=3
   i=3 a=1 -> i=4 > gt=3, selesai
   hasil [0,0,1,1,2,2]  ✓

MENGAPA ARRAY FREKUENSI DILARANG DI SOAL INI: karena dengan array
frekuensi (hitung berapa 0, 1, 2 lalu tulis ulang) soalnya menjadi sepele
dan tidak melatih apa pun. Pembatasan "satu sapuan" memaksa kamu memahami
partisi tiga arah, yang berguna untuk quicksort pada data penuh kembaran.

🔄 ALTERNATIVE APPROACHES:
- Array frekuensi + tulis ulang: O(n) juga tetapi DUA sapuan.
- std::sort: O(n log n), berlebihan untuk hanya tiga nilai.
- Partisi tiga arah ini adalah dasar quicksort untuk data dengan banyak
  nilai kembar: array yang seluruhnya bernilai sama selesai dalam O(n),
  padahal Lomuto biasa membutuhkan O(n^2).
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

    int lt = 0, i = 0, gt = n - 1;
    while (i <= gt) {                          // i <= gt, BUKAN i < n
        if      (a[i] == 0) swap(a[lt++], a[i++]);
        else if (a[i] == 2) swap(a[i], a[gt--]);   // i TIDAK maju
        else                i++;
    }

    string out;
    for (int k = 0; k < n; k++) {
        out += to_string(a[k]);
        out += (k + 1 == n) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
