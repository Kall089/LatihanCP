/*
============================================================
✅ Solution 6: Dua Jalur Sekaligus
============================================================
Approach: DP state gabungan dp[k][i1][i2] dengan langkah bersamaan
Complexity: Time O(R*C*R) | Space O(R*R)
Key Insight: Kalau kedua orang melangkah BERSAMAAN, maka setelah k langkah
             keduanya berada di sel dengan i + j = k. Jadi begitu kita tahu k
             dan baris masing-masing (i1, i2), KOLOMNYA sudah tertentukan:
             j1 = k - i1 dan j2 = k - i2.
             Satu dimensi dihemat secara gratis -- inilah trik utama soal ini.

📖 KENAPA BUKAN O((R*C)^2):
   State naifnya adalah posisi kedua orang secara bebas: (i1,j1,i2,j2), yaitu
   O(R^2 * C^2) = 10^8 untuk R=C=100. Dengan memaksa langkah bersamaan,
   j1 dan j2 menjadi turunan dari k, sehingga state-nya tinggal (k, i1, i2)
   = O((R+C) * R * R) -- turun satu faktor penuh.

📖 TRANSISI: masing-masing orang memilih BAWAH atau KANAN -> 4 kombinasi.
   nilai tambahan = a[n1][j1] + (n1 == n2 ? 0 : a[n2][j2])
   Karena k sama, n1 == n2 berarti j1 == j2 juga, yaitu SEL YANG SAMA.
   Jadi satu perbandingan baris sudah cukup untuk mendeteksi tumpang tindih.

⚠️ HITUNG SEL BERSAMA SEKALI SAJA. Kalau lupa, jawabanmu akan lebih besar --
   dan sampel 3 (satu baris, keduanya terpaksa berjalan identik) langsung
   menangkapnya: jawabannya 10, bukan 20.

⚠️ LEWATI STATE BERSENTINEL. State yang tidak terjangkau bernilai NEG dan
   tidak boleh dipakai bertransisi. Pola yang sama seperti Solution 5.

⚠️ BATAS INDEKS. Setelah menghitung j1 = k+1-n1, WAJIB periksa 0 <= j1 < C
   (dan sama untuk j2). Banyak kombinasi (k, i) yang tidak valid.

⚠️ ROLLING PER k. Kita hanya butuh lapisan k dan k+1, jadi memorinya O(R^2)
   bukan O(R^2 * (R+C)).

VERIFIKASI SAMPEL 1 (2x2: [[1,2],[3,4]]):
   k=0: keduanya di (0,0), nilai 1 (dihitung sekali)
   k=1: satu ke (0,1)=2, satu ke (1,0)=3 -> 1 + 2 + 3 = 6
   k=2: keduanya ke (1,1)=4, dihitung SEKALI -> 6 + 4 = 10  ✓

VERIFIKASI SAMPEL 3 (1x4): keduanya wajib menempuh jalur yang sama, jadi
   setiap sel dihitung sekali -> 1+2+3+4 = 10  ✓
   Kalau kodemu menjawab 20, kamu belum menangani sel bersama.

🔄 ALTERNATIVE APPROACHES:
- MIN-COST MAX-FLOW: model klasik untuk "k jalur disjoint yang memaksimalkan
  keuntungan". Jauh lebih umum (bekerja untuk k jalur sekaligus), tetapi jauh
  lebih berat. DP di atas hanya untuk k = 2.
- Untuk k = 3 jalur, state jadi dp[k][i1][i2][i3] -> O(R*C*R^2), masih mungkin
  untuk R kecil.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 4;

int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int R, C;
   cin >> R >> C;
   vector<vector<ll>> a(R, vector<ll>(C));
   for (auto &row : a)
      for (auto &x : row)
         cin >> x;

   int K = R + C - 2; // total langkah
   vector<vector<ll>> cur(R, vector<ll>(R, NEG)), nxt;
   cur[0][0] = a[0][0]; // keduanya di (0,0)

   for (int k = 0; k < K; k++)
   {
      nxt.assign(R, vector<ll>(R, NEG));
      for (int i1 = 0; i1 < R; i1++)
         for (int i2 = 0; i2 < R; i2++)
         {
            if (cur[i1][i2] == NEG)
               continue; // LEWATI sentinel
            for (int d1 = 0; d1 < 2; d1++)
               for (int d2 = 0; d2 < 2; d2++)
               {
                  int n1 = i1 + d1, n2 = i2 + d2;
                  if (n1 >= R || n2 >= R)
                     continue;
                  int j1 = k + 1 - n1, j2 = k + 1 - n2;
                  if (j1 < 0 || j1 >= C || j2 < 0 || j2 >= C)
                     continue;
                  ll add = a[n1][j1] + (n1 == n2 ? 0 : a[n2][j2]);
                  nxt[n1][n2] = max(nxt[n1][n2], cur[i1][i2] + add);
               }
         }
      cur = nxt;
   }

   cout << cur[R - 1][R - 1] << '\n';
   return 0;
}
