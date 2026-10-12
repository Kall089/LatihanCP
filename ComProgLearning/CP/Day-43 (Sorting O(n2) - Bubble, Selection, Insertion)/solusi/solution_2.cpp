/*
============================================================
✅ Solution 2: Selection Sort Hemat Pertukaran
============================================================
Approach: Selection sort dengan penghindaran swap sia-sia
Complexity: Time O(n^2) perbandingan | Space O(1)
Key Insight: Selection sort menukar PALING BANYAK n-1 kali, karena setiap
             putaran menempatkan tepat satu elemen di posisi finalnya dan
             tidak pernah menyentuhnya lagi. Bandingkan dengan bubble sort
             yang bisa menukar sampai n(n-1)/2 kali.
             Kalau operasi tukar mahal (memindahkan objek besar, menulis ke
             media dengan batas siklus tulis), selection sort adalah pilihan
             yang benar meski perbandingannya lebih banyak.

📖 PENJELASAN PENDEKATAN:
1. Untuk i dari 0 sampai n-2, cari indeks nilai minimum di a[i..n-1].
2. Tukar HANYA kalau indeks minimumnya bukan i itu sendiri.

⚠️ PEMERIKSAAN minIdx != i ADALAH INTI SOAL INI.
   Tanpa pemeriksaan itu, array yang sudah terurut ([1,2,3,4]) akan
   menghasilkan 3 "pertukaran" yang sebenarnya tidak memindahkan apa pun --
   dan sampel 2 memang ditaruh untuk menangkap hal ini.

⚠️ PERBANDINGAN SELALU n(n-1)/2, apa pun datanya. Selection sort BUTA
   terhadap keteraturan data: array yang sudah terurut sekalipun tetap
   memerlukan seluruh perbandingan. Ini berbeda dari bubble (dengan flag)
   dan insertion yang keduanya O(n) pada data terurut.

⚠️ TIDAK STABIL. Karena menukar elemen yang BERJAUHAN, selection sort bisa
   melompatkan sebuah elemen melewati kembarannya:
       [2a, 2b, 1] -> tukar a[0] dan a[2] -> [1, 2b, 2a]
   Kalau soal peduli urutan asli elemen berkunci sama, jangan pakai ini.

🔄 ALTERNATIVE APPROACHES:
- Kalau yang diminta adalah jumlah swap MINIMUM MUTLAK untuk mengurutkan
  (bukan khusus selection sort), jawabannya berbeda: itu dihitung dari
  dekomposisi SIKLUS permutasi, yaitu n - (banyaknya siklus). Soal ini
  meminta selection sort secara spesifik, tetapi pola siklus itu layak
  diketahui dan sering muncul di kontes.
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

    ll swapCount = 0;
    for (int i = 0; i + 1 < n; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;      // '<' -> kemunculan pertama

        if (minIdx != i) {                         // hindari swap sia-sia
            swap(a[i], a[minIdx]);
            swapCount++;
        }
    }

    cout << swapCount << '\n';
    return 0;
}
