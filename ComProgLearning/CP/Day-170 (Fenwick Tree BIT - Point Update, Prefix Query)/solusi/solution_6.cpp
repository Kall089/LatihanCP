/*
============================================================
✅ Solution 6: Nilai Terkecil ke-K yang Dinamis
============================================================
Approach: BIT hitungan + DESCENT di dalam struktur
Complexity: Time O(Q log Q) | Space O(Q)
Key Insight: BIT yang menyimpan HITUNGAN per nilai menjadi multiset dinamis:
             sisip, hapus, dan "berapa yang <= x" semuanya O(log n).
             Untuk "terkecil ke-k", pendekatan naif adalah binary search di
             LUAR struktur (O(log^2 n)); tetapi kita bisa MENURUNI struktur
             BIT secara langsung dan mendapat O(log n).

📖 KENAPA DESCENT BEKERJA:
   Ingat bahwa t[i] menanggung blok sepanjang lowbit(i) yang berakhir di i.
   Mulai dari pos = 0 dan pangkat dua TERBESAR yang <= n, lalu turunkan:
       kalau t[pos + pw] < k, artinya seluruh blok itu belum mencukupi k
       -> lompati blok itu: pos += pw, k -= t[pos]
       kalau tidak, jangan lompat (jawabannya ada di dalam blok itu)
   Setelah seluruh pangkat dua dicoba, pos + 1 adalah indeks terkecil dengan
   query(pos + 1) >= k.

   Ini bekerja karena blok-blok BIT tersusun seperti pohon biner implisit:
   melompati blok sepanjang pw sama dengan turun ke anak kanan pada pohon
   segmen. Kita tidak pernah memanggil query() sama sekali -- hanya membaca
   t[] secara langsung, satu kali per level.

📖 PERBANDINGAN DUA PENDEKATAN:
   Binary search di luar : for setiap tebakan, panggil query -> O(log^2 n)
   Descent               : satu kali jalan menuruni level  -> O(log n)
   Untuk Q = 2*10^5, selisihnya sekitar 18 kali lipat operasi. Keduanya
   lolos di sini, tetapi descent adalah teknik yang layak dikuasai karena
   pola yang sama dipakai pada segment tree (Day 175).

⚠️ OFFLINE WAJIB, sama seperti Exercise 5: seluruh nilai x harus sudah
   diketahui sebelum kamu membangun kamus kompresi. Baca seluruh operasi
   dulu.

⚠️ __builtin_clz(0) TAK TERDEFINISI. Kalau n bisa nol, tangani terpisah.
   Di sini n >= 1 karena setidaknya ada satu operasi.

⚠️ PENGHAPUSAN "- x" MENGURANGI HITUNGAN, bukan menghapus posisi.
   Karena nilai boleh kembar, BIT menyimpan berapa BANYAK salinan setiap
   nilai. update(idx(x), -1) mengurangi satu salinan.

⚠️ MENGEMBALIKAN NILAI ASLI: descent memberi INDEKS terkompresi. Untuk
   mencetak nilainya, petakan kembali lewat kamus: semua[pos - 1].
   Melupakan pemetaan balik ini adalah kesalahan yang mudah terjadi.

VERIFIKASI SAMPEL:
   + 5, + 2, + 8  -> himpunan {2, 5, 8}
   ? 2            -> terkecil kedua = 5   ✓
   - 2            -> himpunan {5, 8}
   ? 2            -> terkecil kedua = 8   ✓

🔄 ALTERNATIVE APPROACHES:
- multiset + advance(iterator, k): O(k) per query karena iterator multiset
  bukan random-access. Untuk k besar ini terlalu lambat.
- policy-based ordered set dengan find_by_order: O(log n), paling pendek,
  tetapi sulit menangani duplikat (butuh trik pasangan nilai-indeks).
- Segment tree dengan descent: setara, tetapi lebih panjang.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> t;

void update(int i, int d) { for (; i <= n; i += i & -i) t[i] += d; }

// Indeks terkecil pos dengan prefix(pos) >= k, dengan MENURUNI struktur BIT.
int descent(int k) {
    int pos = 0;
    for (int pw = 1 << (31 - __builtin_clz(n)); pw > 0; pw >>= 1)
        if (pos + pw <= n && t[pos + pw] < k) {
            pos += pw;
            k -= t[pos];                          // lompati blok ini
        }
    return pos + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    vector<char> jenis(q);
    vector<ll> arg(q);
    vector<ll> semua;

    for (int i = 0; i < q; i++) {                 // OFFLINE: baca semua dulu
        cin >> jenis[i] >> arg[i];
        if (jenis[i] != '?') semua.push_back(arg[i]);
    }

    sort(semua.begin(), semua.end());
    semua.erase(unique(semua.begin(), semua.end()), semua.end());
    n = max((int)semua.size(), 1);
    t.assign(n + 2, 0);

    auto idx = [&](ll x) {
        return int(lower_bound(semua.begin(), semua.end(), x) - semua.begin()) + 1;
    };

    string out;
    for (int i = 0; i < q; i++) {
        if (jenis[i] == '+')      update(idx(arg[i]), +1);
        else if (jenis[i] == '-') update(idx(arg[i]), -1);
        else {
            int pos = descent((int)arg[i]);
            out += to_string(semua[pos - 1]);     // indeks -> NILAI ASLI
            out += '\n';
        }
    }
    cout << out;

    return 0;
}
