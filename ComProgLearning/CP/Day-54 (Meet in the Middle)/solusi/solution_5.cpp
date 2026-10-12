/*
============================================================
✅ Solution 5: Jumlah Subset Terdekat dengan Target
============================================================
Approach: Meet in the middle + memeriksa DUA kandidat
Complexity: Time O(2^(N/2) · N) | Space O(2^(N/2))
Key Insight: Varian "terdekat" berbeda dari "tepat sama" (Solution 2) dan
             "terbesar tanpa melebihi" (Solution 3): kandidat terbaik bisa
             berada DI ATAS maupun DI BAWAH target. Karena itu setelah
             lower_bound memberi posisi, kita harus memeriksa DUA posisi --
             yang ditunjuk dan yang tepat sebelumnya.

📖 PENJELASAN PENDEKATAN:
1. Bagi dua, bangkitkan seluruh jumlah subset, urutkan paruh kiri.
2. Untuk setiap jumlah kanan s, kita ingin jumlah kiri yang paling dekat
   dengan (T - s).
3. i = lower_bound(sk, T - s) memberi posisi pertama yang >= target.
   Kandidatnya: sk[i] (yang pertama >= target) dan sk[i-1] (yang terakhir
   < target). Periksa keduanya, dengan pemeriksaan batas.

⚠️ MEMERIKSA BATAS SEBELUM MENGAKSES:
   i bisa bernilai 0 (tidak ada kandidat di kiri) atau sk.size() (tidak ada
   kandidat di kanan). Mengakses sk[-1] atau sk[sk.size()] adalah perilaku
   tak terdefinisi. Pola pemeriksaan ini sama persis dengan Day 49
   Exercise 3 ("nilai terdekat") -- kenali bentuknya.

⚠️ NILAI NEGATIF TIDAK MENGGANGGU MITM. Ini pertanyaan yang wajar: pada
   sliding window dan two pointers, bilangan negatif merusak monotonisitas
   dan membuat teknik tidak berlaku (Day 34). Tetapi MITM tidak bergantung
   pada monotonisitas sama sekali -- kita ENUMERASI seluruh subset lalu
   mengurutkan hasilnya. Urutan pengurutan tidak peduli dari mana angkanya
   berasal.
   Sampel 3 sengaja memuat -5 dan 5 untuk menegaskan ini.

⚠️ OVERFLOW: N = 40 dengan nilai 10^9 memberi jumlah sampai 4*10^10, dan
   T sampai 10^12. Selisihnya bisa mencapai 10^12 -- muat di long long,
   tetapi jangan memakai int di mana pun dalam rantai ini.

VERIFIKASI SAMPEL 2 (a = [1,2,3], T = 10):
   Seluruh jumlah subset: 0, 1, 2, 3, 3, 4, 5, 6
   Yang paling dekat dengan 10 adalah 6, selisihnya 4.   ✓

VERIFIKASI SAMPEL 3 (a = [-5, 5], T = 0):
   Jumlah subset: 0 (kosong), -5, 5, 0 ({-5,5})
   Ada yang tepat 0, jadi selisihnya 0.   ✓

🔄 ALTERNATIVE APPROACHES:
- Set alih-alih vector terurut: memungkinkan pencarian dengan lower_bound
  fungsi anggota, tetapi lebih lambat dan tidak ada keuntungan di sini.
- Kalau nilainya kecil, DP subset sum atas bitset bisa lebih cepat.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> semuaSubset(const vector<ll>& a) {
    int k = a.size();
    vector<ll> h(1 << k, 0);
    for (int mask = 1; mask < (1 << k); mask++) {
        int b = __builtin_ctz(mask);
        h[mask] = h[mask ^ (1 << b)] + a[b];
    }
    return h;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll T;
    cin >> n >> T;
    vector<ll> a(n);
    for (ll& v : a) cin >> v;

    int k = n / 2;
    vector<ll> sk = semuaSubset(vector<ll>(a.begin(), a.begin() + k));
    vector<ll> sn = semuaSubset(vector<ll>(a.begin() + k, a.end()));

    sort(sk.begin(), sk.end());

    ll best = LLONG_MAX;
    for (ll s : sn) {
        ll butuh = T - s;
        int i = int(lower_bound(sk.begin(), sk.end(), butuh) - sk.begin());

        // DUA kandidat: posisi i dan posisi i-1, dengan pemeriksaan batas
        if (i < (int)sk.size()) best = min(best, llabs(s + sk[i] - T));
        if (i > 0)              best = min(best, llabs(s + sk[i - 1] - T));
    }

    cout << best << '\n';
    return 0;
}
