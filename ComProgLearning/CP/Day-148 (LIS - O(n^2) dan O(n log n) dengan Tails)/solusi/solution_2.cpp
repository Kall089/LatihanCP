/*
============================================================
✅ Solution 2: LIS Versi O(n log n) dengan Tails
============================================================
Approach: array tails + binary search
Complexity: Time O(N log N) | Space O(N)
Key Insight: tails[k] = EKOR TERKECIL di antara SEMUA subsekuens naik yang
             panjangnya k+1 (dari elemen yang sudah diproses). Ekor yang lebih
             kecil tidak pernah merugikan -- apa pun yang bisa disambung ke
             ekor besar bisa juga disambung ke ekor kecil. Itu exchange
             argument yang membenarkan greedy ini.

📖 KENAPA tails SELALU TERURUT MENAIK (dan karenanya boleh di-binary-search):
   Ambil sembarang k. Ada subsekuens berpanjang k+2 yang ekornya tails[k+1].
   Buang elemen terakhirnya -> dapat subsekuens berpanjang k+1 dengan ekor
   yang LEBIH KECIL dari tails[k+1] (karena barisannya naik). Karena tails[k]
   adalah ekor TERKECIL untuk panjang k+1, maka tails[k] < tails[k+1]. ∎

📖 DUA KASUS:
   x lebih besar dari semua isi tails  -> push_back  (LIS memanjang)
   selain itu -> lower_bound memberi posisi p pertama dengan tails[p] >= x;
                 tulis tails[p] = x. Panjang LIS TIDAK berubah, tapi ekornya
                 jadi lebih kecil sehingga masa depan lebih terbuka.

⚠️ ISI tails BUKAN LIS-NYA. Ini kesalahpahaman paling umum tentang algoritma
   ini. Hanya tails.size() yang dijamin benar.
   Contoh [1,6,7,2,3]: setelah memproses 2, tails = [1,2,7]. Barisan itu BUKAN
   subsekuens sah dari [1,6,7,2] -- nilai 2 muncul SETELAH 7 di array asli.
   Untuk mendapat barisannya, lihat Solution 4.

⚠️ lower_bound = KETAT NAIK. Ia menggantikan elemen yang >= x, sehingga nilai
   yang SAMA dengan x ikut tergantikan dan x tidak bisa menyambung dirinya
   sendiri. Sampel 3 ([7,7,7,7]) menguji ini: jawabannya 1, bukan 4.
   Untuk versi tidak menurun, pakai upper_bound (lihat Solution 3).

⚠️ KOSONGKAN tails antar test case pada soal multi-kasus.

VERIFIKASI SAMPEL 1 ([3,1,4,1,5,9,2,6]):
   3 -> [3] ; 1 -> [1] ; 4 -> [1,4] ; 1 -> [1,4]
   5 -> [1,4,5] ; 9 -> [1,4,5,9] ; 2 -> [1,2,5,9] ; 6 -> [1,2,5,6]
   ukuran 4  ✓  (perhatikan [1,2,5,6] sendiri BUKAN subsekuens dari a)

🔄 ALTERNATIVE APPROACHES:
- Fenwick tree prefix-max atas nilai terkompresi (Day 170): O(N log N) juga,
  dan lebih mudah diperluas ke LIS BERBOBOT (AtCoder DP-Q) serta penghitungan.
- Patience sorting: algoritma ini persis aturan menumpuk kartu; tails adalah
  kartu teratas tiap tumpukan, dan banyak tumpukan = panjang LIS.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> tails;
    tails.reserve(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        auto it = lower_bound(tails.begin(), tails.end(), x);   // KETAT
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    cout << tails.size() << '\n';
    return 0;
}
