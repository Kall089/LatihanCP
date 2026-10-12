/*
============================================================
✅ Solution 4: Potongan Palindrom Minimal
============================================================
Approach: Manacher sebagai oracle O(1) + DP partisi
Complexity: Time O(n^2) | Space O(n)
Key Insight: DP partisinya sendiri sederhana; yang mahal adalah pertanyaan
             "apakah S[j..i-1] palindrom" yang ditanyakan O(n^2) kali.
             Manacher menjadikan tiap pertanyaan O(1), sehingga total turun
             dari O(n^3) menjadi O(n^2).

📖 PENJELASAN PENDEKATAN:
1. Manacher sekali -> cek(l, r) dalam O(1) lewat p[l + r + 1] >= r - l + 1.
2. dp[i] = potongan minimal untuk membagi awalan sepanjang i.
   dp[0] = 0.
   dp[i] = min atas semua j < i dengan S[j..i-1] palindrom, dari dp[j] + 1.
3. Jawabannya dp[n].

Jawaban selalu ada karena huruf tunggal selalu palindrom, jadi dp[i] <= i.

CATATAN OPTIMASI: untuk n sampai 10^5 pola ini terlalu lambat. Versi O(n log n)
memakai Eertree atau dekomposisi "palindromic series" (rangkaian palindrom
dengan selisih periode yang sama). Itu materi lanjutan; untuk n <= 5000
versi ini sudah tepat sasaran.

VERIFIKASI "aabbaacc":
   "aabbaa" adalah palindrom (dibaca sama dari dua arah), lalu "c", "c"
   -> 3 potongan  ✓

🔄 ALTERNATIVE APPROACHES:
- DP is_pal[l][r] O(n^2) ruang: untuk n = 5000 butuh 25 juta bool = 25 MB,
  masih muat tapi lebih boros daripada Manacher yang hanya O(n).
- Hashing untuk cek O(1): setara, tapi probabilistik.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> manacher(const string& s) {
    string t = "#";
    for (char c : s) { t += c; t += '#'; }
    int n = t.size();
    vector<int> p(n, 0);
    int c = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (i < r) p[i] = min(r - i, p[2 * c - i]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n
               && t[i - p[i] - 1] == t[i + p[i] + 1]) p[i]++;
        if (i + p[i] > r) { c = i; r = i + p[i]; }
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> p = manacher(s);
    auto pal = [&](int l, int r) { return p[l + r + 1] >= r - l + 1; };

    const int INF = INT_MAX / 2;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (dp[j] + 1 < dp[i] && pal(j, i - 1))
                dp[i] = dp[j] + 1;

    cout << dp[n] << '\n';
    return 0;
}
