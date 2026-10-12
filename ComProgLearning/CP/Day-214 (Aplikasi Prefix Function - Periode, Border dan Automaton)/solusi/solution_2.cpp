/*
============================================================
✅ Solution 2: Semua Border
============================================================
Approach: Telusuri rantai pi
Complexity: Time O(n) | Space O(n)
Key Insight: Himpunan border sebuah string tertutup terhadap operasi
             "ambil border-nya lagi". Maka semua border = pi[n-1],
             pi[pi[n-1]-1], ... sampai mencapai 0.

📖 PENJELASAN PENDEKATAN:
1. Bangun pi.
2. Mulai dari k = pi[n-1]; selama k > 0 catat k, lalu k = pi[k-1].
3. Rantai itu STRICTLY MENURUN, jadi dibalik untuk mendapat urutan menaik.

Kenapa rantai ini lengkap (tidak ada border yang terlewat)? Misal b sebuah
border dengan b < pi[n-1]. Maka b adalah awalan sekaligus akhiran dari
border terpanjang tersebut, artinya b adalah border dari string sepanjang
pi[n-1] — dan itu persis yang dijelajahi langkah berikutnya.

🔄 ALTERNATIVE APPROACHES:
- Hashing: cek tiap panjang 1..n-1 dalam O(1) -> O(n) juga, tapi acak dan
  bisa di-hack. Rantai pi deterministik.
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

    vector<int> pi = bangunPi(s);

    // Telusuri rantai border (menurun)
    vector<int> res;
    int k = pi[n - 1];
    while (k > 0) {
        res.push_back(k);
        k = pi[k - 1];
    }

    // Diminta menaik
    reverse(res.begin(), res.end());

    for (size_t i = 0; i < res.size(); i++)
        cout << res[i] << " \n"[i + 1 == res.size()];
    if (res.empty()) cout << '\n';

    return 0;
}
