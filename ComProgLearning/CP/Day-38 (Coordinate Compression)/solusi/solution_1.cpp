/*
============================================================
✅ Solution 1: Kompres Array
============================================================
Approach: sort + unique + erase + lower_bound
Complexity: Time O(n log n) | Space O(n)
Key Insight: Nilai boleh mencapai 10^9, tetapi paling banyak hanya ada n
             nilai BERBEDA yang benar-benar muncul. Kompresi menukar
             "domain nilai" yang raksasa dengan "domain peringkat" yang
             ukurannya paling besar n.

📖 PENJELASAN PENDEKATAN:
1. Salin array ke v.
2. sort(v) -- wajib, karena unique hanya membuang duplikat BERDAMPINGAN.
   Tanpa sort, [1,2,1] tetap menjadi [1,2,1].
3. v.erase(unique(v.begin(), v.end()), v.end()) -- erase juga wajib.
4. Peringkat setiap elemen = lower_bound(v, a[i]) - v.begin().

⚠️ KENAPA unique SAJA TIDAK CUKUP:
   unique TIDAK menghapus elemen. Ia memindahkan elemen unik ke depan lalu
   mengembalikan iterator ke akhir bagian unik. Isi SETELAH iterator itu
   tidak terdefinisi, dan v.size() TIDAK berubah.
   Kalau kamu lupa erase, lower_bound akan mencari di dalam vektor yang
   ekornya berisi sampah -- kadang hasilnya kebetulan benar, kadang tidak.
   Itu jenis bug terburuk: tidak konsisten.

   sebelum : [5, 5, 999, 1e9, 1e9]   size 5
   unique  : [5, 999, 1e9, ?, ?]     size TETAP 5
   erase   : [5, 999, 1e9]           size 3   ✓

APA YANG DIPERTAHANKAN: urutan relatif dan kesamaan.
APA YANG HILANG       : jarak. Kalau nanti kamu butuh nilai aslinya,
                        pakai v[peringkat] -- karena itu v jangan dibuang.

🔄 ALTERNATIVE APPROACHES:
- map<ll,int> lalu iterasi berurutan untuk memberi nomor: O(n log n) juga,
  tetapi konstantanya jauh lebih besar dan memorinya boros.
- Kalau nilainya kecil (misalnya <= 10^6), tidak perlu kompresi sama sekali.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    // Step 1-3: bangun kamus nilai unik terurut
    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());   // erase WAJIB

    // Step 4: petakan
    string out;
    for (int i = 0; i < n; i++) {
        int idx = int(lower_bound(v.begin(), v.end(), a[i]) - v.begin());
        out += to_string(idx);
        out += (i + 1 == n) ? '\n' : ' ';
    }
    cout << out;
    cout << v.size() << '\n';

    return 0;
}
