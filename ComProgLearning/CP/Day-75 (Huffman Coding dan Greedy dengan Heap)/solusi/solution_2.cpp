/*
============================================================
✅ SOLUSI Exercise 2: Panjang Kode Huffman
============================================================
Difficulty: Easy | Kompleksitas: O(n log n) waktu, O(n) memori

── KAPAN POHON DIBUTUHKAN ──────────────────────────────────
Ada identitas yang menghemat banyak pekerjaan:

    sum( f[i] * kedalaman[i] )  =  sum( setiap nilai gabungan )

Kenapa sama: daun berkedalaman d ikut terhitung dalam d
penggabungan berbeda, karena setiap kali subpohon yang memuatnya
naik satu tingkat, frekuensinya ikut dijumlahkan lagi.

Akibatnya: kalau soal hanya minta TOTAL, kamu tidak perlu pohon
(itulah Exercise 1). Kamu baru butuh pohon eksplisit kalau soal
minta PANJANG KODE per simbol.

── UKURAN POHON ────────────────────────────────────────────
Pohon biner PENUH dengan n daun punya tepat n-1 simpul internal,
jadi 2n-1 simpul seluruhnya. Alokasikan sekaligus, jangan
tumbuh dinamis.

── HEAP BERISI PASANGAN ────────────────────────────────────
Berbeda dari Exercise 1, heap di sini menyimpan
(nilai, indeks simpul) karena kita perlu tahu simpul mana yang
digabungkan agar bisa memasang anak kiri dan kanan.

── TELUSURI SECARA ITERATIF ────────────────────────────────
Pohon Huffman bisa sangat miring. Frekuensi Fibonacci
(1, 1, 2, 3, 5, 8, ...) menghasilkan kedalaman linier terhadap
n. Dengan n = 2*10^5, rekursi akan kehabisan stack.
Karena itu penelusuran di bawah memakai stack eksplisit.

(Catatan menarik: untuk mencapai kedalaman d dibutuhkan total
frekuensi minimal Fib(d+2). Karena Fib(87) sudah melebihi 10^18,
kedalaman tidak pernah melebihi sekitar 87 pada batasan
long long. Tetapi menulis kode iteratif tetap kebiasaan yang
lebih baik.)

── KASUS n = 1 ─────────────────────────────────────────────
Tidak ada penggabungan sama sekali. Total biayanya 0, TETAPI
panjang kodenya 1 — kamu tetap butuh satu bit untuk mengirim
simbol itu. Perbedaan halus ini sering salah; baca contoh
masukan soal untuk memastikan definisinya.

── VERIFIKASI DIRI ─────────────────────────────────────────
Setelah menghitung panjang, periksa bahwa
sum(f[i] * panjang[i]) sama dengan jawaban Exercise 1 pada data
yang sama. Pemeriksaan ini murah dan menangkap hampir semua bug
indeks.

── JEBAKAN ─────────────────────────────────────────────────
1. Alokasi 2n-1, bukan n.
2. Rekursi pada penelusuran.
3. Lupa kasus n = 1.
4. Menyangka kode Huffman unik. Menukar anak kiri/kanan tidak
   mengubah biaya, jadi ada banyak pohon optimal. Panjangnya
   pun bisa tidak unik ketika ada frekuensi yang seri.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> f(n);
    for (ll& x : f) cin >> x;

    if (n == 1) { cout << 1 << '\n'; return 0; }   // tetap butuh satu bit

    // pohon biner penuh dengan n daun: 2n-1 simpul
    vector<int> kiri(2 * n - 1, -1), kanan(2 * n - 1, -1);

    priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                   greater<pair<ll, int>>> pq;     // MIN-heap
    for (int i = 0; i < n; i++) pq.push({f[i], i});

    int next = n;
    while (pq.size() > 1) {
        auto [fx, x] = pq.top(); pq.pop();
        auto [fy, y] = pq.top(); pq.pop();
        kiri[next] = x; kanan[next] = y;
        pq.push({fx + fy, next});
        next++;
    }

    // telusuri ITERATIF dari akar
    vector<int> panjang(n, 0);
    vector<pair<int, int>> st{{next - 1, 0}};      // (simpul, kedalaman)
    while (!st.empty()) {
        auto [u, d] = st.back(); st.pop_back();
        if (kiri[u] == -1) { panjang[u] = d; continue; }   // daun
        st.push_back({kiri[u],  d + 1});
        st.push_back({kanan[u], d + 1});
    }

    for (int i = 0; i < n; i++) cout << panjang[i] << " \n"[i == n - 1];
    return 0;
}
