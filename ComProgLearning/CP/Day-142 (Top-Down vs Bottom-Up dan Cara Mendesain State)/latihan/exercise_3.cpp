#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-142 (Top-Down vs Bottom-Up & Cara Mendesain State)
 * Latihan 3: Pekan Komunitas Kreatif (Vacation - AtCoder DP-C)
 *
 * Selama N hari liburan, Taro wajib memilih tepat satu kegiatan setiap hari:
 * - Kegiatan 0: Berenang di laut (kepuasan a[i])
 * - Kegiatan 1: Menangkap serangga di gunung (kepuasan b[i])
 * - Kegiatan 2: Mengerjakan PR di rumah (kepuasan c[i])
 *
 * Karena Taro mudah bosan, ia TIDAK BOLEH memilih kegiatan yang sama dua hari berturut-turut!
 * Artinya, jika di hari i ia memilih kegiatan 0, maka di hari i+1 ia hanya boleh memilih
 * kegiatan 1 atau kegiatan 2.
 *
 * Nilai kepuasan bisa bernilai positif maupun negatif.
 * Hitung total kepuasan maksimum yang dapat diraih Taro selama N hari.
 *
 * Format Input:
 * Baris pertama berisi satu bilangan bulat N.
 * N baris berikutnya masing-masing berisi 3 bilangan bulat a[i], b[i], dan c[i].
 *
 * Format Output:
 * Satu bilangan bulat: total kepuasan maksimum.
 *
 * Batasan:
 * 1 <= N <= 100.000
 * -1.000.000.000 <= a[i], b[i], c[i] <= 1.000.000.000
 *
 * Test Case 1:
 * Input:
 * 3
 * 10 40 70
 * 20 50 80
 * 30 60 90
 * Output:
 * 210
 * Penjelasan:
 * Hari 1: pilih kegiatan 2 (70)
 * Hari 2: pilih kegiatan 1 (50)
 * Hari 3: pilih kegiatan 2 (90)
 * Total kepuasan = 70 + 50 + 90 = 210.
 *
 * Test Case 2:
 * Input:
 * 1
 * -5 -2 -9
 * Output:
 * -2
 * Penjelasan:
 * Hanya ada 1 hari, pilih yang terbesar yaitu -2.
 *
 * Test Case 3:
 * Input:
 * 7
 * 6 7 8
 * 8 8 3
 * 2 5 2
 * 7 8 6
 * 4 6 8
 * 2 3 4
 * 7 5 1
 * Output:
 * 46
 *
 * Hint 1:
 * Mengapa state 1D dp[i] gagal? Karena saat berada di hari i, kita tidak tahu kegiatan apa
 * yang dipilih di hari i-1, sehingga kita tidak tahu pilihan mana yang dilarang!
 *
 * Hint 2:
 * Tambahkan dimensi kedua: dp[i][j] = kepuasan maksimum sampai hari ke-i dengan kegiatan
 * di hari ke-i adalah j (0, 1, atau 2).
 *
 * Hint 3:
 * Transisi untuk hari ke-i (i >= 1):
 * dp[i][0] = a[i] + max(dp[i-1][1], dp[i-1][2])
 * dp[i][1] = b[i] + max(dp[i-1][0], dp[i-1][2])
 * dp[i][2] = c[i] + max(dp[i-1][0], dp[i-1][1])
 * Jawaban akhir adalah max(dp[n-1][0], max(dp[n-1][1], dp[n-1][2])).
 * Gunakan tipe data long long karena akumulasi nilai dapat melebihi batas 32-bit integer!
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<long long>> cost(n, vector<long long>(3));
    for (int i = 0; i < n; i++) {
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }

    // TODO: Implementasikan DP 2D untuk menghitung kepuasan maksimum
    // Perhatikan penanganan nilai awal hari 0 (basis) dan transisi hari 1 s.d. n-1

    return 0;
}
