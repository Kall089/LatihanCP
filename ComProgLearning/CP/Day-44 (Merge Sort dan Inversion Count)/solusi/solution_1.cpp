/*
============================================================
✅ Solution 1: Gabungkan Dua Array Terurut
============================================================
Approach: Two pointers pada dua array terurut
Complexity: Time O(n + m) | Space O(n + m)
Key Insight: Kalau kedua array sudah terurut, elemen terkecil yang belum
             diambil PASTI berada di salah satu dari dua posisi terdepan.
             Kita tidak perlu melihat elemen lain sama sekali -- itulah
             mengapa penggabungan bisa linier, bukan O((n+m) log(n+m)).

📖 PENJELASAN PENDEKATAN:
1. Dua penunjuk i dan j, keduanya mulai dari 0.
2. Selama keduanya belum habis, ambil yang lebih kecil dan majukan
   penunjuknya.
3. Setelah salah satu habis, SALIN SISA yang lain apa adanya -- sisa itu
   sudah terurut dan seluruhnya lebih besar dari apa pun yang sudah diambil.

⚠️ LANGKAH 3 SERING TERLUPAKAN. Kalau kamu hanya menulis loop while ganda
   tanpa dua loop penyalinan sisa, keluaranmu akan kehilangan elemen.
   Perhatikan bahwa PALING BANYAK SATU dari dua loop sisa yang benar-benar
   berjalan -- menulis keduanya tetap benar dan lebih aman.

⚠️ PERBANDINGAN SAAT SERI (x[i] <= y[j] versus x[i] < y[j]) tidak mengubah
   hasil untuk bilangan biasa, tetapi SANGAT penting kalau elemennya berupa
   pasangan atau struct dengan identitas. Memakai '<=' berarti mengambil
   dari array KIRI saat seri, dan itulah yang membuat merge sort STABIL.
   Biasakan menulis '<=' sekarang supaya tidak salah nanti.

🔄 ALTERNATIVE APPROACHES:
- Gabungkan lalu std::sort: O((n+m) log(n+m)). Benar tetapi membuang
  informasi bahwa kedua array sudah terurut.
- std::merge dari pustaka: melakukan persis ini, satu baris. Di kontes
  boleh dipakai; di sini kita menulis sendiri untuk memahami polanya,
  karena pola inilah inti merge sort.
- Kalau salah satu array punya ruang kosong di belakang, ada varian
  IN-PLACE yang mengisi dari BELAKANG (LeetCode 88) -- tanpa memori tambahan.
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
    vector<int> x(n), y(m);
    for (int& v : x) cin >> v;
    for (int& v : y) cin >> v;

    vector<int> hasil;
    hasil.reserve(n + m);

    int i = 0, j = 0;
    while (i < n && j < m)
        hasil.push_back(x[i] <= y[j] ? x[i++] : y[j++]);   // '<=' -> stabil

    while (i < n) hasil.push_back(x[i++]);                 // salin sisa
    while (j < m) hasil.push_back(y[j++]);                 // paling banyak satu jalan

    string out;
    for (size_t k = 0; k < hasil.size(); k++) {
        out += to_string(hasil[k]);
        out += (k + 1 == hasil.size()) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
