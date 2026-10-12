/*
============================================================
✅ SOLUSI Exercise 2: Mencari Contoh Tandingan Terkecil
============================================================
Difficulty: Easy | Kompleksitas: O(langkah * n * (2^n + n*W))
                   dengan n <= 8 dan W <= 30, sangat ringan

── INI PERKAKAS, BUKAN ALGORITMA ───────────────────────────
Tujuan soal ini adalah membangun alat yang akan kamu pakai
berkali-kali. Setelah stress test menemukan kegagalan, contoh
pertamanya biasanya besar dan sulit dipahami. Kecilkan dulu
sebelum menganalisisnya.

── ALGORITMA PENGECILAN SERAKAH ────────────────────────────
    selama masih ada perubahan:
        untuk tiap barang:
            coba BUANG barang itu
            kalau greedy MASIH salah, terima dan ulangi
        untuk tiap barang, untuk tiap nilai yang lebih kecil:
            coba KECILKAN berat atau nilainya
            kalau greedy MASIH salah, terima dan ulangi

Setiap langkah yang diterima memperkecil masukan secara ketat,
sehingga prosesnya pasti berhenti.

Perhatikan bahwa ini greedy juga — dan seperti greedy pada
umumnya, ia tidak menjamin contoh tandingan TERKECIL secara
global. Ia hanya menjamin contoh yang MINIMAL, yaitu tidak bisa
dikecilkan lagi dengan satu langkah. Untuk keperluan praktis
itu sudah lebih dari cukup.

── KENAPA CONTOH KECIL BEGITU BERHARGA ─────────────────────
1. Bisa DIPAHAMI. Kamu bisa melihat dengan mata telanjang
   kenapa greedy gagal, dan itu berubah menjadi intuisi.
2. Mudah DIINGAT. Menjadi perkakas untuk soal berikutnya.
3. Mudah dipakai MENGUJI ide perbaikanmu.

Semua contoh tandingan klasik berukuran 3 sampai 5 elemen. Itu
bukan kebetulan — pengecilan otomatislah yang membuatnya
begitu.

── JEBAKAN HALUS: JANGAN MENGURUTKAN KELUARAN ──────────────
Naluri dari Day 76 mengatakan "urutkan keluaran agar
deterministik". DI SINI ITU JUSTRU MERUSAK JAWABANNYA.

Alasannya: greedy memakai tie-break INDEKS ketika rasio seri.
Artinya hasil greedy bergantung pada URUTAN masukan. Contoh
tandingan yang ditemukan bisa berhenti menjadi contoh tandingan
setelah diurutkan.

Contoh nyata yang saya temui saat menulis solusi ini:
    barang (6,6) (5,5) (5,2), W = 10  -> greedy 6, optimal 7  ✓ contoh tandingan
    setelah diurutkan menjadi
    barang (5,2) (5,5) (6,6), W = 10  -> greedy 7, optimal 7  ✗ bukan lagi

Pelajarannya: kalau algoritma yang diuji SENSITIF terhadap
urutan masukan, maka urutan adalah bagian dari contoh
tandingan itu sendiri. Determinisme diperoleh dari prosedur
pengecilan yang tetap, bukan dari mengurutkan hasilnya.

── JEBAKAN ─────────────────────────────────────────────────
1. Berhenti setelah satu putaran. Pengecilan sering membuka
   peluang pengecilan berikutnya, jadi ulangi sampai mentok.
2. Membiarkan array menjadi kosong. Jaga minimal satu barang.
3. Mengubah kapasitas W. Soal ini melarangnya, dan pada
   praktiknya mengubah terlalu banyak hal sekaligus membuat
   contoh tandingan sulit ditafsirkan.
4. Lupa bahwa berat dan nilai harus tetap bilangan bulat
   POSITIF.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll W;

// greedy rasio nilai per berat tertinggi
// TIE-BREAK INDEKS itu WAJIB (Day 76): tanpa itu, rasio yang seri
// membuat urutan bergantung implementasi std::sort, dan seluruh
// eksperimen ini menjadi tidak bisa direproduksi.
ll greedyRasio(const vector<pair<ll, ll>>& b) {
    vector<int> ord(b.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        __int128 kiri  = (__int128)b[x].second * b[y].first;
        __int128 kanan = (__int128)b[y].second * b[x].first;
        if (kiri != kanan) return kiri > kanan;
        return x < y;                            // tie-break: indeks asli
    });
    ll sisa = W, tot = 0;
    for (int i : ord) if (b[i].first <= sisa) { tot += b[i].second; sisa -= b[i].first; }
    return tot;
}

// jawaban optimal: knapsack 0/1
ll optimal(const vector<pair<ll, ll>>& b) {
    vector<ll> dp(W + 1, 0);
    for (auto& [w, v] : b)
        for (ll c = W; c >= w; c--) dp[c] = max(dp[c], dp[c - w] + v);
    return dp[W];
}

bool masihSalah(const vector<pair<ll, ll>>& b) {
    return !b.empty() && greedyRasio(b) != optimal(b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n >> W)) return 0;
    vector<pair<ll, ll>> b(n);
    for (auto& [w, v] : b) cin >> w >> v;

    bool berubah = true;
    while (berubah) {
        berubah = false;

        // (a) coba BUANG satu barang
        for (size_t i = 0; i < b.size() && !berubah; i++) {
            vector<pair<ll, ll>> kecil = b;
            kecil.erase(kecil.begin() + i);
            if (masihSalah(kecil)) { b = kecil; berubah = true; }
        }
        if (berubah) continue;

        // (b) coba KECILKAN berat atau nilai
        for (size_t i = 0; i < b.size() && !berubah; i++) {
            for (ll x = 1; x < b[i].first && !berubah; x++) {
                vector<pair<ll, ll>> kecil = b;
                kecil[i].first = x;
                if (masihSalah(kecil)) { b = kecil; berubah = true; }
            }
            for (ll x = 1; x < b[i].second && !berubah; x++) {
                vector<pair<ll, ll>> kecil = b;
                kecil[i].second = x;
                if (masihSalah(kecil)) { b = kecil; berubah = true; }
            }
        }
    }

    // JANGAN diurutkan: urutan adalah bagian dari contoh tandingan
    cout << b.size() << '\n';
    for (auto& [w, v] : b) cout << w << ' ' << v << '\n';
    return 0;
}
