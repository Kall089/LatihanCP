/*
============================================================
✅ Solution 3: Hitung Kemunculan Setiap Prefiks
============================================================
Approach: Agregasi mundur pada rantai pi
Complexity: Time O(n) | Space O(n)
Key Insight: Kalau prefiks sepanjang L muncul di suatu posisi, maka SEMUA
             border dari prefiks itu juga muncul di posisi yang sama.
             Alih-alih menelusuri rantai untuk tiap posisi (O(n^2)),
             kita proses panjang dari besar ke kecil sehingga setiap nilai
             cukup diwariskan SATU langkah — akumulasi terjadi sendirinya.

📖 PENJELASAN PENDEKATAN:
1. cnt[pi[i]]++ untuk setiap i: posisi i menyaksikan kecocokan sepanjang pi[i].
2. for len = n turun ke 1: cnt[pi[len-1]] += cnt[len].
   Saat kita sampai di len, semua kontribusi dari panjang > len sudah masuk
   ke cnt[len], jadi mewariskannya satu langkah sudah membawa seluruh subtree.
3. cnt[len]++ untuk semua len: prefiks selalu muncul minimal sekali (dirinya).

Struktur di balik ini adalah "prefix link tree": simpul len punya induk
pi[len-1]. Langkah 2 adalah akumulasi subtree, dan urutan len menurun
kebetulan sudah merupakan urutan topologis yang benar.

🔄 ALTERNATIVE APPROACHES:
- Suffix automaton: O(n) juga, tapi jauh lebih panjang ditulis.
- Naif menelusuri rantai per posisi: O(n^2) — TLE pada "aaaa...a".
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
    vector<ll> cnt(n + 1, 0);

    // Step 1: sumbangan mentah
    for (int i = 0; i < n; i++) cnt[pi[i]]++;

    // Step 2: wariskan ke border (mundur = urutan topologis yang benar)
    for (int len = n; len > 0; len--) cnt[pi[len - 1]] += cnt[len];

    // Step 3: prefiks itu sendiri
    for (int len = 1; len <= n; len++) cnt[len]++;

    string out;
    for (int len = 1; len <= n; len++) {
        out += to_string(cnt[len]);
        out += '\n';
    }
    cout << out;

    return 0;
}
