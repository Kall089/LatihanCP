/*
============================================================
✅ Solution 5: Semua Border
============================================================
Approach: Menelusuri rantai border lewat pi
Complexity: Time O(n) | Space O(n)
Key Insight:
Sifat yang membuat soal ini mudah: jika B adalah border dari S, maka setiap
border dari B juga merupakan border dari S. Buktinya singkat — B adalah awalan
S dan juga akhiran S, jadi awalan B juga awalan S, dan akhiran B juga akhiran S.

Akibatnya semua border tersusun sebagai rantai menurun:
    pi[n-1]  ->  pi[pi[n-1]-1]  ->  ...  ->  0
Menelusuri rantai ini memberi seluruh border tanpa perlu mengecek satu per satu.

Tanpa sifat ini kita harus membandingkan awalan dan akhiran untuk setiap
panjang, yaitu O(n^2).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    // Bangun tabel pi: pi[i] = panjang awalan terpanjang p[0..i]
    // yang sekaligus menjadi akhirannya (bukan seluruh potongan).
    auto bangunPi = [](const string& p) {
        int m = p.size();
        vector<int> pi(m, 0);
        for (int i = 1; i < m; i++) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) j = pi[j - 1];   // mundur ke border lebih pendek
            if (p[i] == p[j]) j++;
            pi[i] = j;
        }
        return pi;
    };

    vector<int> pi = bangunPi(s), border;

    // Border dari border juga border -> telusuri rantainya
    int k = pi.back();
    while (k > 0) {
        border.push_back(k);
        k = pi[k - 1];
    }
    reverse(border.begin(), border.end());   // dari terpanjang -> jadikan menaik

    if (border.empty()) { cout << -1 << "\n"; return 0; }
    for (int i = 0; i < (int)border.size(); i++)
        cout << border[i] << " \n"[i + 1 == (int)border.size()];

    return 0;
}
