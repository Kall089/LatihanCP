/*
============================================================
✅ Solution 1: Menaiki Tangga
============================================================
Approach: DP 1D dengan rolling variable
Complexity: Time O(N) | Space O(1)
Key Insight: Setiap cara mencapai anak tangga i dibedakan oleh LANGKAH
             TERAKHIRNYA -- naik 1 (dari i-1) atau naik 2 (dari i-2).
             Kedua himpunan itu saling lepas, jadi jumlahnya boleh ditambahkan
             tanpa risiko terhitung dua kali.

📖 MENURUNKAN, BUKAN MENGHAFAL:
   dp[i] = banyak cara mencapai anak tangga ke-i
   keputusan terakhir: dari i-1 atau dari i-2
   dp[i] = dp[i-1] + dp[i-2]

⚠️ dp[0] = 1, BUKAN 0.
   "Berdiri di titik awal" adalah satu cara yang sah: barisan langkah kosong.
   Kalau dp[0] = 0, seluruh hasil menjadi 0. Cara mengecek: dp[2] HARUS 2
   (yaitu 1+1 dan 2). Uji dengan tangan sebelum menulis kode.

⚠️ MODULO. N sampai 10^6 -> hasilnya astronomis. Sampel 3 (N=100) sudah jauh
   melampaui batas long long, jadi ia menguji apakah kamu memodulo.

⚠️ HASILNYA MEMANG FIBONACCI, tapi menurunkan sendiri jauh lebih berguna
   daripada mengenalinya -- karena variannya (langkah 1..k, ada yang rusak,
   biaya minimum) tidak lagi Fibonacci sementara METODENYA tetap sama.

VERIFIKASI SAMPEL 1 (N=4):
   dp = 1, 1, 2, 3, 5  ->  dp[4] = 5  ✓
   Manual: 1111, 112, 121, 211, 22

🔄 ALTERNATIVE APPROACHES:
- Matrix exponentiation / fast doubling: O(log N). Berguna kalau N sampai
  10^18 (Day 100-an), tidak perlu di sini.
- Memoisasi rekursif: benar, tapi rekursi 10^6 dalam -> stack overflow.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    ll a = 1, b = 1;                 // dp[0] = 1, dp[1] = 1
    for (int i = 2; i <= n; i++) {
        ll c = (a + b) % MOD;
        a = b;
        b = c;
    }
    cout << (n == 0 ? 1 : b) << '\n';
    return 0;
}
