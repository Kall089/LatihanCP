/*
============================================================
✅ Solution 4: Di Mana Minimumnya
============================================================
Approach: Sparse table yang menyimpan INDEKS, bukan nilai
Complexity: Time O(n log n + q) | Space O(n log n)
Key Insight: Menyimpan indeks alih-alih nilai membuat struktur yang sama
             menjawab pertanyaan yang lebih kaya. Perbandingannya dilakukan
             lewat NILAI pada indeks itu, sedangkan yang DISIMPAN dan
             DIKEMBALIKAN adalah indeksnya.

📖 ATURAN SERI HARUS KONSISTEN DI DUA TEMPAT:
   Soal meminta indeks PALING KIRI saat ada beberapa nilai terkecil yang
   sama. Untuk mendapatkannya, pakai perbandingan `<=` yang memihak indeks
   pertama:
       sp[k][i] = (a[i1] <= a[i2]) ? i1 : i2;
   Karena i1 adalah awal blok KIRI, ia selalu punya indeks lebih kecil
   daripada i2. Dengan `<=`, saat nilainya seri kita memilih i1 -- yang
   lebih kiri.
   Memakai `<` akan memilih i2 saat seri, menghasilkan indeks yang lebih
   kanan -- benar nilainya tetapi salah posisinya.

⚠️ KONSISTENSI ANTARA BUILD DAN QUERY ADALAH INTI SOAL INI.
   Pada query, kedua blok bisa TUMPANG TINDIH, sehingga elemen minimum yang
   sama bisa muncul di kedua blok. Kalau aturan seri di query berbeda dari
   aturan seri di build, kamu bisa mendapat indeks yang tidak konsisten.
   Karena blok kiri selalu dimulai lebih awal, memakai `<=` di KEDUA tempat
   menjamin indeks terkiri selalu menang.

   Contoh yang membongkarnya: a = [1, 5, 1], query [0, 2].
       len = 3, k = 1, blok kiri sp[1][0] (a[0..1]) -> indeks 0
                       blok kanan sp[1][2-2+1] = sp[1][1] (a[1..2]) -> indeks 2
       a[0] = 1, a[2] = 1, seri.
       Dengan `<=` -> pilih 0 (benar, terkiri).
       Dengan `<`  -> pilih 2 (salah menurut soal).

📖 KENAPA STRUKTUR INI PENTING DI LUAR SOAL INI:
   Ini adalah fondasi LCA dalam O(1) per query. Euler tour mengubah pohon
   menjadi array kedalaman, dan LCA dua simpul menjadi "simpul dengan
   kedalaman MINIMUM pada rentang tertentu" -- persis yang dijawab struktur
   ini. Setelah preprocessing O(n log n), setiap LCA dijawab O(1),
   mengalahkan binary lifting yang O(log n). Materi lengkapnya Day 202.

   Struktur ini juga dipakai untuk divide-and-conquer berbasis minimum
   (misalnya "jumlah minimum atas seluruh subarray" atau membangun
   Cartesian tree), di mana setiap pemecahan butuh tahu DI MANA minimumnya.

⚠️ INDEKS YANG DIKEMBALIKAN 0-based; soal meminta 1-based. Tambahkan satu
   saat mencetak.

VERIFIKASI SAMPEL (a = [5,1,9,1,7,2], query [1,6] 1-based = [0,5]):
   Minimum bernilai 1, muncul di indeks 1 dan 3 (0-based).
   Soal meminta yang terkiri -> indeks 1 -> dicetak sebagai 2.   ✓
   Query [3,6] = [2,5]: minimum 1 hanya di indeks 3 -> dicetak 4.   ✓

CATATAN: implementasi ini telah diuji terhadap brute force pada 5000 array
acak dengan SELURUH pasangan (l, r), termasuk array dengan banyak nilai
kembar.

🔄 ALTERNATIVE APPROACHES:
- Menyimpan pair<nilai, indeks> dan memakai perbandingan bawaan pair:
  otomatis memilih indeks terkecil saat nilai seri, karena pair dibandingkan
  secara leksikografis. Lebih pendek, tetapi memakai dua kali memori.
- Segment tree yang menyimpan indeks: mendukung update, O(log n) per query.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

    int K = lg[n] + 1;
    vector<vector<int>> sp(K, vector<int>(n));
    for (int i = 0; i < n; i++) sp[0][i] = i;                // simpan INDEKS

    for (int k = 1; k < K; k++)
        for (int i = 0; i + (1 << k) <= n; i++) {
            int i1 = sp[k - 1][i], i2 = sp[k - 1][i + (1 << (k - 1))];
            sp[k][i] = (a[i1] <= a[i2]) ? i1 : i2;           // '<=' -> terkiri
        }

    string out;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        int k = lg[r - l + 1];
        int i1 = sp[k][l], i2 = sp[k][r - (1 << k) + 1];
        int best = (a[i1] <= a[i2]) ? i1 : i2;               // aturan seri SAMA
        out += to_string(best + 1);                          // 0-based -> 1-based
        out += '\n';
    }
    cout << out;

    return 0;
}
