/*
============================================================
✅ Solution 6: Menyusun Teks dari Stempel
============================================================
Approach: Z-function untuk himpunan border + sapuan interval
Complexity: Time O(n + m) | Space O(n)
Key Insight: Dua penempelan di posisi a < b dengan jarak d = b - a saling
             tumpang tindih sepanjang L = |P| - d. Tumpang tindih itu
             konsisten PERSIS ketika awalan P sepanjang L sama dengan
             akhiran P sepanjang L — yaitu ketika L adalah BORDER dari P.
             Dan semua border langsung terbaca dari z: z[i] == |P| - i.

📖 PENJELASAN PENDEKATAN:
1. Bangun z(P). Tandai isBorder[|P| - i] = true untuk setiap i dengan
   z[i] == |P| - i. Tambahkan isBorder[0] = true (tidak tumpang tindih
   selalu boleh) dan isBorder[|P|] = true (penempelan identik).
2. Untuk tiap pasangan berurutan p[j], p[j+1]:
   d = p[j+1] - p[j].
   - Kalau d >= |P|: tidak tumpang tindih, selalu valid.
   - Kalau d < |P|: butuh isBorder[|P| - d], kalau tidak -> jawaban 0.
3. Hitung total posisi yang TERTUTUP stempel. Karena posisi terurut menaik,
   sapuan satu arah cukup: setiap penempelan menutup dari max(p[j], akhir+1)
   sampai p[j] + |P| - 1.
4. bebas = N - tertutup. Jawabannya 26^bebas mod 1e9+7.

VERIFIKASI SAMPEL 1 (N=6, P="ioi", posisi 1 dan 3):
   z("ioi") = [0, 0, 1] -> i=2: z=1, |P|-i = 1 ✓ -> isBorder[1] = true
   d = 3 - 1 = 2 < 3, butuh isBorder[3-2] = isBorder[1] = true  ✓ valid
   tertutup: [1..3] lalu [3..5] -> total 5; bebas = 6 - 5 = 1
   jawaban = 26^1 = 26  ✓

VERIFIKASI SAMPEL 2 (N=5, P="ioi", posisi 1 dan 2):
   d = 1 < 3, butuh isBorder[2]. Border "ioi" hanya {1}. -> 0  ✓

EDGE CASE M = 0: tidak ada penempelan, seluruh N posisi bebas -> 26^N.

🔄 ALTERNATIVE APPROACHES:
- Prefix function: rantai border memberi himpunan yang sama. Setara.
- Hashing untuk mengecek tiap tumpang tindih: O(M) query O(1), tapi
  probabilistik dan tidak lebih cepat.
- Menandai setiap posisi tertutup satu per satu: O(M * |P|) -> TLE saat
  M = 10^6 dan |P| = 10^6.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

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

ll pangkat(ll b, ll e, ll mod) {
    ll r = 1; b %= mod;
    while (e) { if (e & 1) r = r * b % mod; b = b * b % mod; e >>= 1; }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; int m;
    cin >> n >> m;
    string p;
    cin >> p;
    int lp = p.size();

    vector<ll> pos(m);
    for (int i = 0; i < m; i++) cin >> pos[i];

    // Step 1: himpunan panjang border
    vector<char> isBorder(lp + 1, 0);
    isBorder[0] = 1;                       // tidak tumpang tindih
    isBorder[lp] = 1;                      // penempelan identik
    vector<int> z = bangunZ(p);
    for (int i = 1; i < lp; i++)
        if (z[i] == lp - i) isBorder[lp - i] = 1;

    // Step 2: validasi tiap pasangan berurutan
    for (int j = 0; j + 1 < m; j++) {
        ll d = pos[j + 1] - pos[j];
        if (d < lp && !isBorder[lp - d]) { cout << 0 << '\n'; return 0; }
    }

    // Step 3: total posisi tertutup (sapuan satu arah, posisi sudah terurut)
    ll tertutup = 0, akhir = 0;            // akhir = posisi terakhir yang sudah tertutup
    for (int j = 0; j < m; j++) {
        ll kiri = max(pos[j], akhir + 1);
        ll kanan = pos[j] + lp - 1;
        if (kanan >= kiri) tertutup += kanan - kiri + 1;
        akhir = max(akhir, kanan);
    }

    // Step 4: sisanya bebas
    cout << pangkat(26, n - tertutup, MOD) << '\n';
    return 0;
}
