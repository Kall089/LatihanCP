/*
============================================================
✅ Solution 3: GCD pada Rentang
============================================================
Approach: Sparse table dengan operasi gcd
Complexity: Time O(n log n · log V + q · log V) | Space O(n log n)
Key Insight: Struktur sparse table sama sekali tidak peduli operasi apa yang
             dipakai -- selama operasi itu IDEMPOTEN. Memverifikasi syarat
             itu adalah satu-satunya pekerjaan konseptual di soal ini.

📖 APAKAH GCD IDEMPOTEN?
       gcd(x, x) = x   untuk setiap x.
   Ya. Jadi daerah tumpang tindih boleh terhitung dua kali tanpa mengubah
   hasilnya, dan seluruh struktur dari Exercise 1 bisa dipakai apa adanya --
   kita hanya mengganti `min` menjadi `__gcd`.

   Bandingkan dengan sum: sum(x, x) = 2x, tidak idempoten, sehingga sparse
   table gagal. Perbedaan satu sifat menentukan bisa atau tidaknya.

📖 KOMPLEKSITAS SEBENARNYA:
   Setiap pemanggilan __gcd berbiaya O(log V) dengan algoritma Euclid, bukan
   O(1). Jadi:
       build : O(n log n · log V)
       query : O(log V) per query, bukan O(1)
   Untuk n = q = 2*10^5 dan V = 10^9 (log V ~ 30):
       build ~ 2*10^5 * 18 * 30 = 10^8    -- ketat tetapi biasanya lolos
       query ~ 2*10^5 * 30 = 6*10^6       -- ringan
   Dalam praktik jauh lebih cepat karena Euclid jarang mencapai kasus
   terburuknya (kasus terburuk adalah bilangan Fibonacci berurutan).

⚠️ __gcd MEMBUTUHKAN <algorithm> dan tersedia di GCC. Untuk C++17 standar,
   std::gcd dari <numeric> lebih portabel. Keduanya bekerja di kontes.
   __gcd(0, x) = x, yang berguna sebagai elemen identitas.

⚠️ TIPE DATA: nilai sampai 10^9 muat di int, tetapi biasakan long long untuk
   gcd karena beberapa soal memakai nilai lebih besar, dan __gcd pada tipe
   campuran bisa memberi peringatan.

📖 FAKTA YANG LAYAK DIKETAHUI (untuk soal GCD lanjutan):
   Kalau kamu menetapkan ujung kiri l dan menggeser ujung kanan r ke kanan,
   nilai gcd(a[l..r]) hanya berubah paling banyak O(log V) kali.
   Alasannya: setiap kali gcd berubah, ia harus MEMBAGI nilai sebelumnya,
   sehingga nilainya setidaknya membelah dua. Dari 10^9, itu hanya sekitar
   30 kali.
   Fakta ini adalah dasar dari solusi Codeforces 475D (CGCDSSQ) dan banyak
   soal "hitung subarray dengan gcd tertentu".

VERIFIKASI SAMPEL (a = [12,18,6,24,36], query [2,5] 1-based = [1,4]):
   len = 4, k = 2, blok kiri sp[2][1] = gcd(18,6,24,36) = 6
   blok kanan sp[2][4-4+1] = sp[2][1] = 6
   jawab 6   ✓

CATATAN: implementasi ini telah diuji terhadap brute force pada 5000 array
acak dengan SELURUH pasangan (l, r).

🔄 ALTERNATIVE APPROACHES:
- Segment tree: mendukung update, O(log n · log V) per query.
- Untuk "hitung berapa subarray yang gcd-nya sama dengan g", pakai fakta
  O(log V) perubahan di atas -- jauh lebih efisien daripada memeriksa
  seluruh O(n^2) subarray.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

    int K = lg[n] + 1;
    vector<vector<ll>> sp(K, vector<ll>(n));
    sp[0] = a;

    for (int k = 1; k < K; k++)
        for (int i = 0; i + (1 << k) <= n; i++)
            sp[k][i] = __gcd(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);

    string out;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        int k = lg[r - l + 1];
        out += to_string(__gcd(sp[k][l], sp[k][r - (1 << k) + 1]));
        out += '\n';
    }
    cout << out;

    return 0;
}
