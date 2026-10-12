/*
============================================================
✅ Solution 5: Substring Berulang Terpanjang
============================================================
Approach: Binary search pada panjang + hash set
Complexity: Time O(n log n) rata-rata | Space O(n)
Key Insight:
Kunci soal ini bukan hashing-nya, melainkan menyadari bahwa jawabannya
MONOTON. Kalau ada substring berulang sepanjang 5, maka memotong satu huruf
dari keduanya menghasilkan substring berulang sepanjang 4. Sifat "kalau bisa
di L maka bisa juga di L-1" inilah yang membuat binary search sah dipakai.

Tanpa binary search kita harus mencoba semua panjang satu per satu: O(n^2).
Dengan binary search hanya O(log n) percobaan, masing-masing O(n).

Perhatikan bahwa kemunculan yang tumpang tindih tetap dihitung, sehingga
"aaaa" menjawab 3 ("aaa" di indeks 0 dan 1).
============================================================
*/

#include <bits/stdc++.h>
#include <unordered_set>   // sebagian bits/stdc++.h tidak memuatnya
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    const ll P = 131, M = 1000000009;
    int n = s.size();
    vector<ll> h(n + 1, 0), p(n + 1, 1);
    for (int i = 0; i < n; i++) {
        h[i + 1] = (h[i] + (ll)(s[i] - 'a' + 1) * p[i]) % M;
        p[i + 1] = p[i] * P % M;
    }
    // hash mentah s[l..r] (masih berbobot p^l)
    auto get = [&](int l, int r) -> ll {
        if (l > r) return 0;
        return (h[r + 1] - h[l] + M) % M;
    };
    // apakah s[a..b] == s[c..d]? kalikan silang, hindari modular inverse
    auto sama = [&](int a, int b, int c, int d) -> bool {
        if (b - a != d - c) return false;
        return get(a, b) * p[c] % M == get(c, d) * p[a] % M;
    };

    // Apakah ada substring sepanjang len yang muncul >= 2 kali?
    auto ada = [&](int len) -> bool {
        if (len == 0) return true;
        unordered_set<ll> terlihat;
        terlihat.reserve(n * 2);
        for (int i = 0; i + len <= n; i++) {
            ll k = get(i, i + len - 1) * p[n - i] % M;   // ternormalisasi
            if (terlihat.count(k)) return true;
            terlihat.insert(k);
        }
        return false;
    };

    // Monoton: kalau len bisa, len-1 pasti bisa juga -> binary search
    int lo = 0, hi = n - 1, jawab = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (ada(mid)) { jawab = mid; lo = mid + 1; }
        else hi = mid - 1;
    }

    cout << jawab << "\n";

    return 0;
}
