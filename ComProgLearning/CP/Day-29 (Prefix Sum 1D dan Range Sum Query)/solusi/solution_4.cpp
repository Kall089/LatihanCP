/*
============================================================
✅ Solution 4: Subarray Kelipatan K
============================================================
Approach: Prefix sum modulo + hitung pasangan sisa kembar
Complexity: Time O(n + K) | Space O(K)
Key Insight: (pre[r+1] - pre[l]) habis dibagi K  <=>  pre[r+1] dan pre[l]
             punya sisa bagi yang SAMA. Jadi masalahnya berubah menjadi
             "hitung berapa pasang prefix yang sisanya kembar" -- dan itu
             cukup array hitungan berukuran K, tanpa map sama sekali.

📖 PENJELASAN PENDEKATAN:
1. cnt berukuran K, cnt[0] = 1 (prefix kosong bersisa 0).
2. Sapu: cur = ((cur + x) % K + K) % K.
3. hasil += cnt[cur] (semua prefix sebelumnya yang sisanya sama), lalu cnt[cur]++.

⚠️ SISA BAGI NEGATIF adalah inti kesulitan soal ini.
   Di C++, (-7) % 3 bernilai -1, BUKAN 2. Kalau kamu langsung memakai hasilnya
   sebagai indeks array, itu akses di luar batas -- dan seringkali TIDAK crash
   di mesin lokal, sehingga lolos pengujianmu lalu RE atau WA di judge.
   Normalisasi ((x % K) + K) % K menyelesaikannya untuk semua kasus.

VERIFIKASI SAMPEL 1 (a = [2,-2,3], K = 3):
   cnt=[1,0,0]
   x=2  -> cur=2, hasil += cnt[2]=0 -> 0, cnt=[1,0,1]
   x=-2 -> cur=0, hasil += cnt[0]=1 -> 1, cnt=[2,0,1]
   x=3  -> cur=0, hasil += cnt[0]=2 -> 3, cnt=[3,0,1]
   Subarray: [2,-2], [3], [2,-2,3]  ->  3  ✓

CATATAN MEMORI: array berukuran K. Dengan K sampai 10^6 itu 8 MB untuk
long long -- aman. Kalau K bisa mencapai 10^9, ganti ke map.

🔄 ALTERNATIVE APPROACHES:
- map<ll,ll> alih-alih array: perlu kalau K sangat besar, tapi lebih lambat.
- Naif O(n^2): cukup untuk n <= 5000.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll K;
    cin >> n >> K;

    vector<ll> cnt(K, 0);
    cnt[0] = 1;                        // prefix kosong

    ll cur = 0, hasil = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        cur = ((cur + x) % K + K) % K; // normalisasi sisa negatif
        hasil += cnt[cur];
        cnt[cur]++;
    }

    cout << hasil << '\n';
    return 0;
}
