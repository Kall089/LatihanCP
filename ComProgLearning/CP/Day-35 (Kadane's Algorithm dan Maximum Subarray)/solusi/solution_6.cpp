/*
============================================================
✅ Solution 6: Submatriks dengan Jumlah Maksimum
============================================================
Approach: Kunci pasangan baris + Kadane 1D pada jumlah kolom
Complexity: Time O(R^2 * C) | Space O(C)
Key Insight: Sebuah submatriks ditentukan oleh empat batas. Kalau kita
             MENGUNCI dua di antaranya (batas baris atas dan bawah), maka
             yang tersisa hanya batas kolom -- dan itu persis masalah
             subarray maksimum satu dimensi. Teknik "kunci satu dimensi,
             selesaikan dimensi lain" adalah salah satu pola paling berguna
             di seluruh CP.

📖 PENJELASAN PENDEKATAN:
1. Untuk setiap batas atas (R kemungkinan):
   reset array kolom[C] menjadi nol.
2. Untuk setiap batas bawah dari atas ke bawah (R kemungkinan):
   TAMBAHKAN baris itu ke kolom[] -- inkremental, bukan dihitung ulang.
   Inilah yang membuat kompleksitasnya O(R^2 * C) dan bukan O(R^3 * C).
3. Jalankan Kadane pada kolom[], ambil maksimumnya.

ANALISIS BATAS: R = C = 300 memberi 300 * 300 * 300 = 2.7*10^7 operasi,
lolos dengan nyaman. Untuk 1000 x 1000 itu menjadi 10^9 -- TIDAK lolos.
Selalu hitung angka ini sebelum memutuskan memakai pendekatan ini.

⚠️ Kadane di dalam harus varian TIDAK BOLEH KOSONG (lokal = LLONG_MIN),
   karena submatriks harus punya setidaknya satu elemen. Sampel 2 dengan
   semua elemen negatif menguji tepat hal ini: jawabannya -1, bukan 0.

VERIFIKASI SAMPEL 1: submatriks terbaik adalah baris 2-4 kolom 2-4
   (9+2 tidak termasuk), yang berjumlah 15. Kadane menemukannya saat
   batas baris terkunci di pasangan yang tepat.

🔄 ALTERNATIVE APPROACHES:
- Prefix sum 2D + coba semua empat batas: O(R^2 * C^2). Untuk 300 itu
  8.1*10^9 -- TLE. Prefix 2D tetap berguna untuk pertanyaan submatriks
  yang batasnya DIBERIKAN (Day 30).
- Kalau matriksnya sangat besar tetapi jarang (banyak nol), pendekatan lain
  diperlukan.
- Kalau submatriksnya wajib persegi berukuran k x k, prefix 2D langsung
  menyelesaikannya dalam O(R*C).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    cin >> R >> C;
    vector<vector<ll>> g(R, vector<ll>(C));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) cin >> g[i][j];

    ll best = LLONG_MIN;

    for (int atas = 0; atas < R; atas++) {
        vector<ll> kolom(C, 0);
        for (int bawah = atas; bawah < R; bawah++) {
            // tambahkan satu baris -- INKREMENTAL
            for (int c = 0; c < C; c++) kolom[c] += g[bawah][c];

            // masalahnya sekarang 1D
            ll cur = 0, lokal = LLONG_MIN;
            for (int c = 0; c < C; c++) {
                cur = max(kolom[c], cur + kolom[c]);
                lokal = max(lokal, cur);
            }
            best = max(best, lokal);
        }
    }

    cout << best << '\n';
    return 0;
}
