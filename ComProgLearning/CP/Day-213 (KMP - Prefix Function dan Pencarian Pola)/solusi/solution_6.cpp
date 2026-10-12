/*
============================================================
✅ Solution 6: Hitung Kemunculan Tiap Prefiks
============================================================
Approach: Akumulasi mundur pada rantai pi
Complexity: Time O(n) | Space O(n)
Key Insight:
Ide utamanya adalah aliran kontribusi. Bayangkan setiap posisi i pada string
menandai satu kemunculan prefiks sepanjang (pi[i]+1)... tetapi lebih tepatnya:
setiap kali prefiks sepanjang (i+1) muncul, maka border-nya (prefiks sepanjang
pi[i]) juga ikut muncul di tempat yang sama.

Karena itu jumlah kemunculan mengalir dari prefiks panjang ke prefiks pendek:
    cnt[pi[i] - 1] += cnt[i]

Arah penelusuran sangat penting. Kalau ditelusuri maju, cnt[i] mungkin masih
akan bertambah dari prefiks yang lebih panjang, sehingga yang dialirkan adalah
nilai yang belum lengkap. Menelusuri mundur menjamin cnt[i] sudah final saat
dipakai.
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

    int n = s.size();
    vector<int> pi = bangunPi(s);
    vector<ll> cnt(n, 1);            // tiap prefiks minimal muncul sekali

    // MUNDUR: kontribusi prefiks panjang dialirkan ke border-nya.
    // Kalau maju, cnt[i] belum lengkap saat dipakai -> hasil salah.
    for (int i = n - 1; i > 0; i--)
        if (pi[i] > 0) cnt[pi[i] - 1] += cnt[i];

    for (int i = 0; i < n; i++)
        cout << cnt[i] << " \n"[i + 1 == n];

    return 0;
}
