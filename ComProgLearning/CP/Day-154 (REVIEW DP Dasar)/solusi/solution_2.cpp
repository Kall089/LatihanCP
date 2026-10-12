/*
============================================================
✅ Solution 2: Rangkaian Pameran Bertumbuh (Maximum Sum Increasing Subsequence)
============================================================
Approach: Dynamic Programming O(N^2) (Weighted LIS)
Complexity: Time O(N^2) | Space O(N)
Key Insight:
1. Perbedaan dengan LIS Biasa:
   LIS biasa menghitung PANJANG (jumlah elemen), sedangkan di sini menghitung JUMLAH NILAI KURASI.
   Oleh karena itu, algoritma binary search tails O(N log N) tidak bisa diaplikasikan langsung,
   tetapi DP O(N^2) bekerja dengan sangat presisi dan efisien untuk N <= 2000.

2. State & Transisi:
   dp[i] = jumlah nilai kurasi terbesar dari subsekuens meningkat ketat yang diakhiri oleh elemen ke-i.
   Basis: dp[i] = v[i] (karya i berdiri sendiri).
   Untuk setiap j < i:
     Jika a[j] < a[i]:
       dp[i] = max(dp[i], dp[j] + v[i]);

3. Jebakan Nilai Negatif:
   Karena v[i] bisa bernilai negatif dan subsekuens tidak boleh kosong:
   - Jawaban akhir BUKAN dp[N-1], melainkan max_{0 <= i < N} dp[i].
   - Variabel ans harus diinisialisasi dengan -4e18 (LLONG_MIN / 4), bukan 0!
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> v[i];
    }

    vector<ll> dp(n);
    ll ans = -INF;

    for (int i = 0; i < n; i++) {
        dp[i] = v[i]; // Subsekuens dimulai dari karya i
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + v[i]);
            }
        }
        ans = max(ans, dp[i]);
    }

    cout << ans << "\n";

    return 0;
}
