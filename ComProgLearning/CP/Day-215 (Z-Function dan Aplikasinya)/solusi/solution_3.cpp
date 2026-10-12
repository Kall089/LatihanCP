/*
============================================================
✅ Solution 3: Border dan Periode dari Z
============================================================
Approach: z[i] == n - i sebagai penanda border
Complexity: Time O(n) | Space O(n)
Key Insight: Sufiks yang dimulai di i adalah border persis ketika ia cocok
             dengan awalan S sampai HABIS. "Sampai habis" berarti panjang
             kecocokan sama dengan sisa panjangnya, yaitu z[i] == n - i.
             Satu baris, langsung dari definisi — tanpa rantai apa pun.

📖 PENJELASAN PENDEKATAN:
1. Bangun z.
2. Kumpulkan semua i (1 <= i < n) dengan z[i] == n - i.
   Panjang border yang bersesuaian adalah n - i.
   Karena i menaik, n - i menurun -> balik untuk urutan menaik.
3. Periode terkecil = i TERKECIL yang memenuhi (karena periode = n - border,
   dan i di sini persis sama dengan n - (n-i) = pergeserannya). Kalau tidak
   ada sama sekali, periode terkecil = n.
4. Pengulangan utuh butuh DUA syarat: ada i < n yang periodik DAN n % i == 0.

Perbandingan dengan pendekatan pi (Day 214): dengan pi kita menelusuri rantai
pi[n-1] -> pi[k-1] -> ...; dengan z kita cukup satu loop lurus. Untuk masalah
border, z memang lebih nyaman. Sebaliknya, untuk "hitung kemunculan setiap
prefiks", rantai pi yang lebih nyaman.

🔄 ALTERNATIVE APPROACHES:
- Prefix function + rantai border: O(n) juga (Day 214 solution 1 & 2).
- Hashing: O(n) tapi probabilistik.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> bangunZ(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> z = bangunZ(s);

    // Step 1: semua border
    vector<int> border;
    for (int i = 1; i < n; i++)
        if (z[i] == n - i) border.push_back(n - i);
    reverse(border.begin(), border.end());

    for (size_t i = 0; i < border.size(); i++)
        cout << border[i] << " \n"[i + 1 == border.size()];
    if (border.empty()) cout << '\n';

    // Step 2: periode terkecil
    int periode = n;
    for (int i = 1; i < n; i++)
        if (z[i] == n - i) { periode = i; break; }
    cout << periode << '\n';

    // Step 3: pengulangan utuh butuh keterbagian juga
    cout << ((periode < n && n % periode == 0) ? "YES" : "NO") << '\n';

    return 0;
}
