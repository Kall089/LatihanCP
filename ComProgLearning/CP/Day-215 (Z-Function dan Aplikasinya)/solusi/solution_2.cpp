/*
============================================================
✅ Solution 2: Cari Pola dengan Z
============================================================
Approach: Z pada string gabungan P + separator + T
Complexity: Time O(n + m) | Space O(n + m)
Key Insight: z[i] pada string gabungan menjawab "berapa huruf dari awal g
             yang cocok mulai posisi i". Karena awal g adalah pola itu sendiri,
             z[i] >= |P| berarti pola muncul utuh di posisi tersebut.

📖 PENJELASAN PENDEKATAN:
1. g = P + '\1' + T.
2. Bangun z(g) dalam O(|P| + |T|).
3. Untuk i mulai dari |P| + 1 (bagian teks), z[i] >= |P| berarti cocok.
4. Indeks di T = i - |P| - 1 (0-based).

KENAPA SEPARATOR WAJIB: tanpa pemisah, kecocokan bisa menyeberang dari daerah
pola ke daerah teks. Contoh P = "aa", T = "aa" tanpa separator menghasilkan
g = "aaaa" dengan z[1] = 3 — bocor, dan hitungan posisi jadi kacau.
Separator memaksa setiap kecocokan berhenti tepat di batas, sehingga z[i] <= |P|.

KENAPA '\1' BUKAN '#': kalau soal mengizinkan karakter apa pun (misalnya input
berupa string ASCII printable), '#' bisa saja ada di dalam P atau T dan
separatormu tidak lagi memisahkan apa pun. '\1' adalah control character yang
praktis tidak pernah muncul di input kontes.

🔄 ALTERNATIVE APPROACHES:
- KMP: O(n+m) waktu, O(m) memori — lebih hemat memori karena tidak menggabung.
- Rabin-Karp: O(n+m) rata-rata, tapi bisa di-hack di Codeforces.
- Aho-Corasick: berlebihan untuk satu pola.
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

    string t, p;
    cin >> t >> p;
    int m = p.size();

    // Step 1: gabungkan dengan separator yang aman
    string g = p + '\1' + t;
    vector<int> z = bangunZ(g);

    // Step 2: pindai bagian teks saja
    vector<int> pos;
    for (int i = m + 1; i < (int)g.size(); i++)
        if (z[i] >= m) pos.push_back(i - m);      // (i - m - 1) 0-based, +1 -> 1-based

    // Step 3: keluarkan
    cout << pos.size() << '\n';
    string out;
    for (size_t i = 0; i < pos.size(); i++) {
        out += to_string(pos[i]);
        out += (i + 1 == pos.size()) ? '\n' : ' ';
    }
    if (pos.empty()) out = "\n";
    cout << out;

    return 0;
}
