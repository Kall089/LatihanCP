/*
============================================================
✅ Solution 1: Blok Terkecil (Kompresi String)
============================================================
Approach: Periode terkecil dari prefix function + cek keterbagian
Complexity: Time O(n) | Space O(n)
Key Insight: p adalah periode  <=>  n - p adalah panjang border.
             Border TERPANJANG (= pi[n-1]) memberi periode TERKECIL.
             Tapi periodik belum tentu berarti pengulangan UTUH.

📖 PENJELASAN PENDEKATAN:
1. Bangun tabel pi dalam O(n).
2. k = n - pi[n-1] adalah periode terkecil.
3. Kalau n % k == 0, string benar-benar tersusun dari n/k salinan blok
   sepanjang k -> jawabannya k.
4. Kalau n % k != 0, tidak ada blok < n yang mengulang utuh -> jawabannya n.

Kenapa langkah 4 benar? Andaikan ada blok sepanjang d < n dengan n % d == 0
yang mengulang utuh. Maka d juga sebuah periode, sehingga d >= k. Menurut
teorema periodisitas, karena d dan k keduanya periode dan d + k <= n + gcd,
gcd(d, k) juga periode. Blok terpendek yang MEMBAGI n selalu kelipatan dari
periode terkecil; kalau k sendiri tidak membagi n, tidak ada kandidat lain
yang lebih kecil dari n.

🔄 ALTERNATIVE APPROACHES:
- Coba semua pembagi n lalu bandingkan: O(n * d(n)) — lolos untuk n kecil,
  tetapi tidak perlu karena pi sudah memberi jawabannya langsung.
- Z-function: z[i] == n - i dan i membagi n -> jawabannya i. O(n) juga.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> bangunPi(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    // Step 1: tabel pi
    vector<int> pi = bangunPi(s);

    // Step 2: periode terkecil
    int k = n - pi[n - 1];

    // Step 3: hanya sah kalau membagi n habis
    cout << ((n % k == 0) ? k : n) << '\n';

    return 0;
}
