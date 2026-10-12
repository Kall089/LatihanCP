/*
============================================================
✅ Solution 3: Muatan Maksimum
============================================================
Approach: Meet in the middle, varian "terbesar tanpa melebihi"
Complexity: Time O(2^(N/2) · N) | Space O(2^(N/2))
Key Insight: Strukturnya sama dengan Solution 2, tetapi pertanyaannya
             berubah dari "tepat sama" menjadi "terbesar yang tidak
             melebihi". Perubahan kecil pada pertanyaan berarti perubahan
             kecil pada bound yang dipakai -- upper_bound lalu mundur satu,
             persis pola dari Day 49.

📖 PENJELASAN PENDEKATAN:
1. Bagi dua, bangkitkan seluruh jumlah subset masing-masing paruh.
2. Urutkan paruh kiri.
3. Untuk setiap jumlah paruh kanan s dengan s <= W:
   sisa = W - s, lalu cari jumlah kiri TERBESAR yang <= sisa:
       idx = upper_bound(sk, sisa) - sk.begin() - 1;
   Kalau idx >= 0, kandidatnya s + sk[idx].

⚠️ PEMERIKSAAN idx >= 0 WAJIB. Kalau seluruh jumlah kiri melebihi sisa,
   upper_bound mengembalikan begin() dan idx menjadi -1. Mengakses sk[-1]
   adalah perilaku tak terdefinisi yang sering tidak crash -- bug senyap.
   (Dalam praktik idx tidak pernah -1 di sini karena sk selalu memuat 0
   dari subset kosong, tetapi menuliskan pemeriksaannya adalah kebiasaan
   yang benar dan melindungi dari varian soal lain.)

⚠️ OVERFLOW: W dan berat masing-masing mencapai 10^18. Menjumlahkan dua
   subset yang keduanya besar bisa MELUAP long long (batas ~9.2*10^18).
   Solusinya di sini: kita hanya menjumlahkan s + sk[idx] SETELAH memastikan
   keduanya tidak melebihi W, sehingga totalnya juga <= W <= 10^18 -- aman.
   Tetapi saat MEMBANGKITKAN subset, jumlah seluruh 20 elemen bisa mencapai
   2*10^19 yang MELUAP. Untuk soal dengan batas seperti ini, pertimbangkan
   memakai unsigned long long atau memotong nilai yang sudah melebihi W
   selama pembangkitan.

⚠️ MENGAPA PREFIX MAKSIMUM TIDAK DIPERLUKAN DI SINI:
   Karena kita memaksimalkan besaran yang SAMA dengan yang kita urutkan
   (jumlah berat). Pada array terurut menaik, "elemen terakhir yang <= sisa"
   otomatis adalah yang terbesar. Prefix maksimum baru wajib ketika ada DUA
   besaran terpisah -- lihat Solution 4.

VERIFIKASI SAMPEL 1 (a = [1,2,3,4], W = 5):
   sk = [0, 1, 2, 3], sn = [0, 3, 4, 7]
   s = 0 -> sisa 5 -> terbesar 3 -> total 3
   s = 3 -> sisa 2 -> terbesar 2 -> total 5   <- terbaik
   s = 4 -> sisa 1 -> terbesar 1 -> total 5
   s = 7 -> melebihi W, dilewati
   jawab 5   ✓

🔄 ALTERNATIVE APPROACHES:
- DP knapsack O(N * W): mustahil, W sampai 10^18.
- Greedy (ambil yang terberat dulu): SALAH untuk knapsack 0/1.
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
    ll W;
    cin >> n >> W;
    vector<ll> a(n);
    for (ll& v : a) cin >> v;

    int k = n / 2;
    vector<ll> sk = semuaSubset(vector<ll>(a.begin(), a.begin() + k));
    vector<ll> sn = semuaSubset(vector<ll>(a.begin() + k, a.end()));

    sort(sk.begin(), sk.end());

    ll best = 0;
    for (ll s : sn) {
        if (s > W) continue;                         // paruh kanan saja sudah lebih
        ll sisa = W - s;
        int idx = int(upper_bound(sk.begin(), sk.end(), sisa) - sk.begin()) - 1;
        if (idx >= 0) best = max(best, s + sk[idx]); // pemeriksaan batas WAJIB
    }

    cout << best << '\n';
    return 0;
}
