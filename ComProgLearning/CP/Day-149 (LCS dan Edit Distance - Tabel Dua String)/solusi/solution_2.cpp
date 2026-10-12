/*
============================================================
✅ Solution 2: LCS + Rekonstruksi
============================================================
Approach: bangun tabel penuh, lalu telusuri balik dari dp[n][m]
Complexity: Time O(n*m) | Space O(n*m)
Key Insight: Tabel DP menyimpan NILAI; jejaknya tersirat di dalam nilai-nilai
             itu sendiri. Kita tidak perlu array parent terpisah -- cukup
             tanyakan di setiap langkah: "sel tetangga mana yang menghasilkan
             nilai ini?"

📖 ATURAN PENELUSURAN dari (i, j):
   a[i-1] == b[j-1]      -> huruf ini bagian dari LCS; ambil, i--, j--
   dp[i-1][j] >= dp[i][j-1] -> naik  (buang a[i-1])
   selain itu               -> kiri  (buang b[j-1])
   Berhenti saat i == 0 atau j == 0. Hasilnya terbalik -> reverse.

⚠️ KENAPA BOLEH MENGAMBIL LANGSUNG SAAT HURUF COCOK?
   Karena saat membangun tabel, sel yang cocok NILAINYA memang berasal dari
   diagonal (lihat Solution 1). Jadi menelusuri diagonal konsisten dengan
   cara nilai itu terbentuk.

⚠️ JAWABANNYA TIDAK UNIK. "abcbdab" vs "bdcaba" punya beberapa LCS sepanjang 4.
   Pilihan >= atau > pada tie-break menentukan yang mana yang keluar; keduanya
   sah. JANGAN membandingkan outputmu dengan satu string tetap.

⚠️ REKONSTRUKSI MEMBUTUHKAN TABEL PENUH. Kalau kamu sudah memakai rolling
   array untuk menghemat memori, informasi jejaknya sudah terbuang. (Ada
   algoritma HIRSCHBERG yang merekonstruksi dengan memori O(min(n,m)) lewat
   divide and conquer, tapi itu materi lanjutan.)

⚠️ PANJANG 0 -> cetak baris kosong, bukan tidak mencetak apa pun. Sampel 3
   mengujinya.

VERIFIKASI SAMPEL 2 (a="axbycz", b="abc"):
   dp[6][3] = 3
   telusuri: (6,3) c==c -> ambil 'c', (5,2)
             (5,2) z vs b beda, dp[4][2]=2 >= dp[5][1]=1 -> naik (4,2)
             (4,2) y vs b beda -> naik (3,2)
             (3,2) b==b -> ambil 'b', (2,1)
             (2,1) x vs a beda -> naik (1,1)
             (1,1) a==a -> ambil 'a', (0,0)
   hasil terbalik "cba" -> reverse -> "abc"  ✓

🔄 ALTERNATIVE APPROACHES:
- Simpan array arah (diagonal/atas/kiri) saat mengisi tabel. Lebih boros
  memori tapi penelusurannya jadi trivial -- berguna kalau rekurensnya rumit.
- Untuk LCS yang LEKSIKOGRAFIS TERKECIL di antara semua LCS, aturan tie-break
  harus diubah dan biasanya butuh preprocessing "huruf berikutnya".
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) { res += a[i-1]; i--; j--; }
        else if (dp[i-1][j] >= dp[i][j-1]) i--;
        else j--;
    }
    reverse(res.begin(), res.end());

    cout << dp[n][m] << '\n' << res << '\n';
    return 0;
}
