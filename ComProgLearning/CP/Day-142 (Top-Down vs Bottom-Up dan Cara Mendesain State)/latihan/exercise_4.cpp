#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-142 (Top-Down vs Bottom-Up & Cara Mendesain State)
 * Latihan 4: Satu Kupon di Jalur Dieng (State Tambahan: Sumber Daya Terbatas)
 *
 * Kamu mendaki jalur pegunungan yang memiliki N pos perhentian berurutan (pos 0 sampai pos N-1),
 * dengan ketinggian pos masing-masing H[0], H[1], ..., H[N-1].
 *
 * Aturan pergerakan:
 * Dari pos i, kamu boleh bergerak ke pos (i + 1) atau pos (i + 2).
 * Energi normal yang dibutuhkan untuk berpindah dari pos i ke pos j adalah |H[i] - H[j]|.
 *
 * Kupon Diskon Spesial:
 * Kamu dibekali tepat 1 kupon sakti. Kupon ini dapat digunakan tepat satu kali untuk
 * MENGGRATISKAN energi satu kali lompatan (biaya lompatan tersebut menjadi 0).
 * Kupon boleh digunakan kapan saja di salah satu lompatan, atau boleh juga tidak digunakan sama sekali.
 *
 * Hitung energi minimum yang harus dikeluarkan untuk mencapai pos terakhir (pos N-1).
 *
 * Format Input:
 * Baris pertama berisi satu bilangan bulat N.
 * Baris kedua berisi N bilangan bulat H[0], H[1], ..., H[N-1].
 *
 * Format Output:
 * Satu bilangan bulat: energi minimum yang dikeluarkan.
 *
 * Batasan:
 * 1 <= N <= 200.000
 * 0 <= H[i] <= 1.000.000.000
 *
 * Test Case 1:
 * Input:
 * 4
 * 0 9 10 100
 * Output:
 * 9
 * Penjelasan:
 * Lompat dari pos 0 ke pos 1 secara normal: biaya |0 - 9| = 9.
 * Lompat dari pos 1 ke pos 3 menggunakan kupon gratis: biaya 0.
 * Total energi = 9 + 0 = 9.
 *
 * Test Case 2:
 * Input:
 * 1
 * 88
 * Output:
 * 0
 * Penjelasan:
 * Sudah berada di pos tujuan sejak awal.
 *
 * Test Case 3:
 * Input:
 * 2
 * 0 1000000000
 * Output:
 * 0
 * Penjelasan:
 * Lompat langsung dari 0 ke 1 dengan kupon gratis: biaya 0.
 *
 * Hint 1:
 * Jalur yang sampai ke pos i dengan kupon masih utuh JAUH LEBIH BERHARGA daripada jalur
 * yang sampai ke pos i dengan kupon yang sudah hangus. Keduanya tidak setara!
 *
 * Hint 2:
 * Gunakan state 2D: dp[i][used]
 * - dp[i][0] = energi minimum mencapai pos i dengan kupon BELUM digunakan.
 * - dp[i][1] = energi minimum mencapai pos i dengan kupon SUDAH digunakan.
 *
 * Hint 3:
 * Dari pos i ke pos next_pos (next_pos = i+1 atau i+2):
 * - Tanpa kupon:
 *   dp[next_pos][0] = min(dp[next_pos][0], dp[i][0] + |H[next_pos] - H[i]|)
 *   dp[next_pos][1] = min(dp[next_pos][1], dp[i][1] + |H[next_pos] - H[i]|)
 * - Dengan kupon (hanya bisa jika kupon belum terpakai sebelumnya, used = 0):
 *   dp[next_pos][1] = min(dp[next_pos][1], dp[i][0] + 0)
 *
 * Gunakan tipe long long karena nilai tinggi mencapai 10^9.
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // TODO: Implementasikan solusi DP 2D dengan status kupon (dp[i][0] dan dp[i][1])
    // Basis: dp[0][0] = 0, dp[0][1] = 0, dan yang lainnya diinisialisasi INF

    return 0;
}
