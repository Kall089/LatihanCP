/*
============================================================
✅ Solution 4: Semua Jumlah yang Bisa Dibentuk
============================================================
Approach: Subset sum (knapsack 0/1 dengan nilai = berat)
Complexity: Time O(N·S) atau O(N·S/64) dengan bitset | Space O(S)
Key Insight: Subset sum adalah knapsack 0/1 yang paling murni: setiap barang
             "nilainya" sama dengan "beratnya", dan kita tidak memaksimalkan
             apa pun -- hanya menandai jumlah mana yang BISA dicapai.
             Karena isinya hanya boolean, bitset memberi percepatan 64 kali
             dengan kode yang justru LEBIH PENDEK.

📖 BATAS ATAS ARRAY: jumlah terbesar yang mungkin adalah total seluruh koin,
   yaitu paling besar 100 x 1000 = 100000. Mengalokasikan lebih dari itu
   hanya membuang memori; mengalokasikan kurang menyebabkan akses di luar batas.

📖 BASIS: bisa[0] = 1. Jumlah nol selalu tercapai dengan subhimpunan KOSONG.
   Melupakan ini membuat seluruh array tetap nol dan jawabannya kosong --
   bug yang gejalanya sangat jelas tetapi penyebabnya sering tidak langsung
   terlihat.

⚠️ SOAL MEMINTA SUBHIMPUNAN TIDAK KOSONG, sehingga jumlah 0 harus DIKELUARKAN
   dari daftar jawaban. Basis bisa[0] = 1 tetap diperlukan untuk perhitungan;
   ia hanya tidak ikut dicetak.

⚠️ ARAH LOOP TETAP MUNDUR. Alasannya identik dengan knapsack biasa: kalau
   maju, sebuah koin bisa dipakai berkali-kali dan kamu akan melaporkan
   jumlah yang sebenarnya tidak bisa dibentuk.
   Contoh: koin [2] saja, maju akan menandai 2, 4, 6, ... padahal hanya 2
   yang benar.

📖 VERSI BITSET -- 64 kali lebih cepat, kode lebih pendek:
       bitset<100001> bs;
       bs[0] = 1;
       for (int x : a) bs |= bs << x;
   Satu operasi `bs << x` menggeser SELURUH 100001 bit sekaligus, dan CPU
   memprosesnya 64 bit per instruksi. Untuk N=100, S=10^5, ini turun dari
   10^7 menjadi sekitar 1.5*10^5 operasi.

   Kenapa `bs |= bs << x` setara dengan loop mundur? Karena operasi geser
   membaca SELURUH keadaan LAMA sekaligus sebelum menulis -- persis jaminan
   yang diberikan loop mundur, tetapi diperoleh secara alami.
   Ini salah satu trik paling berguna di CP dan patut dihafal.

VERIFIKASI SAMPEL 1 (koin [4,2,5,2]):
   Jumlah yang bisa: 2, 4, 5, 6, 7, 8, 9, 11, 13  -> 9 jumlah berbeda.
   Perhatikan 2 muncul dari dua koin berbeda tetapi tetap dihitung SEKALI --
   soal meminta jumlah BERBEDA, bukan banyaknya cara.
   Perhatikan juga 3 TIDAK bisa dibentuk, meski ada koin 2 dan 5.   ✓

🔄 ALTERNATIVE APPROACHES:
- set<int> yang diperluas tiap koin: benar, tetapi O(2^n) dalam kasus
  terburuk dan jauh lebih lambat.
- Menghitung BERAPA CARA alih-alih apakah bisa: ganti tipe menjadi long long
  dan `|=` menjadi `+=`. Struktur rekurensnya identik -- pola "ganti
  operator, dapatkan masalah berbeda".
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
    int total = 0;
    for (int& x : a) { cin >> x; total += x; }   // batas atas = total koin

    vector<char> bisa(total + 1, 0);
    bisa[0] = 1;                                 // subhimpunan KOSONG

    for (int x : a)
        for (int c = total; c >= x; c--)         // MUNDUR: tiap koin sekali
            if (bisa[c - x]) bisa[c] = 1;

    vector<int> hasil;
    for (int s = 1; s <= total; s++)             // mulai dari 1: tidak kosong
        if (bisa[s]) hasil.push_back(s);

    string out = to_string(hasil.size());
    out += '\n';
    for (size_t i = 0; i < hasil.size(); i++) {
        if (i) out += ' ';
        out += to_string(hasil[i]);
    }
    out += '\n';
    cout << out;

    return 0;
}
