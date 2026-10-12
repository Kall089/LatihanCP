/*
============================================================
✅ Solution 4: Susun Ulang Jadi Palindrom
============================================================
Approach: Tabel frekuensi + konstruksi paruh kiri secara alfabet
Complexity: Time O(N + 26) | Space O(N)
Key Insight:
Palindrom dibaca sama dari dua arah, sehingga tiap huruf harus muncul
berpasangan (kiri dan kanan). Satu-satunya posisi yang tidak berpasangan
adalah tepat di tengah, dan itu hanya ada satu. Karena itu syaratnya:
banyaknya huruf berfrekuensi ganjil tidak boleh lebih dari satu.
Menyusun paruh kiri secara alfabet membuat jawabannya tunggal.
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

    int f[26] = {};
    for (char c : s) f[c - 'a']++;

    int ganjil = 0;
    for (int i = 0; i < 26; i++) if (f[i] % 2 == 1) ganjil++;

    if (ganjil > 1) { cout << "TIDAK ADA\n"; return 0; }

    string kiri, tengah;
    for (int i = 0; i < 26; i++) {
        if (f[i] % 2 == 1) tengah = string(1, char('a' + i));
        kiri += string(f[i] / 2, char('a' + i));
    }
    string kanan = kiri;
    reverse(kanan.begin(), kanan.end());

    cout << kiri + tengah + kanan << "\n";

    return 0;
}
