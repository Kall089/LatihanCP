/*
============================================================
✅ Solution 6: Urutan Relatif Kustom
============================================================
Approach: Array frekuensi + pencetakan dalam urutan yang ditentukan
Complexity: Time O(n + V) | Space O(V)
Key Insight: "Mengurutkan" tidak selalu berarti menjalankan algoritma
             pengurutan. Kalau domain nilainya kecil, mengurutkan seringkali
             hanya berarti "mencetak nilai dalam urutan tertentu, masing-
             masing sebanyak frekuensinya". Urutan itu tidak harus menaik --
             ia bisa ditentukan oleh soal.

📖 PENJELASAN PENDEKATAN:
1. cnt[x]++ untuk seluruh elemen A. Nilai paling besar 1000, jadi array
   1001 slot sudah cukup.
2. Sapu B secara berurutan. Untuk setiap nilai b, cetak b sebanyak cnt[b]
   kali, lalu NOLKAN cnt[b] sebagai penanda "sudah tercetak".
3. Sapu seluruh nilai dari 0 sampai 1000. Yang cnt-nya masih tersisa adalah
   nilai yang tidak ada di B; cetak masing-masing sebanyak frekuensinya.
   Karena kita menyapu dari kecil ke besar, bagian ini otomatis terurut
   menaik -- tanpa memanggil sort sama sekali.

⚠️ MENOLKAN cnt SETELAH TERCETAK adalah mekanisme penandaan yang paling
   sederhana. Tanpa itu, langkah 3 akan mencetak ulang nilai-nilai yang
   sudah muncul di langkah 2, dan panjang keluaranmu menjadi lebih dari N.
   Alternatif lain: array boolean terpisah "ada di B". Keduanya benar,
   tetapi menolkan cnt tidak butuh memori tambahan.

⚠️ SOAL MENJAMIN setiap elemen B muncul di A, sehingga cnt[b] selalu >= 1.
   Kalau jaminan itu tidak ada, `while (cnt[b]--)` tetap aman karena
   loopnya langsung berhenti -- tetapi berhati-hatilah karena post-decrement
   pada nilai 0 membuatnya menjadi -1, yang akan mengacaukan langkah 3.
   Solusi ini memakai penolan eksplisit sehingga aman dalam kedua kasus.

⚠️ B DIJAMIN BERISI NILAI BERBEDA. Kalau ada duplikat di B, langkah 2 akan
   mencetak nilai itu pada kemunculan pertama lalu cnt-nya nol, sehingga
   kemunculan kedua tidak mencetak apa-apa. Kebetulan perilakunya benar,
   tetapi jangan mengandalkan kebetulan -- baca jaminan soal.

VERIFIKASI SAMPEL 1:
   A = [2,3,1,3,2,4,6,7,9,2,19], cnt: 1->1, 2->3, 3->2, 4->1, 6->1, 7->1,
       9->1, 19->1
   B = [2,1,4,3,9]
   langkah 2: 2 2 2 | 1 | 4 | 3 3 | 9
   langkah 3: sisa 6, 7, 19 (menaik)
   hasil: 2 2 2 1 4 3 3 9 6 7 19   ✓

🔄 ALTERNATIVE APPROACHES:
- std::sort dengan komparator kustom yang memetakan nilai ke prioritasnya:
  O(n log n), bekerja untuk domain nilai apa pun (tidak terbatas 1000).
  Pilihan yang lebih umum, tetapi lebih lambat di sini.
- stable_sort dengan kunci prioritas: setara.
- Untuk domain besar, kompresi (Day 38) lalu pendekatan ini.
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

    const int MAKS = 1000;
    vector<int> cnt(MAKS + 1, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    string out;
    out.reserve(n * 5);
    bool pertama = true;
    auto cetak = [&](int v) {
        if (!pertama) out += ' ';
        out += to_string(v);
        pertama = false;
    };

    // Langkah 2: ikuti urutan B
    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        while (cnt[b] > 0) { cetak(b); cnt[b]--; }
        cnt[b] = 0;                          // penanda: sudah tercetak
    }

    // Langkah 3: sisanya, menaik -- tanpa memanggil sort
    for (int v = 0; v <= MAKS; v++)
        while (cnt[v] > 0) { cetak(v); cnt[v]--; }

    out += '\n';
    cout << out;

    return 0;
}
