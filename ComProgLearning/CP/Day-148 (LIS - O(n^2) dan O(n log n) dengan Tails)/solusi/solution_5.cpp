/*
============================================================
✅ Solution 5: Menghitung Banyak LIS
============================================================
Approach: dua array DP berpasangan -- panjang dan jumlah
Complexity: Time O(N^2) | Space O(N)
Key Insight: Menghitung "berapa banyak yang optimal" selalu memerlukan DUA
             informasi per state: nilai optimalnya, DAN berapa cara mencapai
             nilai itu. Aturannya universal:
                 nilai baru LEBIH BAIK  -> SALIN jumlahnya (yang lama batal)
                 nilai baru SAMA        -> TAMBAHKAN jumlahnya

📖 REKURENS:
   len[i] = panjang LIS yang berakhir tepat di i
   cnt[i] = ada berapa LIS sepanjang len[i] yang berakhir tepat di i
   untuk setiap j < i dengan a[j] < a[i]:
       len[j]+1 >  len[i]  ->  len[i] = len[j]+1 ; cnt[i] = cnt[j]
       len[j]+1 == len[i]  ->  cnt[i] += cnt[j]
   jawaban = jumlah cnt[i] atas semua i dengan len[i] == max

⚠️ INISIALISASI cnt[i] = 1, BUKAN 0. Setiap elemen sendirian sudah merupakan
   satu LIS berpanjang 1. Sampel 2 ([2,2,2]) menguji ini: jawabannya "1 3" --
   tiga elemen, masing-masing satu LIS berpanjang 1.

⚠️ JANGAN MENJUMLAHKAN cnt SEMBARANGAN DI AKHIR. Hanya i dengan len[i] SAMA
   DENGAN MAKSIMUM yang boleh ikut. Menjumlahkan semuanya adalah bug yang
   sangat sering terjadi.

⚠️ URUTAN CABANG. Cek ">" dulu, baru "==". Kalau ditukar (atau memakai ">="
   untuk cabang pertama), cnt[i] akan tertimpa alih-alih bertambah.

⚠️ MODULO. Banyak LIS bisa tumbuh eksponensial (bayangkan array terurut naik
   dengan banyak nilai sama panjangnya).

VERIFIKASI SAMPEL 1 ([1,3,5,4,7]):
   i=0: len=1 cnt=1
   i=1: dari 1 -> len=2 cnt=1
   i=2: dari 3 -> len=3 cnt=1
   i=3 (4): dari 1 -> len=2 cnt=1 ; dari 3 -> len=3 cnt=1
   i=4 (7): dari 5 -> len=4 cnt=1 ; dari 4 -> len 3+1=4 SAMA -> cnt += 1 = 2
   max len = 4, total cnt = 2  ✓  (1 3 5 7 dan 1 3 4 7)

VERIFIKASI SAMPEL 3 ([1,2,4,3,5,4]):
   LIS panjang 4: (1,2,4,5), (1,2,3,5), (1,2,3,4)  -> 3  ✓

🔄 ALTERNATIVE APPROACHES:
- O(N log N) dengan Fenwick tree (Day 170) atas nilai terkompresi yang
  menyimpan pasangan (panjang maksimum, jumlah). Diperlukan kalau N > ~5000.
- Pola SALIN/TAMBAH ini identik dengan menghitung jalur terpendek di Day 127
  dan Day 120. Sekali kamu mengenalinya, ia muncul di mana-mana.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> len(n, 1);
    vector<ll> cnt(n, 1);                    // setiap elemen = 1 LIS panjang 1
    int best = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) {
                if (len[j] + 1 > len[i]) { len[i] = len[j] + 1; cnt[i] = cnt[j]; }
                else if (len[j] + 1 == len[i]) cnt[i] = (cnt[i] + cnt[j]) % MOD;
            }
        best = max(best, len[i]);
    }

    ll total = 0;
    for (int i = 0; i < n; i++)
        if (len[i] == best) total = (total + cnt[i]) % MOD;   // HANYA yang maksimum

    cout << best << ' ' << total << '\n';
    return 0;
}
