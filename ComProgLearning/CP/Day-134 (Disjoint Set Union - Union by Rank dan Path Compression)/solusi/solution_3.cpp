/*
============================================================
✅ Solution 3: Total Kekayaan Kelompok
============================================================
Approach: DSU dengan agregat disimpan di perwakilan
Complexity: Time O((N + Q) α(N)) | Space O(N)
Key Insight: Agregat apa pun (jumlah, maksimum, minimum, hitungan) bisa
             dilekatkan pada DSU dengan menyimpannya HANYA di perwakilan
             komponen. Saat dua komponen bergabung, agregat keduanya
             digabungkan ke perwakilan yang baru.

📖 POLA UMUMNYA:
       bool unite(a, b) {
           a = find(a); b = find(b);
           if (a == b) return false;
           if (sz[a] < sz[b]) swap(a, b);
           par[b] = a;
           sz[a] += sz[b];
           agregat[a] = gabung(agregat[a], agregat[b]);   <- satu baris tambahan
           return true;
       }
   Fungsi `gabung` bisa apa saja yang ASOSIATIF: +, max, min, gcd, XOR.
   Pola ini bekerja untuk semuanya tanpa perubahan lain.

⚠️ AGREGAT HANYA VALID DI PERWAKILAN -- INI BUG NOMOR SATU DI TOPIK INI.
   Setelah beberapa penggabungan, `jumlah[x]` untuk x yang BUKAN perwakilan
   memuat nilai LAMA yang sudah usang. Membacanya langsung memberi jawaban
   yang salah, dan salahnya tidak konsisten sehingga sulit dilacak.
   SELALU baca lewat jumlah[find(x)].

   Contoh konkret dari sampel: setelah unite(1,2), misalkan perwakilannya
   menjadi 1. Maka jumlah[1] = 30, tetapi jumlah[2] MASIH 20 -- nilai lama.
   Query "2 2" harus membaca jumlah[find(2)] = jumlah[1] = 30, bukan
   jumlah[2] = 20.

⚠️ OVERFLOW: 2*10^5 orang dengan kekayaan 10^9 memberi total 2*10^14.
   int jebol pada 2.1*10^9. long long wajib untuk array agregatnya.
   Perhatikan bahwa `sz` tetap boleh int -- ia paling besar N.

⚠️ INISIALISASI AGREGAT: setiap orang mula-mula sendirian, jadi
   jumlah[i] = w[i], bukan 0. Melupakan ini membuat seluruh jawaban nol.

VERIFIKASI SAMPEL (w = [10, 20, 30, 40]):
   "2 1"     : kelompok {1}, total 10          ✓
   "1 1 2"   : gabung, agregat menjadi 30
   "2 2"     : find(2) menunjuk ke perwakilan gabungan, total 30   ✓
   "1 3 4"   : gabung, agregat menjadi 70
   "2 3"     : total 70                        ✓

🔄 ALTERNATIVE APPROACHES:
- Menyimpan daftar anggota per komponen lalu menjumlahkan saat query:
  O(ukuran) per query -- terlalu lambat.
- Small-to-large merging dengan daftar anggota: berguna kalau kamu butuh
  MENELUSURI anggotanya (bukan hanya agregat), O(N log N) total.
- Untuk agregat sederhana, pola di atas jauh lebih baik.
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

    vector<int> par(n + 1), sz(n + 1, 1);
    vector<ll> jumlah(n + 1, 0);                   // long long: bisa 2*10^14
    iota(par.begin(), par.end(), 0);
    for (int i = 1; i <= n; i++) cin >> jumlah[i]; // inisialisasi = nilai sendiri

    function<int(int)> find = [&](int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    };

    string out;
    while (q--) {
        int jenis;
        cin >> jenis;
        if (jenis == 1) {
            int a, b;
            cin >> a >> b;
            a = find(a); b = find(b);
            if (a == b) continue;
            if (sz[a] < sz[b]) swap(a, b);
            par[b] = a;
            sz[a] += sz[b];
            jumlah[a] += jumlah[b];                // gabungkan ke perwakilan BARU
        } else {
            int a;
            cin >> a;
            out += to_string(jumlah[find(a)]);     // find DULU, jangan jumlah[a]
            out += '\n';
        }
    }
    cout << out;

    return 0;
}
