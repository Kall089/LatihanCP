/*
============================================================
✅ Solution 4: Rekonstruksi LIS
============================================================
Approach: tails + array idx (indeks pengisi) + array par (penyambung)
Complexity: Time O(N log N) | Space O(N)
Key Insight: Isi tails tidak bisa dipakai langsung, tapi POSISI tempat setiap
             elemen mendarat sudah cukup. Saat a[i] mendarat di posisi p,
             penyambungnya adalah elemen yang SAAT ITU mengisi tails[p-1].

📖 KENAPA RANTAINYA SAH:
   par[i] = idx[p-1] pada saat i diproses. Elemen itu:
     (a) muncul SEBELUM i di array -- karena sudah diproses lebih dulu, dan
     (b) nilainya LEBIH KECIL dari a[i] -- karena tails terurut menaik dan
         posisinya p-1 < p.
   Jadi setiap langkah rantainya naik dan urut. Panjang rantai dari idx.back()
   persis sama dengan tails.size().

⚠️ JANGAN MENGEMBALIKAN ISI tails.
   Ini kesalahan nomor satu pada soal rekonstruksi. tails bisa berisi gado-gado
   dari beberapa subsekuens berbeda. Contoh [1,6,7,2,3]: setelah memproses 2,
   tails = [1,2,7], dan 2 muncul SETELAH 7 di array asli -- bukan subsekuens.
   Yang benar HANYA ukurannya.

⚠️ par HARUS DICATAT SEBELUM tails DIPERBARUI.
   Kalau kamu menulis tails[p] = a[i] lebih dulu lalu membaca idx[p-1], nilai
   idx[p-1] masih benar (posisi p-1 tidak tersentuh), tapi kebiasaan mencatat
   dulu membuatmu aman kalau nanti p == 0 ditangani berbeda.

⚠️ p == 0 berarti a[i] memulai rantai baru -> par[i] tetap -1.

⚠️ MULAI PENELUSURAN DARI idx.back(), bukan dari indeks terakhir array.

VERIFIKASI SAMPEL 1 ([3,1,4,1,5,9,2,6]):
   i=0 (3): p=0, par=-1 ; tails=[3] idx=[0]
   i=1 (1): p=0, par=-1 ; tails=[1] idx=[1]
   i=2 (4): p=1, par=idx[0]=1 ; tails=[1,4] idx=[1,2]
   i=3 (1): p=0, par=-1 ; tails=[1,4] idx=[3,2]
   i=4 (5): p=2, par=idx[1]=2 ; tails=[1,4,5] idx=[3,2,4]
   i=5 (9): p=3, par=idx[2]=4 ; tails=[1,4,5,9] idx=[3,2,4,5]
   i=6 (2): p=1, par=idx[0]=3 ; tails=[1,2,5,9] idx=[3,6,4,5]
   i=7 (6): p=3, par=idx[2]=4 ; tails=[1,2,5,6] idx=[3,6,4,7]
   telusuri dari idx.back()=7: a[7]=6 <- a[4]=5 <- a[2]=4 <- a[1]=1
   hasil: 1 4 5 6, panjang 4  ✓
   Perhatikan: tails akhir [1,2,5,6] BUKAN jawabannya -- kebetulan mirip.

🔄 ALTERNATIVE APPROACHES:
- Versi O(n^2) dengan par[i] = j saat dp[i] membaik: jauh lebih mudah ditulis
  saat panik di kontes, kalau N <= 5000.
- Kalau soal meminta LIS yang leksikografis terkecil/terbesar, rekonstruksi
  ini tidak cukup -- butuh aturan tie-break tambahan saat memilih penyambung.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> tails, idx, par(n, -1);
    for (int i = 0; i < n; i++) {
        int p = lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin();
        if (p > 0) par[i] = idx[p - 1];                 // catat penyambung
        if (p == (int)tails.size()) { tails.push_back(a[i]); idx.push_back(i); }
        else { tails[p] = a[i]; idx[p] = i; }
    }

    vector<int> res;
    for (int v = idx.back(); v != -1; v = par[v]) res.push_back(a[v]);
    reverse(res.begin(), res.end());

    cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); i++)
        cout << res[i] << " \n"[i + 1 == res.size()];
    return 0;
}
