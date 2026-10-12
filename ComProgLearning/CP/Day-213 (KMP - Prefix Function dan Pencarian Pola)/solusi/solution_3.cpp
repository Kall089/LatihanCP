/*
============================================================
✅ Solution 3: Border Terpanjang
============================================================
Approach: Membaca langsung nilai terakhir tabel pi
Complexity: Time O(n) | Space O(n)
Key Insight:
Soal ini menunjukkan bahwa pi bukan sekadar alat bantu pencarian pola.
Definisi pi[i] ("awalan terpanjang yang juga menjadi akhiran dari S[0..i]")
adalah definisi border itu sendiri. Jadi pi[n-1] LANGSUNG menjawab soal ini
tanpa perhitungan tambahan apa pun.

Perhatikan bahwa border tidak boleh seluruh string. Untuk "aaaa" jawabannya
3 ("aaa"), bukan 4. Rumus pi sudah menjamin ini karena j selalu dimulai dari
pi[i-1] yang pasti lebih kecil dari i.
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

    vector<int> pi = bangunPi(s);
    // pi[n-1] TEPAT sama dengan panjang border terpanjang
    cout << pi.back() << "\n";

    return 0;
}
