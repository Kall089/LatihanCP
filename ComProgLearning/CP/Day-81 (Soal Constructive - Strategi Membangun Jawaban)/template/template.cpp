/*
============================================================
  Day 81 — Soal Constructive | Template
============================================================
  SOAL CONSTRUCTIVE = "bangun SEBUAH objek yang memenuhi
  syarat", bukan "hitung nilai optimal".

  BEDANYA DENGAN AD-HOC (Day 80):
     ad-hoc       : cari ANGKA
     constructive : cari OBJEK, dan biasanya banyak jawaban
                    benar sekaligus

  LIMA STRATEGI UTAMA
    1. mulai dari kasus kecil, cari POLA, perumum
    2. bangun secara REKURSIF (n dari n-1, atau n dari n/2)
    3. cari KONSTRUKSI BAKU yang jelas benar, lalu perbaiki
    4. buktikan MUSTAHIL lebih dulu (paritas/invarian)
    5. bangun secara GREEDY, lalu tambal pelanggaran

  ATURAN EMAS
    Selalu tulis PEMERIKSA (checker) terpisah. Soal
    constructive punya banyak jawaban benar, sehingga
    membandingkan dengan jawaban contoh TIDAK BISA dipakai.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. PEMERIKSA: alat terpenting hari ini ───────────────
// Soal constructive tidak bisa diuji dengan membandingkan
// keluaran. Kamu HARUS menulis pemeriksa yang memvalidasi
// syarat-syaratnya secara langsung.

// Contoh: permutasi 1..n dengan |p[i] - i| tidak pernah 0.
bool periksaDerangement(const vector<int>& p, int n) {
    if ((int)p.size() != n) return false;
    vector<bool> ada(n + 1, false);
    for (int i = 0; i < n; i++) {
        if (p[i] < 1 || p[i] > n) return false;   // di luar rentang
        if (ada[p[i]]) return false;              // duplikat
        ada[p[i]] = true;
        if (p[i] == i + 1) return false;          // titik tetap
    }
    return true;
}

// ─── 2. STRATEGI 1: POLA DARI KASUS KECIL ─────────────────
// Derangement paling sederhana: geser semua satu langkah.
// n = 1 -> MUSTAHIL (kasus tepi yang wajib diperiksa)

vector<int> derangementGeser(int n) {
    if (n == 1) return {};                        // mustahil
    vector<int> p(n);
    for (int i = 0; i < n; i++) p[i] = (i + 1) % n + 1;
    return p;
}

// ─── 3. STRATEGI 2: BANGUN REKURSIF ───────────────────────
// Contoh: susun 1..n sehingga selisih tetangga tidak pernah 1.
// Ide: taruh semua GANJIL dulu, lalu semua GENAP.
// Titik sambungnya butuh perhatian: ganjil terakhir dan genap
// pertama harus berselisih lebih dari 1.

// PENTING: urutannya GENAP dulu, baru GANJIL.
// Versi "ganjil dulu" gagal untuk n = 4: menghasilkan 1 3 2 4,
// dan |3 - 2| = 1. Titik SAMBUNG antara dua blok itulah yang
// menentukan benar atau salah, dan hanya terlihat kalau kamu
// menguji SELURUH n kecil, bukan beberapa saja.
// Dengan genap dulu: blok berakhir di bilangan genap terbesar
// dan disambung ke 1, sehingga selisihnya minimal 3 untuk n >= 4.
vector<int> tanpaTetanggaBerurutan(int n) {
    if (n == 1) return {1};
    if (n == 2 || n == 3) return {};              // mustahil
    vector<int> p;
    for (int i = 2; i <= n; i += 2) p.push_back(i);   // 2 4 6 ...
    for (int i = 1; i <= n; i += 2) p.push_back(i);   // 1 3 5 ...
    return p;
}

bool periksaTanpaTetangga(const vector<int>& p, int n) {
    if ((int)p.size() != n) return false;
    vector<bool> ada(n + 1, false);
    for (int x : p) {
        if (x < 1 || x > n || ada[x]) return false;
        ada[x] = true;
    }
    for (int i = 1; i < n; i++) if (abs(p[i] - p[i-1]) == 1) return false;
    return true;
}

// ─── 4. STRATEGI 4: BUKTIKAN MUSTAHIL LEBIH DULU ──────────
// Sebelum mencari konstruksi, periksa paritas/invarian.
// Sering separuh kasus uji langsung terjawab "tidak mungkin",
// dan itu jauh lebih murah daripada mencari konstruksi.

// Contoh: bagi 1..n menjadi dua kelompok berjumlah SAMA.
// Total = n(n+1)/2. Mustahil kalau total ganjil.
bool bisaDibagiDua(ll n) { return (n * (n + 1) / 2) % 2 == 0; }

// ─── 5. STRATEGI 5: GREEDY LALU TAMBAL ────────────────────
// Bangun jawaban seenaknya, lalu perbaiki pelanggaran satu
// per satu. Cocok kalau setiap perbaikan tidak merusak yang
// sudah benar.

// Contoh: permutasi dengan tepat k posisi p[i] != i.
// k = 1 MUSTAHIL (tidak bisa memindahkan tepat satu elemen).
vector<int> tepatKBergeser(int n, int k) {
    if (k == 1 || k > n) return {};
    vector<int> p(n);
    for (int i = 0; i < n; i++) p[i] = i + 1;     // identitas
    // balik blok pertama sepanjang k: semuanya bergeser
    for (int i = 0; i < k / 2; i++) swap(p[i], p[k - 1 - i]);
    if (k % 2 == 1) {                              // k ganjil: geser tiga
        swap(p[k / 2], p[k - 1]);
    }
    return p;
}

// ─── 6. JEBAKAN ───────────────────────────────────────────
//
//  a) Lupa kasus n = 1, n = 2, n = 3. Konstruksi yang bagus
//     untuk n besar hampir selalu gagal di situ.
//
//  b) Tidak memeriksa kemustahilan lebih dulu.
//
//  c) Membandingkan keluaran dengan jawaban contoh. Soal
//     constructive punya banyak jawaban benar — WAJIB pakai
//     pemeriksa.
//
//  d) Konstruksi yang "terlihat benar" tanpa diuji. Jalankan
//     pemeriksa pada SELURUH n dari 1 sampai 200.
//
//  e) Lupa mencetak "IMPOSSIBLE" atau -1 sesuai format soal.

// ─── MAIN: uji seluruh konstruksi ─────────────────────────

int main() {
    FASTIO;

    // Uji derangement untuk SELURUH n kecil, bukan beberapa saja.
    int gagal = 0;
    for (int n = 2; n <= 300; n++)
        if (!periksaDerangement(derangementGeser(n), n)) gagal++;
    cout << "derangement geser  : n = 2..300, gagal " << gagal << '\n';
    cout << "  n = 1 -> " << (derangementGeser(1).empty() ? "MUSTAHIL (benar)" : "SALAH") << '\n';

    gagal = 0;
    for (int n = 4; n <= 300; n++)
        if (!periksaTanpaTetangga(tanpaTetanggaBerurutan(n), n)) gagal++;
    cout << "tanpa tetangga     : n = 4..300, gagal " << gagal << '\n';
    cout << "  n = 1 -> " << (periksaTanpaTetangga(tanpaTetanggaBerurutan(1), 1) ? "OK" : "gagal")
         << ", n = 2,3 -> " << (tanpaTetanggaBerurutan(2).empty() && tanpaTetanggaBerurutan(3).empty()
                                ? "MUSTAHIL (benar)" : "SALAH") << '\n';

    // Uji "tepat k bergeser"
    gagal = 0;
    for (int n = 1; n <= 60; n++)
        for (int k = 0; k <= n; k++) {
            auto p = tepatKBergeser(n, k);
            if (k == 1) { if (!p.empty()) gagal++; continue; }
            if (p.empty()) { gagal++; continue; }
            int c = 0;
            for (int i = 0; i < n; i++) if (p[i] != i + 1) c++;
            vector<bool> ada(n + 1, false);
            bool sah = true;
            for (int x : p) { if (x < 1 || x > n || ada[x]) { sah = false; break; } ada[x] = true; }
            if (!sah || c != k) gagal++;
        }
    cout << "tepat k bergeser   : n = 1..60, gagal " << gagal << '\n';

    cout << "bisa dibagi dua    : n = 3 -> " << bisaDibagiDua(3)
         << ", n = 4 -> " << bisaDibagiDua(4)
         << ", n = 5 -> " << bisaDibagiDua(5) << '\n';

    return 0;
}
