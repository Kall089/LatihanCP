/*
============================================================
  Day 75 — Huffman & Greedy dengan Heap | Template
============================================================
  KAPAN HEAP DIBUTUHKAN

  Greedy biasa  : urutan keputusan sudah TETAP sejak awal
                  -> cukup sort sekali
  Greedy + heap : himpunan kandidat BERUBAH karena keputusanmu
                  -> butuh struktur yang selalu memberi ekstrem

  Tanda pengenal terkuat: keputusanmu MENGHASILKAN kandidat baru.
  Huffman menggabungkan dua simpul dan memasukkan hasilnya
  kembali ke dalam himpunan. Sort sekali tidak bisa menangani itu.

  RUMUS HUFFMAN YANG SERING DILUPA
      biaya total = sum( freq[i] * kedalaman[i] )
                  = sum( setiap nilai gabungan yang pernah dibuat )
  Kedua bentuk itu SAMA. Bentuk kedua jauh lebih mudah dihitung.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. HUFFMAN: BIAYA TOTAL ──────────────────────────────
// Gabungkan terus dua nilai TERKECIL. Jumlahkan tiap hasil
// gabungan. Itulah total panjang kode berbobot.
//
// Kasus n = 1: tidak ada penggabungan, biayanya 0.
// (Beberapa soal mendefinisikannya sebagai freq[0]; baca soal.)

ll huffmanBiaya(vector<ll> a) {
    if (a.size() <= 1) return 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq(a.begin(), a.end());
    ll total = 0;
    while (pq.size() > 1) {
        ll x = pq.top(); pq.pop();
        ll y = pq.top(); pq.pop();
        total += x + y;                 // biaya gabungan ini
        pq.push(x + y);                 // hasilnya jadi kandidat baru
    }
    return total;
}

// ─── 2. HUFFMAN: PANJANG KODE TIAP SIMBOL ─────────────────
// Bangun pohonnya secara eksplisit lalu telusuri kedalaman.

vector<int> huffmanPanjang(const vector<ll>& freq) {
    int n = freq.size();
    if (n == 1) return {1};             // satu simbol tetap butuh 1 bit
    vector<ll> nilai(2 * n - 1);
    vector<int> kiri(2 * n - 1, -1), kanan(2 * n - 1, -1);
    for (int i = 0; i < n; i++) nilai[i] = freq[i];

    priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                   greater<pair<ll, int>>> pq;
    for (int i = 0; i < n; i++) pq.push({freq[i], i});

    int next = n;
    while (pq.size() > 1) {
        auto [fx, x] = pq.top(); pq.pop();
        auto [fy, y] = pq.top(); pq.pop();
        nilai[next] = fx + fy;
        kiri[next] = x; kanan[next] = y;
        pq.push({nilai[next], next});
        next++;
    }

    vector<int> panjang(n, 0);
    // telusuri iteratif agar aman dari stack overflow pada n besar
    vector<pair<int, int>> st{{next - 1, 0}};
    while (!st.empty()) {
        auto [u, d] = st.back(); st.pop_back();
        if (kiri[u] == -1) { panjang[u] = d; continue; }
        st.push_back({kiri[u], d + 1});
        st.push_back({kanan[u], d + 1});
    }
    return panjang;
}

// ─── 3. VARIAN: GABUNGKAN K SEKALIGUS (K-ary Huffman) ─────
// Tiap penggabungan menyatukan K nilai. Agar pohonnya penuh,
// jumlah daun harus memenuhi (n - 1) % (K - 1) == 0.
// Kalau tidak, tambahkan simpul dummy bernilai 0.

ll huffmanKAry(vector<ll> a, int K) {
    if (K < 2) return -1;
    int n = a.size();
    if (n <= 1) return 0;
    while ((n - 1) % (K - 1) != 0) { a.push_back(0); n++; }   // dummy

    priority_queue<ll, vector<ll>, greater<ll>> pq(a.begin(), a.end());
    ll total = 0;
    while (pq.size() > 1) {
        ll s = 0;
        for (int i = 0; i < K && !pq.empty(); i++) { s += pq.top(); pq.pop(); }
        total += s;
        pq.push(s);
    }
    return total;
}

// ─── 4. POLA HEAP LAIN: AMBIL TERBESAR BERULANG ───────────
// "Lakukan K operasi, tiap kali ambil elemen terbesar,
//  ubah, kembalikan." Klasik: max-heap.

ll operasiTerbesar(vector<ll> a, int K, function<ll(ll)> ubah) {
    priority_queue<ll> pq(a.begin(), a.end());
    ll skor = 0;
    for (int i = 0; i < K && !pq.empty(); i++) {
        ll x = pq.top(); pq.pop();
        skor += x;
        pq.push(ubah(x));
    }
    return skor;
}

// ─── 5. GABUNG K DAFTAR TERURUT ───────────────────────────
// Heap berisi (nilai, dari daftar mana, indeks ke berapa).

vector<ll> gabungKDaftar(const vector<vector<ll>>& d) {
    struct Item { ll v; int li, idx; };
    auto cmp = [](const Item& a, const Item& b) { return a.v > b.v; };
    priority_queue<Item, vector<Item>, decltype(cmp)> pq(cmp);
    for (size_t i = 0; i < d.size(); i++)
        if (!d[i].empty()) pq.push({d[i][0], (int)i, 0});

    vector<ll> res;
    while (!pq.empty()) {
        auto [v, li, idx] = pq.top(); pq.pop();
        res.push_back(v);
        if (idx + 1 < (int)d[li].size()) pq.push({d[li][idx + 1], li, idx + 1});
    }
    return res;
}

// ─── 6. BRUTE FORCE UNTUK STRESS TEST ─────────────────────
// Coba SEMUA cara menggabungkan; O(n!) jadi n <= 8 saja.

ll bruteGabung(vector<ll> a) {
    if (a.size() <= 1) return 0;
    ll best = LLONG_MAX;
    int n = a.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            vector<ll> b;
            for (int k = 0; k < n; k++) if (k != i && k != j) b.push_back(a[k]);
            b.push_back(a[i] + a[j]);
            best = min(best, a[i] + a[j] + bruteGabung(b));
        }
    return best;
}

// ─── 7. JEBAKAN ───────────────────────────────────────────
//
//  a) priority_queue DEFAULT di C++ adalah MAX-heap.
//     Untuk Huffman kamu butuh MIN-heap:
//        priority_queue<ll, vector<ll>, greater<ll>>
//     Salah arah = jawaban salah, bukan crash. Sulit dilacak.
//
//  b) Lupa long long. n = 2*10^5 dengan freq 10^9: total
//     mencapai sekitar 10^14 * log n. WAJIB long long.
//
//  c) Kasus n = 1. Tidak ada penggabungan. Baca soal untuk
//     tahu apakah jawabannya 0 atau freq[0].
//
//  d) Menyangka "urutkan lalu gabungkan berpasangan" cukup.
//     SALAH: hasil gabungan harus ikut bersaing kembali.
//     Contoh: {1, 1, 1, 1, 100}
//       sort-berpasangan: (1+1)+(1+1) lalu 2+2=4, lalu 4+100
//       Huffman benar   : 2, 3, 5, 105 -> total 115
//
//  e) Menyangka Huffman = "gabungkan dua terkecil" juga optimal
//     untuk MEMAKSIMALKAN. Untuk maksimum, gabungkan dua
//     TERBESAR (max-heap).

// ─── MAIN: demo + stress test ─────────────────────────────

int main() {
    FASTIO;

    vector<ll> f = {5, 9, 12, 13, 16, 45};
    cout << "huffman biaya : " << huffmanBiaya(f) << " (harusnya 224)\n";

    auto p = huffmanPanjang(f);
    cout << "panjang kode  :";
    for (int x : p) cout << ' ' << x;
    cout << '\n';
    ll cek = 0;
    for (size_t i = 0; i < f.size(); i++) cek += f[i] * p[i];
    cout << "sum f*panjang : " << cek << " (harus sama dengan biaya)\n";

    cout << "k-ary K=3     : " << huffmanKAry(f, 3) << '\n';

    mt19937 rng(75);
    bool ok = true;
    for (int t = 0; t < 400 && ok; t++) {
        int n = 1 + rng() % 7;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) a[i] = 1 + rng() % 20;
        if (huffmanBiaya(a) != bruteGabung(a)) ok = false;
    }
    cout << "stress vs brute : " << (ok ? "400 kasus OK" : "GAGAL") << '\n';

    return 0;
}
