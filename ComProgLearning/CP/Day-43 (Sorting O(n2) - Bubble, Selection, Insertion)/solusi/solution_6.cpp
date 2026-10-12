/*
============================================================
✅ Solution 6: Pengurutan Setelah K Sapuan
============================================================
Approach: Simulasi bubble sort dengan pembatas sapuan
Complexity: Time O(nK) | Space O(1)
Key Insight: Soal simulasi tidak menguji algoritma, melainkan KETELITIAN
             membaca definisi. Di sini ada dua detail yang menentukan benar
             atau salah, dan keduanya sengaja diuji oleh sampel.

📖 PENJELASAN PENDEKATAN:
1. Lakukan paling banyak K sapuan.
2. Setiap sapuan berjalan dari indeks 0 sampai batas kanan yang MENYUSUT
   (karena ekor array sudah berada di posisi finalnya).
3. Kalau satu sapuan tidak menghasilkan pertukaran, berhenti -- tetapi
   sapuan itu TETAP DIHITUNG.

⚠️ DETAIL PERTAMA -- SAPUAN PEMBUKTIAN TETAP DIHITUNG.
   Sampel 2 adalah [1,2,3,4] dengan K = 10, dan jawabannya 1, bukan 0.
   Artinya: kita tetap harus melakukan satu sapuan untuk MENGETAHUI bahwa
   array sudah terurut, dan sapuan itu dihitung. Kalau kamu mengecek
   keterurutan lebih dulu lalu tidak menyapu sama sekali, jawabanmu 0 -- salah.

   Ini contoh khas soal simulasi: jawabannya bergantung pada definisi yang
   diberikan soal, bukan pada apa yang "masuk akal" secara umum. Baca ulang
   pernyataan soal sebelum menulis.

⚠️ DETAIL KEDUA -- BATAS KANAN MENYUSUT.
   Setelah sapuan ke-i, i elemen terbesar sudah beres. Kalau kamu tidak
   menyusutkan batasnya, hasilnya tetap benar (hanya lebih lambat), tetapi
   menyusutkannya adalah bagian dari definisi bubble sort baku.

⚠️ K = 0: tidak ada sapuan sama sekali, array dicetak apa adanya, dan
   jumlah sapuan 0. Pastikan loopmu menangani ini tanpa menjalankan apa pun.

VERIFIKASI SAMPEL 1 ([5,4,3,2,1], K = 1):
   satu sapuan: 5>4 tukar, 5>3 tukar, 5>2 tukar, 5>1 tukar
   -> [4,3,2,1,5], sapuan = 1  ✓
   Perhatikan bahwa 5 sampai ke ujung dalam satu sapuan, tetapi elemen kecil
   hanya bergerak satu langkah ke kiri. Ketimpangan ini disebut masalah
   "kura-kura", dan itulah motivasi cocktail shaker sort.

VERIFIKASI SAMPEL 3 ([3,1,4,2], K = 2):
   sapuan 1: 3>1 tukar -> [1,3,4,2]; 3<4 tidak; 4>2 tukar -> [1,3,2,4]
   sapuan 2: 1<3 tidak; 3>2 tukar -> [1,2,3,4]
   sudah terurut setelah 2 sapuan, dan K = 2 sudah habis -> berhenti
   sapuan = 2  ✓

🔄 ALTERNATIVE APPROACHES:
- Untuk n besar dan K besar, ada karakterisasi teoretis: setelah k sapuan,
  posisi setiap elemen bisa dihitung dari struktur inversinya. Tetapi untuk
  n <= 2000, simulasi langsung jauh lebih sederhana dan tidak berisiko salah.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int sapuan = 0;
    for (int i = 0; i < K; i++) {
        int batas = n - 1 - i;                 // ekor sudah beres
        if (batas <= 0) break;                 // tidak ada lagi yang bisa disapu

        bool adaTukar = false;
        for (int j = 0; j < batas; j++)
            if (a[j] > a[j + 1]) { swap(a[j], a[j + 1]); adaTukar = true; }

        sapuan++;                              // sapuan pembuktian TETAP dihitung
        if (!adaTukar) break;
    }

    cout << sapuan << '\n';
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];

    return 0;
}
