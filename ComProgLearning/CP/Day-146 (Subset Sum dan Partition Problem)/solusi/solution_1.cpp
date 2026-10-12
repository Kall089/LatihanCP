/*
============================================================
✅ Solution 1: Ada Target?
============================================================
Approach: Subset sum boolean DP
Complexity: Time O(N*S) | Space O(S)
Key Insight: Sum s bisa dicapai setelah membaca elemen x jika sebelumnya
             sum s-x sudah bisa dicapai. Karena x hanya boleh dipakai sekali,
             update s harus dilakukan dari besar ke kecil.

📖 PENJELASAN PENDEKATAN:
1. Inisialisasi bisa[0] = true untuk subset kosong.
2. Untuk setiap elemen x, scan s dari S turun ke x.
3. Jika bisa[s-x] true, maka bisa[s] juga true.
4. Jawaban ada di bisa[S].

🔄 ALTERNATIVE APPROACHES:
- Brute force semua subset: O(2^N), hanya aman untuk N kecil.
- set<int> reachable: benar, tetapi lebih lambat dan bisa membesar cepat.
- bitset: lebih cepat untuk target besar, dibahas di Solution 6.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, S;
    cin >> n >> S;

    vector<int> a(n);
    for (int &x : a)
        cin >> x;

    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;

    for (int x : a)
    {
        for (int s = S; s >= x; s--)
        {
            if (bisa[s - x])
                bisa[s] = 1;
        }
    }

    cout << (bisa[S] ? "YES" : "NO") << '\n';
    return 0;
}
