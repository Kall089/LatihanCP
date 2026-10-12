/*
============================================================
✅ Solution 1: Nilai Paling Sering Muncul
============================================================
Approach: Array frekuensi global + satu sapuan
Complexity: Time O(n + V) | Space O(V)
Key Insight: Kalau domain nilai kecil (di sini 10^6), array mengalahkan map
             dengan selisih sekitar 100 kali lipat per akses. Untuk n = 10^6,
             itu selisih 1 ms melawan 100 ms -- selisih AC dan TLE.

📖 PENJELASAN PENDEKATAN:
1. cnt[a[i]]++ untuk seluruh elemen.
2. Sapu v dari 1 sampai MAKS, ambil yang cnt-nya terbesar.
   Karena kita menyapu dari NILAI TERKECIL dan memakai perbandingan '>'
   (bukan '>='), yang pertama mencapai nilai maksimum akan bertahan --
   dan itu otomatis nilai terkecil. Aturan tie-breaking selesai tanpa
   kode tambahan.

⚠️ ARRAY HARUS GLOBAL. Dua alasan:
   1. Variabel global otomatis diinisialisasi nol, jadi tidak perlu memset.
   2. `int cnt[1000005]` di dalam main() menempati 4 MB di STACK, dan stack
      biasanya hanya 1-8 MB. Ini penyebab segmentation fault yang sering
      membingungkan karena kodenya sendiri terlihat benar.

⚠️ Kalau nilai bisa negatif, geser dengan offset: cnt[x + OFFSET].
   Kalau nilai bisa mencapai 10^9, kompres dulu (Day 38).

🔄 ALTERNATIVE APPROACHES:
- map<int,int>: benar juga, tetapi ~100x lebih lambat per operasi.
  Untuk n = 10^6 pada soal berbatas waktu ketat, ini berisiko TLE.
- sort lalu hitung berturut-turut: O(n log n), lebih lambat dan lebih panjang.
- Kalau dijamin ada elemen yang muncul > n/2 kali, Boyer-Moore memberi
  jawaban dalam O(1) ruang -- tetapi itu masalah yang berbeda.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAKS = 1000005;
int cnt[MAKS];                 // GLOBAL: otomatis nol, tidak membebani stack

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int nilai = 0, terbanyak = 0;
    for (int v = 1; v < MAKS; v++)
        if (cnt[v] > terbanyak) {          // '>' -> yang terkecil menang saat seri
            terbanyak = cnt[v];
            nilai = v;
        }

    cout << nilai << ' ' << terbanyak << '\n';
    return 0;
}
