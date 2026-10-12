/*
============================================================
✅ Solution 6: Substring Bersama Terpanjang
============================================================
Approach: Binary search pada panjang + hash set dua string
Complexity: Time O((|A| + |B|) log min(|A|,|B|)) | Space O(|A|)
Key Insight:
Polanya persis sama dengan soal sebelumnya, hanya sumbernya dua string.
Sifat monotonnya tetap berlaku: kalau ada substring bersama sepanjang L,
memotong satu huruf tetap menghasilkan substring bersama sepanjang L-1.

Satu detail penting: kedua string HARUS memakai acuan normalisasi yang sama.
Di sini keduanya dinormalkan dengan p[maks - i] memakai satu array pangkat
bersama, sehingga substring identik dari A dan dari B pasti bernilai sama.
Kalau masing-masing dinormalkan dengan panjangnya sendiri, hasilnya tidak
akan pernah cocok.
============================================================
*/

#include <bits/stdc++.h>
#include <unordered_set>   // sebagian bits/stdc++.h tidak memuatnya
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    const ll P = 131, M = 1000000009;
    int na = a.size(), nb = b.size();
    int maks = max(na, nb);

    vector<ll> ha(na + 1, 0), hb(nb + 1, 0), p(maks + 1, 1);
    for (int i = 0; i < maks; i++) p[i + 1] = p[i] * P % M;
    for (int i = 0; i < na; i++) ha[i + 1] = (ha[i] + (ll)(a[i] - 'a' + 1) * p[i]) % M;
    for (int i = 0; i < nb; i++) hb[i + 1] = (hb[i] + (ll)(b[i] - 'a' + 1) * p[i]) % M;

    auto getA = [&](int l, int r) { return (ha[r + 1] - ha[l] + M) % M; };
    auto getB = [&](int l, int r) { return (hb[r + 1] - hb[l] + M) % M; };

    // Adakah substring sepanjang len yang muncul di A dan juga di B?
    // Keduanya dinormalkan memakai array pangkat YANG SAMA supaya sebanding.
    auto ada = [&](int len) -> bool {
        if (len == 0) return true;
        if (len > na || len > nb) return false;
        unordered_set<ll> dariA;
        dariA.reserve(na * 2);
        for (int i = 0; i + len <= na; i++)
            dariA.insert(getA(i, i + len - 1) * p[maks - i] % M);
        for (int i = 0; i + len <= nb; i++)
            if (dariA.count(getB(i, i + len - 1) * p[maks - i] % M)) return true;
        return false;
    };

    int lo = 0, hi = min(na, nb), jawab = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (ada(mid)) { jawab = mid; lo = mid + 1; }
        else hi = mid - 1;
    }

    cout << jawab << "\n";

    return 0;
}
