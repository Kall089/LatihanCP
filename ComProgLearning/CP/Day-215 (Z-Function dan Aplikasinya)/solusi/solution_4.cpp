/*
============================================================
✅ Solution 4: Kalung Berputar
============================================================
Approach: Z pada A + separator + B + B
Complexity: Time O(n) per pasangan | Space O(n)
Key Insight: Setiap rotasi B adalah substring sepanjang |B| dari B+B, dan
             SEBALIKNYA setiap substring sepanjang |B| dari B+B (dimulai di
             posisi 0..|B|-1) adalah sebuah rotasi. Jadi "apakah A rotasi B"
             sama dengan "apakah A muncul di B+B".

📖 PENJELASAN PENDEKATAN:
1. g = A + '\1' + B + B.
2. Bangun z(g).
3. Bagian B+B dimulai di indeks m + 1 (m = |A|). Pergeseran k bersesuaian
   dengan indeks i = m + 1 + k.
4. Hitung k dari 0 sampai m-1 (BUKAN sampai 2m-1) dengan z[i] >= m.

KENAPA HANYA k < m: posisi k = m di B+B menghasilkan substring yang identik
dengan k = 0 (memutar sejauh |B| = tidak memutar). Menghitungnya akan
menggandakan jawaban. Pada sampel "aaaa"/"aaaa", jawaban benar 4, bukan 5.

EDGE CASE: |A| != |B| -> langsung NO tanpa membangun apa pun.

🔄 ALTERNATIVE APPROACHES:
- KMP pada A + '\1' + B + B: sama persis, O(n).
- Booth's algorithm: cari rotasi minimum kedua string lalu bandingkan. O(n),
  tapi tidak langsung memberi BANYAKNYA k yang cocok.
- Hashing: O(n), bisa di-hack.
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

    int q;
    cin >> q;
    while (q--) {
        string a, b;
        cin >> a >> b;

        if (a.size() != b.size()) { cout << "NO\n"; continue; }
        int m = a.size();

        string g = a + '\1' + b + b;
        vector<int> z = bangunZ(g);

        // Hanya pergeseran k = 0..m-1 yang berbeda
        int cnt = 0;
        for (int k = 0; k < m; k++)
            if (z[m + 1 + k] >= m) cnt++;

        if (cnt) cout << "YES " << cnt << '\n';
        else     cout << "NO\n";
    }

    return 0;
}
