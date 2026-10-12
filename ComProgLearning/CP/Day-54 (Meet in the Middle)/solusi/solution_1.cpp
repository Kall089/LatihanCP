/*
============================================================
✅ Solution 1: Bangkitkan Semua Jumlah Subset
============================================================
Approach: Bitmask + pembangunan inkremental
Complexity: Time O(2^N) untuk membangkitkan, O(2^N · N) untuk sort | Space O(2^N)
Key Insight: Setiap subhimpunan dari N benda berkorespondensi tepat satu-satu
             dengan bilangan biner sepanjang N bit. Dan jumlah untuk sebuah
             mask bisa dibangun dari mask yang SATU BIT lebih kecil -- yang
             pasti sudah dihitung karena nilainya lebih kecil.

📖 TRIK INKREMENTAL:
       int b = __builtin_ctz(mask);            // bit terendah yang menyala
       hasil[mask] = hasil[mask ^ (1 << b)] + a[b];

   mask ^ (1 << b) mematikan bit terendah, menghasilkan bilangan yang lebih
   KECIL -- sehingga nilainya sudah dihitung pada iterasi sebelumnya.
   Ini O(1) per subset, total O(2^N).

   Versi naif dua loop bersarang juga benar tetapi O(2^N * N):
       for (mask) for (b) if (mask >> b & 1) hasil[mask] += a[b];
   Untuk N = 20 itu 2*10^7 vs 10^6 -- selisih 20 kali lipat. Untuk soal ini
   keduanya lolos, tetapi kebiasaan memakai versi cepat berguna saat MITM
   dipakai pada batas yang lebih ketat.

⚠️ __builtin_ctz ADALAH INSTRUKSI CPU TUNGGAL (count trailing zeros).
   Ia tidak terdefinisi untuk argumen nol, itulah sebabnya loop dimulai dari
   mask = 1, bukan 0. hasil[0] sudah bernilai 0 dari inisialisasi.

⚠️ NILAI NEGATIF: sampel 2 sengaja memuatnya. Jumlah subset kosong adalah 0,
   tetapi itu BUKAN nilai terkecil kalau ada elemen negatif. Jangan
   berasumsi apa pun tentang urutan sebelum mengurutkan.

⚠️ OVERFLOW: N = 20 dengan nilai 10^9 memberi jumlah maksimal 2*10^10 --
   melebihi int. long long wajib.

⚠️ UKURAN KELUARAN: 2^20 = 1.048.576 bilangan. Mencetaknya satu per satu
   dengan cout bisa lambat; bangun satu string lalu cetak sekali.

🔄 ALTERNATIVE APPROACHES:
- Rekursi (untuk setiap elemen: ambil atau tidak): setara, dan kadang lebih
  mudah dibaca. Tetapi bitmask lebih cepat karena tidak ada overhead
  pemanggilan fungsi.
- Kalau kamu hanya butuh jumlah-jumlah yang BERBEDA, pakai set atau
  urutkan lalu unique (Day 38).
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
    for (ll& v : a) cin >> v;

    int total = 1 << n;
    vector<ll> hasil(total, 0);

    for (int mask = 1; mask < total; mask++) {       // mulai dari 1, bukan 0
        int b = __builtin_ctz(mask);                 // bit terendah yang menyala
        hasil[mask] = hasil[mask ^ (1 << b)] + a[b]; // bangun dari yang lebih kecil
    }

    sort(hasil.begin(), hasil.end());

    string out;
    out.reserve(total * 8);
    for (int i = 0; i < total; i++) {
        out += to_string(hasil[i]);
        out += (i + 1 == total) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
