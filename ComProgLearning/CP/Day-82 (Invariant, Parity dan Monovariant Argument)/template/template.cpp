/*
============================================================
  Day 82 — Invariant, Parity & Monovariant | Template
============================================================
  TIGA ALAT UNTUK SOAL "BISAKAH?" DAN "BERAPA LANGKAH?"

  INVARIAN   : besaran yang TIDAK BERUBAH setelah tiap operasi
               -> membuktikan sesuatu MUSTAHIL
  MONOVARIAN : besaran yang selalu NAIK (atau selalu turun)
               -> membuktikan proses PASTI BERHENTI, dan
                  memberi batas atas jumlah langkah
  PARITAS    : kasus khusus invarian, dan yang paling sering
               dipakai. Periksa ini SEBELUM apa pun.

  CARA MENEMUKAN INVARIAN
    1. tulis beberapa besaran yang wajar (jumlah, XOR, jumlah
       mod k, banyak elemen ganjil, jumlah berbobot posisi)
    2. jalankan operasi acak, cetak nilai besaran itu
    3. yang tidak pernah berubah adalah kandidat invarian
  Template ini menyediakan alat untuk langkah 2 dan 3.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. PENCARI INVARIAN OTOMATIS ─────────────────────────
// Jalankan operasi acak berkali-kali. Besaran yang nilainya
// tidak pernah berubah adalah kandidat invarian.

struct Kandidat { string nama; function<ll(const vector<ll>&)> f; };

template <typename Op>
void cariInvarian(vector<ll> awal, Op operasiAcak,
                  const vector<Kandidat>& kandidat, int langkah, mt19937& rng) {
    vector<ll> nilaiAwal;
    for (auto& k : kandidat) nilaiAwal.push_back(k.f(awal));

    vector<bool> tetap(kandidat.size(), true);
    vector<ll> a = awal;
    for (int t = 0; t < langkah; t++) {
        operasiAcak(a, rng);
        for (size_t i = 0; i < kandidat.size(); i++)
            if (kandidat[i].f(a) != nilaiAwal[i]) tetap[i] = false;
    }
    for (size_t i = 0; i < kandidat.size(); i++)
        cout << "    " << left << setw(28) << kandidat[i].nama
             << (tetap[i] ? "INVARIAN" : "berubah") << '\n';
}

// ─── 2. KUMPULAN KANDIDAT BESARAN YANG LAZIM ──────────────
vector<Kandidat> kandidatBaku() {
    return {
        {"jumlah",              [](const vector<ll>& a){ ll s=0; for(ll x:a) s+=x; return s; }},
        {"jumlah mod 2",        [](const vector<ll>& a){ ll s=0; for(ll x:a) s+=x; return ((s%2)+2)%2; }},
        {"jumlah mod 3",        [](const vector<ll>& a){ ll s=0; for(ll x:a) s+=x; return ((s%3)+3)%3; }},
        {"XOR seluruhnya",      [](const vector<ll>& a){ ll s=0; for(ll x:a) s^=x; return s; }},
        {"banyak elemen ganjil",[](const vector<ll>& a){ ll c=0; for(ll x:a) c+=((x%2)+2)%2; return c; }},
        {"banyak elemen ganjil mod 2",
                                [](const vector<ll>& a){ ll c=0; for(ll x:a) c+=((x%2)+2)%2; return c%2; }},
        {"maksimum",            [](const vector<ll>& a){ return *max_element(a.begin(), a.end()); }},
        {"ukuran",              [](const vector<ll>& a){ return (ll)a.size(); }},
    };
}

// ─── 3. INVARIAN KLASIK: PARITAS PERMUTASI ────────────────
// Setiap PENUKARAN dua elemen membalik paritas permutasi.
// Karena itu paritas menentukan apakah suatu susunan bisa
// dicapai dengan jumlah penukaran GENAP.
// Ini dasar dari soal "15-puzzle" dan sejenisnya.

int paritasPermutasi(vector<int> p) {
    int n = p.size(), tukar = 0;
    vector<bool> lihat(n, false);
    for (int i = 0; i < n; i++) {
        if (lihat[i]) continue;
        int panjang = 0, j = i;
        while (!lihat[j]) { lihat[j] = true; j = p[j]; panjang++; }
        tukar += panjang - 1;                 // siklus panjang L butuh L-1 tukar
    }
    return tukar % 2;
}

// ─── 4. INVARIAN KLASIK: PEWARNAAN PAPAN CATUR ────────────
// Bidak yang selalu berpindah ke warna berlawanan tidak akan
// pernah kembali ke warna semula dalam langkah GENAP.
// Dipakai untuk membuktikan penutupan papan dengan domino
// mustahil ketika jumlah kedua warna tidak sama.

bool bisaDitutupDomino(int n, int m, const vector<pair<int,int>>& lubang) {
    if (((ll)n * m - (ll)lubang.size()) % 2 != 0) return false;   // paritas ukuran
    int putih = 0, hitam = 0;
    set<pair<int,int>> hilang(lubang.begin(), lubang.end());
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (hilang.count({i, j})) continue;
            ((i + j) % 2 == 0 ? putih : hitam)++;
        }
    return putih == hitam;                    // syarat PERLU (belum tentu cukup)
}

// ─── 5. MONOVARIAN: MEMBUKTIKAN PROSES BERHENTI ───────────
// Kalau ada besaran bilangan bulat non-negatif yang selalu
// TURUN setiap langkah, proses pasti berhenti — dan nilai
// awalnya adalah batas atas jumlah langkah.
//
// Contoh: pada setiap langkah, ambil dua bilangan a > b dan
// ganti a dengan a - b. Monovariannya adalah JUMLAH seluruh
// bilangan: ia selalu turun minimal 1.

ll langkahSampaiBerhenti(vector<ll> a) {
    ll langkah = 0;
    while (true) {
        sort(a.begin(), a.end());
        if (a[0] == a.back()) break;          // semua sama, berhenti
        // ganti terbesar dengan (terbesar - terkecil)
        a.back() -= a[0];
        langkah++;
        if (langkah > 100000) return -1;      // penjaga
    }
    return langkah;
}

// ─── 6. JEBAKAN ───────────────────────────────────────────
//
//  a) Invarian membuktikan MUSTAHIL, tetapi TIDAK membuktikan
//     mungkin. Kalau invariannya cocok, kamu masih harus
//     memberikan konstruksi (Day 81).
//
//  b) Lupa memeriksa paritas sebelum mencari konstruksi.
//     Paritas murah dan sering menyelesaikan separuh kasus.
//
//  c) Menyangka pewarnaan papan catur adalah syarat CUKUP.
//     Ia hanya syarat PERLU: papan bisa punya jumlah warna
//     sama tetapi tetap tidak bisa ditutup domino.
//
//  d) Monovarian yang bisa bernilai negatif tidak membuktikan
//     apa-apa. Ia harus terbatas di bawah.
//
//  e) Operator % di C++ bisa memberi sisa NEGATIF. Selalu
//     tulis ((x % m) + m) % m.

// ─── MAIN: demo pencari invarian ──────────────────────────

int main() {
    FASTIO;
    mt19937 rng(82);

    cout << "=== Operasi A: hapus dua elemen x,y; masukkan |x - y| ===\n";
    {
        // Ini teka-teki klasik: apa paritas bilangan yang TERSISA di akhir?
        auto op = [](vector<ll>& a, mt19937& r) {
            if (a.size() < 2) return;
            int i = r() % a.size();
            int j = r() % a.size();
            if (i == j) return;
            if (i > j) swap(i, j);
            ll x = a[i], y = a[j];
            a.erase(a.begin() + j);
            a.erase(a.begin() + i);
            a.push_back(llabs(x - y));
        };
        cariInvarian({3, 5, 7, 11}, op, kandidatBaku(), 2000, rng);
        cout << "  -> |x - y| berparitas SAMA dengan x + y, sehingga jumlah\n"
             << "     berubah dengan kelipatan 2: paritas jumlah INVARIAN.\n"
             << "     Akibatnya bilangan terakhir yang tersisa selalu\n"
             << "     berparitas sama dengan jumlah awal.\n";
    }

    cout << "\n=== Operasi B: pilih satu elemen, tambah 2 ===\n";
    {
        auto op = [](vector<ll>& a, mt19937& r) {
            if (a.empty()) return;
            a[r() % a.size()] += 2;
        };
        cariInvarian({1, 2, 3, 4}, op, kandidatBaku(), 2000, rng);
        cout << "  -> tiap elemen mempertahankan paritasnya sendiri,\n"
             << "     sehingga banyak elemen ganjil tidak berubah\n";
    }

    cout << "\n=== Paritas permutasi ===\n";
    cout << "  identitas [0,1,2,3]     : " << paritasPermutasi({0,1,2,3}) << " (genap)\n";
    cout << "  satu tukar [1,0,2,3]    : " << paritasPermutasi({1,0,2,3}) << " (ganjil)\n";
    cout << "  dua tukar  [1,0,3,2]    : " << paritasPermutasi({1,0,3,2}) << " (genap)\n";

    cout << "\n=== Pewarnaan papan catur (domino) ===\n";
    cout << "  papan 8x8 utuh                 : " << bisaDitutupDomino(8, 8, {}) << " (bisa)\n";
    cout << "  8x8 tanpa dua sudut berlawanan : "
         << bisaDitutupDomino(8, 8, {{0,0},{7,7}}) << " (mustahil: kedua sudut sewarna)\n";
    cout << "  8x8 tanpa dua sudut bersebelahan: "
         << bisaDitutupDomino(8, 8, {{0,0},{0,7}}) << " (lolos syarat perlu)\n";

    cout << "\n=== Monovarian ===\n";
    cout << "  {12, 18} langkah sampai berhenti : " << langkahSampaiBerhenti({12, 18}) << '\n';
    cout << "  {6, 10, 15}                      : " << langkahSampaiBerhenti({6, 10, 15}) << '\n';
    cout << "  -> jumlah selalu turun -> proses PASTI berhenti\n";

    return 0;
}
