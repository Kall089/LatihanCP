/*
============================================================
✅ Solution 4: Pencocokan Pola pada Stream
============================================================
Approach: KMP Automaton (tabel transisi eksplisit)
Complexity: Time O(m*26 + n) | Space O(m*26)
Key Insight: Loop `while (j > 0 && ...) j = pi[j-1]` di KMP hanya bergantung
             pada (state, karakter). Karena kedua argumen itu terbatas,
             seluruh loop bisa dihitung SEKALI di awal dan disimpan sebagai
             tabel. Hasilnya O(1) worst-case per karakter, bukan amortisasi.

📖 PENJELASAN PENDEKATAN:
1. Tambahkan sentinel '#' di akhir pola. Ini membuat state |P| punya
   transisi keluar yang valid dan mencegah akses di luar array.
2. Bangun pi untuk pola+'#'.
3. aut[i][c]:
   - jika karakter c cocok dengan pola[i]  -> i + 1
   - jika tidak                            -> aut[pi[i-1]][c]
   Peminjaman ini sah karena pi[i-1] < i, jadi barisnya sudah jadi.
4. Jalankan: st = aut[st][ch]. Saat st == |P|, pola selesai muncul di posisi ini.

Kenapa tidak perlu mundur pada state |P|? Karena aut[|P|][c] sudah otomatis
sama dengan aut[pi[|P|-1]][c] — automaton sendiri yang menangani "lanjut
setelah cocok", termasuk kemunculan yang tumpang tindih.

🔄 ALTERNATIVE APPROACHES:
- KMP biasa: O(n+m) waktu, O(m) memori — lebih hemat memori, tetapi memakai
  while sehingga hanya O(1) amortisasi. Untuk stream murni tetap sah.
- Hashing rolling: O(n), tapi probabilistik dan tidak nyaman untuk DP.
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

    string t, p;
    cin >> t >> p;
    int m = p.size();

    // Step 1: pola + sentinel
    string pola = p + '#';
    int sz = pola.size();
    vector<int> pi = bangunPi(pola);

    // Step 2: tabel transisi
    vector<array<int, 26>> aut(sz);
    for (int i = 0; i < sz; i++)
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != pola[i]) aut[i][c] = aut[pi[i - 1]][c];
            else                             aut[i][c] = i + ('a' + c == pola[i]);
        }

    // Step 3: proses aliran, satu lookup per karakter
    vector<int> pos;
    int st = 0;
    for (int i = 0; i < (int)t.size(); i++) {
        st = aut[st][t[i] - 'a'];
        if (st == m) pos.push_back(i + 1);   // posisi akhir, 1-based
    }

    cout << pos.size() << '\n';
    for (size_t i = 0; i < pos.size(); i++)
        cout << pos[i] << " \n"[i + 1 == pos.size()];
    if (pos.empty()) cout << '\n';

    return 0;
}
