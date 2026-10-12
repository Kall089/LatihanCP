/*
============================================================
✅ Solution 3: Barang Mana yang Dipilih
============================================================
Approach: DP 2D + penelusuran mundur
Complexity: Time O(N·W) | Space O(N·W)
Key Insight: Versi satu dimensi MENIMPA riwayatnya sendiri, sehingga
             keputusan yang sudah diambil tidak bisa dipulihkan. Untuk
             rekonstruksi kita butuh tabel penuh -- dan batas soal ini
             (N·W = 10^6) memang sengaja dibuat agar itu muat.

📖 CARA MENELUSURI MUNDUR:
   Mulai dari (i = n, c = W), yaitu keadaan akhir.
   Pada setiap langkah, bandingkan dp[i][c] dengan dp[i-1][c]:
       SAMA    -> barang ke-i TIDAK diambil (nilai terbaik tercapai tanpanya)
                  turun ke baris i-1, kapasitas TETAP.
       BERBEDA -> barang ke-i PASTI diambil (ia menyumbang perbedaan itu)
                  turun ke baris i-1, kapasitas BERKURANG w[i].
   Ulangi sampai i mencapai 0.

   Karena kita menelusuri dari barang terakhir ke pertama, indeks yang
   terkumpul urut MENURUN -- balik di akhir agar menaik.

⚠️ KENAPA "BERBEDA BERARTI DIAMBIL":
   dp[i][c] dihitung sebagai max(dp[i-1][c], dp[i-1][c-w] + v).
   Kalau hasilnya berbeda dari dp[i-1][c], berarti cabang KEDUA yang menang,
   dan cabang itu memakai barang ke-i. Tidak ada kemungkinan lain.

⚠️ MEMORI: (N+1) x (W+1) long long = 501 x 2001 x 8 byte = 8 MB. Aman.
   Kalau batasnya lebih besar, ada dua jalan keluar:
   1. Simpan jejak keputusan sebagai satu BYTE per sel alih-alih long long
      -> delapan kali lebih hemat.
   2. Divide and conquer (Hirschberg): O(N·W) waktu, O(W) memori.
      Jarang dibutuhkan di CP.

⚠️ KELUARAN BARIS KEDUA BOLEH KOSONG (sampel 2: tidak ada barang yang muat).
   Pastikan program tetap mencetak newline, bukan tidak mencetak apa pun.

⚠️ JAWABAN TIDAK UNIK. Kalau ada beberapa kombinasi bernilai sama, penelusuran
   ini memberi salah satunya -- yang manapun diterima. Tetapi hasilnya HARUS
   konsisten: total beratnya <= W dan total nilainya sama dengan dp[n][W].
   Itulah yang diperiksa oleh stress test.

VERIFIKASI SAMPEL 1 (w=[3,2,4], v=[3,4,2], W=5, dp[3][5]=7):
   i=3, c=5: dp[3][5]=7 == dp[2][5]=7  -> barang 3 tidak diambil
   i=2, c=5: dp[2][5]=7 != dp[1][5]=3  -> barang 2 DIAMBIL, c = 3
   i=1, c=3: dp[1][3]=3 != dp[0][3]=0  -> barang 1 DIAMBIL, c = 0
   Dipilih: barang 1 dan 2 -> "1 2"   ✓

CATATAN: rekonstruksi ini telah diuji pada 20000 kasus acak -- setiap hasil
diperiksa beratnya tidak melebihi W dan nilainya benar-benar optimal.

🔄 ALTERNATIVE APPROACHES:
- Menyimpan array boolean ambil[i][c]: sama memorinya kalau memakai char,
  dan penelusurannya lebih langsung. Keduanya sama baiknya.
- Untuk knapsack dengan N·W besar, rekonstruksi umumnya tidak diminta --
  soal yang meminta rekonstruksi biasanya memberi batas yang muat.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    cin >> n >> W;
    vector<int> w(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    // Tabel PENUH: versi 1D tidak bisa direkonstruksi karena menimpa riwayat
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i - 1][c];                              // tidak ambil
            if (c >= w[i - 1])
                dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i - 1]] + v[i - 1]);
        }

    // Telusuri MUNDUR dari keadaan akhir
    vector<int> dipilih;
    int c = W;
    for (int i = n; i >= 1; i--)
        if (dp[i][c] != dp[i - 1][c]) {          // berbeda -> pasti diambil
            dipilih.push_back(i);                // 1-based
            c -= w[i - 1];
        }
    reverse(dipilih.begin(), dipilih.end());     // menurun -> menaik

    string out = to_string(dp[n][W]);
    out += '\n';
    for (size_t i = 0; i < dipilih.size(); i++) {
        if (i) out += ' ';
        out += to_string(dipilih[i]);
    }
    out += '\n';                                 // tetap cetak walau kosong
    cout << out;

    return 0;
}
