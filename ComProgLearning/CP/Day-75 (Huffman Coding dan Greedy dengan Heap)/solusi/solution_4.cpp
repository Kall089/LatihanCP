/*
============================================================
✅ SOLUSI Exercise 4: Menghubungkan Kabel Bertingkat
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── PERLUASAN NAIF DAN KENAPA KURANG ────────────────────────
Ambil K terkecil, gabungkan, ulangi. Itu benar sebagai
kerangka, tetapi ada satu masalah: penggabungan yang TIDAK
PENUH (kurang dari K berkas tersisa).

Penggabungan tidak penuh itu boros. Pertanyaannya: sebaiknya
terjadi di AWAL atau di AKHIR?

── JAWABANNYA: DI AWAL ─────────────────────────────────────
Ingat identitas Huffman: biaya total sama dengan
sum(ukuran[i] * kedalaman[i]). Penggabungan yang terjadi lebih
AWAL berada lebih DALAM di pohon, sehingga anggotanya terhitung
lebih banyak kali.

Kalau langkah tidak penuh terjadi di awal, yang "kurang" berada
di kedalaman maksimum — dan tempat itu seharusnya diisi oleh
nilai TERKECIL. Menaruh kekurangan di situ tidak merugikan.

Kalau langkah tidak penuh terjadi di akhir, kekurangan berada
dekat akar, memaksa nilai-nilai besar turun lebih dalam. Itu
lebih mahal.

── CARA MEMAKSANYA: SIMPUL DUMMY ───────────────────────────
Tambahkan beberapa berkas berukuran NOL. Karena min-heap selalu
mengambil yang terkecil, dummy pasti terambil pada penggabungan
PERTAMA — persis tempat yang kita inginkan. Dan karena
ukurannya nol, dummy tidak menambah biaya sama sekali.

── BERAPA BANYAK DUMMY ─────────────────────────────────────
Setiap penggabungan mengubah K berkas menjadi 1, jadi mengurangi
jumlah berkas sebanyak (K - 1). Agar berakhir tepat di 1 berkas
dengan semua penggabungan PENUH, kita butuh

    (n - 1) mod (K - 1) == 0

Tambahkan dummy satu per satu sampai syarat itu terpenuhi.
Paling banyak K-2 dummy dibutuhkan.

── MEMERIKSA DENGAN K = 2 ──────────────────────────────────
Dengan K = 2, syaratnya (n-1) mod 1 == 0, selalu benar, jadi
tidak ada dummy dan kodenya kembali menjadi Huffman biasa.
Sampel 2 memakai K = 2 dan harus memberikan hasil yang sama
persis dengan Exercise 1. Pakai itu sebagai pemeriksaan.

── JEBAKAN ─────────────────────────────────────────────────
1. Lupa dummy. Sampel 1 (n=5, K=3) tanpa dummy memberi jawaban
   yang lebih besar dari 21.
2. Menambahkan dummy di akhir alih-alih membiarkan heap
   mengambilnya lebih dulu. Dengan min-heap dan nilai nol,
   urutannya terjaga otomatis.
3. n = 1: tidak ada penggabungan, jawabannya 0. Periksa ini
   SEBELUM menambahkan dummy.
4. K = 1 tidak masuk akal (jumlah berkas tak pernah berkurang).
   Batasan soal menjamin K >= 2, tetapi kode defensif tetap
   baik.
5. Lupa long long.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    if (!(cin >> n >> K)) return 0;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    if (n <= 1) { cout << 0 << '\n'; return 0; }

    // tambahkan dummy agar seluruh penggabungan penuh
    int m = n;
    while ((m - 1) % (K - 1) != 0) { a.push_back(0); m++; }

    priority_queue<ll, vector<ll>, greater<ll>> pq(a.begin(), a.end());

    ll total = 0;
    while (pq.size() > 1) {
        ll s = 0;
        for (int i = 0; i < K; i++) { s += pq.top(); pq.pop(); }
        total += s;
        pq.push(s);
    }

    cout << total << '\n';
    return 0;
}
